#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "zstd.h"
TEST(Zstd, RoundTrip) {
  std::string in(10000, 'z');
  std::vector<char> out(ZSTD_compressBound(in.size()));
  size_t n = ZSTD_compress(out.data(), out.size(), in.data(), in.size(), 3);
  ASSERT_FALSE(ZSTD_isError(n));
  std::string back(in.size(), '\0');
  size_t m = ZSTD_decompress(&back[0], back.size(), out.data(), n);
  ASSERT_FALSE(ZSTD_isError(m));
  EXPECT_EQ(back, in);
}
