#include <string>
#include "gtest/gtest.h"
#include "snappy.h"
TEST(Snappy, RoundTrip) {
  std::string in(7000, 's'), out, back;
  snappy::Compress(in.data(), in.size(), &out);
  ASSERT_TRUE(snappy::Uncompress(out.data(), out.size(), &back));
  EXPECT_EQ(back, in);
}
