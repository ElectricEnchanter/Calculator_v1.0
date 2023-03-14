#ifndef DEPCALC_H
#define DEPCALC_H

#include <QMainWindow>

namespace Ui {
class depcalc;
}

class depcalc : public QMainWindow
{
    Q_OBJECT

public:
    explicit depcalc(QWidget *parent = nullptr);
    ~depcalc();

private:
    Ui::depcalc *ui;
};

#endif // DEPCALC_H
