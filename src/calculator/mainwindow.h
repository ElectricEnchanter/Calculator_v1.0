#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <depcalc.h>
#include <graph.h>
#include <loancalc.h>

#include <QAbstractButton>
#include <QAudioOutput>
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

  void on_pushButton_clicked();

 private:
  Ui::MainWindow *ui;
  Dialog dialog;
  loanCalc loanCalc;
  depcalc depCalc;
 signals:
  void aboba();
};
#endif  // MAINWINDOW_H
