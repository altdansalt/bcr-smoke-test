#include "ares.h"
#include "gtest/gtest.h"
TEST(CAres, InitAndVersion) {
  ASSERT_EQ(ares_library_init(ARES_LIB_INIT_ALL), ARES_SUCCESS);
  int v = 0;
  EXPECT_NE(ares_version(&v), nullptr);
  EXPECT_GT(v, 0);
  ares_channel channel = nullptr;
  EXPECT_EQ(ares_init(&channel), ARES_SUCCESS);
  ares_destroy(channel);
  ares_library_cleanup();
}
