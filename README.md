# bcr-smoke-test

A smoke test for Bazel remote caches and remote build execution: one repository that
builds and tests the **most common configurations of the most popular rulesets and
toolchains in the [Bazel Central Registry](https://registry.bazel.build/)**.

```sh
git clone https://github.com/altdansalt/bcr-smoke-test
cd bcr-smoke-test
bazel build //...               # fast tier: every ruleset, ~2 min cold on 8 cores incl. downloads
bazel test //...
bazel test //... --config=full  # everything, incl. gRPC C++, OpenSSL, crate_universe, Kotlin, ... (~16 min cold)
```

If both commands succeed against your remote cache / RBE service, that service very
probably works with most of the Bazel rules in the wild: C/C++, Java/Kotlin, Python, Go,
Rust, JavaScript/TypeScript, protobuf/gRPC, shell, packaging, foreign (CMake/autotools)
builds, and the common Starlark tooling. Every package contains real code that is
compiled and executed, not just `build_test`s.

## Two tiers

Targets tagged `heavy` are skipped by default (`.bazelrc` sets `--build_tag_filters=-heavy`
and `--test_tag_filters=-heavy`); `--config=full` clears the filters. The default tier still
exercises every ruleset and toolchain; what it leaves out is the *expensive library builds*:

| skipped by default | why |
|---|---|
| gRPC C++ (`proto/grpc`, `proto/googleapis`), `cc_proto_library` (`proto/`) | libgrpc++ and libprotobuf/libprotoc are ~10 min of the cold build |
| `py_proto_library` (`python/`), `cc_fuzz_test` (`fuzzing/`) | each pulls libprotobuf and abseil in through code-generation plugins |
| grpc-java (`jvm/`) | its protoc plugin links libprotoc |
| rules_kotlin (`jvm/kotlin`) | compiles the rules_kotlin builder |
| crate_universe (`rust/`; a dependency-free crate stays in the fast tier) | compiles the `cargo-bazel` generator |
| `configure_make` / `make` / CMake with Unix Makefiles (`foreign_cc/`; the Ninja variant stays) | GNU make is built from source |
| OpenSSL, BoringSSL, curl, mbedtls, c-ares, freetype, abseil, re2 (`cc/libs`) | minutes each |
| gawk, m4 (`contrib/gnu`) | built from source via rules_cc_autoconf |

Measured cold on this repo's development VM (8 cores, fresh caches, including all downloads):

| | fetch | build | test | total |
|---|---|---|---|---|
| default tier | 39 s | 86 s | 2 s | 127 s (~2 min) |
| `--config=full` | 81 s | 14.4 min | 4 s | ~16 min |

Point it at your service the usual way, for example:

```sh
bazel test //... --remote_cache=grpcs://cache.example.com
bazel test //... --remote_executor=grpcs://rbe.example.com --extra_execution_platforms=... --extra_toolchains=...
```

(`user.bazelrc` is `.gitignore`d and imported by `.bazelrc`, so you can keep those flags there.)
See "Validating a remote cache or RBE service" below for a procedure that actually proves the
service was used, and "What your workers need" for the execution-platform contract.

## How the modules were chosen

Modules are ranked by **direct dependents in the BCR**: the number of *other* modules whose
latest (non-yanked) version declares a non-dev `bazel_dep` on them, `boost.*` excluded because
its ~150 sub-modules would swamp the ranking. The script is `tools/bcr_dependents.py` and the
snapshot (BCR `main` at commit `c5543c07`, 2026-09-18) is `docs/bcr_direct_dependents.csv`. The
repo covers the top 50 plus a handful of very common modules just below the cut. Each `bazel_dep`
requests the latest version in the BCR at snapshot time (Bazel's version selection may pick a
higher one if another module asks for it; `bazel mod graph --depth=1` shows what was resolved),
with the exceptions noted in the table. The "exercised in" column is derived from textual
`@module` references in BUILD/.bzl files (`tools/gen_readme_table.py`); the per-directory READMEs
say exactly which rules are built and which tests execute.

<!-- table:start -->
| # | module | direct dependents | version here | exercised in | note |
|--:|---|--:|---|---|---|
| 1 | `rules_cc` | 769 | 0.2.25 | `apple/`, `cc/`, `cc_autoconf/`, `foreign_cc/`, `fuzzing/`, `proto/` |  |
| 2 | `platforms` | 606 | 1.1.0 | `apple/`, `cc/`, `platforms/`, `skylib/` |  |
| 3 | `bazel_skylib` | 561 | 1.9.2 | `apple/`, `contrib/`, `js/`, `licensing/`, `pkg/`, `platforms/`, `skylib/`, `stardoc/` |  |
| 4 | `rules_license` | 184 | 1.0.0 | `licensing/` |  |
| 5 | `rules_python` | 155 | 2.3.3 | `python/` |  |
| 6 | `protobuf` | 129 | 36.2 | `go/`, `jvm/`, `proto/`, `python/` |  |
| 7 | `rules_shell` | 121 | 0.8.0 | `cc/`, `contrib/`, `licensing/`, `perl/`, `pkg/`, `rust/`, `shell/` |  |
| 8 | `rules_go` | 93 | 0.63.0 | `go/` |  |
| 9 | `zlib` | 86 | 1.3.2 | `cc/` |  |
| 10 | `googletest` | 77 | 1.18.0.bcr.1 | `cc/`, `fuzzing/`, `proto/` |  |
| 11 | `gazelle` | 73 | 0.54.0 | `go/` |  |
| 12 | `rules_java` | 68 | 9.9.0 | `jvm/` |  |
| 13 | `bazel_features` | 66 | 1.51.0 | `skylib/` |  |
| 14 | `bazel_lib` | 65 | 3.7.2 | `contrib/` |  |
| 15 | `rules_proto` | 62 | 7.1.0 | `proto/` |  |
| 16 | `abseil-cpp` | 57 | 20260817.0 | `cc/` |  |
| 17 | `package_metadata` | 49 | 0.0.13 | `licensing/` |  |
| 18 | `apple_support` | 48 | 2.8.4 |  |  |
| 19 | `rules_cc_autoconf` | 45 | 0.24.0 | `cc_autoconf/` |  |
| 20 | `aspect_bazel_lib` | 44 | 2.22.5 | `contrib/` |  |
| 21 | `rules_rust` | 36 | 0.74.0 | `rust/` |  |
| 22 | `openssl` | 35 | 4.0.1.bcr.0 | `cc/` |  |
| 23 | `rules_swift` | 33 | 4.1.0 | `apple/` |  |
| 24 | `rules_jvm_external` | 32 | 7.1 |  |  |
| 25 | `aspect_rules_js` | 31 | 3.4.1 | `js/` |  |
| 26 | `eigen` | 29 | 5.0.1.bcr.2 | `cc/` |  |
| 27 | `boringssl` | 28 | 0.20260813.0 | `cc/` |  |
| 28 | `grpc` | 28 | 1.84.0 | `proto/` |  |
| 29 | `buildifier_prebuilt` | 27 | 10.0.1 | `buildifier/` |  |
| 30 | `re2` | 26 | 2025-11-05.bcr.1 | `cc/` |  |
| 31 | `zstd` | 24 | 1.5.7.bcr.2 | `cc/` |  |
| 32 | `cmake_configure_file` | 23 | 0.1.7 | `cc/` |  |
| 33 | `rules_nodejs` | 23 | 6.7.5 |  |  |
| 34 | `rules_pkg` | 22 | 1.3.0 | `pkg/` |  |
| 35 | `fmt` | 20 | 12.2.0 | `cc/` |  |
| 36 | `googleapis` | 18 | 0.0.0-20260825-d10ac924 | `proto/` |  |
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
| 48 | `toolchain_utils` | 13 | 1.3.0 | `contrib/` | 1.3.2 is broken in the BCR (references a missing package); pinned to 1.3.0 |
| 49 | `glib` | 12 | — |  | left out: large GNOME base library, rarely a build-system concern |
| 50 | `libpng` | 12 | 1.6.58 | `cc/` |  |
| 51 | `rules_android` | 12 | — |  | left out: needs a locally installed Android SDK (`ANDROID_HOME`), not hermetic |
| 52 | `rules_autoconf` | 12 | — |  | exercised transitively via `rules_cc_autoconf` |
| 53 | `rules_foreign_cc` | 12 | 0.16.0 | `foreign_cc/` |  |
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
| `third_party/` | upstream license texts for the few adapted example files |
| `proto/` | protobuf, rules_proto, grpc, googleapis, googleapis-cc |
| `jvm/` | rules_java, rules_jvm_external, rules_kotlin, grpc-java |
| `python/` | rules_python, pybind11_bazel, abseil-py, py_proto_library |
| `go/` | rules_go (incl. cgo), gazelle, go_proto_library |
| `rust/` | rules_rust (hermetic toolchain, crate_universe) |
| `js/` | aspect_rules_js, rules_nodejs, aspect_rules_ts |
| `shell/`, `skylib/`, `platforms/`, `licensing/`, `stardoc/`, `buildifier/` | rules_shell, bazel_skylib, bazel_features, platforms, rules_license, package_metadata, stardoc, buildifier_prebuilt |
| `contrib/` | aspect_bazel_lib, bazel_lib, tar.bzl, jq.bzl, yq.bzl, toml.bzl, rules_multitool, ape, toolchain_utils, download_utils, gawk, m4 |
| `foreign_cc/`, `pkg/`, `perl/`, `fuzzing/`, `cc_autoconf/` | rules_foreign_cc, rules_pkg, rules_perl, rules_fuzzing, rules_cc_autoconf |
| `apple/` | apple_support, rules_swift, rules_apple (macOS hosts only; skipped elsewhere) |

## Toolchain variants

The defaults mirror what most projects run: the C/C++ compiler is whatever rules_cc auto-detects on
the host (gcc or clang), and everything else is the ruleset's hermetic toolchain. Each config below
swaps one toolchain for the other common real-world choice; they combine freely with `--config=full`.

| config | what changes |
|---|---|
| `--config=llvm` | hermetic LLVM from `toolchains_llvm` (latest bundled 19.x/20.x) instead of the host C/C++ compiler |
| `--config=host_clang` / `--config=host_gcc` | force rules_cc's auto-configuration onto the host `clang` / `gcc` |
| `--config=local_jdk` | the JDK on `PATH`/`JAVA_HOME` instead of the downloaded remote JDK |
| `--config=local_python` | the host `python3` (introspected by rules_python's local toolchain support) instead of the downloaded CPython; the pip lock is for 3.12, so pip-dependent tests need a 3.12 host interpreter |

Not offered: rules_go's `go_sdk.host()` (discouraged upstream, breaks on distro Go upgrades), and the
Node/Rust/Kotlin/Perl rules, which have no supported host-toolchain mode.

## What your workers need

The repo deliberately uses the rulesets' *default* toolchains, which is what most dependents do.
That means a remote executor's worker image must provide what a typical developer machine does:

- a C/C++ compiler and binutils (`gcc`/`clang`, `ar`, `ld`) picked up by `rules_cc`'s
  auto-configured toolchain — or bring your own hermetic toolchain via `--extra_toolchains`
  and `--extra_execution_platforms` / `--host_platform`, as you would for any C++ RBE setup;
- `bash` and POSIX utilities (`coreutils`, `grep`, `sed`, `tr`, `find`): Bazel's test runner and
  the shell-based rulesets (rules_shell, rules_foreign_cc, bazel_skylib's `run_binary` tools)
  assume them;
- the ability to run downloaded binaries (prebuilt `protoc`, Node.js, Go, Rust, JDK, cmake, ninja,
  jq, buildifier ...) — glibc-based Linux x86_64/arm64 or macOS.

Everything else (Python, Node, JDK, Go, Rust, Perl, cmake/ninja, protoc, buildifier, jq, ...) is
fetched by module extensions and shipped to workers as action inputs. Apple targets need macOS
workers with Xcode.

## Validating a remote cache or RBE service

Green `bazel test //...` alone only proves the build works *somewhere*. To prove the remote service
did the work:

```sh
# 1. Populate the remote cache from a fresh output base, no disk cache.
bazel --output_base=/tmp/ob1 test //... --disk_cache= --remote_cache=grpcs://cache.example.com \
    --execution_log_compact_file=/tmp/exec1.log
# 2. Rebuild from another fresh output base and check that actions were cache hits.
bazel --output_base=/tmp/ob2 test //... --disk_cache= --remote_cache=grpcs://cache.example.com \
    --execution_log_compact_file=/tmp/exec2.log
#    The console summary should report "N remote cache hit"; the execution log lists per-action
#    `cacheHit`/`runner` details (see https://bazel.build/remote/cache-remote).
# 3. For remote execution, forbid local fallback so every action must run remotely.
bazel --output_base=/tmp/ob3 test //... --disk_cache= --remote_executor=grpcs://rbe.example.com \
    --remote_local_fallback=false --noremote_accept_cached --nocache_test_results \
    --remote_download_minimal
```

`--noremote_accept_cached` forces real execution; `--remote_download_minimal` additionally checks
that nothing in the build depends on outputs being materialized locally.

## Platform notes

- Verified on Linux x86_64 (Bazel 9.2.0, see `.bazelversion`). CI also runs macOS.
- macOS-only rules are gated with `target_compatible_with = ["@platforms//os:macos"]`; wildcard
  patterns such as `//...` skip incompatible targets automatically on Linux.
  `rules_apple` bundling rules additionally need a macOS *execution* platform and are only
  reached through a macOS-only `build_test`.
- Network is used only by repository rules and module extensions (fetching toolchains and
  npm/pip/Maven/crate dependencies from committed lockfiles). No build action or test needs
  network, which is what makes this usable for RBE.
- `protobuf` ≥ 33.4 downloads a prebuilt `protoc` by default; `--config=source_protoc` builds
  it from source instead if you want the heavier C++ path exercised.

## Known gotchas at these versions

<!-- gotchas:start -->
- **rules_jvm_external**: protobuf and grpc-java both `maven.install` into the default `maven`
  namespace, so the root `maven_install.json` also pins their artifacts (`known_contributing_modules`
  lists them). Bump either module, then `REPIN=1 bazel run @maven//:pin`.
- **rules_java**: Bazel defaults to the host JDK; `.bazelrc` sets `--java_runtime_version=remotejdk_21`
  so `java_test`/`kt_jvm_*` work without a local JDK.
- **rules_rust**: load crate_universe from `@rules_rust//crate_universe:extensions.bzl` (plural). The
  deprecated singular file is one extension shared with protobuf 36.2's lockfile-less usage, which
  fails under rules_rust 0.74. A committed `Cargo.Bazel.lock` is what keeps a clean clone from
  needing `cargo` to re-resolve at fetch time.
- **rules_python**: `compile_pip_requirements` is not used because its generated `.test` target needs
  network; the lock is produced with `uv pip compile --generate-hashes` (see `python/README.md`).
- **aspect_rules_js** with pnpm 10 requires a lifecycle allow-list (`allowBuilds: {}` in
  `pnpm-workspace.yaml`); **aspect_rules_ts** 3.x needs an explicit `transpiler = "tsc"`.
- **gazelle**: `go_deps` needs an existing `go.sum`; run tidy through the hermetic SDK as
  `bazel run @rules_go//go -- mod tidy -e` (the `-e` tolerates Bazel-generated proto packages).
- **rules_foreign_cc** 0.16 registers prebuilt cmake and ninja itself, but GNU make is built from
  source via the BCR `make` module (a few thousand actions on first build).
- **rules_license** 1.0.0: `write_licenses_info` crashes at analysis time if any transitive dep has
  no license metadata, so the report target here only covers the `licensing/` package.
- **rules_apple** bundling rules need a macOS execution platform and fail toolchain resolution on
  Linux *before* `target_compatible_with` is checked; they are `manual` and reached via a
  macOS-only `build_test`.
- **toolchain_utils** 1.3.2's BCR entry references a package that does not exist; pinned to 1.3.0.
- **googleapis**: the `envoy_api` version pulled in by grpc 1.84 imports a repo the latest googleapis
  no longer generates, so `envoy_api` is bumped explicitly.
- **toolchains_protoc** is obsolete: protobuf ≥ 33.4 has `--@protobuf//bazel/flags:prefer_prebuilt_protoc`
  (default on). `--config=source_protoc` here turns it off.
- **Bazel 9.x Skymeld**: a main repo with case-clashing top-level names (here `LICENSE` and
  `licensing/`) makes lazily planted `execroot/_main/external/*` symlinks fail with ENOENT, so
  `bazel test //...` fails on `external/...` paths.
  `.bazelrc` disables Skymeld (`--noexperimental_merged_skyframe_analysis_execution`); analysis in
  `docs/bazel-skymeld-symlink-race.md`, fix + failing tests on a fork branch: <https://github.com/altdansalt/bazel/tree/skymeld-external-dir-not-created-with-case-clash>.
- Aspect rulesets phone home by default; `.bazelrc` sets `--repo_env=DO_NOT_TRACK=1`.
<!-- gotchas:end -->

## Contributing

Add a directory per ruleset, keep sources tiny, make every target part of `//...`, and attribute
copied code. Regenerate the module table with `tools/gen_readme_table.py`.

## License

Apache-2.0 (see `LICENSE`). Third-party snippets keep their original licenses, noted where used.
