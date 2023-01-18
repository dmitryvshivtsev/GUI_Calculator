#ifndef DEPOSIT_VIEW_H
#define DEPOSIT_VIEW_H

#include <QWidget>
#include "../Controller/s21_controller.h"
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class depositView;
}

class depositView : public QWidget {
    Q_OBJECT

public:
    explicit depositView(QWidget *parent = nullptr);
    ~depositView();
    std::string sum_deposit, days, rate, minus_rate,
                period_type = "0", capit= "0";

private slots:
    void back();
    void result();
    void on_period_type_payments_activated(int index);
    void on_capitalization_check_stateChanged(int arg1);

private:
    Ui::depositView *ui;
    s21::Controller controller;
};

#endif // DEPOSIT_VIEW_H
