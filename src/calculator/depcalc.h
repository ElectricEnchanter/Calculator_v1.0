#ifndef DEPCALC_H
#define DEPCALC_H

#include <stdio.h>

#include <QButtonGroup>
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

  void on_reset_clicked();

  void on_refillButtonShow_clicked();

  void on_dateRefilInputButton_clicked();

  void on_calendarWidget_2_clicked(const QDate &date);

  void on_dateWithdInputButton_clicked();

  void on_withdButtonShow_clicked();

  void on_calendarWidget_3_activated(const QDate &date);

  void on_periodEndInputButton_clicked();

 private:
  Ui::depcalc *ui;
};

#endif  // DEPCALC_H
