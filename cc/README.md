# cc: rules_cc and the popular C/C++ library modules

Exercises:

- `rules_cc` 0.2.x: `cc_library` (with `defines`/`local_defines` chosen by `select()` over
  `@platforms//os` and `@platforms//cpu`), `cc_binary`, `cc_test`, `cc_shared_library` +
  `dynamic_deps`.
- `googletest`: `@googletest//:gtest_main` in every test.
- `cmake_configure_file`: generates `config.h` from `config.h.in` (CMake `configure_file()` semantics).
- One small gtest per library module, each calling the library's API so the whole thing must
  compile and link: zlib, zstd, re2, lz4, bzip2, xz, nlohmann_json, rapidjson, brotli, snappy,
  mbedtls, c-ares, openssl, curl, boringssl, abseil-cpp, google_benchmark, eigen, fmt, gflags,
  tinyxml2, libpng, freetype. (openssl and boringssl are linked into *different* tests since
  they export the same symbols.)

All sources here are original to this repo.
