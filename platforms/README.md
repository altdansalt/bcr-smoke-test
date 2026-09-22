# platforms — platforms 1.1.0

Exercises: our own `constraint_setting` / `constraint_value`s, a `platform()` inheriting
`@platforms//host` plus our constraint (`bazel build ... --platforms=//platforms:host_rbe`),
`config_setting`s on `@platforms//os:*` and `@platforms//cpu:*` consumed by `select()`
(`platform_select_test` diffs two independently selected results), and a target + test with
`target_compatible_with = ["@platforms//os:macos"]` that `bazel build //...` / `bazel test //...`
must *skip* on Linux (`--skip_incompatible_explicit_targets` is in `.bazelrc`).

All code written for this repo.
