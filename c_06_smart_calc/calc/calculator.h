#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <creditcalc.h>
#include <depositcalc.h>

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QtMath>

#ifdef __cplusplus
extern "C" {
#include "../calc.h"
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
  Q_OBJECT
  enum types { NO, YES, NUM, FUNC, RBRACKET, BIN, UN, DOT, EQ, AC };

 public:
  Calculator(QWidget *parent = nullptr);
  ~Calculator();

 private slots:
  void digitClicked();
  void functionClicked();
  void leftClicked();
  void rightClicked();
  void binaryClicked();
  void unaryClicked();
  void dotClicked();
  void equalsClicked();
  void acClicked();
  void printGraph();
  void printClicked();
  void xClicked();

  void on_actionCredit_mode_triggered();

  void on_actionDeposit_mode_triggered();

 private:
  Ui::Calculator *ui;
  void setTextFromButton(QString str);
  void setType(int newType);
  int type = NO;
  int prevType = NO;
  int dotOn = NO;
  int numLen = 0;
  int brackets = 0;
  int xOn = NO;
  int x1, x2, y1, y2;
  QVector<double> x, y;
  double xBegin, xEnd, h, X;
  CreditCalc creditWidget;
  DepositCalc depositWidget;
};

#endif  // CALCULATOR_H
