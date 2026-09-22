#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "zlib.h"
TEST(Zlib, RoundTrip) {
  std::string in(10000, 'a');
  std::vector<Bytef> out(compressBound(in.size()));
  uLongf out_len = out.size();
  ASSERT_EQ(compress(out.data(), &out_len, reinterpret_cast<const Bytef*>(in.data()), in.size()), Z_OK);
  EXPECT_LT(out_len, in.size());
  std::string back(in.size(), '\0');
  uLongf back_len = back.size();
  ASSERT_EQ(uncompress(reinterpret_cast<Bytef*>(&back[0]), &back_len, out.data(), out_len), Z_OK);
  EXPECT_EQ(back, in);
  EXPECT_STREQ(zlibVersion(), ZLIB_VERSION);
}
