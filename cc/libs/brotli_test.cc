#include <string>
#include <vector>
#include "brotli/decode.h"
#include "brotli/encode.h"
#include "gtest/gtest.h"
TEST(Brotli, RoundTrip) {
  std::string in(6000, 'r');
  std::vector<uint8_t> out(BrotliEncoderMaxCompressedSize(in.size()));
  size_t out_len = out.size();
  ASSERT_TRUE(BrotliEncoderCompress(BROTLI_DEFAULT_QUALITY, BROTLI_DEFAULT_WINDOW, BROTLI_MODE_GENERIC, in.size(), reinterpret_cast<const uint8_t*>(in.data()), &out_len, out.data()));
  std::string back(in.size(), '\0');
  size_t back_len = back.size();
  ASSERT_EQ(BrotliDecoderDecompress(out_len, out.data(), &back_len, reinterpret_cast<uint8_t*>(&back[0])), BROTLI_DECODER_RESULT_SUCCESS);
  EXPECT_EQ(back, in);
}
