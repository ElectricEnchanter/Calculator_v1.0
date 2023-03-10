#ifndef LOANCALC_H
#define LOANCALC_H

#include <QDialog>
#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QtMath>

#include "ui_loancalc.h"

namespace Ui {
class loanCalc;
}

extern "C" {
#include "../SmartCalc_v1.0.h"
}

class loanCalc : public QMainWindow {
  Q_OBJECT

 public:
  explicit loanCalc(QWidget *parent = nullptr);
  ~loanCalc();
  int a;
  QCPBars *procents;
  QCPBars *restSum;

 private slots:

  void on_equal_clicked();

 private:
  Ui::loanCalc *ui;
};

#endif  // LOANCALC_H
