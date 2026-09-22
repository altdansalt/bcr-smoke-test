#include "fmt/format.h"
#include "gtest/gtest.h"
TEST(Fmt, Format) { EXPECT_EQ(fmt::format("{}-{:02d}", "bcr", 7), "bcr-07"); }
