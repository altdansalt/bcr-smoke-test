# python — rules_python, protobuf (py_proto_library), pybind11_bazel, abseil-py

Modules exercised (versions from the root `MODULE.bazel`):

| Module | Rules / features |
|---|---|
| `rules_python` 2.3.3 | hermetic CPython 3.12 toolchain via the `python` extension (`python.defaults` + `python.toolchain`); `py_library`, `py_binary`, `py_test`; `pip.parse` with a committed hash-pinned `requirements_lock.txt` (`six`, `tomli`, `pyyaml`) consumed through `requirement()` |
| `protobuf` 36.2 | `proto_library` + `py_proto_library` (`person.proto` -> `person_pb2`), used from a `py_test` |
| `pybind11_bazel` 3.0.1 | `pybind_extension` C++ module (`fastmath.cc`) imported and called from a `py_test` |
| `abseil-py` 2.4.0 | `absltest`-based `py_test` using `absl.flags` |

Targets: `:greeter` (py_library), `:main` (py_binary), `:greeter_test`, `:absl_test`,
`:person_proto`, `:person_py_proto`, `:person_test`, `:fastmath` (pybind_extension), `:fastmath_test`.

## Lock file

`requirements_lock.txt` is generated from `requirements.in` with uv (hashes for all
platforms, so the lock is usable on Linux/macOS/Windows):

```
uv pip compile --generate-hashes --universal --python-version 3.12 python/requirements.in -o python/requirements_lock.txt
```

`compile_pip_requirements` is intentionally not used: its generated `.test` target
runs pip-compile and needs network access at test time.

## Attribution

- `fastmath.cc` is adapted from `examples/basic/basic.cpp` in
  https://github.com/pybind/pybind11_bazel (BSD-3-Clause).
- Everything else was written for this repo.
