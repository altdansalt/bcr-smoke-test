#include "Eigen/Dense"
#include "gtest/gtest.h"
TEST(Eigen, MatrixMultiply) {
  Eigen::Matrix2d a;
  a << 1, 2, 3, 4;
  Eigen::Matrix2d b = a * Eigen::Matrix2d::Identity();
  EXPECT_DOUBLE_EQ(b(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(a.determinant(), -2.0);
}
