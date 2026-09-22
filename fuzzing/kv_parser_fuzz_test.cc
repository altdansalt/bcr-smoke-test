// Fuzz target skeleton from rules_fuzzing examples/bzlmod/cc_fuzz_test.cc
// (https://github.com/bazel-contrib/rules_fuzzing, Apache-2.0).
#include <cstddef>
#include <cstdint>
#include <string_view>

#include "fuzzing/kv_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  auto parsed = smoke::ParseKeyValues(
      std::string_view(reinterpret_cast<const char *>(data), size));
  (void)parsed;
  return 0;
}
