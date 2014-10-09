#ifndef CAPACITORBANKPLACEMENT_H
#define CAPACITORBANKPLACEMENT_H

#include <QDialog>
namespace Ui {
class CapacitorBankPlacement;
}

namespace db
{
    class ISQLDatabase;
}

class CapacitorBankPlacement : public QDialog
{
    Q_OBJECT

public:
    explicit CapacitorBankPlacement(QWidget *parent = 0);
    ~CapacitorBankPlacement();
    QString getAlias();
    QString getName();
    int getID();
    QString getCatalogType();
    QString getBankType();
    QString getNLC();
    QString getBankControl();
    QString getPhaseCode();
    int getNormalSection();
    QString getLDM();
    QString getDescription();



    void setAlias(QString a);
    void setName(QString a);
    void setID(int a);
    void setNormalSection(int a);
    void setDescription(QString a);
    void setCatalogType(QString a);
    void setBankType(QString a);
    void setNLC(QString a);
    void setBankControl(QString a);
    void setPhaseCode(QString a);
    void setLDM(QString a);

    void selectBankPlacement();


private slots:
    void on_capacitorbankplacement_buttonBox_accepted();

    void on_capacitorbankplacement_buttonBox_rejected();

private:
    Ui::CapacitorBankPlacement *ui;

    bool insertCapacitorBank(int ID, QString alias, QString name,QString catalogType, QString bankType, QString NLC,QString bankControl, QString phaseCode, int normalSection, QString LDM, QString description);
    bool insertCapBankNaming(int systemID,int typeID,int ID, QString name, int producerID);

    bool updateCapacitorBank(int ID, QString alias, QString name,QString catalogType, QString bankType, QString NLC,QString bankControl, QString phaseCode, int normalSection, QString LDM, QString description);
    bool updateCapBankNaming(int systemID,int typeID,int ID, QString name, int producerID);
};

#endif // CAPACITORBANKPLACEMENT_H
