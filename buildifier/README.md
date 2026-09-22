# buildifier — buildifier_prebuilt 10.0.1

Exercises: `buildifier(name = "buildifier")` (`bazel run //buildifier` formats + lint-fixes the
whole repo), `buildifier(name = "check", mode = "diff", lint_mode = "warn")`
(`bazel run //buildifier:check`), and `buildifier_test` which lints the listed BUILD/.bzl files
hermetically (no `no_sandbox`, so it also works under remote execution). Add new packages' BUILD
files to `STARLARK_FILES`; they must be visible (package `default_visibility` public or
`exports_files(["BUILD.bazel"])`).

All code written for this repo.
