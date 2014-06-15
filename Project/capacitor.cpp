#include "capacitor.h"
#include "ui_capacitor.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QMessageBox"

extern db::ISQLDatabase *pDB;
extern int searchwindowID;
extern int JobID;
Capacitor::Capacitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Capacitor)
   {
           ui->setupUi(this);
           this->setWindowTitle("Capacitor Catalog");
           if(searchwindowID != 0){
            QString s = QString::number(searchwindowID);
            ui->capacitorID_lineEdit->setText(s);
            ui->capacitorID_lineEdit->setEnabled(false);
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



void Capacitor::on_capacitor_buttonBox_accepted()
{

    if(searchwindowID != 0)
    {
        insertCapacitor(searchwindowID, getName(), getAlias(), getRatedVoltage(),getNumberOfPhases(), getDescription(),
                        getNominalSection(),getConnectionType(),
                       getMinVoltage(), getMaxVoltage() ,
                      getReactivePower(), getActivePowerLoss());
        close();
    }
    else
    {
        insertCapacitor(getID(), getName(), getAlias(), getRatedVoltage(),getNumberOfPhases(), getDescription(),
                        getNominalSection(),getConnectionType(),
                       getMinVoltage(), getMaxVoltage() ,
                      getReactivePower(), getActivePowerLoss());
        close();
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
