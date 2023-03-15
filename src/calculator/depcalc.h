#ifndef DEPCALC_H
#define DEPCALC_H

#include <stdio.h>

#include <QDateTimeEdit>
#include <QMainWindow>

extern "C" {
#include "../SmartCalc_v1.0.h"
}

namespace Ui {
class depcalc;
}

class depcalc : public QMainWindow {
  Q_OBJECT

 public:
  explicit depcalc(QWidget *parent = nullptr);
  ~depcalc();

 private slots:
  void on_equalButton_clicked();

  void on_periodStartInputButton_clicked();

  void on_calendarWidget_clicked(const QDate &date);

  void on_periodEndInputButton_clicked();

  void on_reset_clicked();

 private:
  Ui::depcalc *ui;
};

#endif  // DEPCALC_H
