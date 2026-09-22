#include <cstring>
#include "gtest/gtest.h"
#include "mbedtls/sha256.h"
#include "mbedtls/version.h"
TEST(Mbedtls, Sha256) {
  unsigned char out[32];
  const char* msg = "abc";
  ASSERT_EQ(mbedtls_sha256(reinterpret_cast<const unsigned char*>(msg), std::strlen(msg), out, 0), 0);
  EXPECT_EQ(out[0], 0xba);
  EXPECT_EQ(out[31], 0xad);
  EXPECT_GT(mbedtls_version_get_number(), 0u);
}
