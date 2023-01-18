#include "s21_controller.h"

namespace s21 {
void Controller::checkExpression(std::string expression, double x,
                                 double &result) {
  Model::begin(expression, x, result);
}

void Controller::creditCalculate(std::map<std::string, std::string> data,
                                 std::vector<double> &monthly,
                                 double &overpayment, double &res_pay) {
  if (data.at("type") == "0")  // Тип платежей
    Model::annuitantCreditCalculate(data, monthly, overpayment, res_pay);
  else
    Model::differentiatedCreditCalculate(data, monthly, overpayment, res_pay);
}

void Controller::calculateDeposit(std::map<std::string, std::string> data,
                                  double &tax_sum, double &total_sum, double &profit) {
  Model::depositCalculate(data, tax_sum, total_sum, profit);
}

}  // namespace s21
