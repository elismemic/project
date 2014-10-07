#include "jobs.h"
#include "ui_jobs.h"
#include "cablehead.h"
#include "createjob.h"
#include "cableheadplacement.h"
#include "busbarplacement.h"
#include "junction.h"
#include <QAbstractButton>
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include <QMessageBox>
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mymodel.h"
#include "busbar.h"
#include "jobitem.h"
#include <QAbstractItemModel>
#include "mainwindow.h"
#include "junctionplacement.h"

extern int user;
extern int globalJobId;
extern db::ISQLDatabase *pDB;

Jobs::Jobs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Jobs)
{
    ui->setupUi(this);
    //connectSQLite();
    selectType();
    selectStatus();
    selectOwner();
    updateTableView();

    ui->tableView_browse->setVisible(false);
    ui->comboBox_owner->setVisible(false);
    ui->comboBox_status->setVisible(false);

    ui->pushButton_activate->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->deleteItem->setEnabled(false);
    ui->pushButton_item->setEnabled(false);
}


/*bool Jobs::connectSQLite()
{
    pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);

    if (!pDB->connect("C:/Users/darko/Desktop/ABCD/project.db"))
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

}*/

bool Jobs::selectOwner(){

    int id;
    td::String name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID,Name from Users"));

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "ID" << id
             << "Name" << name;

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
                ui->comboBox_owner->addItem(QString::fromUtf8(name.c_str()),QString::number(id));
            }

            std::cout<< "Transaction OK" <<std::endl;
            return true;
        }
}

bool Jobs::selectStatus(){
    ui->comboBox_status->addItem("IN WORK",QString::number(0));
    ui->comboBox_status->addItem("ACTIVATED",QString::number(1));
    ui->comboBox_status->addItem("CANCELED",QString::number(2));
    return true;
}

Jobs::~Jobs()
{
    delete ui;
}

void Jobs::selectType()
{
    ui->comboBox_type->addItem("ALL JOBS",0);
    ui->comboBox_type->addItem("Id",1);
    ui->comboBox_type->addItem("Name",2);
    ui->comboBox_type->addItem("Owner",3);
    ui->comboBox_type->addItem("Status",4);

}

void Jobs::on_comboBox_type_currentIndexChanged(int index)
{
    if(index == 0){
        ui->lineEdit_search->setEnabled(false);
        ui->comboBox_owner->setVisible(false);
        ui->comboBox_status->setVisible(false);
        ui->label_sear_type->setVisible(true);
    }else if(index == 3){
        ui->lineEdit_search->setVisible(false);
        ui->comboBox_owner->setVisible(true);
        ui->comboBox_status->setVisible(false);
    }else if(index == 4){
        ui->lineEdit_search->setVisible(false);
        ui->comboBox_status->setVisible(true);
        ui->comboBox_owner->setVisible(false);
    }else if(index == 1 || index == 2){
        ui->lineEdit_search->setEnabled(true);
        ui->lineEdit_search->setVisible(true);
        ui->comboBox_status->setVisible(false);
        ui->comboBox_owner->setVisible(false);
    }
}


