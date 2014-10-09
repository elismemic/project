#include "reactorcatalog.h"
#include "ui_reactorcatalog.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mymodel.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QMessageBox"
#include "QFileDialog"

extern  db::ISQLDatabase *pDB;
extern int JobID;
extern int searchwindowID;
extern int searchwindowJobID ;

ReactorCatalog::ReactorCatalog(QWidget *parent) :
 QDialog(parent),
 ui(new Ui::ReactorCatalog)
{
        ui->setupUi(this);
        this->setWindowTitle("Reactor Catalog");
        if(searchwindowID != 0)
        {
                   QString s = QString::number(searchwindowID);
                   ui->reactorID_lineEdit->setText(s);
                   ui->reactorID_lineEdit->setEnabled(false);
        }
        if(searchwindowJobID != JobID)
           {
            ui->reactorButtons_buttonBox->setEnabled(false);
        }

}

ReactorCatalog::~ReactorCatalog()
{
    delete ui;
}

QString ReactorCatalog::getName()
{
    return ui->reactorName_lineEdit->text();
}

int ReactorCatalog::getID()
{
    return ui->reactorID_lineEdit->text().toInt();
}

QString ReactorCatalog::getAlias()
{
    return ui->reactorAlias_lineEdit->text();
}

float ReactorCatalog::getRatedVoltage()
{
    return ui->reactorRatedVoltage_comboBox->currentText().toFloat();
}

float ReactorCatalog::getMaximumVoltage()
{
    return ui->reactorMaxVoltage_lineEdit->text().toFloat();
}
\
QString ReactorCatalog::getDescription()
{
    return ui->reactorDescription_plainTextEdit->toPlainText();
}

QString ReactorCatalog::getNumberOfPhases()
{
    return ui->reactorNumPhases_comboBox->currentText();
}

QString ReactorCatalog::getConnectionType()
{
    return ui->reactorConnectionType_comboBox->currentText();
}

int ReactorCatalog::getNominalSection()
{
    return ui->reactorNominalSection_lineEdit->text().toInt();
}

float ReactorCatalog:: getNominalCurrent()
{
   return ui->reactorNominalCurrent_lineEdit->text().toFloat();
}


float ReactorCatalog::getMinimumVoltage()
{
    return ui->reactorMinVoltage_lineEdit->text().toFloat();
}

float ReactorCatalog::getReactivePower()
{
    return ui->reactorReactivePower_lineEdit->text().toFloat();
}
float ReactorCatalog::getActivePowerLoss()
{
    return ui->reactorActivePowerLoss_lineEdit->text().toFloat();
}

void ReactorCatalog::setName()
{
     ui->reactorName_lineEdit->setText("");
}

void ReactorCatalog::setID()
{
     ui->reactorID_lineEdit->setText("");
}

void ReactorCatalog::setAlias()
{
     ui->reactorAlias_lineEdit->setText("");
}

void ReactorCatalog::setRatedVoltage()
{
     ui->reactorRatedVoltage_comboBox->setCurrentText("");
}

void ReactorCatalog::setMaximumVoltage()
{
     ui->reactorMaxVoltage_lineEdit->setText("");
}

void ReactorCatalog::setDescription()
{
     ui->reactorDescription_plainTextEdit->setPlainText("");
}

void ReactorCatalog::setNumberOfPhases()
{
     ui->reactorNumPhases_comboBox->setCurrentText("");
}

void ReactorCatalog::setConnectionType()
{
     ui->reactorConnectionType_comboBox->setCurrentText("");
}

void ReactorCatalog::setNominalSection()
{
     ui->reactorNominalSection_lineEdit->setText("");
}

void ReactorCatalog::setMinimumVoltage()
{
     ui->reactorMinVoltage_lineEdit->setText("");
}





