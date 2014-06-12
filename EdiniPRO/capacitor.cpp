#include "capacitor.h"
#include "ui_capacitor.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"

Capacitor::Capacitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Capacitor),
    pDB(0)
   {
           ui->setupUi(this);
           connectSQLite();
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

float Capacitor::getNominalSection()
{
    return ui->capacitorNominalSection_lineEdit->text().toFloat();
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

bool Capacitor::connectSQLite()
{
    if (pDB)
        pDB->release();

    pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);
        //give path for our database
    if (!pDB->connect("C:/Users/Edin/Downloads/Project.db"))
    {
        std::cout << "Cannot connect to database" << std::endl;
        td::String err;
        pDB->getErrorStr(err);
        std::cout << err.c_str() << std::endl;
        pDB->release();
        pDB = 0;
        return false;
    }
    std::cout << "Connection OK!" << std::endl;
    return true;

}

bool Capacitor::insertCapacitor(QString alias, float ratedVoltage, QString noOfPhases,
                    float minVoltage, float maxVoltage, float nominalSection, QString connectionType, QString description,
                   float reactivePower, float activePowerLoss)
{
    if (!pDB)
        return false;
    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refnoOfPhases(50);
    db::Ref<td::String> refConnectionType(50);
    db::Ref<td::String> refDescription(200);


    td::String td_alias = alias.toUtf8();
    td::String td_noOfPhases = noOfPhases.toUtf8();
    td::String td_description = description.toUtf8();
    td::String td_connectionType = connectionType.toUtf8();

    refAlias = td_alias;
    refnoOfPhases = td_noOfPhases;
    refConnectionType = td_connectionType;
    refDescription = td_description;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO Capacitor(Alias, Rated_Voltage, Number_Of_Phases, Minimum_Voltage, Maximum_Voltage, Nominal_Section, Connection_Type, Description, ReactivePower, Active_Power_Loss) VALUES (?,?,?,?,?,?,?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refAlias << ratedVoltage << refnoOfPhases << minVoltage << maxVoltage << nominalSection
           << refConnectionType << refDescription << reactivePower << activePowerLoss;


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
        std::cout << "Data inserted" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool Capacitor::insertNaming(QString name)
{
    if (!pDB)
        return false;
    db::Ref<td::String> refName(50);


    td::String td_name = name.toUtf8();
    refName = td_name;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,"INSERT INTO Naming(Name) VALUES (?)"));


    //allocate parameter and bind it to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refName;


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
        std::cout << "Data inserted" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool Capacitor::insertID(int id)
{
    if (!pDB)
        return false;

    td::INT4 insert_ID(id);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,"INSERT INTO Type(ID) VALUES (?)"));


    //allocate parameter and bind it to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_ID;


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
        std::cout << "Data inserted" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

void Capacitor::on_capacitor_buttonBox_accepted()
{
    if(ui->capacitor_buttonBox->Save){
        insertCapacitor(getAlias(), getRatedVoltage(), getNumberOfPhases(),
                               getMinVoltage(), getMaxVoltage(), getNominalSection(), getConnectionType(), getDescription(),
                               getReactivePower(), getActivePowerLoss());
        insertNaming(getName());
        insertID(getID());
    }

    else if(ui->capacitor_buttonBox->Cancel)
    {
        close();
    }
}
