#ifndef REACTORCATALOG_H
#define REACTORCATALOG_H

#include <QDialog>

namespace Ui {
class ReactorCatalog;
}

namespace db
{
    class ISQLDatabase;
}

class ReactorCatalog : public QDialog
{
    Q_OBJECT

public:
    explicit ReactorCatalog(QWidget *parent = 0);
    ~ReactorCatalog();

    //getter methods
    QString getAlias();
    QString getName();
    int getID();
    float getRatedVoltage();
    float getMaximumVoltage();
    QString getDescription();
    QString getNumberOfPhases();
    QString getConnectionType();
    int getNominalSection();
    float getNominalCurrent();
    float getMinimumVoltage();
    float getReactivePower();
    float getActivePowerLoss();

    void setAlias();
    void setName();
    void setID();
    void setRatedVoltage();
    void setMaximumVoltage();
    void setDescription();
    void setNumberOfPhases();
    void setConnectionType();
    void setNominalSection();
    void setMinimumVoltage();
private slots:
    void on_reactorButtons_buttonBox_accepted();

    void on_reactorButtons_buttonBox_rejected();

private:
    Ui::ReactorCatalog *ui;

    bool insertReactorCatalog(QString description, int ID,  QString alias,QString connectionType,QString numberOfPhases,
                              float ratedVoltage, float maximumVoltage,float minimumVoltage,int nominalSection,
                             float reactivePower, float activePowerLoss,float nominalCurrent, QString name
                               );




};

#endif // REACTORCATALOG_H
