#include "s21_view.h"

#include "ui_s21_view.h"

s21_view::s21_view(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::s21_view) {
  ui->setupUi(this);
  setWindowTitle("Calculator by Rosettel");
  setFixedSize(size());

  QVector<QPushButton *> digits{
      ui->one_button,         ui->two_button,          ui->three_button,
      ui->four_button,        ui->five_button,         ui->six_button,
      ui->seven_button,       ui->eight_button,        ui->nine_button,
      ui->zero_button,        ui->dot_button,          ui->x_button,
      ui->openBracket_button, ui->closeBracket_button, ui->mod_button,
      ui->plus_button,        ui->minus_button,        ui->mul_button,
      ui->div_button,         ui->degree_button};
  for (auto i : digits) {
    connect(i, SIGNAL(clicked()), this, SLOT(digits_and_operators()));
  }

  QVector<QPushButton *> funcs{
      ui->sin_button,  ui->cos_button,  ui->tan_button,
      ui->atan_button, ui->asin_button, ui->acos_button,
      ui->ln_button,   ui->log_button,  ui->sqrt_button};
  for (auto i : funcs) {
    connect(i, SIGNAL(clicked()), this, SLOT(functions()));
  }

  connect(ui->AC_button, SIGNAL(clicked()), this, SLOT(AC()));
  connect(ui->del_button, SIGNAL(clicked()), this, SLOT(del()));
  connect(ui->equal_button, SIGNAL(clicked()), this, SLOT(res()));
  connect(ui->draw_button, SIGNAL(clicked()), this, SLOT(drawGraph()));
}

s21_view::~s21_view() { delete ui; }

void s21_view::digits_and_operators() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->input_box->text() + button->text();
  ui->input_box->setText(new_label);
}

void s21_view::functions() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->input_box->text() + button->text() + "(";
  ui->input_box->setText(new_label);
}

void s21_view::del() {
  QString new_label = ui->input_box->text();
  new_label.chop(1);
  ui->input_box->setText(new_label);
}

void s21_view::AC() {
  ui->input_box->setText("");
  ui->widget->clearGraphs();
  x_.clear();
  y_.clear();
  ui->widget->replot();
}

void s21_view::errorMessage() {
  ui->input_box->setText("");
  QMessageBox message;
  message.setText("Wrong expression! Please, try again");
  message.setIcon(QMessageBox::Critical);
  message.exec();
}

void s21_view::res() {
  std::string expression = "(" + ui->input_box->text().toStdString() + ")";
  double x_num = ui->x_val->text().toDouble();
  try {
    this->controller.checkExpression(expression, x_num, result_num_);
    QString value;
    value = QString::number(this->result_num_, 'g', 16);
    ui->input_box->setText(value);
  } catch (...) {
    errorMessage();
  }
}

void s21_view::drawGraph() {
  try {
    ui->widget->clearGraphs();
    xBegin_ = ui->SpinBox_Xmin->text().toDouble();
    xEnd_ = ui->SpinBox_Xmax->text().toDouble();
    yBegin_ = ui->SpinBox_Ymin->text().toDouble();
    yEnd_ = ui->SpinBox_Ymax->text().toDouble();
    h = 0.0005 * (qFabs(xBegin_) + qFabs(xEnd_));
    ui->widget->xAxis->setRange(xBegin_, xEnd_);
    ui->widget->yAxis->setRange(yBegin_, yEnd_);
    QString str = ui->input_box->text();
    if (!str.contains("x")) {
      ui->input_box->setText("x");
    } else {
      Y = 0;
      h = 0.0005 * (qFabs(xBegin_) + qFabs(xEnd_));
      QString value;
      QString tmp = str;
      for (X = xBegin_; X <= xEnd_; X += h) {
        value = tmp.replace("x", ('(' + QString::number(X) + ')'));
        controller.checkExpression(value.toStdString(), ui->x_val->value(), Y);
        x_.emplace_back(X);
        y_.emplace_back(Y);
        tmp = str;
      }
      ui->widget->addGraph();
      ui->widget->graph(0)->addData(x_, y_);
      ui->widget->replot();
      x_.clear();
      y_.clear();
    }
  } catch (...) {
    errorMessage();
  }
}

void s21_view::on_credit_button_clicked() {
  credit.show();
  this->close();
}

void s21_view::on_deposit_button_clicked() {
  deposit.show();
  this->close();
}
