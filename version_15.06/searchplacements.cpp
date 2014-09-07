#include "searchplacements.h"
#include "ui_searchplacements.h"
#include <QAbstractButton>
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "busbar.h"
#include "junction.h"
#include "cablehead.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mymodel.h"
#include <QAbstractItemModel>
#include "busbarplacement.h"
#include "cableheadplacement.h"

SearchPlacements::SearchPlacements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchPlacements)
{
    ui->setupUi(this);
    connectSQLite();
    selectPhaseCode();
    selectSectionType();
    selectType();
    ui->comboBox_phase_code->setVisible(false);
    ui->comboBox_sec_type->setVisible(false);
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_edit->setEnabled(false);

}

SearchPlacements::~SearchPlacements()
{
    delete ui;
}

void SearchPlacements::enableButtons(){
    ui->pushButton_delete->setEnabled(true);
    ui->pushButton_edit->setEnabled(true);
}

void SearchPlacements::disableButtons(){
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_edit->setEnabled(false);

}

bool SearchPlacements::connectSQLite()
{
    pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);

    if (!pDB->connect("C:/Users/nevres/Downloads/project.db"))
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



void SearchPlacements::selectType()
{
    ui->comboBox_type->addItem("Id",0);
    ui->comboBox_type->addItem("Name",1);
    ui->comboBox_type->addItem("Alias Name",2);
    ui->comboBox_type->addItem("Phase Code",3);
    ui->comboBox_type->addItem("Section Type",4);
}


void SearchPlacements::on_comboBox_type_currentIndexChanged(int index)
{
    if(index == 3){
        ui->lineEdit_search->setVisible(false);
        ui->comboBox_sec_type->setVisible(false);
        ui->comboBox_phase_code->setVisible(true);
    }else if(index == 4){
        ui->lineEdit_search->setVisible(false);
        ui->comboBox_sec_type->setVisible(true);
        ui->comboBox_phase_code->setVisible(false);
    }else{
        ui->lineEdit_search->setVisible(true);
        ui->comboBox_sec_type->setVisible(false);
        ui->comboBox_phase_code->setVisible(false);
    }
}


void SearchPlacements::on_pushButton_search_clicked()
{
    if(catalogType == 1)
        selectBusbarPlacement();
    if(catalogType == 2)
        selectCableHeadPlacement();
    if(catalogType == 3)
        selectJunctionPlacement();
}

void SearchPlacements::on_pushButton_edit_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    QString uid = model->index(row, 0).data().toString();

    BusbarPlacement busbar;
    CableHeadPlacement cableHead;
    //Junction junction;

    if(catalogType == 1){
        busbar.setUid(uid.toInt());
        busbar.enableUid(false);
        busbar.exec();
    }
    if(catalogType == 2){
        cableHead.setUid(uid.toInt());
        cableHead.enableUid(false);
        cableHead.exec();
    }/*
    if(catalogType == 3){
        junction.setUid(uid.toInt());
        junction.enableUid(false);
        junction.exec();
    }*/

}


bool SearchPlacements::selectSectionType(){

    int id;
    td::String name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Id,Name from section_type"));

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "Id" << id
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
                ui->comboBox_sec_type->addItem(QString::fromUtf8(name.c_str()),QString::number(id));
            }

            std::cout<< "Transaction OK" <<std::endl;
            return true;
        }
}


bool SearchPlacements::selectPhaseCode(){
    int id;
    td::String name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Id,Name from phase_code"));

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "Id" << id
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
                ui->comboBox_phase_code->addItem(QString::fromUtf8(name.c_str()),QString::number(id));
            }

            std::cout<< "Transaction OK" <<std::endl;
            return true;
        }
}

bool SearchPlacements::selectBusbarPlacement()
{

    if (!pDB)
        return false;


    int phase_code = ui->comboBox_phase_code->currentIndex();
    int section_type = ui->comboBox_sec_type->currentIndex();

    QString searchMe = ui->lineEdit_search->text();

    db::Ref<td::String> refSearchme(20);
    td::String td_searchMe = searchMe.toUtf8();
    refSearchme = td_searchMe;


    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select busbar_placement.Id, busbar_placement.Name, busbar_placement.Alias_Name, busbar_catalog.Name as Catalog_Type, section_type.Name as Busbar_Section_Type, phase_code.Name as Phase_Code, busbar_placement.Description from busbar_placement inner join busbar_catalog inner join section_type inner join phase_code on busbar_placement.Catalog_Type = busbar_catalog.Id and Section_Type = section_type.Id and busbar_placement.Phase_Code = phase_code.Id where busbar_placement.Id = ? or busbar_placement.Name = ? or busbar_placement.Alias_Name = ? or busbar_placement.Section_Type = ? or busbar_placement.Phase_Code = ?"));
    db::Params params(pStat->allocParams());

    if(ui->comboBox_type->currentIndex() != 3)
       phase_code = -3;
    if(ui->comboBox_type->currentIndex() != 4)
        section_type = -3;

    params <<refSearchme<<refSearchme<<refSearchme<<section_type<<phase_code;;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(7);

        columns[0].name = "Id";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 50;

        columns[2].name = "Alias_Name";
        columns[2].tdType = td::nch;
        columns[2].len = 0;

        columns[3].name = "Catalog_Type";
        columns[3].tdType = td::nch;
        columns[3].len = 0;

        columns[4].name = "Busbar_Section_Type";
        columns[4].tdType = td::nch;
        columns[4].len = 0;

        columns[5].name = "Phase_Code";
        columns[5].tdType = td::nch;
        columns[5].len = 0;

        columns[6].name = "Description";
        columns[6].tdType = td::nch;
        columns[6].len = 0;


        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))

            return false;

        if(rs->rowCount()!=0)
            enableButtons();
        else
            disableButtons();

        model = new MyModel(this, rs, true);


        //change stripe color
        /*td::Color c;
        c.setColor(20,150,20);
        model->setStripeColor(c);*/

        ui->tableView->setModel(model);
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setStretchLastSection(true);

        return true;
}

