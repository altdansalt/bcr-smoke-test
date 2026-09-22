#include "gtest/gtest.h"
#include "ft2build.h"
#include FT_FREETYPE_H
TEST(FreeType, InitAndVersion) {
  FT_Library lib;
  ASSERT_EQ(FT_Init_FreeType(&lib), 0);
  FT_Int major = 0, minor = 0, patch = 0;
  FT_Library_Version(lib, &major, &minor, &patch);
  EXPECT_EQ(major, 2);
  FT_Done_FreeType(lib);
}
