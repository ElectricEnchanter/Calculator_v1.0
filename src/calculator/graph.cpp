#include "graph.h"

#include "ui_graph.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);

  h = 0.0001;

  ui->widget->xAxis->setRange(-15, 15);
  ui->widget->yAxis->setRange(-15, 15);

  ui->widget->addGraph();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

Dialog::~Dialog() { delete ui; }

void Dialog::on_build_clicked() {
  int err = 0;
  QByteArray sstr = ui->input->text().toLocal8Bit();
  char *input = sstr.data();
  if (*input == '\0') err = 8;
  QByteArray ssstr = ui->Xinput->text().toLocal8Bit();
  double Dot = atof(ssstr);

  Numbers *NumHead = NULL;
  Operations *OpHead = NULL;
  char output[255] = {""};

  if (err == 0) err = Validator(input, output);
  ui->widget->xAxis->setRange(-Dot, Dot);
  ui->widget->yAxis->setRange(-Dot, Dot);
  ui->widget->clearGraphs();
  x.clear();
  y.clear();

  if (err == 0 && Dot != 0) {
    for (X = -Dot; X <= fabs(Dot); X += h) {
      double num = Count(output, &NumHead, &OpHead, X);
      x.push_back(X);
      y.push_back(num);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDot, Qt::red, Qt::red, 30));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
  } else if (err == 1)
    ui->input->setText("Нет числа после точки или 2 точки в числе");
  else if (err == 2)
    ui->input->setText("Не правильное количество скобок");
  else if (err == 3)
    ui->input->setText("Скобки пустые");
  else if (err == 4)
    ui->input->setText("После знака нет числа");
  else if (err == 5)
    ui->input->setText("X не число");
  else if (err == 6 || Dot == 0)
    ui->input->setText("Запись не имеет смысла");
  else if (err == 10 || Dot == 0)
    ui->input->setText("INVALID CHARACTER(S)");
}

void Dialog::on_pushButton_clicked() {
  ui->input->setText("");
  ui->Xinput->setText("");
}

void Dialog::on_exit_clicked() { this->close(); }
