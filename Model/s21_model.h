#ifndef S21_MODEL_H
#define S21_MODEL_H

#include <iostream>
#include <cmath>
#include <list>
#include <cstring>
#include <algorithm>
#include <strings.h>
#include <utility>
#include <vector>
#include <map>

enum type { number, plus_minus, mul_div_mod, power, math_operator, brackets };

namespace s21 {
class Model {
 public:
  Model();
  Model(double value, std::string oper, short int priority);
  ~Model() { ; };

  static bool validation(std::string &expression);
  static void mainParser(std::string expression, std::list<s21::Model> &list, double x);
  static std::list<s21::Model> polishNotation(std::list<s21::Model> &list);
  static double calculateExpression(std::list<s21::Model> &list);
  static void begin(std::string expression, double x, double &res);
  static void annuitantCreditCalculate(std::map<std::string, std::string> data, std::vector<double> &monthly,
                                       double &overpayment, double &res_pay);
  static void differentiatedCreditCalculate(std::map<std::string, std::string> data, std::vector<double> &monthly,
                                            double &overpayment, double &res_pay);
  static void depositCalculate(std::map<std::string, std::string> data,
                               double &tax_sum, double &total_sum, double &profit);

  double getValue() const;
  std::string getOperator() const;
  short int getPriority() const;

private:
  double value_;
  std::string operator_;
  short int priority_;

  static bool validationBrackets(std::string &expression);
  static bool operatorAndDigitsValidation(std::string &expression);
  static bool isDigit(char symbol);
  static bool isOperator(char symbol);
  static bool isFunction(char symbol);
  static void replace(std::string &str);
  static bool replace_symbol(std::string &str, const std::string& sym_off,
                             const std::string& sym_on);
  static void operatorParser(char symbol, std::list<s21::Model> &list);
  static void mathFuncParser(char i, char next, std::list<s21::Model> &list);
  static void calculateIsOperators(std::list<double> &tmp_list, const std::string& oper);
  static void calculateIsMathFunction(std::list<double> &tmp_list, const std::string& oper);
};
}  // namespace s21



#endif // S21_MODEL_H
