# jvm

Smoke tests for the JVM rulesets in the BCR. Layout follows the common
`java/<pkg>` / `javatests/<pkg>` monorepo convention so `java_test` can infer
its `test_class` from the path.

| Module | Rules exercised | Where |
| --- | --- | --- |
| rules_java 9.9.0 | `java_library`, `java_binary`, `java_test` (JUnit 4 via the built-in `BazelTestRunner`) | `java/com/example/greeter`, `javatests/com/example/greeter` |
| rules_jvm_external 7.1 | `maven.install` module extension with a pinned lockfile (`//:maven_install.json`), `@maven//:...` targets (guava, gson, junit, hamcrest) | `MODULE.bazel` (`# --- jvm ---` block), all BUILD files |
| protobuf 36.2 | `proto_library`, `java_proto_library`, `java_lite_proto_library`, `@protobuf//:protobuf_java`, `@protobuf//:protobuf_javalite` | `BUILD.bazel`, `greeter.proto` |
| grpc-java 1.82.0 | `java_grpc_library`, `@grpc-java//{api,stub,inprocess,testing}`; in-process server + unary call in `GreeterServiceTest` | `BUILD.bazel`, `java/...`, `javatests/...` |
| rules_kotlin 2.4.20 | `kt_jvm_library` (depending on a `java_library`), `kt_jvm_binary`, `kt_jvm_test` | `kotlin/` |

## Notes

- The workspace needs a JDK for `java_binary`/`java_test`/`kt_jvm_*` targets. To stay
  hermetic (no host JDK) the repo uses `--java_runtime_version=remotejdk_21`
  (rules_java's remote JDK); Bazel's default is `local_jdk`.
- The `maven` namespace is shared: protobuf and grpc-java also call
  `maven.install(name = "maven", ...)`, so their artifacts are resolved together with
  ours and appear in `maven_install.json`. `known_contributing_modules` silences the
  corresponding warning. Regenerate the lockfile with `REPIN=1 bazel run @maven//:pin`.
- `java_lite_proto_library` generates classes with the same names as
  `java_proto_library`, so the lite test depends only on the lite flavour.
- rules_kotlin registers its default toolchain from its own `MODULE.bazel`; nothing
  needs to be registered by the root module.

## Attribution

- `javatests/com/example/greeter/GreeterServiceTest.java` is adapted from
  [grpc-java](https://github.com/grpc/grpc-java)
  `examples/src/test/java/io/grpc/examples/helloworld/HelloWorldServerTest.java`
  (Apache License 2.0).
- Everything else is original, minimal code written for this repo.
