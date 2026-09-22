# bcr-smoke-test — progress

## What's happening right now
Baseline works: `rules_cc` + 17 C/C++ library modules build and 18 tests pass on Bazel 9.2.0.
Parallel agents are now writing one package per language/ruleset family in separate clones
(jvm, python, go, rust, js, proto/grpc, starlark tooling, contrib tooling, native/pkg/perl).
Once they report back I merge, run `bazel build //...` and `bazel test //...`, then codex review.

## Plan
1. ~~MODULE.bazel with all top modules at their latest BCR versions; make `bazel mod deps` resolve.~~
2. One package per ruleset exercising its most common rules (copy-and-slim from upstream examples, attributed). **(in progress)**
3. `bazel build //...` and `bazel test //...` green on Linux x86_64 (macOS-only rulesets gated by `target_compatible_with`).
4. Codex review, README, publish public GitHub repo.

## Done
- Bazelisk installed (Bazel 9.2.0); MODULE.bazel resolves with ~80 direct modules.
- `cc/`: rules_cc + 23 C/C++ library modules, 25 tests green.
- `apple/`: rules_swift / rules_apple / apple_support targets, gated to macOS (skipped on Linux).
- Ranking recomputed from the BCR clone with `tools/bcr_dependents.py` (docs/bcr_direct_dependents.csv).
- GitHub Actions workflow (ubuntu + macos) drafted.

## Decisions / gotchas so far
- `toolchain_utils` pinned to 1.3.0: the BCR entry for 1.3.2 references a package (`toolchain/searator`) that does not exist.
- `envoy_api` bumped explicitly to 0.0.0-20260901: the version grpc 1.84 pulls in uses a googleapis extension repo that the latest googleapis no longer provides.
- protobuf 36.2's own crate_universe usage (no lockfile) fails under rules_rust 0.74 if evaluated; we load crate_universe from `extensions.bzl` so that extension is never evaluated.
- Aspect telemetry opted out via `--repo_env=DO_NOT_TRACK=1`.
