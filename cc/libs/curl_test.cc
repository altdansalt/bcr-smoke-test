#include "curl/curl.h"
#include "gtest/gtest.h"
TEST(Curl, VersionAndHandle) {
  ASSERT_EQ(curl_global_init(CURL_GLOBAL_DEFAULT), CURLE_OK);
  EXPECT_NE(curl_version(), nullptr);
  CURL* h = curl_easy_init();
  ASSERT_NE(h, nullptr);
  EXPECT_EQ(curl_easy_setopt(h, CURLOPT_URL, "https://example.invalid/"), CURLE_OK);
  curl_easy_cleanup(h);
  curl_global_cleanup();
}
