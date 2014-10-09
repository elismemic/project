#include "reactorbankplacement.h"
#include "ui_reactorbankplacement.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QMessageBox"

extern  db::ISQLDatabase *pDB;
extern int JobID;
extern int searchwindowID;
extern int searchwindowJobID ;

ReactorBankPlacement::ReactorBankPlacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReactorBankPlacement)
{   //form setup
    ui->setupUi(this);
    this->setWindowTitle("Reactor Bank Placement");
    if(searchwindowID != 0)
    {
               QString s = QString::number(searchwindowID);
               ui->reactorBPUID_lineEdit->setText(s);
               ui->reactorBPUID_lineEdit->setEnabled(false);
    }
    if(searchwindowJobID != JobID)
       {
        ui->reactorBPButtons_buttonBox->setEnabled(false);
    }


}
//dealocates memory destructor
ReactorBankPlacement::~ReactorBankPlacement()
{
    delete ui;
}

//implementation of getters
int ReactorBankPlacement::getID()
{
    return ui->reactorBPUID_lineEdit->text().toInt();
}

QString ReactorBankPlacement::getName()
{
    return ui->reactorBPName_lineEdit->text();
}

QString ReactorBankPlacement::getAlias()
{
    return ui->reactorBPAlias_lineEdit->text();
}

QString ReactorBankPlacement::getCatalogType()
{
    return ui->reactorBPCatType_comboBox->currentText();
}

QString ReactorBankPlacement::getBankType()
{
    return ui->reactorBPBankType_comboBox->currentText();
}

QString ReactorBankPlacement::getDescription()
{
    return ui->reactorBPDescription_textEdit->toPlainText();
}

QString ReactorBankPlacement::getNoLoadControl()
{
    return ui->reactorBPNLC_comboBox->currentText();
}

QString ReactorBankPlacement::getBankControl()
{
    return ui->reactorBPBC_comboBox->currentText();
}

QString ReactorBankPlacement::getPhaseCode()
{
    return ui->reactorBPPC_comboBox->currentText();
}



int ReactorBankPlacement::getNormalSection()
{
    return ui->reactorBPNormSect_lineEdit->text().toInt();
}

QString ReactorBankPlacement::getLoadDemandModel()
{
    return ui->reactorBPLDM_comboBox->currentText();
}

int ReactorBankPlacement::getSystemID()

{
    return ui->reactorBPsystemID_lineEdit->text().toInt();
}



//inserts data to reactor placement
bool ReactorBankPlacement::insertReactorBankPlacement
(QString description,QString name,QString alias, QString catalogType, QString bankType,
                                                      QString noLoadControl, QString bankControl,
                                                     QString phaseCode, int normalSection, QString loadDemandModel,int ID,int SystemID)
{

    if (!pDB)
        return false;

    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refName(50);
    db::Ref<td::String> refCatalogType(50);
    db::Ref<td::String> refBankType(50);
    db::Ref<td::String> refDescription(200);
    db::Ref<td::String> refNoLoadControl(50);
    db::Ref<td::String> refBankControl(50);
    db::Ref<td::String> refPhaseCode(50);
    db::Ref<td::String> refLoadDemandModel(50);


    td::String td_alias = alias.toUtf8();    
    td::String td_name = name.toUtf8();
    td::String td_catalogType = catalogType.toUtf8();
    td::String td_bankType = bankType.toUtf8();
    td::String td_description = description.toUtf8();
    td::String td_noLoadControl = noLoadControl.toUtf8();
    td::String td_bankControl = bankControl.toUtf8();
    td::String td_phaseCode = phaseCode.toUtf8();
    td::String td_loadDemandModel = loadDemandModel.toUtf8();


    refAlias = td_alias;
    refName = td_name;
    refCatalogType = td_catalogType;
    refBankType = td_bankType;
    refDescription = td_description;
    refNoLoadControl = td_noLoadControl;
    refBankControl = td_bankControl;
    refPhaseCode = td_phaseCode;
    refLoadDemandModel = td_loadDemandModel;


    td::INT4 insertNormalSection(normalSection);
    td::INT4 insertJobID(JobID);
    td::INT4 insertSystemID(SystemID);
    td::INT4 insertTypeID(36);
    td::INT4 insertID(ID);


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO PlacementReactorBank(Description,Name,Alias,CatalogType,BankType,NoLoadControl,BankControl,PhaseCode,NormalSection,LoadDemandModel,JobID,TypeID,ID,SystemID) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refDescription << refName << refAlias << refCatalogType << refBankType << refNoLoadControl <<
              refBankControl << refPhaseCode << insertNormalSection << refLoadDemandModel
              << insertJobID << insertTypeID << insertID << insertSystemID
              ;


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
        QMessageBox::information(this,"Info","Data inserted");

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;


}


