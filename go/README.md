# go — rules_go + gazelle smoke test

Exercises the most common Go setup of a Bazel monorepo under bzlmod.

| Module | Version | What is exercised |
| --- | --- | --- |
| `rules_go` | 0.63.0 | `go_sdk.download(version = "1.26.8")` (hermetic SDK), `go_library`, `go_binary`, `go_test` (one internal `package greeter` test file and one external `package greeter_test` test file in the same `go_test`), `go_proto_library` with the default `@rules_go//proto:go_proto` compiler (`protoc-gen-go` built from `@org_golang_google_protobuf`). |
| `gazelle` | 0.54.0 | `go_deps.from_file(go_mod = "//:go.mod")` module extension resolving `github.com/google/uuid`, `github.com/stretchr/testify` and `google.golang.org/protobuf` from the committed `go.mod`/`go.sum`; the `gazelle(name = "gazelle")` runner target (`//go:gazelle`) with a `# gazelle:prefix` directive. All `BUILD.bazel` files below `go/` are exactly what `bazel run //go:gazelle` generates (`size = "small"` was added to the tests by hand; gazelle preserves it). |
| `protobuf` | 36.2 | `proto_library` (`@protobuf//bazel:proto_library.bzl`, the load gazelle emits) for `greetingpb/greeting.proto`. |

## Targets

- `//go:gazelle` — gazelle runner (built by `bazel build //go/...`; regenerate with `bazel run //go:gazelle`).
- `//go/greeter:greeter` (`go_library`, depends on `@com_github_google_uuid//:uuid`) and `//go/greeter:greeter_test` (`go_test`; internal + external test files, consumes the generated proto and `@org_golang_google_protobuf//proto`, asserts with `@com_github_stretchr_testify//require`).
- `//go/greetingpb:greetingpb_proto`, `:greetingpb_go_proto`, `:greetingpb` (`proto_library` -> `go_proto_library` -> `go_library`, the standard gazelle triple).
- `//go/cmd/hello:hello` (`go_binary`, embeds `:hello_lib`) and `//go/cmd/hello:hello_test`.

## Layout notes

- `go.mod` / `go.sum` live at the repository root (module `github.com/bcr-smoke-test/bcr-smoke-test`), the standard gazelle/go_deps setup; the Go code lives under `go/` with `# gazelle:prefix github.com/bcr-smoke-test/bcr-smoke-test/go` in `go/BUILD.bazel`. `//:go.mod` resolves because the repo root has a (empty) `BUILD.bazel`.
- The `gazelle` target passes `extra_args = ["go"]` so it only walks this directory (gazelle resolves directory arguments relative to the workspace root).
- Regenerate `go.sum` with the hermetic SDK: `bazel run @rules_go//go -- mod tidy -e` from the repo root (`-e` because `go/greetingpb` only exists as Bazel-generated code, so the Go tool cannot resolve that import; the `go` target also runs `bazel mod tidy` afterwards, which may reformat `MODULE.bazel`). An empty `go.sum` must exist before the first run, otherwise the `go_deps` extension fails to read it.

All code in this directory was written for this repository (no code copied from other projects).
