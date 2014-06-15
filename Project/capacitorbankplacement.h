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




private slots:
    void on_capacitorbankplacement_buttonBox_accepted();

    void on_capacitorbankplacement_buttonBox_rejected();

private:
    Ui::CapacitorBankPlacement *ui;

    bool insertCapacitorBank(int ID, QString alias, QString name,QString catalogType, QString bankType, QString NLC,QString bankControl, QString phaseCode, int normalSection, QString LDM, QString description);

};

#endif // CAPACITORBANKPLACEMENT_H
