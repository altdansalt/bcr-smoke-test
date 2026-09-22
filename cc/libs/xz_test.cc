#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "lzma.h"
TEST(Xz, RoundTrip) {
  std::string in(8000, 'x');
  std::vector<uint8_t> out(lzma_stream_buffer_bound(in.size()));
  size_t out_pos = 0;
  ASSERT_EQ(lzma_easy_buffer_encode(6, LZMA_CHECK_CRC64, nullptr, reinterpret_cast<const uint8_t*>(in.data()), in.size(), out.data(), &out_pos, out.size()), LZMA_OK);
  std::string back(in.size(), '\0');
  size_t in_pos = 0, back_pos = 0;
  uint64_t memlimit = UINT64_MAX;
  ASSERT_EQ(lzma_stream_buffer_decode(&memlimit, 0, nullptr, out.data(), &in_pos, out_pos, reinterpret_cast<uint8_t*>(&back[0]), &back_pos, back.size()), LZMA_OK);
  EXPECT_EQ(back, in);
}
