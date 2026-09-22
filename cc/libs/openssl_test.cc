#include <cstring>
#include "gtest/gtest.h"
#include "openssl/crypto.h"
#include "openssl/sha.h"
TEST(OpenSsl, Sha256) {
  unsigned char out[SHA256_DIGEST_LENGTH];
  const char* msg = "abc";
  SHA256(reinterpret_cast<const unsigned char*>(msg), std::strlen(msg), out);
  EXPECT_EQ(out[0], 0xba);
  EXPECT_EQ(out[31], 0xad);
  EXPECT_NE(OpenSSL_version(OPENSSL_VERSION), nullptr);
}
