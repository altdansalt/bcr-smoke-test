# rust — rules_rust smoke test

Exercises **rules_rust 0.74.0** with a hermetic Rust 1.98.0 toolchain
(`rust.toolchain(edition = "2021", versions = ["1.98.0"])`, registered via
`@rust_toolchains//:all`) and third-party crates via **crate_universe**.

| Target | Rule | What it checks |
|---|---|---|
| `:bcr_smoke_rust` | `rust_library` | library using `anyhow`, `serde` (derive), `serde_json` from `@crates//:...` |
| `:hello` | `rust_binary` | binary linking the library |
| `:unit_test` | `rust_test(crate = ...)` | inline `#[cfg(test)]` tests in `src/lib.rs` |
| `:integration_test` | `rust_test(srcs = ...)` | separate integration-test crate in `tests/` |
| `:bcr_smoke_rust_doc` | `rust_doc` | rustdoc generation (build only) |
| `:hello_test` | `sh_test` | runs the binary and checks its JSON output |

## crate_universe

`MODULE.bazel` uses `crate.from_cargo(...)` from
`@rules_rust//crate_universe:extensions.bzl` (plural; the singular
`extension.bzl` is deprecated) with:

- `manifests = ["//rust:Cargo.toml"]` — a real, tiny Cargo package mirroring the Bazel targets
- `cargo_lockfile = "//rust:Cargo.lock"` — committed Cargo lockfile
- `lockfile = "//rust:Cargo.Bazel.lock"` — committed crate_universe lockfile, so a clean
  clone builds without running cargo (no `CARGO_BAZEL_REPIN`)

To repin after changing `Cargo.toml` (needs network, run once):

```sh
CARGO_BAZEL_REPIN=1 bazel build //rust/...
```

Both lockfiles are (re)written in place. An empty `Cargo.lock` / `Cargo.Bazel.lock` is
enough to bootstrap the first repin (no host cargo needed; crate_universe uses the
hermetic toolchain's cargo).

All code here was written for this repo (no copied upstream files).
