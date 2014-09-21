#include "capacitorbankplacement.h"
#include "ui_capacitorbankplacement.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mymodel.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QMessageBox"

extern db::ISQLDatabase *pDB;
extern int searchwindowID;
extern int searchwindowJobID;
extern int JobID;
extern bool editable;
extern bool editClicked;
CapacitorBankPlacement::CapacitorBankPlacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CapacitorBankPlacement)
   {

           ui->setupUi(this);
           ui->bankplacementSID_lineEdit->setText("2");
           ui->bankplacementSID_lineEdit->setEnabled(false);
           this->setWindowTitle("Capacitor Bank Placement");
           if(editClicked == true)
           {
            QString s = QString::number(searchwindowID);
            ui->bankplacementUID_lineEdit->setText(s);
            ui->bankplacementUID_lineEdit->setEnabled(false);
            selectBankPlacement();
            editClicked = false;
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

void CapacitorBankPlacement::setCatalogType(QString a)
{
    ui->bankplacementCatType_comboBox->setCurrentText(a);
}

void CapacitorBankPlacement::setBankType(QString a)
{
    ui->bankplacementBankType_comboBox->setCurrentText(a);
}

void CapacitorBankPlacement::setNLC(QString a)
{
    ui->bankplacementNLC_comboBox->setCurrentText(a);
}

void CapacitorBankPlacement::setBankControl(QString a)
{
    ui->bankplacementBC_comboBox->setCurrentText(a);
}

void CapacitorBankPlacement::setPhaseCode(QString a)
{
    ui->bankplacementPC_comboBox->setCurrentText(a);
}

void CapacitorBankPlacement::setLDM(QString a)
{
    ui->bankplacementLDM_comboBox->setCurrentText(a);
}

void CapacitorBankPlacement::selectBankPlacement()
{
    td::INT4 insert_ID(searchwindowID);
    td::INT4 insert_JobID(searchwindowJobID);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_SELECT,
       "Select Alias,Name,CatalogType,BankType,NoLoadControl,BankControl,PhaseCode,NormalSection,LoadDemandModel,Description FROM CapacitorBankPlacement WHERE ID = ? AND JobID = ?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_ID << insert_JobID;


    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(10);
        columns[0].name = "Alias";
        columns[0].tdType = td::nch;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 0;

        columns[2].name = "CatalogType";
        columns[2].tdType = td::nch;
        columns[2].len = 0;

        columns[3].name = "BankType";
        columns[3].tdType = td::nch;
        columns[3].len = 0;

        columns[4].name = "NoLoadControl";
        columns[4].tdType = td::nch;
        columns[4].len = 0;

        columns[5].name = "BankControl";
        columns[5].tdType = td::nch;
        columns[5].len = 0;

        columns[6].name = "PhaseCode";
        columns[6].tdType = td::nch;
        columns[6].len = 0;

        columns[7].name = "NormalSection";
        columns[7].tdType = td::int4;
        columns[7].len = 0;

        columns[8].name = "LoadDemandModel";
        columns[8].tdType = td::nch;
        columns[8].len = 0;

        columns[9].name = "Description";
        columns[9].tdType = td::nch;
        columns[9].len = 0;



        db::Recordset* rs = new db::Recordset(columns);

        if (!rs->load(pStat.getPtr()))
            exit(0);

        MyModel *model = new MyModel(this, rs, true);

        QModelIndex idx = model->index(0,0);
            QString alias = model->data(idx, Qt::DisplayRole).toString();
            setAlias(alias);

            idx = model->index(0,1);
            QString name = model->data(idx, Qt::DisplayRole).toString();
            setName(name);

            idx = model->index(0,2);
            QString catType = model->data(idx, Qt::DisplayRole).toString();
            setCatalogType(catType);

            idx = model->index(0,3);
            QString bankType = model->data(idx, Qt::DisplayRole).toString();
            setBankType(bankType);

            idx = model->index(0,4);
            QString NLC = model->data(idx, Qt::DisplayRole).toString();
            setNLC(NLC);

            idx = model->index(0,5);
            QString bankControl = model->data(idx, Qt::DisplayRole).toString();
            setBankControl(bankControl);

            idx = model->index(0,6);
            QString phaseCode = model->data(idx, Qt::DisplayRole).toString();
            setPhaseCode(phaseCode);

            idx = model->index(0,7);
            int normalSection = model->data(idx, Qt::DisplayRole).toInt();
            setNormalSection(normalSection);

            idx = model->index(0,8);
            QString ldm = model->data(idx, Qt::DisplayRole).toString();
            setLDM(ldm);

            idx = model->index(0,9);
            QString description = model->data(idx, Qt::DisplayRole).toString();
            setDescription(description);
}

bool CapacitorBankPlacement::updateCapacitorBank(int ID, QString alias, QString name,QString catalogType, QString bankType,
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
    td::INT4 insert_JobID(22);
    td::INT4 insert_SystemID(1);
    td::INT4 insert_TypeID(38);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE CapacitorBankPlacement SET SystemID=?,JobID=?,TypeID=?,Alias=?,Name=?,CatalogType=?, BankType=?, NoLoadControl=?, BankControl=?, PhaseCode=?, NormalSection=?, LoadDemandModel=?, Description=? WHERE ID=?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_SystemID << insert_JobID << insert_TypeID << refAlias << refName << refCatalogType << refBankType << refNLC << refBankControl << refPhaseCode
           << insert_NS << refLDM << refDescription << insert_ID;


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
         QMessageBox::information(this,"Database Info","Data Updated");

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}



bool CapacitorBankPlacement::updateCapBankNaming(int systemID,int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(38);
    td::INT4 insert_SystemID(1);
    td::INT4 insert_ID(id);
    td::INT4 insert_producerID(producerID);

    db::Ref<td::String> refName(50);
    td::String td_name = name.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE PlacementNaming SET SystemID=?,TypeID=?,Name=?,ProducerID=? WHERE ID=?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_SystemID << insert_TypeID << refName << insert_producerID << insert_ID;


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

    if (DebugTrace(1000))
        mu::getTracer() << "Update finished!\n";
    return bRet;
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



bool CapacitorBankPlacement::insertCapBankNaming(int systemID,int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(38);
    td::INT4 insert_SystemID(1);
    td::INT4 insert_ID(id);
    td::INT4 insert_producerID(producerID);

    db::Ref<td::String> refName(50);
    td::String td_name = name.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO PlacementNaming(SystemID,TypeID,ID,Name,ProducerID) VALUES (?,?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_SystemID << insert_TypeID << insert_ID << refName << insert_producerID;


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

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}



void CapacitorBankPlacement::on_capacitorbankplacement_buttonBox_accepted()
{
    if(searchwindowID != 0)
    {
        if(updateCapBankNaming(1,38,searchwindowID,getName(),1))
    {
        updateCapacitorBank(searchwindowID,getAlias(), getName(),getCatalogType(), getBankType(), getNLC(),
                                                        getBankControl(), getPhaseCode(), getNormalSection(),
                                                      getLDM(), getDescription());

        close();
    }
        else
        {
             QMessageBox::information(this,"Information","Could not update data!");
        }
    }
    else
    {
        if(insertCapBankNaming(1,38,getID(),getName(),1))
        {
        insertCapacitorBank(getID(),getAlias(), getName(),getCatalogType(), getBankType(), getNLC(),
                                                        getBankControl(), getPhaseCode(), getNormalSection(),
                                                      getLDM(), getDescription() );   
        close();
        }
        else
        {
        QMessageBox::information(this,"Information","Could not insert data - ID already exists!");
        }
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