bool SearchPlacements::selectCableHeadPlacement()
{

    if (!pDB)
        return false;

    int phase_code = ui->comboBox_phase_code->currentIndex();
    int section_type = ui->comboBox_sec_type->currentIndex();

    QString searchMe = ui->lineEdit_search->text();

    db::Ref<td::String> refSearchme(20);
    td::String td_searchMe = searchMe.toUtf8();
    refSearchme = td_searchMe;


    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select cable_head_placement.Id, cable_head_placement.Name, cable_head_placement.Alias_Name, cable_head_catalog.Name as Catalog_Type, section_type.Name as Section_Type, phase_code.Name as Phase_Code, cable_head_placement.Description from cable_head_placement inner join cable_head_catalog inner join section_type inner join phase_code on cable_head_placement.Catalog_Type = cable_head_catalog.Id and Section_Type = section_type.Id and cable_head_placement.Phase_Code = phase_code.Id where cable_head_placement.Id = ? or cable_head_placement.Name = ? or cable_head_placement.Alias_Name = ? or cable_head_placement.Section_Type = ? or cable_head_placement.Phase_Code = ?"));
    db::Params params(pStat->allocParams());

    if(ui->comboBox_type->currentIndex() != 3)
       phase_code = -3;
    if(ui->comboBox_type->currentIndex() != 4)
        section_type = -3;

    params <<refSearchme<<refSearchme<<refSearchme<<section_type<<phase_code;


    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(7);

        columns[0].name = "Id";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 50;

        columns[2].name = "Alias_Name";
        columns[2].tdType = td::nch;
        columns[2].len = 0;

        columns[3].name = "Catalog_Type";
        columns[3].tdType = td::nch;
        columns[3].len = 0;

        columns[4].name = "Section_Type";
        columns[4].tdType = td::nch;
        columns[4].len = 0;

        columns[5].name = "Phase_Code";
        columns[5].tdType = td::nch;
        columns[5].len = 0;

        columns[6].name = "Description";
        columns[6].tdType = td::nch;
        columns[6].len = 0;


        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))

            return false;

        if(rs->rowCount()!=0)
            enableButtons();
        else
            disableButtons();

        model = new MyModel(this, rs, true);


        //change stripe color
        /*td::Color c;
        c.setColor(20,150,20);
        model->setStripeColor(c);*/

        ui->tableView->setModel(model);
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setStretchLastSection(true);

        return true;
}

bool SearchPlacements::selectJunctionPlacement()
{

    if (!pDB)
        return false;

    QString searchMe = ui->lineEdit_search->text();

    db::Ref<td::String> refSearchme(20);
    td::String td_searchMe = searchMe.toUtf8();
    refSearchme = td_searchMe;


    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select junction_catalog.Id, junction_catalog.Name, junction_catalog.Alias_Name, rated_voltage.Name as Voltage, junction_type.Name as Junction, junction_catalog.Description from junction_catalog inner join rated_voltage inner join junction_type on junction_catalog.Rated_Voltage = rated_voltage.Id and junction_catalog.[Junction_Type] = junction_type.[Id] where junction_catalog.Id = ? or junction_catalog.Name = ? or Alias_Name = ? or Rated_Voltage = ?"));
    db::Params params(pStat->allocParams());

    //if(ui->comboBox_type->currentIndex() != 3)
      //  searchMeRatedVoltage = -3;

    params <<refSearchme<<refSearchme<<refSearchme;


    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(6);

        columns[0].name = "Id";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 50;

        columns[2].name = "Alias_Name";
        columns[2].tdType = td::nch;
        columns[2].len = 0;

        columns[3].name = "Voltage";
        columns[3].tdType = td::nch;
        columns[3].len = 0;

        columns[4].name = "Junction";
        columns[4].tdType = td::nch;
        columns[4].len = 0;

        columns[5].name = "Description";
        columns[5].tdType = td::nch;
        columns[5].len = 0;


        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))
            return false;

        if(rs->rowCount()!=0)
            enableButtons();
        else
            disableButtons();

        model = new MyModel(this, rs, true);


        //change stripe color
        /*td::Color c;
        c.setColor(20,150,20);
        model->setStripeColor(c);*/

        ui->tableView->setModel(model);
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setStretchLastSection(true);

        return true;
}

void SearchPlacements::setCatalogType(int type){
    catalogType = type;
}


void SearchPlacements::on_pushButton_clicked()
{
    close();
}

void SearchPlacements::on_pushButton_new_clicked()
{
    BusbarPlacement busbar;
    CableHeadPlacement cableHead;
    //Junction junction;

    if(catalogType == 1){
        busbar.enableUid(true);
        busbar.exec();
    }
    if(catalogType == 2){
        cableHead.enableUid(true);
        cableHead.exec();
    }

}
