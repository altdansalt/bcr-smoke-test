#include "gtest/gtest.h"
#include "tinyxml2.h"
TEST(TinyXml2, Parse) {
  tinyxml2::XMLDocument doc;
  ASSERT_EQ(doc.Parse("<root><item n=\"4\"/></root>"), tinyxml2::XML_SUCCESS);
  EXPECT_EQ(doc.FirstChildElement("root")->FirstChildElement("item")->IntAttribute("n"), 4);
}
