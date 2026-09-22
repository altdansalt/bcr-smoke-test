#include <string>
#include <vector>
#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
absl::StatusOr<int> Parse(absl::string_view s) {
  int v;
  if (!absl::SimpleAtoi(s, &v)) return absl::InvalidArgumentError("not an int");
  return v;
}
TEST(Abseil, StringsContainersStatus) {
  std::vector<std::string> parts = absl::StrSplit("a,b,c", ',');
  EXPECT_EQ(absl::StrJoin(parts, "-"), "a-b-c");
  absl::flat_hash_map<std::string, int> m = {{"x", 1}};
  EXPECT_EQ(m["x"], 1);
  EXPECT_EQ(absl::StrFormat("%d-%s", 7, "z"), "7-z");
  EXPECT_TRUE(Parse("12").ok());
  EXPECT_FALSE(Parse("nope").ok());
  EXPECT_EQ(absl::Seconds(90), absl::Minutes(1) + absl::Seconds(30));
}
