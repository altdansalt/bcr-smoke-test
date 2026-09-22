#include "gtest/gtest.h"
#include "nlohmann/json.hpp"
TEST(NlohmannJson, ParseAndDump) {
  auto j = nlohmann::json::parse(R"({"rules":["cc","java"],"n":2})");
  EXPECT_EQ(j["n"], 2);
  EXPECT_EQ(j["rules"][1], "java");
  EXPECT_EQ(j.dump(), R"({"n":2,"rules":["cc","java"]})");
}
