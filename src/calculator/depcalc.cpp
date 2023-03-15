#include "depcalc.h"

#include "QDebug"
#include "ui_depcalc.h"

depcalc::depcalc(QWidget *parent) : QMainWindow(parent), ui(new Ui::depcalc) {
  ui->setupUi(this);
  ui->calendarWidget->hide();
}

depcalc::~depcalc() { delete ui; }

void depcalc::on_equalButton_clicked() {
  double depAmount = atof(ui->depAmountInput->text().toLocal8Bit());
  QByteArray ar = (ui->periodStartInput->text().toLocal8Bit());
  char *inputStart = ar.data();
  QByteArray ar2 = (ui->periodEndInput->text().toLocal8Bit());
  char *inputEnd = ar2.data();
  double interRate = atof(ui->interRateInput->text().toLocal8Bit());
  // double mesProc = interRate / (100 * 12);
  int payFrequencyIndex = ui->payFrequencyBox->currentIndex();
  bool capitalFlag = ui->capitalization->checkState();

  int start = ymd_to_mord(inputStart);
  int end = ymd_to_mord(inputEnd);
  int days = end - start - 1;

  qDebug() << days;
  double procents = 0;
  if (capitalFlag == false) {
    procents = (depAmount * interRate * days / 365) / 100;
    ui->AccruedIntOutput->setText(QString::number(procents));
    ui->endAmountOutput->setText(QString::number(procents + depAmount));
  } else if (payFrequencyIndex == 0) {
    procents = depAmount * pow(1 + ((interRate / 100) / 365), days);
    ui->AccruedIntOutput->setText(QString::number(procents - depAmount));
    ui->endAmountOutput->setText(QString::number(procents + depAmount));
  }

  ui->AccruedIntOutput->setText(QString::number(procents));
  ui->endAmountOutput->setText(QString::number(procents + depAmount));
}

void depcalc::on_periodStartInputButton_clicked() {
  ui->calendarWidget->show();
}

void depcalc::on_periodEndInputButton_clicked() { ui->calendarWidget->show(); }

void depcalc::on_calendarWidget_clicked(const QDate &date) {
  if (ui->periodStartInput->text().isEmpty()) {
    ui->periodStartInput->setText(date.toString("yyyy.MM.dd"));
  } else
    ui->periodEndInput->setText(date.toString("yyyy.MM.dd"));
  ui->calendarWidget->hide();
}

void depcalc::on_reset_clicked() {
  ui->depAmountInput->setText("");
  ui->periodStartInput->setText("");
  ui->periodEndInput->setText("");
  ui->interRateInput->setText("");
}
