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
  //  int data = 0;
  int days = ymd_to_mord(inputEnd) - ymd_to_mord(inputStart) - 1;
  double procents = 0;
  double payout2 = 0;
  double payout = depAmount;
  double depAmount2 = depAmount;
  int payoutCount = 0;
  int y, m, d, y1, m1, d1;
  sscanf(inputStart, "%d.%d.%d", &y, &m, &d);
  sscanf(inputEnd, "%d.%d.%d", &y1, &m1, &d1);
  QVector<QString> labels;
  labels << "Дата"
         << "Начислено процентов"
         << "Вклад пополнен"
         << "Остаток на вкладе";
  ui->tableWidget->setColumnCount(4);  // Указываем число колонок

  ui->tableWidget->setShowGrid(true);  // Включаем сетку
  ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  // Разрешаем выделение построчно
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  // Устанавливаем заголовки колонок
  ui->tableWidget->setHorizontalHeaderLabels(labels);
  // Растягиваем последнюю колонку на всё доступное пространство
  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
  //  ui->tableWidget->resizeColumnsToContents();

  if (!ui->capitalization->checkState()) {
    procents = (depAmount * interRate * days / 365) / 100;
    ui->AccruedIntOutput->setText(QString::number(procents));
    ui->endAmountOutput->setText(QString::number(depAmount));
  } else {
    switch (ui->payFrequencyBox->currentIndex()) {
      case 0:
        procents = depAmount * pow(1 + (((interRate / 100) / 12)), days / 30);
        ui->AccruedIntOutput->setText(
            QString::number(procents - depAmount, 'f', 2));
        ui->endAmountOutput->setText(
            QString::number((procents - depAmount) + depAmount, 'f', 2));
        break;
      case 1:
        procents = depAmount * pow(1 + (((interRate / 100) / 2)), days / 182);
        ui->AccruedIntOutput->setText(
            QString::number(procents - depAmount, 'f', 2));
        ui->endAmountOutput->setText(
            QString::number((procents - depAmount) + depAmount, 'f', 2));
        break;
      case 2:
        procents = depAmount * pow(1 + (((interRate / 100) / 1)), days / 365);
        payoutCount = days / 365 + 1;
        ui->tableWidget->setRowCount(payoutCount);
        ui->AccruedIntOutput->setText(QString::number(procents - depAmount));
        ui->endAmountOutput->setText(
            QString::number((procents - depAmount) + depAmount));

        for (int i = 0; i <= payoutCount; i++) {
          ui->tableWidget->setItem(
              i, 0,
              new QTableWidgetItem(QString::number(y) + '.' +
                                   QString::number(m) + '.' +
                                   QString::number(d)));
          if (i != 0)
            ui->tableWidget->setItem(
                i, 1, new QTableWidgetItem(QString::number(payout2, 'f', 2)));
          if (i != 0)
            ui->tableWidget->setItem(
                i, 2, new QTableWidgetItem(QString::number(payout2, 'f', 2)));
          else
            ui->tableWidget->setItem(
                i, 2, new QTableWidgetItem(QString::number(payout, 'f', 2)));
          ui->tableWidget->setItem(
              i, 3, new QTableWidgetItem(QString::number(depAmount2, 'f', 2)));
          depAmount2 = depAmount2 + (depAmount2 * (interRate / 100));
          payout = depAmount2 - depAmount;
          payout2 = payout - payout2;
          y++;
        }
        break;
      case 3:
        procents = (depAmount * interRate * days / 365) / 100;
        ui->AccruedIntOutput->setText(QString::number(procents));
        ui->endAmountOutput->setText(QString::number(depAmount + procents));
        payoutCount = 2;
        ui->tableWidget->setRowCount(payoutCount);
        for (int i = 0; i <= payoutCount; i++) {
          ui->tableWidget->setItem(
              i, 0,
              new QTableWidgetItem(QString::number(y) + '.' +
                                   QString::number(m) + '.' +
                                   QString::number(d)));
          if (i == 0) {
            ui->tableWidget->setItem(
                i, 2, new QTableWidgetItem(QString::number(depAmount, 'f', 2)));
            ui->tableWidget->setItem(
                i, 3, new QTableWidgetItem(QString::number(depAmount, 'f', 2)));

          } else {
            ui->tableWidget->setItem(
                i, 1, new QTableWidgetItem(QString::number(procents, 'f', 2)));

            ui->tableWidget->setItem(
                i, 2, new QTableWidgetItem(QString::number(procents, 'f', 2)));
            ui->tableWidget->setItem(i, 3,
                                     new QTableWidgetItem(QString::number(
                                         procents + depAmount, 'f', 2)));
          }

          y = y1;
          m = m1;
          d = d1;
        }
        break;
    }
  }
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
