# contrib: bazel-lib and friends

Smoke coverage for the "contrib tooling" modules in the BCR. One subpackage per module; every
subpackage builds something and diff-tests (or otherwise asserts on) the produced output so the
tool actually runs. All downloads happen in module extensions / repo rules declared in the
`# --- contrib ---` block of `MODULE.bazel`; builds and tests are offline.

| Package | Module (version) | Rules / API exercised |
| --- | --- | --- |
| `//contrib/aspect_bazel_lib` | `aspect_bazel_lib` 2.22.5 | `copy_file`, `copy_to_directory`, `directory_path`, `expand_template`, `write_source_files`, `run_binary`, `params_file`, `diff_test`, plus the `jq`, `yq`, `tar` re-exports |
| `//contrib/bazel_lib` | `bazel_lib` 3.7.2 | `copy_directory`, `copy_to_directory`, `copy_to_bin`, `expand_template` (inline template), `write_source_file`, `assert_contains`, `assert_outputs`, `assert_directory_contains`, `bats_test` |
| `//contrib/tar` | `tar.bzl` 0.10.9 | `tar` + `mutate()`, `mtree_spec`, `mtree_mutate`, `compress = "gzip"`; listings via `@bsd_tar_toolchains//:resolved_toolchain` (`$(BSDTAR_BIN)`) |
| `//contrib/jq` | `jq.bzl` 0.6.2 | `jq` (`--slurp` merge), `jq_test`, `$(JQ_BIN)` in a `genrule` via `@jq_toolchains//:resolved_toolchain` |
| `//contrib/yq` | `yq.bzl` 0.4.0 | `yq` (delete key; YAML to JSON with `-o=json`), `yq_test` |
| `//contrib/toml` | `toml.bzl` 0.4.1 | `toml.decode` / `toml.encode` (pure Starlark, evaluated at load time in `config.bzl`) |
| `//contrib/multitool` | `rules_multitool` 1.11.1 | `multitool.hub(lockfile = ...)` with `jq` 1.8.1 for linux/macos x x86_64/arm64; `@multitool//tools/jq` as a `genrule` tool and in an `sh_test` |
| `//contrib/ape` | `ape` 1.1.1-alpha.1 | `ape_toolchain` registering `@ape//ape/toolchain/info:jq`, `toolchain_resolved` + `$(JQ)` Make variable, `toolchain_test`, `@ape//ape:jq` run via `native_test` |
| `//contrib/toolchain_utils` | `toolchain_utils` 1.3.0 | `toolchain_info`, `toolchain` per exec platform (`@toolchain_utils//toolchain/constraint/{cpu,os}:*`), `toolchain_resolved`, `toolchain_test` with `stdout` diff, `$(SHFMT)` in a `genrule` |
| `//contrib/download_utils` | `download_utils` 1.2.3 | `download_file` with `integrity` (a LICENSE text file, and the four `shfmt` binaries used above) |
| `//contrib/gnu` | `gawk` 5.4.0.bcr.1, `m4` 1.4.21.bcr.4 | `@gawk//:gawk` and `@m4//:m4` (built from source with rules_cc) as `genrule` tools |

Both `aspect_bazel_lib` (legacy name) and `bazel_lib` (its successor) are used from the same
workspace, which mirrors what most real repos look like mid-migration.

## Notes

- `aspect_bazel_lib`, `bazel_lib`, `jq.bzl`, `yq.bzl`, `tar.bzl` and `rules_multitool` register
  their own toolchains from their `MODULE.bazel`; the root module only needs `use_repo` of the
  hub repos when a `genrule` wants the `$(JQ_BIN)` / `$(BSDTAR_BIN)` Make variables.
- `jq_test` and `diff_test` are byte-for-byte comparisons after the filter; jq preserves key order,
  so "semantically equal" inputs must also have the same key order.
- `yq.bzl` does not infer the output format from the `outs` extension: pass `-o=yaml` / `-o=json`.
- `write_file`/`expand_template` outputs have no trailing newline unless the content list ends with `""`.
- The `toolchain_utils` + `download_utils` pattern (download one binary per execution platform,
  wrap in `toolchain_info`, register with `exec_compatible_with`, expose via `toolchain_resolved`)
  is copied from the toolchain_utils README.
- The APE (Cosmopolitan) `jq` reports `jq-` for `--version` (no version baked in), so the ape
  `toolchain_test` only asserts non-empty stdout; the genrule diff test checks real jq output.
- `toolchain_utils` is pinned to 1.3.0 (1.3.2 in the BCR references a package that does not exist).

## Attribution

- BUILD patterns for `aspect_bazel_lib` / `bazel_lib` follow the docs and `lib/tests` of
  https://github.com/bazel-contrib/bazel-lib (Apache-2.0).
- `contrib/tar` follows `tar/tests/BUILD` and `examples/migrate-rules_pkg/BUILD` of
  https://github.com/bazel-contrib/tar.bzl (Apache-2.0).
- `contrib/jq`, `contrib/yq` follow the docs/tests of https://github.com/bazel-contrib/jq.bzl and
  https://github.com/bazel-contrib/yq.bzl (Apache-2.0).
- `contrib/toml/config.bzl` adapts the README example of https://github.com/jvolkman/toml.bzl (Apache-2.0).
- `contrib/multitool/multitool.lock.json` follows the lockfile schema of
  https://github.com/theoremlp/rules_multitool (Apache-2.0); binaries are jq 1.8.1 GitHub releases.
- `contrib/ape/BUILD.bazel` is slimmed from `e2e/toolchain/curl/BUILD.bazel` of
  https://gitlab.arm.com/bazel/ape (MIT); `contrib/toolchain_utils` follows the README of
  https://gitlab.arm.com/bazel/toolchain_utils (MIT). shfmt binaries are v3.11.0 GitHub releases
  of https://github.com/mvdan/sh (BSD-3-Clause).
- Everything else is original, trivially small input/expected data.
