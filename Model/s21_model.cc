#include "s21_model.h"

namespace s21 {
Model::Model() : Model(0, "", 0) { ; }

Model::Model(double value, std::string oper, short int priority)
    : value_(value), operator_(std::move(oper)), priority_(priority) {
  ;
}

double Model::getValue() const { return this->value_; }
std::string Model::getOperator() const { return this->operator_; }
short int Model::getPriority() const { return this->priority_; }

void Model::begin(std::string expression, double x, double &res) {
  std::list<s21::Model> exp_list;
  replace(expression);
  if (!validation(expression)) {
    throw std::invalid_argument("Incorrect input");
  }
  mainParser(expression, exp_list, x);
  exp_list = polishNotation(exp_list);
  res = calculateExpression(exp_list);
}

bool Model::validation(std::string &expression) {
  bool result = false;
  if (validationBrackets(expression) &&
          operatorAndDigitsValidation(expression))
    result = true;
  return result;
}

bool Model::validationBrackets(std::string &expression) {
  bool result = false;
  bool emptyBody = false;
  short int bracketsCheck = 0;
  for (auto i = expression.begin(); i != expression.end(); i++) {
    if (*i == '(') {
      bracketsCheck++;
      if (*(i + 1) == ')') emptyBody = true;
    } else if (*i == ')') {
      bracketsCheck--;
      if (bracketsCheck < 0) result = false;
    }
  }
  if (bracketsCheck == 0 && !emptyBody) result = true;
  return result;
}

bool Model::operatorAndDigitsValidation(std::string &expression) {
  bool result = true;
  for (auto i = expression.begin(); i != expression.end(); i++) {
    if (*i == '.' && (!isDigit(*(i + 1)) || !isDigit(*(i - 1)))) {
      result = false;
    } else if (isOperator(*i)) {
      if (*i == 'm' && isOperator(*(i - 1))) {
        result = false;
      } else if (*i == '+' || *i == '-') {
        if (isOperator(*(i + 1)) || isOperator(*(i - 1)))
          result = false;
        else if (*(i + 1) == ')')
          result = false;
      } else if (*i == '*' || *i == '/' || *i == '^') {
        if (isOperator(*(i + 1)) || isOperator(*(i - 1)))
          result = false;
        else if (*(i + 1) == ')' || *(i - 1) == '(')
          result = false;
      } else if (isFunction(*i)) {
        if (!isOperator(*(i - 1))) {
          result = false;
        }
      }
    }
  }
  return result;
}

bool Model::isDigit(char symbol) {
  bool result = false;
  if (symbol >= '0' && symbol <= '9') result = true;
  return result;
}

bool Model::isOperator(char symbol) {
  bool result = false;
  if (symbol == '^' || symbol == '*' || symbol == '+' || symbol == '-' ||
      symbol == '/' || symbol == 'm')
    result = true;
  return result;
}

bool Model::isFunction(char symbol) {
  bool result = false;
  if (symbol == 's' || symbol == 'c' || symbol == 't' || symbol == 'a' ||
      symbol == 'l')
    result = true;
  return result;
}

bool Model::replace_symbol(std::string &str, const std::string &sym_off,
                           const std::string &sym_on) {
  bool flag_unar = false;
  size_t pos;
  while ((pos = str.find(sym_off)) != str.npos) {
    str.replace(pos, sym_off.size(), sym_on);
    flag_unar = true;
  }
  return flag_unar;
}

void Model::replace(std::string &str) {
  replace_symbol(str, "e+", "*10^");
  replace_symbol(str, "e-", "/10^");
  replace_symbol(str, "(+", "(0+");
  replace_symbol(str, "(-", "(0-");
}

void Model::operatorParser(char symbol, std::list<s21::Model> &list) {
  if (symbol == '+') {
    Model lexeme(0, "+", plus_minus);
    list.push_back(lexeme);
  } else if (symbol == '-') {
    Model lexeme(0, "-", plus_minus);
    list.push_back(lexeme);
  } else if (symbol == '*') {
    Model lexeme(0, "*", mul_div_mod);
    list.push_back(lexeme);
  } else if (symbol == '/') {
    Model lexeme(0, "/", mul_div_mod);
    list.push_back(lexeme);
  } else if (symbol == 'm') {
    Model lexeme(0, "mod", mul_div_mod);
    list.push_back(lexeme);
  } else if (symbol == '^') {
    Model lexeme(0, "^", power);
    list.push_back(lexeme);
  }
}

void Model::mathFuncParser(char i, char next, std::list<s21::Model> &list) {
  if (i == 's') {
    if (next == 'i') {
      Model lexeme(0, "sin", math_operator);
      list.push_back(lexeme);
    } else if (next == 'q') {
      Model lexeme(0, "sqrt", math_operator);
      list.push_back(lexeme);
    }
  } else if (i == 'a') {
    if (next == 's') {
      Model lexeme(0, "asin", math_operator);
      list.push_back(lexeme);
    } else if (next == 'c') {
      Model lexeme(0, "acos", math_operator);
      list.push_back(lexeme);
    } else if (next == 't') {
      Model lexeme(0, "atan", math_operator);
      list.push_back(lexeme);
    }
  } else if (i == 'l') {
    if (next == 'o') {
      Model lexeme(0, "log", math_operator);
      list.push_back(lexeme);
    } else if (next == 'n') {
      Model lexeme(0, "ln", math_operator);
      list.push_back(lexeme);
    }
  } else if (i == 't') {
    Model lexeme(0, "tan", math_operator);
    list.push_back(lexeme);
  } else if (i == 'c') {
    Model lexeme(0, "cos", math_operator);
    list.push_back(lexeme);
  }
}

void Model::mainParser(std::string expression, std::list<s21::Model> &list,
                       double x) {
  for (auto i = expression.begin(); i != expression.end(); i++) {
    if (isDigit(*i) || *i == '.') {
      std::string num;
      for (; isDigit(*i) || *i == '.'; i++) num += *i;
      i--;
      Model num_lex(std::stod(num), "", number);
      list.push_back(num_lex);
    }
    if (isOperator(*i)) {
      operatorParser(*i, list);
    } else if (isFunction(*i)) {
      mathFuncParser(*i, *(i + 1), list);
      if (*i == 'a' && *(i + 1) != 'n') i += 3;
      if (*(i + 1) == 'q') i += 3;
    } else if (*i == '(') {
      Model lexeme(0, "(", brackets);
      list.push_back(lexeme);
    } else if (*i == ')') {
      Model lexeme(0, ")", brackets);
      list.push_back(lexeme);
    } else if (*i == 'x') {
      Model lexeme(x, "", number);
      list.push_back(lexeme);
    }
  }
}

std::list<s21::Model> Model::polishNotation(std::list<s21::Model> &list) {
  std::list<s21::Model> ready, support;
  for (auto &i : list) {
    if (i.getPriority() == number) {
      ready.push_back(i);
    } else {
      if (i.getOperator() == "(" &&
          i.getPriority() ==
              brackets) {  // Если скобка открылась, то пушим ее в саппорт
        support.push_back(i);
      } else {
        // Если скобка закрылась, начинаем доставать из саппорта все, пока не
        // встретим открытую скобку
        if (i.getOperator() == ")") {
          while (!support.empty() && support.back().getOperator() != "(") {
            Model elem = support.back();
            support.pop_back();
            ready.push_back(elem);
          }
          if (!support.empty()) support.pop_back();
        } else if (!support.empty() &&
                   i.getPriority() <= support.back().getPriority()) {
          while (!support.empty() &&
                 i.getPriority() <= support.back().getPriority()) {
            if (support.back().getOperator() == "(") break;
            Model elem = support.back();
            support.pop_back();
            ready.push_back(elem);
          }
          support.push_back(i);
        } else {
          support.push_back(i);
        }
      }
    }
  }
  while (!support.empty()) {
    Model elem = support.back();
    support.pop_back();
    ready.push_back(elem);
  }
  return ready;
}

double Model::calculateExpression(std::list<s21::Model> &list) {
  std::list<double> tmp_list;
  for (auto &i : list) {
    if (i.priority_ == number) {
      tmp_list.push_back(i.value_);
    } else if (isOperator(i.operator_[0])) {
      calculateIsOperators(tmp_list, i.operator_);
    } else if (isFunction(i.operator_[0])) {
      calculateIsMathFunction(tmp_list, i.operator_);
    }
  }
  double result = tmp_list.back();
  tmp_list.pop_back();
  return result;
}

void Model::calculateIsOperators(std::list<double> &tmp_list,
                                 const std::string &oper) {
  double tmp_num, result;
  tmp_num = tmp_list.back();
  tmp_list.pop_back();
  if (oper == "+") {
    result = tmp_list.back() + tmp_num;
    tmp_list.pop_back();
    tmp_list.push_back(result);
  } else if (oper == "-") {
    result = tmp_list.back() - tmp_num;
    tmp_list.pop_back();
    tmp_list.push_back(result);
  } else if (oper == "*") {
    result = tmp_list.back() * tmp_num;
    tmp_list.pop_back();
    tmp_list.push_back(result);
  } else if (oper == "/") {
    result = tmp_list.back() / tmp_num;
    tmp_list.pop_back();
    tmp_list.push_back(result);
  } else if (oper == "mod") {
    result = tmp_list.back();
    tmp_list.pop_back();
    tmp_list.push_back(fmod(result, tmp_num));
  } else if (oper == "^") {
    result = tmp_list.back();
    tmp_list.pop_back();
    tmp_list.push_back(pow(result, tmp_num));
  }
}

void Model::calculateIsMathFunction(std::list<double> &tmp_list,
                                    const std::string &oper) {
  double result;
  result = tmp_list.back();
  tmp_list.pop_back();
  if (oper == "sin") {
    tmp_list.push_back(sin(result));
  } else if (oper == "cos") {
    tmp_list.push_back(cos(result));
  } else if (oper == "tan") {
    tmp_list.push_back(tan(result));
  } else if (oper == "ln") {
    tmp_list.push_back(log(result));
  } else if (oper == "log") {
    tmp_list.push_back(log10(result));
  } else if (oper == "sqrt") {
    tmp_list.push_back(sqrt(result));
  } else if (oper == "asin") {
    tmp_list.push_back(asin(result));
  } else if (oper == "acos") {
    tmp_list.push_back(acos(result));
  } else if (oper == "atan") {
    tmp_list.push_back(atan(result));
  }
}

void Model::annuitantCreditCalculate(std::map<std::string, std::string> data,
                                     std::vector<double> &monthly,
                                     double &overpayment, double &res_pay) {
  std::string sum_text = data.at("total_credit");
  std::string months = data.at("period");
  std::string rate = data.at("percent");
  int months_int = std::stoi(months);

  std::string str_formula = sum_text + "*(" + rate + "/(100 * 12)/(1-(1+" +
                            rate + "/(100 * 12)" + ")^(0-" + months + ")))";
  double tmp_res = 0;
  begin(str_formula, 1, tmp_res);
  for (auto i = 0; i < months_int; i++) monthly.push_back(tmp_res);

  std::string str_full = std::to_string(tmp_res) + "*" + months;
  begin(str_full, 1, res_pay);

  std::string string_over = std::to_string(res_pay) + "-" + sum_text;
  begin(string_over, 1, overpayment);
}

void Model::differentiatedCreditCalculate(
    std::map<std::string, std::string> data, std::vector<double> &monthly,
    double &overpayment, double &res_pay) {
  std::string sum_text = data.at("total_credit");
  std::string months = data.at("period");
  std::string rate = data.at("percent");

  int months_int = std::stoi(months);
  double sum_num = std::stod(sum_text);
  double equal_shares = 0;
  std::string eq_shares_formula = sum_text + "/" + months;
  begin(eq_shares_formula, 1, equal_shares);

  double debt_num = sum_num, percent_on_debt = 0, pay_of_month = 0;
  for (auto i = 0; i < months_int; i++) {
    std::string percent_on_debt_formula =
        std::to_string(debt_num) + "*(" + rate + "/100)/" + "12";
    // Вычисляем процент на долг
    begin(percent_on_debt_formula, 1, percent_on_debt);
    // Прибавляем процент на долг за месяц к итоговой переплате
    overpayment += percent_on_debt;
    std::string pay_of_month_formula =
        std::to_string(equal_shares) + "+" + std::to_string(percent_on_debt);
    // Вычисляем месячный платеж (тело кредита + проценты)
    begin(pay_of_month_formula, 1, pay_of_month);
    monthly.push_back(pay_of_month);
    res_pay += pay_of_month;

    debt_num -= equal_shares;
  }
  overpayment = round(overpayment * 100) / 100;
  res_pay = round(res_pay * 100) / 100;
}

void Model::depositCalculate(std::map<std::string, std::string> data,
                             double &tax_sum, double &total_sum,
                             double &profit) {
  double sum = std::stod(data.at("sum"));
  int period = std::stoi(data.at("time"));
  double percent_rate = std::stod(data.at("percent_rate"));
  double tax_rate = std::stod(data.at("tax_rate"));
  int period_payments = std::stoi(data.at("period_payments"));
  int capit_flag = std::stoi(data.at("capit_flag"));

  if (!capit_flag) {
    profit = (sum * percent_rate * period / 365) / 100;
  } else {
    double add_percent_period = 0;
    double mul_period = 0;
    if (period_payments == 0) {
      add_percent_period = 1;
      mul_period = 365;
    } else if (period_payments == 1) {
      add_percent_period = 30.5;
      mul_period = 12;
    } else if (period_payments == 2) {
      add_percent_period = 91;
      mul_period = 4;
    } else if (period_payments == 3) {
      add_percent_period = 365;
      mul_period = 1;
    }
    double tmp = add_percent_period / 365;
    tmp = sum * percent_rate * tmp / 100;
    profit = tmp * mul_period;
    profit += profit * 0.04881126;
  }
  tax_sum = 0;
  tax_sum = profit * (tax_rate / 100);
  total_sum = sum + profit - tax_sum;
}

}  // namespace s21
