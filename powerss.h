#ifndef POWERSS_H
#define POWERSS_H

#include <QMainWindow>
#include "mymodel.h"

namespace db
{
    class ISQLDatabase;
}

namespace Ui {
class PowerSS;
}

class PowerSS : public QMainWindow
{
    Q_OBJECT

public:
    explicit PowerSS(QWidget *parent = 0);
    ~PowerSS();

private slots:
    void on_actionEnergy_Consumer_triggered();

    void on_actionGenerating_Unit_triggered();

    void on_actionAsynchronous_Motor_triggered();

    void on_actionAsynchronous_Motor_Pla_triggered();

    void on_actionGenerating_Unit_Pla_triggered();

    void on_actionShunt_Resistor_Pla_triggered();

    void on_actionSearch_Jobs_triggered();

private:
    Ui::PowerSS *ui;
    bool connectSQLite();

};

#endif // POWERSS_H
