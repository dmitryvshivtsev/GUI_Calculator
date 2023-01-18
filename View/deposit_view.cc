#include "deposit_view.h"

#include "s21_view.h"
#include "ui_deposit_view.h"

depositView::depositView(QWidget *parent)
    : QWidget(parent), ui(new Ui::depositView) {
  ui->setupUi(this);

  setWindowTitle("Deposit Calc");
  setFixedSize(size());

  connect(ui->back_button, SIGNAL(clicked()), this, SLOT(back()));
  connect(ui->result_deposit_button, SIGNAL(clicked()), this, SLOT(result()));
}

depositView::~depositView() { delete ui; }

void depositView::back() {
  s21_view *view = new s21_view;
  view->show();
  this->close();
}

void depositView::result() {
  double tax_sum, total_sum, profit;

  this->sum_deposit = ui->deposit_sum_line->text().toStdString();
  this->days = ui->period_line->text().toStdString();
  this->rate = ui->percent_line->text().toStdString();
  this->minus_rate = ui->tax_line->text().toStdString();

  std::map<std::string, std::string> data = {
      {"sum", this->sum_deposit},
      {"percent_rate", this->rate},
      {"time", this->days},
      {"tax_rate", this->minus_rate},
      {"period_payments", this->period_type},
      {"capit_flag", this->capit}};

  controller.calculateDeposit(data, tax_sum, total_sum, profit);

  ui->profit_label->setText(QString::number(profit, 'g', 7));
  ui->tax_sum_label->setText(QString::number(tax_sum, 'g', 7));
  ui->sum_deposit_label->setText(QString::number(total_sum, 'g', 7));
}

void depositView::on_period_type_payments_activated(int index) {
  this->period_type = std::to_string(index);
}

void depositView::on_capitalization_check_stateChanged(int arg1) {
  this->capit = std::to_string(arg1);
}
