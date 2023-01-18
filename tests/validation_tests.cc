#include <gtest/gtest.h>

#include "../Model/s21_model.h"

TEST(Test_1, brackets_validation_1) {
  std::string test = "(3+(2+2))";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_1, brackets_validation_2) {
  std::string test = "2+(2)";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_1, brackets_validation_3) {
  std::string test = "(2+2))";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_1, brackets_validation_4) {
  std::string test = "2+2)";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_1, brackets_validation_5) {
  std::string test = "(2+2";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_1, brackets_validation_6) {
  std::string test = "2+()";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_1, brackets_validation_7) {
  std::string test = ")";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_2, dot_validation_1) {
  std::string test = "2.2+4.3";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_2, dot_validation_2) {
  std::string test = "2.2-2.2+2";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_2, dot_validation_3) {
  std::string test = "2.2.+4.3";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_2, dot_validation_4) {
  std::string test = "2..2+4..3";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_2, dot_validation_5) {
  std::string test = "2.+4";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_2, dot_validation_6) {
  std::string test = "0.0+9.9";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_3, operators_validation_1) {
  std::string test = "5*5";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_3, operators_validation_2) {
  std::string test = "3+5";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_3, operators_validation_3) {
  std::string test = "8-5";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_3, operators_validation_4) {
  std::string test = "55^2";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_3, operators_validation_5) {
  std::string test = "-5*2^4+3-(4^2)";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_3, operators_validation_6) {
  std::string test = "500/((4+1)/10)^2";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_3, operators_validation_7) {
  std::string test = "1+5**5";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_3, operators_validation_8) {
  std::string test = "1++2-3*4/5^6";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_3, operators_validation_9) {
  std::string test = "1+2-3*4//5^6";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_4, functions_validation_1) {
  std::string test = "cos(x)";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_4, functions_validation_2) {
  std::string test = "sin(228)";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_4, functions_validation_3) {
  std::string test = "log(ln(144))";
  EXPECT_TRUE(s21::Model::validation(test));
}

TEST(Test_4, functions_validation_4) {
  std::string test = "cosmos()";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_4, functions_validation_5) {
  std::string test = "cos(sin())";
  EXPECT_FALSE(s21::Model::validation(test));
}

TEST(Test_4, functions_validation_6) {
  std::string test = "sin(x";
  EXPECT_FALSE(s21::Model::validation(test));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
