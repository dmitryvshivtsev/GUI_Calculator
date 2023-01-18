#ifndef S21_VIEW_H
#define S21_VIEW_H

#include "../Controller/s21_controller.h"
#include <QMainWindow>
#include <QVector>
#include <QMessageBox>
#include "credit_view.h"
#include "deposit_view.h"

#define EPS 1e-7

QT_BEGIN_NAMESPACE
namespace Ui { class s21_view; }
QT_END_NAMESPACE

class s21_view : public QMainWindow
{
    Q_OBJECT

public:
    s21_view(QWidget *parent = nullptr);
    ~s21_view();

private slots:
    void digits_and_operators();
    void functions();
    void AC();
    void del();
    void res();
    void drawGraph();
    void errorMessage();
    void on_credit_button_clicked();

    void on_deposit_button_clicked();

private:
    Ui::s21_view *ui;
    s21::Controller controller;
    creditView credit;
    depositView deposit;

    double result_num_;
    double xBegin_, xEnd_, yBegin_, yEnd_, h, X, Y;
    int N_;
    QVector<double> x_, y_;
};
#endif // S21_VIEW_H
