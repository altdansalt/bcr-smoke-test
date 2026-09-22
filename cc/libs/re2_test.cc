#include <string>
#include "gtest/gtest.h"
#include "re2/re2.h"
TEST(Re2, Matches) {
  int year = 0;
  EXPECT_TRUE(RE2::FullMatch("bazel-2026", "bazel-(\\d+)", &year));
  EXPECT_EQ(year, 2026);
  EXPECT_FALSE(RE2::FullMatch("nope", "\\d+"));
}
