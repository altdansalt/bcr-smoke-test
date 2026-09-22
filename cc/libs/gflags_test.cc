#include "gflags/gflags.h"
#include "gtest/gtest.h"
DEFINE_int32(smoke_level, 3, "a flag");
TEST(Gflags, DefaultAndSet) {
  EXPECT_EQ(FLAGS_smoke_level, 3);
  gflags::SetCommandLineOption("smoke_level", "5");
  EXPECT_EQ(FLAGS_smoke_level, 5);
}
