#include "cc/greeter.h"
#include "gtest/gtest.h"
TEST(Greeter, Greets) { EXPECT_EQ(bcr_smoke::Greet("x"), "Hello, x!"); }
TEST(Greeter, HostDescriptionIsSet) {
  EXPECT_NE(bcr_smoke::HostDescription().find('/'), std::string::npos);
  EXPECT_EQ(bcr_smoke::HostDescription().find("unset"), std::string::npos);
}
