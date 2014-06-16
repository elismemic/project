#ifndef REACTORBANKPLACEMENT_H
#define REACTORBANKPLACEMENT_H

#include <QDialog>

namespace Ui {
class ReactorBankPlacement;
}

//forward declaration (.h)
namespace db
{
    class ISQLDatabase;
}

class ReactorBankPlacement : public QDialog
{
    Q_OBJECT

public:
    explicit ReactorBankPlacement(QWidget *parent = 0);
    ~ReactorBankPlacement();

    //getter methods
    int getID();
    int getSystemID();
    QString getName();
    QString getAlias();
    QString getCatalogType();
    QString getBankType();
    QString getDescription();
    QString getNoLoadControl();
    QString getBankControl();
    QString getPhaseCode();
    int getNormalSection();
    QString getLoadDemandModel();




//slot
private slots:
    void on_reactorBPButtons_buttonBox_accepted();

    void on_reactorBPButtons_buttonBox_rejected();

private:
    //pointer to form
    Ui::ReactorBankPlacement *ui;




    //inserting into the db table
    bool insertReactorBankPlacement(QString description,QString name,QString alias, QString catalogType, QString bankType,
                                     QString noLoadControl, QString bankControl,
                                    QString phaseCode, int normalSection, QString loadDemandModel,int ID,int SystemID);




};

#endif // REACTORBANKPLACEMENT_H
