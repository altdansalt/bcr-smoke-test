# skylib — bazel_skylib 1.9.2 + bazel_features 1.51.0

Rules exercised (`bazel_skylib`): `write_file`, `copy_file`, `expand_template`, `diff_test`,
`native_binary`, `native_test` (wrapping `//cc:hello`), `run_binary`, `select_file`, `build_test`,
`bool_flag` / `string_flag` (`rules/common_settings.bzl`) with `config_setting(flag_values)`,
`selects.config_setting_group`, `bzl_library`, and `lib/unittest.bzl` (`unittest.suite`,
`analysistest`). `greeting.bzl` is a tiny custom rule/macro built on `lib/paths.bzl`,
`lib/dicts.bzl` and `lib/selects.bzl` (`selects.with_or`); `greeting_test.bzl` unit- and
analysis-tests it.

`bazel_features`: `features.bzl` defines a rule that branches on
`bazel_features.rules.write_action_has_mnemonic` at analysis time; `features_test.bzl` asserts
the feature value types with `unittest` and the chosen action mnemonic with `analysistest`.

Try the flags: `bazel build //skylib:flags_txt --//skylib:lang=fr` (or `--//skylib:shout`).

Attribution: the unittest/analysistest pattern is copied and slimmed from
https://github.com/bazelbuild/bazel-skylib/blob/main/tests/unittest_tests.bzl (Apache-2.0);
everything else is written for this repo.
