#ifndef CREDIT_VIEW_H
#define CREDIT_VIEW_H

#include <QWidget>
#include "../Controller/s21_controller.h"
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class creditView;
}

class creditView : public QWidget {
    Q_OBJECT

public:
    explicit creditView(QWidget *parent = nullptr);
    ~creditView();
    std::string total_credit_amount, period, percent, type = "0";

private slots:
    void back();
    void result();

    void on_type_credit_comboBox_activated(int index);

private:
    Ui::creditView *ui;
    s21::Controller controller;
};

#endif // CREDIT_VIEW_H
