// Round-trips a message (with a well-known Timestamp field) through
// SerializeToString/ParseFromString, plus a message from the rules_proto shim.
#include <string>

#include "gtest/gtest.h"
#include "proto/greeting.pb.h"
#include "proto/legacy.pb.h"

TEST(Greeting, SerializeParseRoundTrip) {
  smoke::proto::Greeting in;
  in.set_name("bcr");
  in.set_times(3);
  in.mutable_sent_at()->set_seconds(1700000000);
  in.mutable_sent_at()->set_nanos(42);

  std::string bytes;
  ASSERT_TRUE(in.SerializeToString(&bytes));
  ASSERT_FALSE(bytes.empty());

  smoke::proto::Greeting out;
  ASSERT_TRUE(out.ParseFromString(bytes));
  EXPECT_EQ(out.name(), "bcr");
  EXPECT_EQ(out.times(), 3);
  EXPECT_EQ(out.sent_at().seconds(), 1700000000);
  EXPECT_EQ(out.sent_at().nanos(), 42);
}

TEST(Legacy, RulesProtoShim) {
  smoke::proto::LegacyPing ping;
  ping.set_seq(7);
  smoke::proto::LegacyPing copy;
  ASSERT_TRUE(copy.ParseFromString(ping.SerializeAsString()));
  EXPECT_EQ(copy.seq(), 7u);
}
