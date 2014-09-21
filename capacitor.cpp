#include "capacitor.h"
#include "ui_capacitor.h"
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
Capacitor::Capacitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Capacitor)
   {
           ui->setupUi(this);
           this->setWindowTitle("Capacitor Catalog");
           if(editClicked == true)
           {
            QString s = QString::number(searchwindowID);
            ui->capacitorID_lineEdit->setText(s);
            ui->capacitorID_lineEdit->setEnabled(false);
            selectCapacitor();
            editClicked = false;
           }

   }

Capacitor::~Capacitor()
{
    delete ui;
}

QString Capacitor::getName()
{
    return ui->capacitorName_lineEdit->text();
}

QString Capacitor::getAlias()
{
    return ui->capacitorAlias_lineEdit->text();
}

int Capacitor::getID()
{
    return ui->capacitorID_lineEdit->text().toInt();
}

float Capacitor::getRatedVoltage()
{
    return ui->capacitorRatedVoltage_comboBox->currentText().toFloat();
}

QString Capacitor::getNumberOfPhases()
{
    return ui->capacitorNumberOfPhasescomboBox->currentText();
}

float Capacitor::getMinVoltage()
{
    return ui->capacitorMinVoltage_lineEdit->text().toFloat();
}

float Capacitor::getMaxVoltage()
{
    return ui->capacitorMaxVoltage_lineEdit->text().toFloat();
}

int Capacitor::getNominalSection()
{
    return ui->capacitorNominalSection_lineEdit->text().toInt();
}

QString Capacitor::getConnectionType()
{
    return ui->capacitorConnectionType_comboBox->currentText();
}

QString Capacitor::getDescription()
{
    return ui->capacitorDescription_plainTextEdit->toPlainText();
}

float Capacitor::getReactivePower()
{
    return ui->capacitorReactivePower_lineEdit->text().toFloat();
}

float Capacitor::getActivePowerLoss()
{
    return ui->capacitorActivePowerLoss_lineEdit->text().toFloat();
}


void Capacitor::setName(QString a)
{
    ui->capacitorName_lineEdit->setText(a);
}

void Capacitor::setAlias(QString a)
{
    ui->capacitorAlias_lineEdit->setText(a);
}

void Capacitor::setID(int a)
{
    QString s = QString::number(a);
    ui->capacitorID_lineEdit->setText(s);
}

void Capacitor::setRatedVoltage(float a)
{
    QString s = QString::number(a);
    ui->capacitorRatedVoltage_comboBox->setCurrentText(s);
}

void Capacitor::setNumberOfPhases(QString a)
{
    ui->capacitorNumberOfPhasescomboBox->setCurrentText(a);
}

void Capacitor::setMinVoltage(float a)
{
    QString s = QString::number(a);
    ui->capacitorMinVoltage_lineEdit->setText(s);
}

void Capacitor::setMaxVoltage(float a)
{
    QString s = QString::number(a);
    ui->capacitorMaxVoltage_lineEdit->setText(s);
}

void Capacitor::setNominalSection(int a)
{
    QString s = QString::number(a);
    ui->capacitorNominalSection_lineEdit->setText(s);
}

void Capacitor::setConnectionType(QString a)
{
    ui->capacitorConnectionType_comboBox->setCurrentText(a);
}

void Capacitor::setDescription(QString a)
{
    ui->capacitorDescription_plainTextEdit->setPlainText(a);
}

void Capacitor::setReactivePower(float a)
{
    QString s = QString::number(a);
    ui->capacitorReactivePower_lineEdit->setText(s);
}

void Capacitor::setActivePowerLoss(float a)
{
    QString s = QString::number(a);
    ui->capacitorActivePowerLoss_lineEdit->setText(s);
}

