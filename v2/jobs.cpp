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
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mymodel.h"
#include "busbar.h"
#include "jobitem.h"
#include <QAbstractItemModel>

Jobs::Jobs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Jobs)
{
    ui->setupUi(this);
    connectSQLite();
    selectType();
    selectStatus();
    selectOwner();

    ui->tableView_browse->setVisible(false);
    ui->comboBox_owner->setVisible(false);
    ui->comboBox_status->setVisible(false);

    ui->pushButton_activate->setEnabled(false);
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_item->setEnabled(false);
}


bool Jobs::connectSQLite()
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

}

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

    int id;
    td::String status;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID,Name from Status"));

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "ID" << id
             << "Name" << status;

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
                ui->comboBox_status->addItem(QString::fromUtf8(status.c_str()),QString::number(id));
            }

            std::cout<< "Transaction OK" <<std::endl;
            return true;
        }
}

Jobs::~Jobs()
{
    delete ui;
}

void Jobs::selectType()
{
    ui->comboBox_type->addItem("Id",0);
    ui->comboBox_type->addItem("Name",1);
    ui->comboBox_type->addItem("Owner",2);
    ui->comboBox_type->addItem("Status",3);

}

void Jobs::on_comboBox_type_currentIndexChanged(int index)
{
    if(index == 2){
        ui->lineEdit_search->setVisible(false);
        ui->comboBox_owner->setVisible(true);
        ui->comboBox_status->setVisible(false);
    }else if(index == 3){
        ui->lineEdit_search->setVisible(false);
        ui->comboBox_status->setVisible(true);
        ui->comboBox_owner->setVisible(false);
    }else{
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
    int status = ui->comboBox_status->currentIndex();
    int owner = ui->comboBox_owner->currentIndex();


    db::Ref<td::String> refSearchme(20);
    td::String td_searchMe = searchMe.toUtf8();
    refSearchme = td_searchMe;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Jobs.ID, Jobs.Name, Users.Name as User, Status.Name as Status, Creation_date, Activation_date from Jobs inner join Users inner join Status on Jobs.UserID = Users.ID and Jobs.Status = Status.ID where Jobs.ID= ? or Jobs.Name = ? or Jobs.UserID = ? or Status = ?"));
    db::Params params(pStat->allocParams());

    if(ui->comboBox_type->currentIndex() != 2)
        owner = -3;
    if(ui->comboBox_type->currentIndex() != 3)
        status = -3;

    params << refSearchme << refSearchme << owner << status;

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

        if(rs->rowCount() != 0){
            enableButtons();
        }

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
    ui->tableView_browse->setVisible(true);
    browseJob();
}

void Jobs::enableButtons(){
    ui->pushButton_activate->setEnabled(true);
    ui->pushButton_item->setEnabled(true);
    ui->pushButton_delete->setEnabled(true);
    ui->pushButton_edit->setEnabled(true);
}


void Jobs::disableButtons(){
    ui->pushButton_activate->setEnabled(false);
    ui->pushButton_item->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_edit->setEnabled(false);
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


    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select CatNaming.Id as Id, CatNaming.Name as Name, Alias_Name, Description, EnumPSTypes.[Name] as Type from CatNaming inner join JobCatalogs inner join EnumPSTypes on JobCatalogs.CatID = CatNaming.[Id] and JobCatalogs.[CatID] = CatNaming.[Id] and CatNaming.[TypeId] = EnumPSTypes.[ID] where JobCatalogs.JobID = ? UNION select PlacNaming.Id as Id, PlacNaming.Name as Name, Alias_Name, Description, EnumPSTypes.[Name] as Type from PlacNaming inner join JobPlacements inner join EnumPSTypes on JobPlacements.PlacID = PlacNaming.Id and JobPlacements.PlacID = PlacNaming.ID and PlacNaming.[TypeId] = EnumPSTypes.ID where JobPlacements.JobID = ?"));
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

    if(type == "busbars"){busbar.setUid(uid); busbar.enableUid(false); busbar.exec();}
    if(type == "cable heads"){cable_head.setUid(uid); cable_head.enableUid(false); cable_head.exec();}
    if(type == "jumpers"){junction.setUid(uid); junction.enableUid(false); junction.exec();}
    //if(type == "Busbar Placement"){bb_placement.setUid(getUidByName(name)); bb_placement.exec();}
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
    ui->tableView_browse->setVisible(true);
    browseJob();
}

void Jobs::on_pushButton_edit_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    int uid = model->index(row, 0).data().toString().toInt();

    CreateJob job;
    job.updateForm(uid);
    job.exec();
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
}
