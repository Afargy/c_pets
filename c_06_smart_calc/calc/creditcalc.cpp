#include "creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_pushButton_clicked() {
  if (ui->annuity->isChecked()) {
    double amount = ui->totalAmount->value();
    int months = ui->term->value();
    double interest = ui->interestRate->value() / 1200;

    double monthly = amount * ((interest * pow((1 + interest), months)) /
                               (pow((1 + interest), months) - 1));
    double totalPay = monthly * months;
    double over = totalPay - amount;

    ui->monthlyPayment->setText(QString::number(monthly, 'f', 2));
    ui->overpayment->setText(QString::number(over, 'f', 2));
    ui->totalPayment->setText(QString::number(totalPay, 'f', 2));
  } else {
    double amount = ui->totalAmount->value();
    int months = ui->term->value();
    double interest = ui->interestRate->value() / 1200;
    double rest = amount, body{amount / months};
    double m1{0}, m2{0}, totalPay{0};

    for (int i = 1; i <= months; i++) {
      double percents{0.0}, monthly{0.0};

      percents = rest * interest;
      monthly = body + percents;
      rest = rest - body;
      totalPay += monthly;

      if (i == 1) m1 = monthly;
      if (i == months) m2 = monthly;

      ui->display->insertPlainText("month: ");
      ui->display->insertPlainText(QString::number(i) + "\t");

      ui->display->insertPlainText("body: ");
      ui->display->insertPlainText(QString::number(body, 'f', 2) + "\t\t");

      ui->display->insertPlainText("percents: ");
      ui->display->insertPlainText(QString::number(percents, 'f', 2) + "\t\t");

      ui->display->insertPlainText("payment: ");
      ui->display->insertPlainText(QString::number(monthly, 'f', 2) + "\t");

      ui->display->insertPlainText("rest: ");
      ui->display->insertPlainText(QString::number(rest, 'f', 2) + "\n");
    }

    double over = totalPay - amount;

    ui->monthlyPayment->setText(QString::number(m1, 'f', 2) + " - " +
                                QString::number(m2, 'f', 2));
    ui->overpayment->setText(QString::number(over));
    ui->totalPayment->setText(QString::number(totalPay));
  }
}

void CreditCalc::on_pushButton_2_clicked() { ui->display->setText(""); }
