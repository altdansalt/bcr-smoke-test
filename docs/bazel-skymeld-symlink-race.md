# Bazel 9.x Skymeld: `execroot/_main/external/` never created when the main repo has case-clashing top-level names

Found while building this repo (2026-09-22). Reproduced on Bazel 9.1.0, 9.2.0 and 9.3.0rc2 on Linux x86_64.
It was worked around with `common --noexperimental_merged_skyframe_analysis_execution`; the repo has
since renamed `license/` to `licensing/` (the clash also breaks `git checkout` on case-insensitive
filesystems), so the trigger is gone. To reproduce, `git mv licensing license` and fix up the labels.

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

## Mechanism (confirmed)

The trigger is a **case-insensitive name clash between two top-level entries of the main
repository**: this repo has a `LICENSE` file and a `license/` package. When such a clash exists,
`SymlinkForest.eagerlyPlantSymlinkForestSinglePackagePath` does not plant those entries eagerly;
`IncrementalPackageRoots` plants the *package* one lazily when a top-level target that uses it is
ready, and records the planted link in `lazilyPlantedSymlinks`.

That same set is passed to `SymlinkForest.plantSingleSymlinkForExternalRepo` as
`alreadyPlantedExternalRepoLinks`, and it is the only thing that decides whether
`execroot/_main/external/` gets created:

```java
if (alreadyPlantedExternalRepoLinks.isEmpty()) {
  execroot.getRelative("external").createDirectoryAndParents();
}
if (!alreadyPlantedExternalRepoLinks.add(execrootLink)) return Optional.empty();
execrootLink.createSymbolicLink(source);   // ENOENT if external/ was never created
```

So as soon as the main-repo `license` link has been recorded, every external-repo planter that
runs before some other planter happened to create `external/` sees a non-empty set, skips the
`mkdir`, and fails with `FileNotFoundException`. The planters run on a 200-thread pool per
event, so which ones fail is a race, but any event batch that contains `//license` (here:
`//buildifier:buildifier_test`, whose `srcs` include `//license:BUILD.bazel`) reliably loses some
links. Failed links stay in the set and are never retried, so later actions hit ENOENT.

Evidence:

- 5/5 runs of `bazel test //buildifier:buildifier_test --experimental_merged_skyframe_analysis_execution --nocache_test_results`
  fail with the clash present; 0/5 fail after `git mv LICENSE LICENSE.txt` (nothing else changed).
- The first occurrence in this repo's history coincides exactly with adding `//license:BUILD.bazel`
  to that test's `srcs`, and no agent workspace that lacked the `LICENSE` file ever hit it.
- A `--profile` confirms `prepareForExecution` (the eager wipe/plant) completes before any lazy
  planting, ruling out an earlier hypothesis of a delete/plant race.

Fix: keep main-repo lazily planted links and external-repo links in separate sets. A branch with
the fix, a unit test (`IncrementalPackageRootsTest`) and a shell integration test
(`skymeld_symlink_forest_test.sh`), both of which fail before the change and pass after it, is at
<https://github.com/altdansalt/bazel/tree/skymeld-external-dir-not-created-with-case-clash>. No pull request has been opened.

## Not the same as

`7c0e2110` "Fix Skymeld external repository package root loss on warm server" (bazelbuild/bazel#30800,
2026-09-03) is about `PackageRoots` lookups for header discovery, not about the symlinks on disk.
