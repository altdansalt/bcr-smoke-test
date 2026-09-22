#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "lz4.h"
#include "lz4frame.h"
TEST(Lz4, RoundTrip) {
  std::string in(5000, 'q');
  std::vector<char> out(LZ4_compressBound(in.size()));
  int n = LZ4_compress_default(in.data(), out.data(), in.size(), out.size());
  ASSERT_GT(n, 0);
  std::string back(in.size(), '\0');
  ASSERT_EQ(LZ4_decompress_safe(out.data(), &back[0], n, back.size()), (int)in.size());
  EXPECT_EQ(back, in);
  EXPECT_EQ(LZ4F_getVersion(), (unsigned)LZ4F_VERSION);
}
