#include <gtest/gtest.h>

#include "../Model/s21_model.h"

TEST(Test_1, calculation_test_1) {
  std::string test = "2+2";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_EQ(4, result);
}

TEST(Test_1, calculation_test_2) {
  std::string test = "2+2/2*2";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_EQ(4, result);
}

TEST(Test_1, calculation_test_3) {
  std::string test = "cos(1)";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_DOUBLE_EQ(0.54030230586813977, result);
}

TEST(Test_1, calculation_test_4) {
  std::string test = "17*3+(5^3*2)/5*cos(1)";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_DOUBLE_EQ(78.015115293406993, result);
}

TEST(Test_1, calculation_test_5) {
  std::string test = "153432mod5";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_EQ(2, result);
}

TEST(Test_1, calculation_test_6) {
  std::string test = "153430mod5";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_EQ(0, result);
}

TEST(Test_1, calculation_test_7) {
  std::string test = "2^(2^(2^2))";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_EQ(65536, result);
}

TEST(Test_1, calculation_test_8) {
  std::string test = "2^2^2^2";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_DOUBLE_EQ(256, result);
}

TEST(Test_1, calculation_test_9) {
  std::string test = "(log(10)*13.532)/5*(2.4^2)";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_DOUBLE_EQ(15.588863999999999, result);
}

TEST(Test_1, calculation_test_10) {
  std::string test = "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
                     "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
                     "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
                     "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
                     "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
                     "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
                     "1+1+1+1+1+1+1";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_DOUBLE_EQ(127, result);
}

TEST(Test_1, calculation_test_11) {
  std::string test = "2458*6325.3/99*(3^2)+(-5*3)";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_DOUBLE_EQ(1413402.0363636366, result);
}

TEST(Test_1, calculation_test_12) {
  std::string test = "(-55)+5";
  double result = 0;
  s21::Model::begin(test, 1, result);
  EXPECT_DOUBLE_EQ(-50, result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}