bool Jobs::updateTableView()
{
    if (!pDB)
        return false;

    QString searchMe = ui->lineEdit_search->text();
    QString status = ui->comboBox_status->currentText();
    int owner = ui->comboBox_owner->currentIndex();

    if(ui->comboBox_type->currentIndex() == 0)
        searchMe = "%%";

    db::Ref<td::String> refSearchme(20);
    td::String td_searchMe = searchMe.toUtf8();
    refSearchme = td_searchMe;

    if(ui->comboBox_type->currentIndex() != 4)
        status = "stbd";

    db::Ref<td::String> refStatus(20);
    td::String td_status = status.toUtf8();
    refStatus = td_status;


    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Jobs.ID, Jobs.Name, Users.Name as User, Jobs.Status as Status, Creation_date, Activation_date from Jobs inner join Users on Jobs.UserID = Users.ID  where Jobs.ID= ? or Jobs.Name LIKE ? or Jobs.UserID = ? or Jobs.Status = ?"));

    db::Params params(pStat->allocParams());

    if(ui->comboBox_type->currentIndex() != 3)
        owner = -3;

    params << refSearchme << refSearchme << owner << refStatus;


    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(6);
        columns[0].name = "ID";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 50;

        columns[2].name = "User";
        columns[2].tdType = td::nch;
        columns[2].len = 0;

        columns[3].name = "Status";
        columns[3].tdType = td::nch;
        columns[3].len = 0;

        columns[4].name = "Creation_date";
        columns[4].tdType = td::nch;
        columns[4].len = 10;

        columns[5].name = "Activation_date";
        columns[5].tdType = td::nch;
        columns[5].len = 10;


        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))
            return false;

        //if(rs->rowCount() != 0){ enableButtons();}

        // true for stripes

        model = new MyModel(this, rs, true);

        ui->tableView->setModel(model);
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setStretchLastSection(true);

        return true;
}

void Jobs::on_pushButton_search_clicked()
{
    updateTableView();
}

void Jobs::on_pushButton_browse_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    int uid = model->index(row, 0).data().toInt();

    if(uid){
        globalJobId = uid;
        this->close();}
    else{
         QMessageBox::information(this,"Status","Please Choose a Job");
    }
}

void Jobs::enableButtons(){
    ui->pushButton_activate->setEnabled(true);
    ui->pushButton_item->setEnabled(true);
    ui->pushButton_delete->setEnabled(true);
    ui->deleteItem->setEnabled(true);
}

void Jobs::disableButtons(){
    ui->pushButton_activate->setEnabled(false);
    ui->pushButton_item->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->deleteItem->setEnabled(false);
}


bool Jobs::browseJob()
{

    if (!pDB)
        return false;

    int row = ui->tableView->selectionModel()->currentIndex().row();
    QString uid = model->index(row, 0).data().toString();

    db::Ref<td::String> refUid(20);
    td::String td_uid = uid.toUtf8();
    refUid = td_uid;

    std::cout<<td_uid;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select CatNaming.Id as Id, CatNaming.Name as Name, Alias_Name, Description, EnumPSTypes.[Name] as Type from CatNaming inner join JobCatalogs inner join EnumPSTypes on JobCatalogs.CatID = CatNaming.[Id] and JobCatalogs.[TypeID] = CatNaming.[TypeId] and CatNaming.[TypeId] = EnumPSTypes.[ID] where JobCatalogs.JobID = ? UNION select PlacNaming.Id as Id, PlacNaming.Name as Name, Alias_Name, Description, EnumPSTypes.[Name] as Type from PlacNaming inner join JobPlacements inner join EnumPSTypes on JobPlacements.PlacID = PlacNaming.Id and JobPlacements.[TypeID] = PlacNaming.[TypeId] and PlacNaming.[TypeId] = EnumPSTypes.ID where JobPlacements.JobID = ?"));
    db::Params params(pStat->allocParams());
    params << refUid << refUid;

    cnt::SafeFullVector<db::CPPColumnDesc> columns2;

        columns2.reserve(5);

        columns2[0].name = "Id";
        columns2[0].tdType = td::int4;
        columns2[0].len = 0;

        columns2[1].name = "Name";
        columns2[1].tdType = td::nch;
        columns2[1].len = 0;

        columns2[2].name = "Alias_Name";
        columns2[2].tdType = td::nch;
        columns2[2].len = 0;

        columns2[3].name = "Description";
        columns2[3].tdType = td::nch;
        columns2[3].len = 0;

        columns2[4].name = "Type";
        columns2[4].tdType = td::nch;
        columns2[4].len = 0;


        db::Recordset* rs2 = new db::Recordset(columns2);

        if (!rs2->load(pStat.getPtr()))
            return false;

        if(rs2->rowCount() == 0){return false;}

        // true for stripes

        model2 = new MyModel(this, rs2, true);

        ui->tableView_browse->setModel(model2);
        ui->tableView_browse->resizeRowsToContents();
        ui->tableView_browse->horizontalHeader()->setStretchLastSection(true);

        return true;
}

