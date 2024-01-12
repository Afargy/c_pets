#include "depositcalc.h"

#include "ui_depositcalc.h"

DepositCalc::DepositCalc(QWidget *parent)
    : QWidget(parent), ui(new Ui::DepositCalc) {
  ui->setupUi(this);
}

DepositCalc::~DepositCalc() { delete ui; }

void DepositCalc::on_pushButton_clicked() {
  double amount = ui->amountDeposit->value();
  double tRate = ui->tax->value() / 100;
  int term = ui->term->value();
  double iRate = ui->interest->value() / 36500;
  double interest{0}, tax{0}, iSum{0}, sum{amount};

  interest = amount * iRate * term;
  iSum = interest;
  sum += iSum;
  tax = iSum * tRate;

  ui->totalAmount->setText(QString::number(sum, 'f', 2));
  ui->totalInterest->setText(QString::number(iSum, 'f', 2));
  ui->totalTax->setText(QString::number(tax, 'f', 2));
}
