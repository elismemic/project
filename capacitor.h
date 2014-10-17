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
    int getNominalSection();
    QString getConnectionType();
    QString getDescription();
    float getReactivePower();
    float getActivePowerLoss();


    void setName(QString a);
    void setAlias(QString a);
    void setID(int a);
    void setRatedVoltage(float a);
    void setNumberOfPhases(QString a);
    void setMinVoltage(float a);
    void setMaxVoltage(float a);
    void setNominalSection(int a);
    void setConnectionType(QString a);
    void setDescription(QString a);
    void setReactivePower(float a);
    void setActivePowerLoss(float a);

    void selectCapacitor();
    bool updateCapacitor(int id, QString name, QString aliasName, float ratedVoltage,QString numberOfPhases, QString description,
                         int nominalSection,QString connectionType,
                        float minVoltage, float maxVoltage ,
                       float reactivePower, float activePowerLoss);
    bool updateCapacitor2(int id, QString name, QString aliasName, float ratedVoltage,QString numberOfPhases, QString description,
                         int nominalSection,QString connectionType,
                        float minVoltage, float maxVoltage ,
                       float reactivePower, float activePowerLoss);
    //bool updateCapacitorNaming(int typeID,int ID, QString name, int producerID);
    bool insertJobCat(int);
    int getFlag();
    friend bool actiCap(int,int);
    friend bool editFlag(int);
    int getMinJobOfCap(int);



private slots:
    void on_capacitor_buttonBox_accepted();
    void on_capacitor_buttonBox_rejected();

private:
    Ui::Capacitor *ui;

    bool insertCapacitor(int id, QString name, QString aliasName, float ratedVoltage,QString numberOfPhases, QString description,
                         int nominalSection,QString connectionType,
                        float minVoltage, float maxVoltage ,
                       float reactivePower, float activePowerLoss);
    bool insertCapacitorNaming(int typeID,int ID, QString name, int producerID);


};

#endif // CAPACITOR_H
