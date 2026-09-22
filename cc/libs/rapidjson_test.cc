#include "gtest/gtest.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
TEST(RapidJson, ParseAndWrite) {
  rapidjson::Document d;
  d.Parse(R"({"answer":42})");
  ASSERT_FALSE(d.HasParseError());
  EXPECT_EQ(d["answer"].GetInt(), 42);
  rapidjson::StringBuffer sb;
  rapidjson::Writer<rapidjson::StringBuffer> w(sb);
  d.Accept(w);
  EXPECT_STREQ(sb.GetString(), R"({"answer":42})");
}
