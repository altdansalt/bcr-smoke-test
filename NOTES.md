# Notes (lab notebook)

## 2026-09-22 Skymeld symlink-forest hiccup
After `bazel run //buildifier` reformatted many BUILD files and I edited ~30 more, the next `bazel test //...`
failed with `execvp(external/bazel_tools/tools/test/test-setup.sh): No such file`. java.log showed
`IncrementalPackageRoots.plantSingleSymlinkForPackage` → `FileNotFoundException execroot/_main/external/<repo>`
(Bazel 9.2 incremental symlink planting under Skymeld). It persisted across `bazel clean`, went away after one
run with `--noexperimental_merged_skyframe_analysis_execution`, and could not be reproduced afterwards from
`bazel clean` (with or without `.bazelignore`). Treating it as a transient Bazel server-state bug; no repo change.
