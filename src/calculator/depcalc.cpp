#include "depcalc.h"
#include "ui_depcalc.h"

depcalc::depcalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::depcalc)
{
    ui->setupUi(this);
}

depcalc::~depcalc()
{
    delete ui;
}
