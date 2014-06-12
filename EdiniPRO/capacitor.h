#ifndef CAPACITOR_H
#define CAPACITOR_H

#include <QDialog>

namespace Ui {
class Capacitor;
}

namespace db
{
    class ISQLDatabase;
}

class Capacitor : public QDialog
{
    Q_OBJECT

public:
    explicit Capacitor(QWidget *parent = 0);
    ~Capacitor();
    QString getName();
    QString getAlias();
    int getID();
    float getRatedVoltage();
    QString getNumberOfPhases();
    float getMinVoltage();
    float getMaxVoltage();
    float getNominalSection();
    QString getConnectionType();
    QString getDescription();
    float getReactivePower();
    float getActivePowerLoss();


private slots:
    void on_capacitor_buttonBox_accepted();

private:
    Ui::Capacitor *ui;
    db::ISQLDatabase *pDB;

    bool connectSQLite();
    bool insertCapacitor(QString alias, float ratedVoltage, QString noOfPhases,
                        float minVoltage, float maxVoltage, float nominalSection, QString connectionType, QString description,
                       float reactivePower, float activePowerLoss);
    bool insertNaming(QString name);
    bool insertID(int id);
};

#endif // CAPACITOR_H
