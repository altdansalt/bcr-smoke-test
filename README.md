# bcr-smoke-test

A smoke test for Bazel remote caches and remote build execution: one repository that
builds and tests the **most common configurations of the most popular rulesets and
toolchains in the [Bazel Central Registry](https://registry.bazel.build/)**.

```sh
git clone https://github.com/<org>/bcr-smoke-test
cd bcr-smoke-test
bazel build //...
bazel test //...
```

If both commands succeed against your remote cache / RBE service, that service very
probably works with most of the Bazel rules in the wild: C/C++, Java/Kotlin, Python, Go,
Rust, JavaScript/TypeScript, protobuf/gRPC, shell, packaging, foreign (CMake/autotools)
builds, and the common Starlark tooling. Every package contains real code that is
compiled and executed, not just `build_test`s.

Point it at your service the usual way, for example:

```sh
bazel test //... --remote_cache=grpcs://cache.example.com
bazel test //... --remote_executor=grpcs://rbe.example.com --platforms=//platforms:rbe   # etc.
```

(`user.bazelrc` is `.gitignore`d and imported by `.bazelrc`, so you can keep those flags there.)

## How the modules were chosen

Modules are ranked by **direct dependents in the BCR**: the number of *other* modules whose
latest (non-yanked) version declares a non-dev `bazel_dep` on them, `boost.*` excluded because
its ~150 sub-modules would swamp the ranking. The script is `tools/bcr_dependents.py` and the
snapshot (BCR `main` on 2026-09-18) is `docs/bcr_direct_dependents.csv`. The repo covers the top
50 plus a handful of very common modules just below the cut. Each module is pinned at the latest
version in the BCR at snapshot time, with the exceptions noted in the table.

<!-- table:start -->
| # | module | direct dependents | version here | exercised in | note |
|--:|---|--:|---|---|---|
| 1 | `rules_cc` | 769 | 0.2.25 | `apple/`, `cc/` |  |
| 2 | `platforms` | 606 | 1.1.0 | `apple/`, `cc/` |  |
| 3 | `bazel_skylib` | 561 | 1.9.2 | `apple/`, `js/` |  |
| 4 | `rules_license` | 184 | 1.0.0 |  |  |
| 5 | `rules_python` | 155 | 2.3.3 | `python/` |  |
| 6 | `protobuf` | 129 | 36.2 | `go/`, `python/` |  |
| 7 | `rules_shell` | 121 | 0.8.0 | `rust/` |  |
| 8 | `rules_go` | 93 | 0.63.0 | `go/` |  |
| 9 | `zlib` | 86 | 1.3.2 | `cc/` |  |
| 10 | `googletest` | 77 | 1.18.0.bcr.1 | `cc/` |  |
| 11 | `gazelle` | 73 | 0.54.0 | `go/` |  |
| 12 | `rules_java` | 68 | 9.9.0 |  |  |
| 13 | `bazel_features` | 66 | 1.51.0 |  |  |
| 14 | `bazel_lib` | 65 | 3.7.2 |  |  |
| 15 | `rules_proto` | 62 | 7.1.0 |  |  |
| 16 | `abseil-cpp` | 57 | 20260817.0 | `cc/` |  |
| 17 | `package_metadata` | 49 | 0.0.13 |  |  |
| 18 | `apple_support` | 48 | 2.8.4 |  |  |
| 19 | `rules_cc_autoconf` | 45 | 0.24.0 |  |  |
| 20 | `aspect_bazel_lib` | 44 | 2.22.5 |  |  |
| 21 | `rules_rust` | 36 | 0.74.0 | `rust/` |  |
| 22 | `openssl` | 35 | 4.0.1.bcr.0 | `cc/` |  |
| 23 | `rules_swift` | 33 | 4.1.0 | `apple/` |  |
| 24 | `rules_jvm_external` | 32 | 7.1 |  |  |
| 25 | `aspect_rules_js` | 31 | 3.4.1 | `js/` |  |
| 26 | `eigen` | 29 | 5.0.1.bcr.2 | `cc/` |  |
| 27 | `boringssl` | 28 | 0.20260813.0 | `cc/` |  |
| 28 | `grpc` | 28 | 1.84.0 |  |  |
| 29 | `buildifier_prebuilt` | 27 | 10.0.1 |  |  |
| 30 | `re2` | 26 | 2025-11-05.bcr.1 | `cc/` |  |
| 31 | `zstd` | 24 | 1.5.7.bcr.2 | `cc/` |  |
| 32 | `cmake_configure_file` | 23 | 0.1.7 | `cc/` |  |
| 33 | `rules_nodejs` | 23 | 6.7.5 |  |  |
| 34 | `rules_pkg` | 22 | 1.3.0 |  |  |
| 35 | `fmt` | 20 | 12.2.0 | `cc/` |  |
| 36 | `googleapis` | 18 | 0.0.0-20260825-d10ac924 |  |  |
| 37 | `curl` | 17 | 8.21.0.bcr.2 | `cc/` |  |
| 38 | `google_benchmark` | 17 | 1.9.5 | `cc/` |  |
| 39 | `nlohmann_json` | 17 | 3.12.0.bcr.2 | `cc/` |  |
| 40 | `rules_apple` | 17 | 5.1.0 | `apple/` |  |
| 41 | `lz4` | 16 | 1.10.0.bcr.1 | `cc/` |  |
| 42 | `aspect_tools_telemetry` | 15 | 0.5.2 |  | pulled in by the Aspect rulesets; telemetry disabled via `--repo_env=DO_NOT_TRACK=1` |
| 43 | `boost.filesystem` | 15 | — |  | not included |
| 44 | `libx11` | 15 | — |  | left out: X11 client library, only meaningful with a display server |
| 45 | `pybind11_bazel` | 14 | 3.0.1 | `python/` |  |
| 46 | `rules_proto_grpc` | 14 | — |  | left out: its dependents are almost entirely its own per-language plugin modules |
| 47 | `freetype` | 13 | 2.14.1.bcr.1 | `cc/` |  |
| 48 | `toolchain_utils` | 13 | 1.3.0 |  | 1.3.2 is broken in the BCR (references a missing package); pinned to 1.3.0 |
| 49 | `glib` | 12 | — |  | left out: large GNOME base library, rarely a build-system concern |
| 50 | `libpng` | 12 | 1.6.58 | `cc/` |  |
| 51 | `rules_android` | 12 | — |  | left out: needs a locally installed Android SDK (`ANDROID_HOME`), not hermetic |
| 52 | `rules_autoconf` | 12 | — |  | exercised transitively via `rules_cc_autoconf` |
| 53 | `rules_foreign_cc` | 12 | 0.16.0 |  |  |
| 54 | `rules_gazebo` | 12 | — |  | left out: Gazebo-specific |
| 55 | `tinyxml2` | 12 | 11.0.0 | `cc/` |  |
| 56 | `boost.algorithm` | 11 | — |  | not included |
| 57 | `gflags` | 11 | 2.3.1 | `cc/` |  |
| 58 | `gz-utils` | 11 | — |  | not included |
| 59 | `rules_rs` | 11 | — |  | not included |
| 60 | `bzip2` | 10 | 1.0.8.bcr.4 | `cc/` |  |
<!-- table:end -->

## Layout

One directory per ruleset family. Each has a `README.md` saying which rules it exercises and
attributing any code adapted from the rulesets' own examples.

| directory | modules |
|---|---|
| `cc/` | rules_cc, googletest, cmake_configure_file and 23 C/C++ library modules |
| `proto/` | protobuf, rules_proto, grpc, googleapis, googleapis-cc |
| `jvm/` | rules_java, rules_jvm_external, rules_kotlin, grpc-java |
| `python/` | rules_python, pybind11_bazel, abseil-py, py_proto_library |
| `go/` | rules_go, gazelle, go_proto_library |
| `rust/` | rules_rust (hermetic toolchain, crate_universe) |
| `js/` | aspect_rules_js, rules_nodejs, aspect_rules_ts |
| `shell/`, `skylib/`, `platforms/`, `license/`, `stardoc/`, `buildifier/` | rules_shell, bazel_skylib, bazel_features, platforms, rules_license, package_metadata, stardoc, buildifier_prebuilt |
| `contrib/` | aspect_bazel_lib, bazel_lib, tar.bzl, jq.bzl, yq.bzl, toml.bzl, rules_multitool, ape, toolchain_utils, download_utils, gawk, m4 |
| `foreign_cc/`, `pkg/`, `perl/`, `fuzzing/`, `cc_autoconf/` | rules_foreign_cc, rules_pkg, rules_perl, rules_fuzzing, rules_cc_autoconf |
| `apple/` | apple_support, rules_swift, rules_apple (macOS hosts only; skipped elsewhere) |

## Platform notes

- Verified on Linux x86_64 (Bazel 9.2.0, see `.bazelversion`). CI also runs macOS.
- macOS-only rules are gated with `target_compatible_with = ["@platforms//os:macos"]`, so
  `bazel build //...` skips them on Linux (`--skip_incompatible_explicit_targets` is set).
  `rules_apple` bundling rules additionally need a macOS *execution* platform and are only
  reached through a macOS-only `build_test`.
- Network is used only by repository rules and module extensions (fetching toolchains and
  npm/pip/Maven/crate dependencies from committed lockfiles). No build action or test needs
  network, which is what makes this usable for RBE.
- `protobuf` ≥ 33.4 downloads a prebuilt `protoc` by default; `--config=source_protoc` builds
  it from source instead if you want the heavier C++ path exercised.

## Known gotchas at these versions

<!-- gotchas:start -->
<!-- gotchas:end -->

## Contributing

Add a directory per ruleset, keep sources tiny, make every target part of `//...`, and attribute
copied code. Regenerate the module table with `tools/gen_readme_table.py`.

## License

Apache-2.0 (see `LICENSE`). Third-party snippets keep their original licenses, noted where used.
