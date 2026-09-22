# Bazel 9.x: Skymeld race wipes lazily planted `execroot/_main/external/*` symlinks

Found while building this repo (2026-09-22). Reproduced on Bazel 9.1.0, 9.2.0 and 9.3.0rc2 on Linux x86_64.
Worked around in `.bazelrc` with `common --noexperimental_merged_skyframe_analysis_execution`.

## Symptom

On a run where analysis and actions are (almost) entirely cached, `bazel test //...` fails with
actions or tests that cannot find files under `external/`, e.g.

```
src/main/tools/linux-sandbox-pid1.cc:584: "execvp(external/bazel_tools/tools/test/test-setup.sh, ...)": No such file or directory
```

or

```
Copying directory package [for tool] failed: Exec failed due to IOException:
.../execroot/_main/external/aspect_rules_ts++typescript+npm_typescript/package/LICENSE.txt (No such file or directory)
```

`execroot/_main/external/` is missing the symlink for that repository. `java.log` contains many
(tens to hundreds of) entries like:

```
com.google.devtools.build.lib.util.AbruptExitException: Failed to prepare the symlink forest:
  java.io.FileNotFoundException: [unix_jni.cc:297] .../execroot/_main/external/platforms (No such file or directory)
	at com.google.devtools.build.lib.skyframe.IncrementalPackageRoots.throwAbruptExitException(IncrementalPackageRoots.java:339)
	at com.google.devtools.build.lib.skyframe.IncrementalPackageRoots.plantSingleSymlinkForPackage(IncrementalPackageRoots.java:332)
	at com.google.devtools.build.lib.skyframe.IncrementalPackageRoots.lambda$recursiveRegisterAndPlantMissingSymlinks$0(IncrementalPackageRoots.java:267)
Caused by: java.io.FileNotFoundException: ... execroot/_main/external/platforms (No such file or directory)
	at com.google.devtools.build.lib.unix.NativePosixFiles.symlink(Native Method)
	at com.google.devtools.build.lib.buildtool.SymlinkForest.plantSingleSymlinkForExternalRepo(SymlinkForest.java:475)
```

The build does not stop at those exceptions; it carries on with a partially planted forest.

## Reproduction (this repository)

```sh
git clone <this repo> && cd bcr-smoke-test
sed -i '/noexperimental_merged_skyframe_analysis_execution/d' .bazelrc   # remove the workaround
bazel test //...                      # cold: usually passes (analysis is slow enough)
bazel test //... --nocache_test_results   # warm: fails, java.log full of "Failed to prepare the symlink forest"
```

The window is timing-dependent. A warm analysis cache makes it near-certain; we also hit it on a
freshly started server with a populated `--disk_cache` (Bazel 9.1.0, 9.2.0, 9.3.0rc2), and never with
Skymeld disabled (4/4 clean runs). The mechanism below is a hypothesis from reading the source that
matches the log evidence; it has not been confirmed with a debugger.

## Mechanism (reading Bazel 9.2.0 sources)

`ExecutionTool.prepareForExecution` does, in this order:

1. `IncrementalPackageRoots.createAndRegisterToEventBus(...)` — subscribes to
   `TopLevelTargetReadyForSymlinkPlanting` events, and
2. `incrementalPackageRoots.eagerlyPlantSymlinksToSingleSourceRoot()` →
   `SymlinkForest.eagerlyPlantSymlinkForestSinglePackagePath`, whose first statement is
   `deleteTreesBelowNotPrefixed(execroot, "bazel-")`, which deletes `execroot/_main/external/`.

Under Skymeld, analysis runs concurrently with this. When top-level targets are already analyzed
(warm server, or very fast analysis), their events arrive between steps 1 and 2 and
`lazilyPlantSymlinks` starts planting `execroot/_main/external/<repo>` links on the 200-thread
planting pool. Step 2 then deletes the `external` directory under them:

- planters still in flight fail with `FileNotFoundException` (the log lines above), and
- links that were already planted are silently deleted, but stay in `lazilyPlantedSymlinks`, so
  they are never re-planted (`plantSingleSymlinkForExternalRepo` also only re-creates the
  `external` directory when that set is empty).

Actions that later need those repos (test-setup.sh from `bazel_tools`, tool directories, …)
fail with ENOENT. The non-Skymeld path plants the whole forest up front, before execution, and is
not affected.

A fix would be to finish the eager planting (the deletion in particular) before registering the
subscriber, or to hold `stateLock` around the delete/plant sequence.

## Not the same as

`7c0e2110` "Fix Skymeld external repository package root loss on warm server" (bazelbuild/bazel#30800,
2026-09-03) is about `PackageRoots` lookups for header discovery, not about the symlinks on disk.
