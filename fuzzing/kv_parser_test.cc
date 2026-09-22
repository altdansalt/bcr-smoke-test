#include "fuzzing/kv_parser.h"

#include "gtest/gtest.h"

TEST(KvParser, ParsesPairs) {
  auto m = smoke::ParseKeyValues("a=1;b=two;;=skipped;noeq");
  EXPECT_EQ(m.size(), 2u);
  EXPECT_EQ(m["a"], "1");
  EXPECT_EQ(m["b"], "two");
}
