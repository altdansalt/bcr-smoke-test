# proto — protobuf / rules_proto / grpc / googleapis

Smoke tests for the protobuf-family modules. protobuf 36.2 downloads a prebuilt `protoc`
by default (`--@protobuf//bazel/flags:prefer_prebuilt_protoc`, see `--config=source_protoc` in
`.bazelrc` to compile it instead); the language plugins (`protoc-gen-cpp`, `grpc_cpp_plugin`) and
the runtimes are built from source.

| Package | Module(s) | Rules exercised |
|---|---|---|
| `//proto` | protobuf 36.2, rules_proto 7.1.0 | `proto_library`, `cc_proto_library` (from `@protobuf//bazel:*.bzl`); cross-repo dep on `@protobuf//:timestamp_proto`; one `proto_library` loaded via the legacy `@rules_proto//proto:defs.bzl` shim; `cc_test` that serializes/parses. |
| `//proto/grpc` | grpc 1.84.0 | `cc_grpc_library` (`grpc_only = True`) over `proto_library` + `cc_proto_library`; `cc_test` that starts an insecure gRPC server on `127.0.0.1:0` and makes one unary RPC. |
| `//proto/googleapis` | googleapis, googleapis-cc 1.1.5, googleapis-grpc-cc 1.0.0 (via grpc), googleapis-rules-registry 1.1.5 | `proto_library` depending on `@googleapis//google/rpc:status_proto` and `@googleapis//google/type:date_proto`; `cc_test` using `@googleapis//google/rpc:status_cc_proto` and `@googleapis//google/longrunning:longrunning_cc_grpc`. |

## Notes

- `rules_proto` 7.x is only a shim: `proto/defs.bzl` re-exports `proto_library` from `@protobuf`.
- `cc_grpc_library` in grpc 1.84 still defaults to `grpc_only = False` (the legacy mode that generates its own
  `proto_library`/`cc_proto_library`); the modern convention is `grpc_only = True` with the `proto_library` in
  `srcs` and the `cc_proto_library` in `deps`.
- googleapis with Bzlmod: language-specific targets live in `@googleapis` itself (e.g.
  `@googleapis//google/rpc:status_cc_proto`). They are real only when the matching flavor module
  (`googleapis-cc`, `googleapis-grpc-cc`, `googleapis-java`, ...) is a `bazel_dep`; the flavor registers
  the rule with `googleapis-rules-registry`, otherwise the target is a macro that `fail()`s with instructions.

## Attribution

- `proto/grpc/greeter.proto` is slimmed from
  https://github.com/grpc/grpc/blob/master/examples/protos/helloworld.proto (Apache-2.0).
- Everything else was written for this repo.
