#include "resistorplacement.h"
#include "ui_resistorplacement.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QMessageBox"

extern  db::ISQLDatabase *pDB;
extern int JobID;
extern int searchwindowID;

ResistorPlacement::ResistorPlacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResistorPlacement)
{
    ui->setupUi(this);
    ui->resistorPSystID_lineEdit->setEnabled(false);
    this->setWindowTitle("Resistor Placement");
    if(searchwindowID != 0)
    {
               QString s = QString::number(searchwindowID);
               ui->resistorPUID_lineEdit->setText(s);
               ui->resistorPUID_lineEdit->setEnabled(false);
    }
}

ResistorPlacement::~ResistorPlacement()
{
    delete ui;
}

QString ResistorPlacement::getName()
{
    return ui->resistorPName_lineEdit->text();
}

QString ResistorPlacement::getAlias()
{
    return ui->resistorPAlias_lineEdit->text();
}

int ResistorPlacement::getSystemID()
{
    return ui->resistorPSystID_lineEdit->text().toInt();
}

int ResistorPlacement::getID()
{
    return ui->resistorPUID_lineEdit->text().toInt();
}

QString ResistorPlacement::getCatalogType()
{
    return ui->resistorPCatType_comboBox->currentText();
}

QString ResistorPlacement::getDescription()
{
    return ui->resistorPDescription_textEdit->toPlainText();
}




bool ResistorPlacement::insertResistorPlacement(QString description,QString name,QString alias,QString catalogType, int systemID,
                                                int ID)
{
    if (!pDB)
        return false;
    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refName(50);
    db::Ref<td::String> refCatalogType(50);
    db::Ref<td::String> refDescription(150);


    td::String td_alias = alias.toUtf8();
    td::String td_catalogType = catalogType.toUtf8();
    td::String td_description = description.toUtf8();
    td::String td_name = name.toUtf8();

    refAlias = td_alias;
    refCatalogType = td_catalogType;
    refDescription = td_description;
    refName = td_name;

    td::INT4 insert_systemID(systemID);
    td::INT4 insert_JobID(JobID);
    td::INT4 insert_typeID(7);
    td::INT4 insert_ID(ID);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
    "INSERT INTO PlacementResistor(Description,Name,Alias,CatalogType,JobID,TypeID,CatNamingID,SystemID) VALUES (?,?,?,?,?,?,?,?)"));


    //allocate parameter and bind it to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refDescription << refName << refAlias << refCatalogType << insert_JobID << insert_typeID << insert_ID << insert_systemID;


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



void ResistorPlacement::on_resistorPButtons_buttonBox_accepted()
{


        insertResistorPlacement(getDescription(),getName(),getAlias(),getCatalogType(), getSystemID(),
                                getID());
close();

}

void ResistorPlacement::on_resistorPButtons_buttonBox_rejected()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Discard","Are you sure you want to discard all changes made?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            close();
        }
}
