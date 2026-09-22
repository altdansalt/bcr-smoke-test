# cc_autoconf — rules_cc_autoconf 0.24.0

| Target | Rule |
| --- | --- |
| `//cc_autoconf:package` | `package_info` (PACKAGE_NAME / PACKAGE_VERSION) |
| `//cc_autoconf:autoconf` | `autoconf` with `macros.AC_CHECK_FUNCS` + `macros.AC_CHECK_HEADERS` run against the configured `cc_toolchain` |
| `//cc_autoconf:config` | `autoconf_hdr` rendering `config.h` from `config.h.in` |
| `//cc_autoconf:config_test` | `cc_test` that includes the generated header and fails at compile time if a `HAVE_*` macro is wrong |

The checks run as Bazel actions (`CcAutoconfCheck`), no shell `configure` involved.
The generated header lives in `bazel-bin/cc_autoconf/config.h`, so it is included
as `"cc_autoconf/config.h"`.

## Attribution

Slimmed from `examples/simple` in <https://github.com/periareon/rules_cc_autoconf>
(MIT): `BUILD.bazel`, `config.h.in` and `config_test.c` are adapted from
`examples/simple/{BUILD.bazel,config.h.in,simple_test.c}`.
