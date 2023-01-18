#include "credit_view.h"

#include "s21_view.h"
#include "ui_credit_view.h"

creditView::creditView(QWidget *parent)
    : QWidget(parent), ui(new Ui::creditView) {
  ui->setupUi(this);
  setWindowTitle("Credit calculator");
  setFixedSize(size());
  connect(ui->back_button, SIGNAL(clicked()), this, SLOT(back()));
  connect(ui->result_credit_button, SIGNAL(clicked()), this, SLOT(result()));
}

creditView::~creditView() { delete ui; }

void creditView::back() {
  s21_view *view = new s21_view;
  view->show();
  this->close();
}

void creditView::result() {
  ui->listWidget->clear();
  double overpayment, res_pay;
  std::vector<double> monthly = {};

  this->total_credit_amount = ui->credit_sum_line->text().toStdString();
  this->period = ui->period_line->text().toStdString();
  this->percent = ui->percent_line->text().toStdString();

  std::map<std::string, std::string> data = {
      {"total_credit", this->total_credit_amount},
      {"percent", this->percent},
      {"type", this->type},
      {"period", this->period}};

  controller.creditCalculate(data, monthly, overpayment, res_pay);

  ui->full_label->setText(QString::number(res_pay, 'g', 7));
  ui->overpayment_label->setText(QString::number(overpayment, 'g', 7));
  for (unsigned long i = 0; i < monthly.size(); i++) {
    QString month_counter = QString::number(i + 1);
    QString monthly_str = month_counter + " месяц - " +
                          QString::number(monthly[i], 'g', 7) + " рублей";
    ui->listWidget->addItem(monthly_str);
  }
}

void creditView::on_type_credit_comboBox_activated(int index) {
  this->type = std::to_string(index);
}
