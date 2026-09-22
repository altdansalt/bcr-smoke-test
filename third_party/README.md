# Third-party notices

Small pieces of this repository are adapted ("copy-and-slim") from the example code of the
rulesets under test. Each adapted file names its source in a header comment and the package
`README.md` repeats it. This directory keeps the upstream license texts for those sources.

| adapted file(s) | upstream | license file |
|---|---|---|
| `python/fastmath.cc` | [pybind/pybind11_bazel](https://github.com/pybind/pybind11_bazel) `examples/basic/basic.cpp` | `licenses/pybind11_bazel.LICENSE` (BSD-3-Clause) |
| `cc_autoconf/BUILD.bazel`, `config.h.in`, `config_test.c` | [periareon/rules_cc_autoconf](https://github.com/periareon/rules_cc_autoconf) `examples/simple` | `licenses/rules_cc_autoconf.LICENSE` |
| `contrib/ape/BUILD.bazel` | [gitlab.arm.com/bazel/ape](https://gitlab.arm.com/bazel/ape) `e2e/toolchain/curl/BUILD.bazel` | `licenses/ape.LICENSE` |
| `contrib/toolchain_utils/*` (pattern from README) | [gitlab.arm.com/bazel/toolchain_utils](https://gitlab.arm.com/bazel/toolchain_utils) | `licenses/toolchain_utils.LICENSE` |
| `jvm/javatests/.../GreeterServiceTest.java` | [grpc/grpc-java](https://github.com/grpc/grpc-java) `examples/.../HelloWorldServerTest.java` | `licenses/grpc-java.LICENSE` (Apache-2.0) |
| `foreign_cc/cmake_greet/CMakeLists.txt`, `foreign_cc/make_mul/Makefile`, `foreign_cc/configure_add/configure` | [bazel-contrib/rules_foreign_cc](https://github.com/bazel-contrib/rules_foreign_cc) `examples/` | `licenses/rules_foreign_cc.LICENSE` (Apache-2.0) |
| `skylib/greeting_test.bzl` | [bazelbuild/bazel-skylib](https://github.com/bazelbuild/bazel-skylib) `tests/` | `licenses/bazel_skylib.LICENSE` (Apache-2.0) |
| `licensing/licenses_used.bzl` | [bazelbuild/rules_license](https://github.com/bazelbuild/rules_license) sample report | `licenses/rules_license.LICENSE` (Apache-2.0) |
| `fuzzing/kv_parser_fuzz_test.cc` (harness skeleton) | [bazel-contrib/rules_fuzzing](https://github.com/bazel-contrib/rules_fuzzing) `examples/bzlmod/cc_fuzz_test.cc` | `licenses/rules_fuzzing.LICENSE` (Apache-2.0) |
| `perl/greeter_test.t` (pattern) | [bazelbuild/rules_perl](https://github.com/bazelbuild/rules_perl) `examples/fibonacci/fibonacci_test.t` | `licenses/rules_perl.LICENSE` (Apache-2.0) |
| `proto/grpc/greeter.proto` | [grpc/grpc](https://github.com/grpc/grpc) `examples/protos/helloworld.proto` | `licenses/grpc.LICENSE` (Apache-2.0) |
| `contrib/toml/config.bzl` (example document) | [jvolkman/toml.bzl](https://github.com/jvolkman/toml.bzl) README | `licenses/toml.bzl.LICENSE` (Apache-2.0) |

Everything else in the repository is original and licensed under the top-level `LICENSE` (Apache-2.0).
The versions adapted from are the module versions in `MODULE.bazel` at the time of writing.
