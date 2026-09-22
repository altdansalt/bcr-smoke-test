#include <cstring>
#include "ares.h"
#include "gtest/gtest.h"
// Uses only pure API (no ares_init(), which reads the host's resolver configuration).
TEST(CAres, LibraryInitAndAddressParsing) {
  ASSERT_EQ(ares_library_init(ARES_LIB_INIT_ALL), ARES_SUCCESS);
  int v = 0;
  EXPECT_NE(ares_version(&v), nullptr);
  EXPECT_GT(v, 0);
  unsigned char buf[16];
  ASSERT_EQ(ares_inet_pton(AF_INET, "10.1.2.3", buf), 1);
  EXPECT_EQ(buf[3], 3);
  char out[64];
  EXPECT_STREQ(ares_inet_ntop(AF_INET, buf, out, sizeof(out)), "10.1.2.3");
  EXPECT_STREQ(ares_strerror(ARES_SUCCESS), "Successful completion");
  ares_library_cleanup();
}
