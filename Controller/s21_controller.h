#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H

#include "../Model/s21_model.h"

namespace s21 {
class Controller {
  public:
    Controller() { ; }
    ~Controller() { ; }
    static void checkExpression(std::string expression, double x, double &result);
    static void creditCalculate(std::map<std::string, std::string> data, std::vector<double> &monthly,
                                double &overpayment, double &res_pay);
    static void calculateDeposit(std::map<std::string, std::string> data,
                                 double &tax_sum, double &total_sum, double &profit);
  };
}

#endif // S21_CONTROLLER_H
