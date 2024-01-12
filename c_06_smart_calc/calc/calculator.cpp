#include "calculator.h"

#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  ui->setupUi(this);
  QString butNames[31]{
      "but0",      "but1",      "but2", "but3",    "but4",
      "but5",      "but6",      "but7", "but8",    "but9",  // 0-9 digits
      "sin",       "cos",       "tan",  "asin",    "acos",
      "atan",      "ln",        "log",  "sqrt",  //  10-18 functions
      "l_bracket", "r_bracket",                 // 19-20 left and right brackets
      "mul",       "div",       "pow",  "mod",  // 21-24 binary operators
      "add",       "sub",                       // 25-26 unary operators
      "dot",       "equals",    "ac",   "x_button"  // 27-30 diffrent
  };

  QPushButton *buttons[31];

  for (int i = 0; i < 31; i++) {
    QString name{butNames[i]};
    buttons[i] = Calculator::findChild<QPushButton *>(name);
    if (i < 10) {
      connect(buttons[i], SIGNAL(clicked()), this, SLOT(digitClicked()));
    } else if (i < 19) {
      connect(buttons[i], SIGNAL(clicked()), this, SLOT(functionClicked()));
    } else if (i == 19) {
      connect(buttons[i], SIGNAL(clicked()), this, SLOT(leftClicked()));
    } else if (i == 20) {
      connect(buttons[i], SIGNAL(clicked()), this, SLOT(rightClicked()));
    } else if (i < 25) {
      connect(buttons[i], SIGNAL(clicked()), this, SLOT(binaryClicked()));
    } else if (i < 27) {
      connect(buttons[i], SIGNAL(clicked()), this, SLOT(unaryClicked()));
    } else if (i == 27) {
      connect(buttons[i], SIGNAL(clicked()), this, SLOT(dotClicked()));
    } else if (i == 28) {
      connect(buttons[i], SIGNAL(clicked()), this, SLOT(equalsClicked()));
    } else if (i == 29) {
      connect(buttons[i], SIGNAL(clicked()), this, SLOT(acClicked()));
    } else if (i == 30) {
      connect(buttons[i], SIGNAL(clicked()), this, SLOT(xClicked()));
    }
  }
  connect(ui->print, SIGNAL(clicked()), this, SLOT(printClicked()));
}

Calculator::~Calculator() { delete ui; }

void Calculator::setTextFromButton(QString str) {
  ui->display->setText(ui->display->text() + ((QPushButton *)sender())->text() +
                       str);
}

void Calculator::setType(int newType) {
  prevType = type;
  type = newType;
}

void Calculator::digitClicked() {
  if (type != RBRACKET) {
    setType(NUM);
    if (prevType != NUM) numLen = 0;
    if (numLen == 0) dotOn = NO;
    numLen++;
    if (numLen < 16) setTextFromButton("");
  }
}

void Calculator::functionClicked() {
  if (type != NUM && type != RBRACKET && type != DOT) {
    setType(FUNC);
    brackets++;
    setTextFromButton("(");
  }
}

void Calculator::leftClicked() {
  if (type != NUM && type != RBRACKET && type != DOT) {
    setType(FUNC);
    brackets++;
    setTextFromButton("");
  }
}

void Calculator::rightClicked() {
  if (brackets > 0 && type != FUNC && type != BIN && type != UN &&
      type != DOT) {
    setType(RBRACKET);
    brackets--;
    setTextFromButton("");
  }
}

void Calculator::binaryClicked() {
  if (type != NO && type != FUNC && type != BIN && type != UN && type != DOT) {
    setType(BIN);
    setTextFromButton("");
  }
}

void Calculator::unaryClicked() {
  if (type != DOT) {
    setType(UN);
    setTextFromButton("");
  }
}

void Calculator::dotClicked() {
  if (type == NUM && dotOn == NO && numLen < 16) {
    dotOn = YES;
    setTextFromButton("");
  }
}

void Calculator::equalsClicked() {
  if (brackets != 0) {
    ui->result->setText("Close parenthesis");
  } else if (type == NO || type == UN || type == BIN) {
    ui->result->setText("Wrong expression");
  } else {
    QString str1 = ui->display->text();
    QByteArray ba = str1.toLocal8Bit();
    char *str2 = ba.data();
    double result{0};
    int err = calculate(str2, ui->x_value->value(), &result);
    if (!err) {
      ui->result->setText(QString::number(result));
    } else {
      ui->result->setText("Division by zero");
    }
  }
}

void Calculator::acClicked() {
  type = NO;
  prevType = NO;
  numLen = NO;
  brackets = NO;
  dotOn = NO;
  xOn = NO;
  ui->display->setText("");
  ui->result->setText("");
}

void Calculator::printGraph() {
  h = 0.1;
  xBegin = x1;
  xEnd = x2;

  ui->graph->xAxis->setRange(x1, x2);
  ui->graph->yAxis->setRange(y1, y2);
  ui->graph->replot();

  for (X = xBegin; X <= xEnd; X += h) {
    if (xOn) {
      x.push_back(X);
      QString str1 = ui->display->text();
      QByteArray ba = str1.toLocal8Bit();
      char *str2 = ba.data();
      double result{0};
      calculate(str2, X, &result);
      y.push_back(result);
    } else {
      x.push_back(X);
      double res = ui->result->text().toDouble();
      y.push_back(res);
    }
  }

  ui->graph->addGraph();
  ui->graph->graph(0)->addData(x, y);
  ui->graph->replot();
}

void Calculator::printClicked() {
  y.clear();
  x.clear();
  ui->graph->clearGraphs();
  x1 = ui->minX->value();
  x2 = ui->maxX->value();
  y1 = ui->minY->value();
  y2 = ui->maxY->value();
  printGraph();
}

void Calculator::xClicked() {
  if (type != RBRACKET && type != NUM) {
    setType(NUM);
    xOn = YES;
    if (prevType != NUM) numLen = 15;
    setTextFromButton("");
  }
}

void Calculator::on_actionCredit_mode_triggered() { creditWidget.show(); }

void Calculator::on_actionDeposit_mode_triggered() { depositWidget.show(); }
