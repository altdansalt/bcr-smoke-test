#include <cstring>
#include "gtest/gtest.h"
#include "openssl/sha.h"
#include "openssl/ssl.h"
TEST(BoringSsl, Sha256AndSslCtx) {
  unsigned char out[SHA256_DIGEST_LENGTH];
  const char* msg = "abc";
  SHA256(reinterpret_cast<const unsigned char*>(msg), std::strlen(msg), out);
  EXPECT_EQ(out[0], 0xba);
  SSL_CTX* ctx = SSL_CTX_new(TLS_method());
  ASSERT_NE(ctx, nullptr);
  SSL_CTX_free(ctx);
}
