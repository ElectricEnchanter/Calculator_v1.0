#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->groupBox->hide();
  ui->groupBox2->hide();
  player = new QMediaPlayer;
  audioOutput = new QAudioOutput;
  connect(ui->digit, &QButtonGroup::buttonClicked, this,
          &MainWindow::digit_click);
  connect(ui->digit2, &QButtonGroup::buttonClicked, this,
          &MainWindow::digit2_click);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digit_click(QAbstractButton *btm) {
  QString text = btm->text();
  ui->input->setText(ui->input->text() + text);
}

void MainWindow::digit2_click(QAbstractButton *btm) {
  QString text = btm->text();
  ui->input->setText(ui->input->text() + text + '(');
}

void MainWindow::on_AC_clicked() {
  ui->input->setText("");
  ui->XInput->setText("");
}

void MainWindow::on_equal_clicked() {
  int err = 0;
  QByteArray sstr = ui->input->text().toLocal8Bit();
  char *input = sstr.data();
  if (*input == '\0') err = 8;
  QByteArray ssstr = ui->XInput->text().toLocal8Bit();
  double Dot = atof(ssstr);

  Numbers *NumHead = NULL;
  Operations *OpHead = NULL;
  char output[255] = {""};

  if (err == 0) err = Validator(input, output);

  if (err == 0) {
    double num = Count(output, &NumHead, &OpHead, Dot);
    ui->input->setText(QString::number(num));
  } else if (err == 1)
    ui->input->setText("ОШИБКА: Нет числа после точки или 2 точки в числе");
  else if (err == 2)
    ui->input->setText(
        "ОШИБКА: Не правильное количество скобок или написана ерунда");
  else if (err == 3)
    ui->input->setText("ОШИБКА: Скобки пустые");
  else if (err == 4)
    ui->input->setText("ОШИБКА: После знака нет числа");
  else if (err == 5)
    ui->input->setText("ОШИБКА: X не число");
  else if (err == 6)
    ui->input->setText("ОШИБКА: Запись не имеет смысла");
}

void MainWindow::on_Graph_clicked() {
  dialog.setModal(true);
  dialog.setWindowTitle("ГРАФИК");
  dialog.exec();
}

void MainWindow::on_Credit_clicked() {
  loanCalc.setWindowTitle("КРЕДИТНЫЙ");
  loanCalc.show();
}

void MainWindow::on_Deposit_clicked() {
  depCalc.setWindowTitle("ДЕПОЗИТНЫЙ");
  depCalc.show();
}

void MainWindow::on_addFuncButton_valueChanged(int value) {
  if (value == 1)
    ui->groupBox->show();
  else
    ui->groupBox->hide();
}

void MainWindow::on_addAdededPartsButton_clicked() {
  if (ui->addAdededPartsButton->isChecked())
    ui->groupBox2->show();
  else
    ui->groupBox2->hide();
}