int Jobs::getUidByName(QString name){

    if (!pDB){
         std::cout<< "Transaction failed, Database Connection not Created" <<std::endl;
         return false;}

    int uid;

    db::Ref<td::String> refName(20);
    td::String td_name = name.toUtf8();
    refName = td_name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"select Id from busbar_catalog where Name = ? UNION select Id from busbar_placement where Name = ? UNION select Id from cable_head_catalog where cable_head_catalog.Name = ? UNION select Id from cable_head_placement where cable_head_placement.Name = ? UNION select Id from junction_catalog where Name = ? UNION select Id from junction_placement where Name = ?"));

    db::Params params(pStat->allocParams());
        params << refName<<refName<<refName<<refName<<refName<<refName;

    db::Columns cols(pStat->allocBindColumns(1));
        cols << "Id" << uid;

        if (!pStat->execute())
            {
                std::cout << "testSelect2 - Exec NOT ok\n";
                td::StringUTF8 strErr;
                pStat->getErrorStr(strErr);
                std::cout << strErr.c_str() << std::endl;
                return -1;
            }

        if(pStat->moveNext()){
            return uid;
        }

        return uid;
}

void Jobs::on_tableView_browse_clicked(const QModelIndex &index)
{
    int row = ui->tableView_browse->selectionModel()->currentIndex().row();
    QString type = model2->index(row, 4).data().toString();
    int uid = model2->index(row, 0).data().toString().toInt();

    Busbar busbar;
    CableHead cable_head;
    Junction junction;
    BusbarPlacement bb_placement;
    CableHeadPlacement ch_placement;
    JunctionPlacement junction_placement;

    int typeInt = 20;

    if(type == "Equivalent Source") typeInt = 20;
    if(type == "Busbar Section(vertical)") typeInt = 21;
    if(type == "Busbar Section(horizontal)") typeInt = 22;
    if(type == "Busbar free style") typeInt = 23;
    if(type == "Connectivity node") typeInt = 24;
    if(type == "Cable head") typeInt = 25;
    if(type == "Source sink connector") typeInt = 26;
    if(type == "Jumper (z =0)") typeInt=39;


    if(type == "busbars"){busbar.setUid(uid); busbar.enableUid(false); busbar.exec();}
    if(type == "cable heads"){cable_head.setUid(uid); cable_head.enableUid(false); cable_head.exec();}
    if(type == "jumpers"){junction.setUid(uid); junction.enableUid(false); junction.exec();}

    if(type == "Equivalent Source" || type == "Busbar Section(vertical)" || type == "Busbar section (horizontal)" || type == "Busbar free style"){
        bb_placement.setUid(uid);
        bb_placement.setPlacementType(typeInt);
        bb_placement.updateForm(uid);
        bb_placement.enableUid(false);
        bb_placement.exec();
    }

    if(type == "Connectivity node" || type == "Cable head" || type == "Source sink connector"){
        ch_placement.setUid(uid);
        ch_placement.setPlacementType(typeInt);
        ch_placement.updateForm(uid);
        ch_placement.enableUid(false);
        ch_placement.exec();
    }

    if(type=="Jumper (z =0)") {
        junction_placement.setUid(uid);
        junction_placement.setPlacementType(typeInt);
        junction_placement.updateForm(uid);
        junction_placement.enableUid(false);
        junction_placement.exec();

    }
    //if(type == "Busbar Catalog"){busbar.setUid(getUidByName(name)); busbar.exec();}
    //if(type == "Busbar Placement"){bb_placement.setUid(getUidByName(name)); bb_placement.exec();}
}