bool ReactorCatalog::insertReactorCatalog(QString description, int ID,  QString alias,QString connectionType,QString numberOfPhases,
                                          float ratedVoltage, float maximumVoltage,float minimumVoltage,int nominalSection,
                                         float reactivePower, float activePowerLoss,float nominalCurrent, QString name)
{
    if (!pDB)
        return false;
    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refName(50);
    db::Ref<td::String> refConnectionType(50);
    db::Ref<td::String> refnoOfPhases(50);
    db::Ref<td::String> refDescription(200);

    td::String td_alias = alias.toUtf8();
    td::String td_connectionType = connectionType.toUtf8();
    td::String td_numberOfPhases = numberOfPhases.toUtf8();
    td::String td_description = description.toUtf8();
    td::String td_name = name.toUtf8();

    refAlias = td_alias;
    refConnectionType = td_connectionType;
    refnoOfPhases = td_numberOfPhases;
    refDescription = td_description;
    refName = td_name;

    td::INT4 insert_ID(ID);
    td::INT4 insert_JobID(JobID);
    td::INT4 insert_TypeID(6);
    td::INT4 insert_nominalSection(nominalSection);


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO CatalogReactor(Description,JobID,TypeID,ID,Alias,ConnectionType,NumberOfPhases,RatedVoltage,MaxVoltage,MinVoltage,NominalSection,ReactivePower,ActivePowerLoss,NominalCurrent,Name) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refDescription << insert_JobID << insert_TypeID << insert_ID << refAlias << refConnectionType
           << refnoOfPhases << ratedVoltage << maximumVoltage << minimumVoltage << insert_nominalSection << reactivePower
              << activePowerLoss << nominalCurrent << refName;


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



bool ReactorCatalog::updateReactorCatalog(QString description, int ID,  QString alias,QString connectionType,QString numberOfPhases,
                                          float ratedVoltage, float maximumVoltage,float minimumVoltage,int nominalSection,
                                         float reactivePower, float activePowerLoss,float nominalCurrent, QString name)
{
    if (!pDB)
        return false;
    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refName(50);
    db::Ref<td::String> refConnectionType(50);
    db::Ref<td::String> refnoOfPhases(50);
    db::Ref<td::String> refDescription(200);

    td::String td_alias = alias.toUtf8();
    td::String td_connectionType = connectionType.toUtf8();
    td::String td_numberOfPhases = numberOfPhases.toUtf8();
    td::String td_description = description.toUtf8();
    td::String td_name = name.toUtf8();

    refAlias = td_alias;
    refConnectionType = td_connectionType;
    refnoOfPhases = td_numberOfPhases;
    refDescription = td_description;
    refName = td_name;

    td::INT4 insert_ID(ID);
    td::INT4 insert_JobID(JobID);
    td::INT4 insert_TypeID(6);
    td::INT4 insert_nominalSection(nominalSection);


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "UPDATE CatalogReactor SET Description=?,JobID=?,TypeID=?,Alias=?,ConnectionType=?,NumberOfPhases=?,RatedVoltage=?,MaxVoltage=?,MinVoltage=?,NominalSection=?,ReactivePower=?,ActivePowerLoss=?,NominalCurrent=?,Name=? WHERE ID = ?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refDescription << insert_JobID << insert_TypeID  << refAlias << refConnectionType
           << refnoOfPhases << ratedVoltage << maximumVoltage << minimumVoltage << insert_nominalSection << reactivePower
              << activePowerLoss << nominalCurrent << refName << insert_ID;


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

bool ReactorCatalog::insertReactorNaming(int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(6);
    td::INT4 insert_ID(id);
    td::INT4 insert_producerID(producerID);

    db::Ref<td::String> refName(50);
    td::String td_name = name.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSER INTO CatNaming TypeID,Name,ProducerID,ID VALUES(?,?,?,?)"));


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


bool ReactorCatalog::updateReactorNaming(int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(6);
    td::INT4 insert_ID(id);
    td::INT4 insert_producerID(producerID);

    db::Ref<td::String> refName(50);
    td::String td_name = name.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "UPDATE CatNaming SET TypeID=?,Name=?,ProducerID=? WHERE ID = ?"));


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




void ReactorCatalog::on_reactorButtons_buttonBox_accepted()
{

    if(searchwindowID != 0)
        {
            if(updateReactorNaming(6,getID(), getName(), 2))
            {
            updateReactorCatalog(getDescription(), getID(),  getAlias(),getConnectionType(),getNumberOfPhases(),
                             getRatedVoltage(), getMaximumVoltage(),getMinimumVoltage(),getNominalSection(),
                            getReactivePower(), getActivePowerLoss(),getNominalCurrent(), getName());
            close();
            }

         else
         {
               QMessageBox::information(this,"Info","ID already exists");
         }
    }
    else
    {
        if(insertReactorNaming(6,getID(), getName(), 2))
        {
        insertReactorCatalog(getDescription(), getID(),  getAlias(),getConnectionType(),getNumberOfPhases(),
                         getRatedVoltage(), getMaximumVoltage(),getMinimumVoltage(),getNominalSection(),
                        getReactivePower(), getActivePowerLoss(),getNominalCurrent(), getName());
        close();
        }

     else
     {
           QMessageBox::information(this,"Info","ID already exists");
     }

    }
}

void ReactorCatalog::on_reactorButtons_buttonBox_rejected()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Discard","Are you sure you want to discard all changes made?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            close();
        }
}



