#include <QApplication>
#include <QLabel>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("СМАРТ КАЛк");
  w.show();
  return a.exec();
}
