#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <math.h>

#include <QWidget>

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

 private:
  Ui::CreditCalc *ui;
};

#endif  // CREDITCALC_H
