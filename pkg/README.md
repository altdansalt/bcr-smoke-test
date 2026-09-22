# pkg — rules_pkg 1.3.0

Exercises the mapping rules and the archive rules most rules_pkg users reach for:

| Target | Rule |
| --- | --- |
| `//pkg:bin_files`, `//pkg:doc_files` | `pkg_files` with `prefix`, `strip_prefix.from_pkg()` and `pkg_attributes(mode = ...)`; includes the compiled `//cc:hello` binary |
| `//pkg:hi_link` | `pkg_mklink` (`bin/hi -> hello`) |
| `//pkg:install_tree` | `pkg_filegroup` with `prefix = "usr"` |
| `//pkg:smoke_tar` | `pkg_tar` (`package_dir = "/opt/smoke"`, `extension = "tar.gz"`) |
| `//pkg:smoke_zip` | `pkg_zip` |
| `//pkg:smoke_deb` | `pkg_deb` wrapping the tar (pure-python, no host `dpkg` needed) |
| `//pkg:smoke_tar_contents_test` | rules_pkg's own `verify_archive_test` (py_test on the hermetic rules_python toolchain) |
| `//pkg:smoke_tar_test` | `sh_test` (rules_shell) running `tar tvf` and asserting paths, the 0755 mode and the symlink |
| `//pkg:archives_build_test` | bazel_skylib `build_test` for the zip and deb |

All sources are original. Note that rules_python prints a deprecation notice about
implicit `__init__.py` creation for `verify_archive_test`; it is harmless.