void Jobs::on_pushButton_new_clicked()
{
    CreateJob job;
    job.exec();
}

void Jobs::on_tableView_clicked(const QModelIndex &index)
{

    int row = ui->tableView->selectionModel()->currentIndex().row();
    int jobId = model->index(row, 0).data().toString().toInt();

    if(isCurrentUser(jobId) || !isInWork(jobId)){
        enableButtons();
        ui->tableView_browse->setEnabled(true);}
    else{
        disableButtons();
        ui->tableView_browse->setEnabled(false);}

    if(browseJob())
        ui->tableView_browse->setVisible(true);
    else ui->tableView_browse->setVisible(false);
}


void Jobs::on_pushButton_delete_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    int uid = model->index(row, 0).data().toString().toInt();

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"DELETE FROM Jobs where ID = ?"));

    db::Params params(pStat->allocParams());
        params << uid;

    if(pStat->execute()){
        std::cout<<"Deleted Successfully"<<std::endl;
    }else
        std::cout<<"Could not Delete"<<std::endl;

    updateTableView();
    browseJob();
}

bool Jobs::isCurrentUser(int JobId){

    int id;
    td::String name;

    td::INT4 jobId(JobId);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select UserID from Jobs where Jobs.[ID] = ?"));

    db::Params params(pStat->allocParams());
        params << jobId;

    db::Columns cols(pStat->allocBindColumns(1));
        cols << "UserID" << id;


        if (!pStat->execute())
            {
                std::cout << "testSelect2 - Exec NOT ok\n";
                td::StringUTF8 strErr;
                pStat->getErrorStr(strErr);
                std::cout << strErr.c_str() << std::endl;
                return false;
            }
        else{

            if (pStat->moveNext())
            {
                if(id == user)
                    return true;
            }

            return false;
        }
}

bool Jobs::isInWork(int JobId){

    td::String status;

    td::INT4 jobId(JobId);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select Status from Jobs where Jobs.[ID] = ?"));

    db::Params params(pStat->allocParams());
        params << jobId;

    db::Columns cols(pStat->allocBindColumns(1));
        cols << "Status" << status;


        if (!pStat->execute())
            {
                std::cout << "testSelect2 - Exec NOT ok\n";
                td::StringUTF8 strErr;
                pStat->getErrorStr(strErr);
                std::cout << strErr.c_str() << std::endl;
                return false;
            }
        else{

            if (pStat->moveNext())
            {
                QString status_new = status.c_str();
                if(status_new == "IN WORK")
                    return true;
            }

            return false;
        }

}

void Jobs::on_pushButton_cancel_clicked()
{
    this->close();
}

void Jobs::on_pushButton_item_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    int uid = model->index(row, 0).data().toString().toInt();
    QString name = model->index(row,1).data().toString();

    JobItem jobItem;
    jobItem.setJobId(uid);
    jobItem.setJobName(name);
    jobItem.setFields();
    jobItem.exec();

    updateTableView();
    browseJob();
}


