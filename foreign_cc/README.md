# foreign_cc — rules_foreign_cc 0.16.0

Builds three tiny in-repo non-Bazel projects with the hermetic toolchains that
rules_foreign_cc registers by default (prebuilt cmake 3.31 and ninja 1.13,
GNU make 4.4.1 built from the BCR `make` module) and links the resulting static
libraries into `cc_test`s.

| Target | Rule | Project |
| --- | --- | --- |
| `//foreign_cc:greet` | `cmake` (Unix Makefiles generator) | `cmake_greet/` (CMakeLists.txt + greet.c) |
| `//foreign_cc:greet_ninja` | `cmake` with `generate_args = ["-GNinja"]` | same |
| `//foreign_cc:add` | `configure_make` (`configure_in_place = True`) | `configure_add/` (hand-written `configure` + Makefile.in) |
| `//foreign_cc:mul` | `make` | `make_mul/` (plain Makefile honouring `PREFIX`) |
| `//foreign_cc:{greet,greet_ninja,add,mul}_test` | `cc_test` | consume the libraries above |

Each source tree is exposed through a `filegroup(name = "all_srcs", srcs = glob(["**"]))`
as in the rules_foreign_cc docs. No `MODULE.bazel` extension usage is needed: the
module's own `MODULE.bazel` registers `@rules_foreign_cc_toolchains//:all`
(see `docs/src/bzlmod_examples.md`, "Defaults only").

## Attribution

- `cmake_greet/CMakeLists.txt` and the `cmake()` / `cc_test` layout are slimmed from
  rules_foreign_cc `examples/cmake_hello_world_lib/static` (Apache-2.0,
  <https://github.com/bazel-contrib/rules_foreign_cc>), which itself credits
  <https://github.com/Akagi201/learning-cmake>.
- `configure_add/configure` follows the pattern of
  `examples/configure_modify_input_source/simple_lib/configure` (Apache-2.0).
- `make_mul/Makefile` is slimmed from `examples/make_simple/code/Makefile` (Apache-2.0).
- All C sources are original.