bool Capacitor::updateCapacitorNaming(int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(5);
    td::INT4 insert_ID(id);
    td::INT4 insert_producerID(producerID);

    db::Ref<td::String> refName(50);
    td::String td_name = name.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE CatNaming SET TypeID=?,Name=?,ProducerID=? WHERE ID=?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_TypeID << refName << insert_producerID  << insert_ID;


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

bool Capacitor::updateCapacitor(int id, QString name, QString aliasName, float ratedVoltage,QString numberOfPhases, QString description,
                     int nominalSection,QString connectionType,
                    float minVoltage, float maxVoltage ,
                   float reactivePower, float activePowerLoss)
{
    if (!pDB)
        return false;

    td::INT4 insert_ID(id);
    td::INT4 insert_nominalSection(nominalSection);
    td::INT4 insert_TypeID(5);
    td::INT4 insert_JobID(JobID);

    db::Ref<td::String> refName(50);
    db::Ref<td::String> refAliasName(50);
    db::Ref<td::String> refConnectionType(50);
    db::Ref<td::String> refNumberOfPhases(50);
    db::Ref<td::String> refDescription(200);


    td::String td_name = name.toUtf8();
    td::String td_aliasName = aliasName.toUtf8();
    td::String td_description = description.toUtf8();
    td::String td_connectionType = connectionType.toUtf8();
    td::String td_numberOfPhases = numberOfPhases.toUtf8();

    refName = td_name;
    refAliasName = td_aliasName;
    refDescription = td_description;
    refConnectionType = td_connectionType;
    refNumberOfPhases = td_numberOfPhases;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE CatalogCapacitor SET Description=?,JobID=?,TypeID=?,Alias=?,ConnectionType=?,NumberOfPhases=?,RatedVoltage=?,MaxVoltage=?,MinVoltage=?,NominalSection=?,ReactivePower=?,ActivePowerLoss=?,Name=? WHERE ID = ?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refDescription << insert_JobID << insert_TypeID << refAliasName << refConnectionType << refNumberOfPhases
           << ratedVoltage << maxVoltage << minVoltage << insert_nominalSection << reactivePower << activePowerLoss << refName << insert_ID;


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
        mu::getTracer() << "Update finished!\n";
    return bRet;

}

void Capacitor::selectCapacitor()
{
    td::INT4 insert_ID(searchwindowID);
    td::INT4 insert_JobID(searchwindowJobID);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_SELECT,
       "Select Description,Alias,ConnectionType,NumberOfPhases,RatedVoltage,MaxVoltage,MinVoltage,NominalSection,ReactivePower,ActivePowerLoss,Name FROM CatalogCapacitor WHERE ID = ? AND JobID = ?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_ID << insert_JobID;


    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(11);
        columns[0].name = "Description";
        columns[0].tdType = td::nch;
        columns[0].len = 0;

        columns[1].name = "Alias";
        columns[1].tdType = td::nch;
        columns[1].len = 0;

        columns[2].name = "ConnectionType";
        columns[2].tdType = td::nch;
        columns[2].len = 0;

        columns[3].name = "NumberOfPhases";
        columns[3].tdType = td::nch;
        columns[3].len = 0;

        columns[4].name = "RatedVoltage";
        columns[4].tdType = td::real8;
        columns[4].len = 0;

        columns[5].name = "MaxVoltage";
        columns[5].tdType = td::real8;
        columns[5].len = 0;

        columns[6].name = "MinVoltage";
        columns[6].tdType = td::real8;
        columns[6].len = 0;

        columns[7].name = "NominalSection";
        columns[7].tdType = td::int4;
        columns[7].len = 0;

        columns[8].name = "ReactivePower";
        columns[8].tdType = td::real8;
        columns[8].len = 0;

        columns[9].name = "ActivePowerLoss";
        columns[9].tdType = td::real8;
        columns[9].len = 0;

        columns[10].name = "Name";
        columns[10].tdType = td::nch;
        columns[10].len = 0;

        db::Recordset* rs = new db::Recordset(columns);

        if (!rs->load(pStat.getPtr()))
            exit(0);

        MyModel *model = new MyModel(this, rs, true);

        QModelIndex idx = model->index(0,0);
            QString description = model->data(idx, Qt::DisplayRole).toString();
            setDescription(description);

            idx = model->index(0,1);
            QString alias = model->data(idx, Qt::DisplayRole).toString();
            setAlias(alias);

            idx = model->index(0,2);
            QString connType = model->data(idx, Qt::DisplayRole).toString();
            setConnectionType(connType);

            idx = model->index(0,3);
            QString NoOfPh = model->data(idx, Qt::DisplayRole).toString();
            setNumberOfPhases(NoOfPh);

            idx = model->index(0,4);
            float ratedVoltage = model->data(idx, Qt::DisplayRole).toFloat();
            setRatedVoltage(ratedVoltage);

            idx = model->index(0,5);
            float maxVoltage = model->data(idx, Qt::DisplayRole).toFloat();
            setMaxVoltage(maxVoltage);

            idx = model->index(0,6);
            float minVoltage = model->data(idx, Qt::DisplayRole).toFloat();
            setMinVoltage(minVoltage);

            idx = model->index(0,7);
            int nominalSection = model->data(idx, Qt::DisplayRole).toInt();
            setNominalSection(nominalSection);

            idx = model->index(0,8);
            float rp = model->data(idx, Qt::DisplayRole).toFloat();
            setReactivePower(rp);

            idx = model->index(0,9);
            float apl = model->data(idx, Qt::DisplayRole).toFloat();
            setActivePowerLoss(apl);

            idx = model->index(0,10);
            QString name = model->data(idx, Qt::DisplayRole).toString();
            setName(name);
}


bool Capacitor::insertCapacitor(int id, QString name, QString aliasName, float ratedVoltage,QString numberOfPhases, QString description,
                                int nominalSection,QString connectionType,
                               float minVoltage, float maxVoltage ,
                              float reactivePower, float activePowerLoss)
{
    if (!pDB)
        return false;

    td::INT4 insert_ID(id);
    td::INT4 insert_nominalSection(nominalSection);
    td::INT4 insert_TypeID(5);
    td::INT4 insert_JobID(JobID);

    db::Ref<td::String> refName(50);
    db::Ref<td::String> refAliasName(50);
    db::Ref<td::String> refConnectionType(50);
    db::Ref<td::String> refNumberOfPhases(50);
    db::Ref<td::String> refDescription(200);


    td::String td_name = name.toUtf8();
    td::String td_aliasName = aliasName.toUtf8();
    td::String td_description = description.toUtf8();
    td::String td_connectionType = connectionType.toUtf8();
    td::String td_numberOfPhases = numberOfPhases.toUtf8();

    refName = td_name;
    refAliasName = td_aliasName;
    refDescription = td_description;
    refConnectionType = td_connectionType;
    refNumberOfPhases = td_numberOfPhases;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO CatalogCapacitor(Description,JobID,TypeID,ID,Alias,ConnectionType,NumberOfPhases,RatedVoltage,MaxVoltage,MinVoltage,NominalSection,ReactivePower,ActivePowerLoss,Name) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refDescription << insert_JobID << insert_TypeID << insert_ID << refAliasName << refConnectionType << refNumberOfPhases
           << ratedVoltage << maxVoltage << minVoltage << insert_nominalSection << reactivePower << activePowerLoss << refName;


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

bool Capacitor::insertCapacitorNaming(int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(5);
    td::INT4 insert_ID(id);
    td::INT4 insert_producerID(producerID);

    db::Ref<td::String> refName(50);
    td::String td_name = name.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO CatNaming(TypeID,ID,Name,ProducerID) VALUES (?,?,?,?)"));


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



void Capacitor::on_capacitor_buttonBox_accepted()
{

    if(searchwindowID != 0)
    {
        if(updateCapacitorNaming(5,searchwindowID,getName(),2))
        {
        updateCapacitor(searchwindowID, getName(), getAlias(), getRatedVoltage(),getNumberOfPhases(), getDescription(),
                        getNominalSection(),getConnectionType(),
                       getMinVoltage(), getMaxVoltage() ,
                      getReactivePower(), getActivePowerLoss());
        close();
        }
        else
        {
            QMessageBox::information(this,"Information","Could not update data!");
        }
    }
    else
    {
        if(insertCapacitorNaming(5,getID(),getName(),2))
        {
        insertCapacitor(getID(), getName(), getAlias(), getRatedVoltage(),getNumberOfPhases(), getDescription(),
                        getNominalSection(),getConnectionType(),
                       getMinVoltage(), getMaxVoltage() ,
                      getReactivePower(), getActivePowerLoss());
        close();
        }
        else
        {
            QMessageBox::information(this,"Information","Could not insert data - ID already exists!");
        }
    }
}

void Capacitor::on_capacitor_buttonBox_rejected()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Discard","Are you sure you want to discard all changes made?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        close();
    }
}
