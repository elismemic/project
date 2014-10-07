#include "jobitem.h"
#include "ui_jobitem.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QMessageBox"
#include <QStandardItemModel>
#include "mainwindow.h"

extern db::ISQLDatabase *pDB;

JobItem::JobItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JobItem)
{
    ui->setupUi(this);
    addType();
    ui->comboBox_item->clear();
    selectCatalog(11); type = 11;
}

void JobItem::setFields(){
    ui->lineEdit_Id->setEnabled(false);
    ui->lineEdit_Name->setEnabled(false);
    ui->lineEdit_Id->setText(QString::number(jobID));
    ui->lineEdit_Name->setText(jobName);
}

JobItem::~JobItem()
{
    delete ui;
}

void JobItem::addType()
{
    ui->comboBox_type->addItem("Busbar Catalog",0);
    ui->comboBox_type->addItem("Cable Head Catalog",1);
    ui->comboBox_type->addItem("Junction Catalog",2);
    ui->comboBox_type->addItem("Equivalent Source",3);
    ui->comboBox_type->addItem("Busbar Section Horizontal",4);
    ui->comboBox_type->addItem("Busbar Section Vertical",5);
    ui->comboBox_type->addItem("Busbar Free Style",6);
    ui->comboBox_type->addItem("Connectivity Node",7);
    ui->comboBox_type->addItem("Cable Head",8);
    ui->comboBox_type->addItem("Source Sink Connector",9);
    ui->comboBox_type->addItem("Jumber(z = 0)",10);
}


bool JobItem::selectCatalog(int index)
{
    if (!pDB){
         std::cout<< "Transaction failed not pDB" <<std::endl;
         return false;}

    td::String Name;
    td::INT4 id;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name,Id from CatNaming where TypeId = ? UNION SELECT Name,Id from PlacNaming where TypeId = ?"));
    db::Params params(pStat->allocParams());

    params << index<<index;

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "Name" << Name
             << "Id" << id;

        if (!pStat->execute())
            {
                std::cout << "testSelect2 - Exec NOT ok\n";
                td::StringUTF8 strErr;
                pStat->getErrorStr(strErr);
                std::cout << strErr.c_str() << std::endl;
                return false;
            }
            else{

            while (pStat->moveNext())
            {
                ui->comboBox_item->addItem(QString::fromUtf8(Name.c_str()),QString::number(id));

                int row = ui->comboBox_item->findText(Name.c_str());
                if(isItemAvailable(index,id))
                qobject_cast<QStandardItemModel*>(ui->comboBox_item->model())->item(row)->setEnabled(false);
            }
            return true;
        }
}

void JobItem::setJobId(int jobId)
{
    jobID = jobId;
}

void JobItem::setJobName(QString name){
    jobName = name;
}

void JobItem::on_comboBox_type_currentIndexChanged(int index)
{
    ui->comboBox_item->setEnabled(true);
    ui->comboBox_item->clear();
    switch(index){

    case 0: selectCatalog(11); type = 11; break;
    case 1: selectCatalog(12);type = 12;break;
    case 2: selectCatalog(13);type = 13;break;
    case 3: selectCatalog(20);type = 20;break;
    case 4: selectCatalog(21);type = 21;break;
    case 5: selectCatalog(22);type = 22;break;
    case 6: selectCatalog(23);type = 23;break;
    case 7: selectCatalog(24);type = 24;break;
    case 8: selectCatalog(25);type = 25;break;
    case 9: selectCatalog(26);type = 26;break;
    case 10: selectCatalog(39);type = 39;break;
    }

}

void JobItem::on_pushButton_2_clicked()
{
    this->close();
}

void JobItem::on_pushButton_clicked()
{
    int Id = getCatalogId(ui->comboBox_item->currentText(),type);
    
    if(type >=11 && type <=13)
        insertJobCatalogs(jobID, type, Id);
    else
        insertJobPlacement(jobID,type,Id,0); //needs to change systemId accordingly

    updateCatalogs(Id,type,jobID);
}

bool JobItem::insertJobCatalogs(int jobId, int typeId, int catId){

    if (!pDB)
        return false;

    td::INT4 td_jobId(jobId);
    td::INT4 td_typeId(typeId);
    td::INT4 td_catId(catId);


    //start transaction log
    db::Transaction trans(pDB);



    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,"Insert into JobCatalogs VALUES(?,?,?)"));
    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << td_jobId << td_typeId <<td_catId;

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
        std::cout << "Data Updated" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Updating finished!\n";

    return bRet;
}


 bool JobItem::insertJobPlacement(int jobId, int typeId, int placId, int systemId){

        if (!pDB)
            return false;

        td::INT4 td_jobId(jobId);
        td::INT4 td_typeId(typeId);
        td::INT4 td_placId(placId);
        td::INT4 td_systemId(systemId);

        //start transaction log
        db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
        db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO JobPlacements VALUES(?,?,?,?)"));
        //allocate parameters and bind them to the statement
        db::Params params(pStat->allocParams());
        //bind params
        params <<td_systemId<<td_jobId << td_typeId <<td_placId;

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
            std::cout << "Data Updated" << std::endl;

        if (DebugTrace(1000))
            mu::getTracer() << "Updating finished!\n";

        return bRet;
}

