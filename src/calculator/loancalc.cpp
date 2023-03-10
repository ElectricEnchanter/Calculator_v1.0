#include "loancalc.h"

#include "QDebug"
#include "ui_loancalc.h"

loanCalc::loanCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::loanCalc) {
  ui->setupUi(this);

  QLinearGradient gradient(0, 0, 0, 400);
  gradient.setColorAt(0, QColor(90, 90, 90));
  gradient.setColorAt(0.38, QColor(105, 105, 105));
  gradient.setColorAt(1, QColor(70, 70, 70));
  ui->widget->setBackground(QBrush(gradient));
}

loanCalc::~loanCalc() { delete ui; }

void loanCalc::on_equal_clicked() {
  ui->widget->clearGraphs();
  QVector<double> ticks;
  QVector<QString> labels;

  double restSumd = atof(ui->inputSum->text().toLocal8Bit());
  int month = atof(ui->inputTerm->text().toLocal8Bit());
  double stavka = atof(ui->intputRate->text().toLocal8Bit());

  int newIndex = ui->inputPayType->currentIndex();

  double rest = loan(restSumd, month, stavka, newIndex);
  double loanOverpay = loanOverpayment(rest, month, stavka, restSumd, newIndex);

  ui->outputMonPay->setText(QString::number(rest));
  ui->outputAccrInter->setText(QString::number(loanOverpay));

  double SumDebtInter = restSumd + loanOverpay;
  ui->outputSumDebtInter->setText(QString::number(SumDebtInter));

  // create empty bar chart objects:
  QCPBars *procents = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
  QCPBars *restSum = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
  procents->setAntialiased(false);
  restSum->setAntialiased(false);

  procents->setStackingGap(1);
  restSum->setStackingGap(1);
  // set names and colors:
  restSum->setName("Основной долг");
  restSum->setPen(QPen(QColor(111, 9, 176).lighter(170)));
  restSum->setBrush(QColor(111, 9, 176));
  procents->setName("Проценты");
  procents->setPen(QPen(QColor(250, 170, 20).lighter(150)));
  procents->setBrush(QColor(250, 170, 20));

  // stack bars on top of each other:
  procents->moveAbove(restSum);

  // prepare x axis with country labels:
  QVector<QString> stroka;
  stroka << "-й месяц";
  ticks << 1 << 2;  //тут вектор даблов
  labels << "Январь"
         << "Февраль"
         << "Март"
         << "Апрель"
         << "Май"
         << "Июнь"
         << "Июль";
  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
  textTicker->addTicks(QVector<double>(month),
                       labels + stroka);  // тут собоставление по числам и
                                          // названиям думал плюсовать строки
  ui->widget->xAxis->setTicker(textTicker);
  ui->widget->xAxis->setTickLabelRotation(60);
  ui->widget->xAxis->setSubTicks(false);
  ui->widget->xAxis->setTickLength(0, 4);
  ui->widget->xAxis->setRange(0, 8);
  ui->widget->xAxis->setBasePen(QPen(Qt::white));
  ui->widget->xAxis->setTickPen(QPen(Qt::white));
  ui->widget->xAxis->grid()->setVisible(true);
  ui->widget->xAxis->grid()->setPen(
      QPen(QColor(130, 130, 130), 0, Qt::DotLine));
  ui->widget->xAxis->setTickLabelColor(Qt::white);
  ui->widget->xAxis->setLabelColor(Qt::white);

  // prepare y axis:
  ui->widget->yAxis->setRange(0, SumDebtInter);
  ui->widget->yAxis->setPadding(5);  // a bit more space to the left border
  ui->widget->yAxis->setLabel("Ежемесячный платеж");
  ui->widget->yAxis->setBasePen(QPen(Qt::white));
  ui->widget->yAxis->setTickPen(QPen(Qt::white));
  ui->widget->yAxis->setSubTickPen(QPen(Qt::white));
  ui->widget->yAxis->grid()->setSubGridVisible(true);
  ui->widget->yAxis->setTickLabelColor(Qt::white);
  ui->widget->yAxis->setLabelColor(Qt::white);
  ui->widget->yAxis->grid()->setPen(
      QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
  ui->widget->yAxis->grid()->setSubGridPen(
      QPen(QColor(130, 130, 130), 0, Qt::DotLine));

  // Add data:
  QVector<double> restSumData, procentsData;
  restSumData << 4000 << 22222;
  procentsData << 4000 << 3333;
  restSum->setData(ticks, restSumData);
  procents->setData(ticks, procentsData);

  // setup legend:
  ui->widget->legend->setVisible(true);
  ui->widget->axisRect()->insetLayout()->setInsetAlignment(
      0, Qt::AlignTop | Qt::AlignHCenter);
  ui->widget->legend->setBrush(QColor(255, 255, 255, 100));
  ui->widget->legend->setBorderPen(Qt::NoPen);
  QFont legendFont = font();
  legendFont.setPointSize(10);
  ui->widget->legend->setFont(legendFont);
  ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
