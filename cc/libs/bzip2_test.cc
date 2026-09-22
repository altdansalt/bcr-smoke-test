#include <string>
#include <vector>
#include "bzlib.h"
#include "gtest/gtest.h"
TEST(Bzip2, RoundTrip) {
  std::string in(8000, 'b');
  std::vector<char> out(in.size() + 1000);
  unsigned out_len = out.size();
  ASSERT_EQ(BZ2_bzBuffToBuffCompress(out.data(), &out_len, &in[0], in.size(), 9, 0, 30), BZ_OK);
  std::string back(in.size(), '\0');
  unsigned back_len = back.size();
  ASSERT_EQ(BZ2_bzBuffToBuffDecompress(&back[0], &back_len, out.data(), out_len, 0, 0), BZ_OK);
  EXPECT_EQ(back, in);
}