int JobItem::getCatalogId(QString name, int type){

    int Id;

    td::String Name;

    db::Ref<td::String> refName(20);
    td::String td_name = name.toUtf8();
    refName = td_name;

    if (!pDB){
         std::cout<< "Transaction failed not pDB" <<std::endl;
         return false;}

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Id from CatNaming where TypeId = ? and Name = ? UNION SELECT Id from PlacNaming where TypeID = ? and Name = ?"));
    db::Params params(pStat->allocParams());
    params << type<<refName <<type<<refName;

    db::Columns cols(pStat->allocBindColumns(1));
        cols << "Id" << Id;

        if (!pStat->execute())
            {
                QMessageBox::information(this,"Connection status","Could not connect to database");
        }
            else{
            if (pStat->moveNext())
                return Id;
        }
        return Id;
}

bool JobItem::updateCatalogs(int Id, int type, int jobId)
{
    if (!pDB)
        return false;

    td::INT4 td_jobId(jobId);
    td::INT4 td_typeId(type);
    td::INT4 td_catId(Id);

    db::StatementPtr pStat1(pDB->createStatement(db::IStatement::DBS_INSERT, "Update CatBusbar Set JobId = ? where Id = ?"));
    db::StatementPtr pStat2(pDB->createStatement(db::IStatement::DBS_INSERT, "Update CatCableHead Set JobId = ? where Id = ?"));
    db::StatementPtr pStat3(pDB->createStatement(db::IStatement::DBS_INSERT, "Update CatJunction Set JobId = ? where Id = ?"));
    db::StatementPtr pStat4(pDB->createStatement(db::IStatement::DBS_INSERT, "Update PlacBusbar Set JobId = ? where Id = ?"));
    db::StatementPtr pStat5(pDB->createStatement(db::IStatement::DBS_INSERT, "Update PlacCableHead Set JobId = ? where Id = ?"));
    db::StatementPtr pStat6(pDB->createStatement(db::IStatement::DBS_INSERT, "Update PlacJunction Set JobId = ? where Id = ?"));

    db::Params params1(pStat1->allocParams());
    params1 << td_jobId  <<td_catId;

    db::Params params2(pStat2->allocParams());
    params2 << td_jobId <<td_catId;

    db::Params params3(pStat3->allocParams());
    params3 << td_jobId <<td_catId;

    db::Params params4(pStat4->allocParams());
    params4 << td_jobId <<td_catId;

    db::Params params5(pStat5->allocParams());
    params5 << td_jobId <<td_catId;

    db::Params params6(pStat6->allocParams());
    params6 << td_jobId <<td_catId;

    switch(type){
    case 11: pStat1->execute(); break;
    case 12: pStat2->execute(); break;
    case 13: pStat3->execute(); break;
    case 20:
    case 21:
    case 22:
    case 23: pStat4->execute(); break;
    case 24:
    case 25:
    case 26: pStat5->execute(); break;
    case 39: pStat6->execute(); break;
    }

    return true;
}

bool JobItem::isItemAvailable(int typeId, int catId)
{
    if (!pDB)
        return false;

    td::INT4 typeID(typeId);
    td::INT4 catID(catId);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select ID from JobCatalogs inner join Jobs on JobCatalogs.JobID = Jobs.[ID] where Jobs.[Status] = 'IN WORK' and JobCatalogs.[TypeID] = ? and JobCatalogs.[CatID] = ?"));
    mem::PointerReleaser<db::IStatement> pStat1(pDB->createStatement(db::IStatement::DBS_SELECT, "select ID from JobPlacements inner join Jobs on JobPlacements.JobID = Jobs.[ID] where Jobs.[Status] = 'IN WORK' and JobPlacements.[TypeID] = ? and JobPlacements.[PlacID] = ?"));

    db::Params params(pStat->allocParams());
    params << typeID << catID;

    db::Params params1(pStat1->allocParams());
    params1 << typeID << catID;

    if(typeId >= 11 || typeId <=13){
        if (!pStat->execute())
            return false;
        if(pStat->moveNext()){
            return true;}
    }else{
        if (!pStat1->execute())
            return false;
        if(pStat1->moveNext()){
            return true;}
    }

    return false;
}
