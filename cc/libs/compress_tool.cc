// Tiny CLI combining abseil flags, zlib and zstd.
#include <cstdio>
#include <string>
#include <vector>
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "zlib.h"
#include "zstd.h"
ABSL_FLAG(std::string, algo, "zstd", "zlib or zstd");
ABSL_FLAG(int, size, 4096, "input size in bytes");
int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  std::string in(absl::GetFlag(FLAGS_size), 'k');
  size_t n = 0;
  if (absl::GetFlag(FLAGS_algo) == "zlib") {
    std::vector<Bytef> out(compressBound(in.size()));
    uLongf len = out.size();
    compress(out.data(), &len, reinterpret_cast<const Bytef*>(in.data()), in.size());
    n = len;
  } else {
    std::vector<char> out(ZSTD_compressBound(in.size()));
    n = ZSTD_compress(out.data(), out.size(), in.data(), in.size(), 1);
  }
  std::printf("%s: %zu -> %zu bytes\n", absl::GetFlag(FLAGS_algo).c_str(), in.size(), n);
  return 0;
}
