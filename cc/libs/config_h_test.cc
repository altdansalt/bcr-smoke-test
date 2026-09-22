#include "cc/libs/config.h"
#include "gtest/gtest.h"
TEST(CmakeConfigureFile, Substitutions) {
  EXPECT_EQ(SMOKE_VERSION_MAJOR, 1);
  EXPECT_EQ(SMOKE_VERSION_MINOR, 2);
  EXPECT_STREQ(SMOKE_VERSION_STRING, "1.2");
#ifndef HAVE_ZLIB
  FAIL() << "HAVE_ZLIB should be defined";
#endif
#ifdef HAVE_NOTHING
  FAIL() << "HAVE_NOTHING should be undefined";
#endif
}
