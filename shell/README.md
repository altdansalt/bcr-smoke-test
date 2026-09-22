# shell — rules_shell 0.8.0

Rules exercised: `sh_library`, `sh_binary`, `sh_test` (loaded from `@rules_shell//shell:*.bzl`).
`greet_test` runs the `sh_binary` via `$(rootpath ...)` and the C++ binary `//cc:hello` via
`rlocation("$(rlocationpath ...)")` from `@bazel_tools//tools/bash/runfiles` -- the canonical
runfiles pattern that has to work under remote execution.

Attribution: the "runfiles.bash initialization v3" boilerplate in `greet.sh` / `greet_test.sh` is
from https://github.com/bazelbuild/bazel/blob/master/tools/bash/runfiles/runfiles.bash (Apache-2.0).