bool ReactorBankPlacement::updateReactorBankPlacement
(QString description,QString name,QString alias, QString catalogType, QString bankType,
                                                      QString noLoadControl, QString bankControl,
                                                     QString phaseCode, int normalSection, QString loadDemandModel,int ID,int SystemID)
{

    if (!pDB)
        return false;

    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refName(50);
    db::Ref<td::String> refCatalogType(50);
    db::Ref<td::String> refBankType(50);
    db::Ref<td::String> refDescription(200);
    db::Ref<td::String> refNoLoadControl(50);
    db::Ref<td::String> refBankControl(50);
    db::Ref<td::String> refPhaseCode(50);
    db::Ref<td::String> refLoadDemandModel(50);


    td::String td_alias = alias.toUtf8();
    td::String td_name = name.toUtf8();
    td::String td_catalogType = catalogType.toUtf8();
    td::String td_bankType = bankType.toUtf8();
    td::String td_description = description.toUtf8();
    td::String td_noLoadControl = noLoadControl.toUtf8();
    td::String td_bankControl = bankControl.toUtf8();
    td::String td_phaseCode = phaseCode.toUtf8();
    td::String td_loadDemandModel = loadDemandModel.toUtf8();


    refAlias = td_alias;
    refName = td_name;
    refCatalogType = td_catalogType;
    refBankType = td_bankType;
    refDescription = td_description;
    refNoLoadControl = td_noLoadControl;
    refBankControl = td_bankControl;
    refPhaseCode = td_phaseCode;
    refLoadDemandModel = td_loadDemandModel;


    td::INT4 insertNormalSection(normalSection);
    td::INT4 insertJobID(JobID);
    td::INT4 insertSystemID(SystemID);
    td::INT4 insertTypeID(36);
    td::INT4 insertID(ID);


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "UPDATE PlacementReactorBank SET Description=?,Name=?,Alias=?,CatalogType=?,BankType=?,NoLoadControl=?,BankControl=?,PhaseCode=?,NormalSection=?,LoadDemandModel=?,JobID=?,TypeID=?,SystemID=? WHERE ID=?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refDescription << refName << refAlias << refCatalogType << refBankType << refNoLoadControl <<
              refBankControl << refPhaseCode << insertNormalSection << refLoadDemandModel
              << insertJobID << insertTypeID << insertSystemID << insertID
              ;


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
        QMessageBox::information(this,"Info","Data updated");

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;


}



void ReactorBankPlacement::on_reactorBPButtons_buttonBox_accepted()
{

    if(searchwindowID != 0)
        {
            if(updatePlacNaming(36, searchwindowID,getName(),2))
            {
                updateReactorBankPlacement(getDescription(),getName(),getAlias(), getCatalogType(), getBankType(),
                                           getNoLoadControl(), getBankControl(),
                                          getPhaseCode(), getNormalSection(), getLoadDemandModel(),getID(),getSystemID());
            close();
            }

         else
         {
               QMessageBox::information(this,"Info","ID already exists");
         }
    }
    else
    {
        if(insertPlacNaming(36, getID(),getName(),2))
        {
            insertReactorBankPlacement(getDescription(),getName(),getAlias(), getCatalogType(), getBankType(),
                                       getNoLoadControl(), getBankControl(),
                                      getPhaseCode(), getNormalSection(), getLoadDemandModel(),getID(),getSystemID());
        close();
        }

     else
     {
           QMessageBox::information(this,"Info","ID already exists");
     }

    }



}

void ReactorBankPlacement::on_reactorBPButtons_buttonBox_rejected()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Discard","Are you sure you want to discard all changes made?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            close();
        }
}


bool ReactorBankPlacement::insertPlacNaming(int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(36);
    td::INT4 insert_ID(id);
    td::INT4 insert_producerID(producerID);

    db::Ref<td::String> refName(50);
    td::String td_name = name.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO PlacementNaming(SystemID,TypeID,ID,Name,ProducerID) VALUES (2,?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_TypeID << insert_ID << refName << insert_producerID;


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




bool ReactorBankPlacement::updatePlacNaming(int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(36);
    td::INT4 insert_ID(id);
    td::INT4 insert_producerID(producerID);

    db::Ref<td::String> refName(50);
    td::String td_name = name.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "UPDATE PlacementNaming SET SystemID=2,TypeID=?,Name=?,ProducerID=? WHERE ID=?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_TypeID << refName << insert_producerID << insert_ID ;


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


