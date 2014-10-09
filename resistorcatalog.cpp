#include "resistorcatalog.h"
#include "ui_resistorcatalog.h"
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

ResistorCatalog::ResistorCatalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResistorCatalog)
{
    ui->setupUi(this);
    this->setWindowTitle("Resistor Catalog");

    if(searchwindowID != 0)
    {
               QString s = QString::number(searchwindowID);
               ui->resistorUID_lineEdit->setText(s);
               ui->resistorUID_lineEdit->setEnabled(false);
    }
    if(searchwindowJobID != JobID)
       {
        ui->resistorButtons_buttonBox->setEnabled(false);
    }

}

ResistorCatalog::~ResistorCatalog()
{
    delete ui;
}

QString ResistorCatalog::getName()
{
    return ui->resistorName_lineEdit->text();
}
int ResistorCatalog::getID()
{
    return ui->resistorUID_lineEdit->text().toInt();
}

QString ResistorCatalog::getAlias()
{
    return ui->resistorAlias_lineEdit->text();
}

float ResistorCatalog::getRatedVoltage()
{
    return ui->resistorRV_comboBox->currentText().toFloat();
}

float ResistorCatalog::getR()
{
    return ui->resistorR_lineEdit->text().toFloat();
}

float ResistorCatalog::getX()
{
    return ui->resistorX_lineEdit->text().toFloat();
}

QString ResistorCatalog::getDescription()
{
    return ui->resistorDescription_textEdit->toPlainText();
}




void ResistorCatalog::setName()
{
     ui->resistorName_lineEdit->setText("");
}
void ResistorCatalog::setID()
{
     ui->resistorUID_lineEdit->setText("");
}

void ResistorCatalog::setAlias()
{
     ui->resistorAlias_lineEdit->setText("");
}

void ResistorCatalog::setRatedVoltage()
{
     ui->resistorRV_comboBox->setCurrentText("");
}

void ResistorCatalog::setR()
{
     ui->resistorR_lineEdit->setText("");
}

void ResistorCatalog::setX()
{
     ui->resistorX_lineEdit->setText("");
}

void ResistorCatalog::setDescription()
{
     ui->resistorDescription_textEdit->setPlainText("");
}


bool ResistorCatalog::updateResistorCatalog(QString name, float ratedVoltage, int ID, QString alias, float R,
                          float X, QString description)
{
    if (!pDB)
        return false;

    td::INT4 insert_JobID(JobID);
    td::INT4 insert_TypeID(7);
    td::INT4 insert_ID(ID);

    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refName(50);
    db::Ref<td::String> refDescription(150);


    td::String td_alias = alias.toUtf8();
    td::String td_description = description.toUtf8();
    td::String td_name = name.toUtf8();

    refAlias = td_alias;
    refDescription = td_description;
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
    "UPDATE CatalogResistor SET Description=?, JobID=?, TypeID=?, Name=?, Alias=?, RatedVoltage=?,R=?,X=? WHERE ID =?"));


    //allocate parameter and bind it to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refDescription << insert_JobID << insert_TypeID << refName << refAlias << ratedVoltage << R << X << insert_ID;


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

bool ResistorCatalog::updateResistorNaming(int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(7);
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


bool ResistorCatalog::insertResistorCatalog(QString name, float ratedVoltage, int ID, QString alias, float R,
                          float X, QString description)
{
    if (!pDB)
        return false;

    td::INT4 insert_JobID(JobID);
    td::INT4 insert_TypeID(7);
    td::INT4 insert_ID(ID);

    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refName(50);
    db::Ref<td::String> refDescription(150);


    td::String td_alias = alias.toUtf8();
    td::String td_description = description.toUtf8();
    td::String td_name = name.toUtf8();

    refAlias = td_alias;
    refDescription = td_description;
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
    "INSERT INTO CatalogResistor(Description, JobID, TypeID,ID, Name, Alias, RatedVoltage,R,X) VALUES (?,?,?,?,?,?,?,?,?)"));


    //allocate parameter and bind it to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refDescription << insert_JobID << insert_TypeID << insert_ID << refName << refAlias << ratedVoltage << R << X;


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

bool ResistorCatalog::insertResistorNaming(int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(7);
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


void ResistorCatalog::on_resistorButtons_buttonBox_accepted()
{

    if(searchwindowID != 0)
        {
            if(updateResistorNaming(7,searchwindowID, getName(), 2))
            {
            updateResistorCatalog(getName(), getRatedVoltage(), searchwindowID, getAlias(), getR(),
                                  getX(), getDescription());
            close();
            }

         else
         {
               QMessageBox::information(this,"Info","ID already exists");
         }
    }
    else
    {
        if(insertResistorNaming(6,getID(), getName(), 2))
        {
        insertResistorCatalog(getName(), getRatedVoltage(), getID(), getAlias(), getR(),
                              getX(), getDescription());
        close();
        }

     else
     {
           QMessageBox::information(this,"Info","ID already exists");
     }

    }
}

void ResistorCatalog::on_resistorButtons_buttonBox_rejected()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Discard","Are you sure you want to discard all changes made?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            close();
        }
}



