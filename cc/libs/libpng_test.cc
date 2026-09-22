#include "gtest/gtest.h"
#include "png.h"
TEST(LibPng, Version) {
  EXPECT_STREQ(png_get_libpng_ver(nullptr), PNG_LIBPNG_VER_STRING);
  png_structp p = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  ASSERT_NE(p, nullptr);
  png_destroy_write_struct(&p, nullptr);
}
