#ifndef GRAPH_H
#define GRAPH_H

#include <ctype.h>
#include <stdlib.h>

#include <QDialog>
#include <QTimer>
#include <QVector>
#include <QtMath>

extern "C" {
#include "../SmartCalc_v1.0.h"
}
namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
  Q_OBJECT

 public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();

 private slots:

  void on_build_clicked();

  void on_pushButton_clicked();

 private:
  Ui::Dialog *ui;
  double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;

  int time;
};

#endif  // GRAPH_H