bool Jobs:: updateCatalogsPlacements(int Id, int type)
{
    if (!pDB)
        return false;

    td::INT4 td_typeId(type);
    td::INT4 td_catId(Id);

    db::StatementPtr pStat1(pDB->createStatement(db::IStatement::DBS_INSERT, "Update CatBusbar Set JobId = NULL where Id = ?"));
    db::StatementPtr pStat2(pDB->createStatement(db::IStatement::DBS_INSERT, "Update CatCableHead Set JobId = NULL where Id = ?"));
    db::StatementPtr pStat3(pDB->createStatement(db::IStatement::DBS_INSERT, "Update CatJunction Set JobId = NULL where Id = ?"));
    db::StatementPtr pStat4(pDB->createStatement(db::IStatement::DBS_INSERT, "Update PlacBusbar Set JobId = NULL where Id = ?"));
    db::StatementPtr pStat5(pDB->createStatement(db::IStatement::DBS_INSERT, "Update PlacCableHead Set JobId = NULL where Id = ?"));
    db::StatementPtr pStat6(pDB->createStatement(db::IStatement::DBS_INSERT, "Update PlacJunction Set JobId = NULL where Id = ?"));

    db::Params params1(pStat1->allocParams());
    params1 <<td_catId;

    db::Params params2(pStat2->allocParams());
    params2  <<td_catId;

    db::Params params3(pStat3->allocParams());
    params3 <<td_catId;

    db::Params params4(pStat4->allocParams());
    params4  <<td_catId;

    db::Params params5(pStat5->allocParams());
    params5  <<td_catId;

    db::Params params6(pStat6->allocParams());
    params6  <<td_catId;

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

void Jobs::on_pushButton_activate_clicked()
{
    int rowJobs = ui->tableView->selectionModel()->currentIndex().row();
    int jobId = model->index(rowJobs, 0).data().toString().toInt();

    td::String date = QDate::currentDate().toString("yyyy/MM/dd").toUtf8();
    db::Ref<td::String> refDate(20);
    refDate = date;

    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    td::INT4 id = (rand() % ((1000 + 1) - 0) + 0);

    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE Jobs SET Activation_date = ?, Status = 'ACTIVATED', Id = ? WHERE Id = ?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params <<refDate<<id<<jobId;

    if (!pStat->execute())
    {
        td::String strErr;
        pStat->getErrorStr(strErr);
        if (DebugTrace(1000))
            mu::getTracer() << strErr;
        //rollback will be called
    }


    //commit transaction
    bool  bRet = trans.commit();
    if (bRet)
        std::cout << "Data Updated" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Updating finished!\n";

    updateTableView();
}

void Jobs::on_deleteItem_clicked()
{
    int rowJobs = ui->tableView->selectionModel()->currentIndex().row();
    int jobId = model->index(rowJobs, 0).data().toString().toInt();

    int rowItems = ui->tableView_browse->selectionModel()->currentIndex().row();
    int id = model2->index(rowItems, 0).data().toString().toInt();
    QString type = model2->index(rowItems, 4).data().toString();
    int typeInt;

    if(type == "busbars") typeInt = 11;
    if(type == "cable heads") typeInt = 12;
    if(type == "jumpers") typeInt = 13;
    if(type == "Equivalent Source") typeInt = 20;
    if(type =="Busbar Section(vertical)") typeInt = 21;
    if(type =="Busbar section(horizontal)") typeInt = 22;
    if(type =="Busbar free style") typeInt = 23;
    if(type =="Connectivity node") typeInt = 24;
    if(type =="Cable head") typeInt = 25;
    if(type =="Source sink connector") typeInt = 26;
    if(type =="Jumper (z =0)") typeInt = 39;

    updateCatalogsPlacements(id, typeInt);

    td::INT4 td_jobId(jobId);
    td::INT4 td_typeInt(typeInt);
    td::INT4 td_id(id);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"DELETE FROM JobCatalogs where JobID = ? and TypeID = ? and CatID = ?"));
    mem::PointerReleaser<db::IStatement> pStat1(pDB->createStatement(db::IStatement::DBS_SELECT,"DELETE FROM JobPlacements where JobID = ? and TypeID = ? and PlacID = ?"));

    db::Params params(pStat->allocParams());
        params << td_jobId<< td_typeInt<< td_id;

    db::Params params1(pStat1->allocParams());
        params1 << td_jobId<< td_typeInt<< td_id;

    if(typeInt >= 11 && typeInt <= 13)
        if(!pStat->execute())
            std::cout<<"Could not delete"<<std::endl;
        else
            std::cout<<"Deleted Sucessfully"<<std::endl;
    else
        if(!pStat1->execute())
            std::cout<<"Could not delete"<<std::endl;
        else
            std::cout<<"Deleted Sucessfully"<<std::endl;

    updateTableView();
    browseJob();
}
