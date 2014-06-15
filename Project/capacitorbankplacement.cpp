#include "capacitorbankplacement.h"
#include "ui_capacitorbankplacement.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QMessageBox"

extern db::ISQLDatabase *pDB;
extern int searchwindowID;
extern int JobID;
CapacitorBankPlacement::CapacitorBankPlacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CapacitorBankPlacement)
   {
           ui->setupUi(this);
           this->setWindowTitle("Capacitor Bank Placement");
           if(searchwindowID != 0)
           {
            QString s = QString::number(searchwindowID);
            ui->bankplacementUID_lineEdit->setText(s);
            ui->bankplacementUID_lineEdit->setEnabled(false);
           }

   }
CapacitorBankPlacement::~CapacitorBankPlacement()
{
    delete ui;
}
//getters methods

QString CapacitorBankPlacement::getAlias()
{
    return ui->bankplacementAlias_lineEdit->text();
}

QString CapacitorBankPlacement::getName()
{
    return ui->name_lineEdit->text();
}

int CapacitorBankPlacement::getID()
{
    return ui->bankplacementUID_lineEdit->text().toInt();
}
QString CapacitorBankPlacement::getCatalogType()
{
    return ui->bankplacementCatType_comboBox->currentText();
}
QString CapacitorBankPlacement::getBankType()
{
    return ui->bankplacementBankType_comboBox->currentText();
}
QString CapacitorBankPlacement::getNLC()
{
    return ui->bankplacementNLC_comboBox->currentText();
}
QString CapacitorBankPlacement::getBankControl()
{
    return ui->bankplacementBC_comboBox->currentText();
}
QString CapacitorBankPlacement::getPhaseCode()
{
    return ui->bankplacementPC_comboBox->currentText();
}
int CapacitorBankPlacement::getNormalSection()
{
    return ui->bankplacementNS_lineEdit->text().toInt();
}
QString CapacitorBankPlacement::getLDM()
{
    return ui->bankplacementLDM_comboBox->currentText();
}
QString CapacitorBankPlacement::getDescription()
{
    return ui->bankplacementDescription_plainTextEdit->toPlainText();
}




void CapacitorBankPlacement::setAlias(QString a)
{
    ui->bankplacementAlias_lineEdit->setText(a);
}

void CapacitorBankPlacement::setName(QString a)
{
    ui->name_lineEdit->setText(a);
}

void CapacitorBankPlacement::setID(int a)
{
    QString s = QString::number(a);
    ui->bankplacementUID_lineEdit->setText(s);
}

void CapacitorBankPlacement::setNormalSection(int a)
{
    QString s = QString::number(a);
    ui->bankplacementNS_lineEdit->setText(s);
}

void CapacitorBankPlacement::setDescription(QString a)
{
    ui->bankplacementDescription_plainTextEdit->setPlainText(a);
}




bool CapacitorBankPlacement::insertCapacitorBank(int ID, QString alias, QString name,QString catalogType, QString bankType,
                                                 QString NLC, QString bankControl, QString phaseCode,
                                                 int normalSection, QString LDM, QString description )
{
    if (!pDB)
        return false;
    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refName(50);
    db::Ref<td::String> refCatalogType(50);
    db::Ref<td::String> refBankType(50);
    db::Ref<td::String> refBankControl(50);
    db::Ref<td::String> refNLC(50);
    db::Ref<td::String> refPhaseCode(50);
    db::Ref<td::String> refLDM(50);
    db::Ref<td::String> refDescription(200);


    td::String td_alias = alias.toUtf8();
    td::String td_name = name.toUtf8();
    td::String td_bankControl = bankControl.toUtf8();
    td::String td_catalogType = catalogType.toUtf8();
    td::String td_bankType = bankType.toUtf8();
    td::String td_NLC = NLC.toUtf8();
    td::String td_phaseCode = phaseCode.toUtf8();
    td::String td_LDM = LDM.toUtf8();
    td::String td_description = description.toUtf8();


    refAlias = td_alias;
    refName = td_name;
    refCatalogType = td_catalogType;
    refBankType = td_bankType;
    refBankControl = td_bankControl;
    refNLC = td_NLC;
    refPhaseCode = td_phaseCode;
    refLDM = td_LDM;
    refDescription = td_description;

    td::INT4 insert_NS(normalSection);
    td::INT4 insert_ID(ID);
    td::INT4 insert_JobID(JobID);
    td::INT4 insert_SystemID(1);
    td::INT4 insert_TypeID(38);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO CapacitorBankPlacement(SystemID,JobID,TypeID,ID,Alias,Name,CatalogType, BankType, NoLoadControl, BankControl, PhaseCode, NormalSection, LoadDemandModel, Description) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_SystemID << insert_JobID << insert_TypeID << insert_ID << refAlias << refName << refCatalogType << refBankType << refNLC << refBankControl << refPhaseCode
           << insert_NS << refLDM << refDescription;


    if (!pStat->execute())
    {
        td::String strErr;
        pStat->getErrorStr(strErr);
        if (DebugTrace(1000))
            mu::getTracer() << strErr;
        //rollback will be called
        return false;
    }

    //commit transaction
    bool  bRet = trans.commit();
    if (bRet)
         QMessageBox::information(this,"Database Info","Data Inserted");

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}







void CapacitorBankPlacement::on_capacitorbankplacement_buttonBox_accepted()
{
    if(searchwindowID != 0)
    {

        insertCapacitorBank(searchwindowID,getAlias(), getName(),getCatalogType(), getBankType(), getNLC(),
                                                        getBankControl(), getPhaseCode(), getNormalSection(),
                                                      getLDM(), getDescription() );

        close();
    }
    else
    {
        insertCapacitorBank(getID(),getAlias(), getName(),getCatalogType(), getBankType(), getNLC(),
                                                        getBankControl(), getPhaseCode(), getNormalSection(),
                                                      getLDM(), getDescription() );

        close();
    }


}

void CapacitorBankPlacement::on_capacitorbankplacement_buttonBox_rejected()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Discard","Are you sure you want to discard all changes made?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        close();
    }
}
