#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <depcalc.h>
#include <graph.h>
#include <loancalc.h>
#include <math.h>
#include <stdio.h>

#include <QAbstractButton>
#include <QAudioOutput>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QResource>
#include <QVector>
extern "C" {
#include "../SmartCalc_v1.0.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  QMediaPlayer *player;
  QAudioOutput *audioOutput;
  ~MainWindow();

 private slots:

  void digit_click(QAbstractButton *btm);

  void digit2_click(QAbstractButton *btm);

  void on_AC_clicked();

  void on_equal_clicked();

  void on_Graph_clicked();

  void on_Credit_clicked();

  void on_Deposit_clicked();

  void on_addFuncButton_valueChanged(int value);

  void on_addAdededPartsButton_clicked();

 protected:
  void keyPressEvent(QKeyEvent *e) override;

 private:
  Ui::MainWindow *ui;
  Dialog dialog;
  loanCalc loanCalc;
  depcalc depCalc;
};
#endif  // MAINWINDOW_H
