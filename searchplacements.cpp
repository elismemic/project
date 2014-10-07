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
#include "junctionplacement.h"

extern db::ISQLDatabase *pDB;
extern int globalJobId;
SearchPlacements::SearchPlacements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchPlacements)
{
    ui->setupUi(this);
    //connectSQLite();
    selectPhaseCode();
    selectSectionType();
    selectType();
    checkJob();
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

void SearchPlacements::checkJob() {
    if(globalJobId>0){
        ui->pushButton_new->setEnabled(false);
        ui->pushButton_delete->setEnabled(false);
}
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
    selectPlacement();
}

void SearchPlacements::on_pushButton_edit_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    QString uid = model->index(row, 0).data().toString();

    BusbarPlacement busbar;
    CableHeadPlacement cableHead;
    JunctionPlacement junction;

    if(catalogType == 1){
        busbar.setUid(uid.toInt());
        busbar.setPlacementType(this->placementType);
        busbar.updateForm(uid.toInt());
        busbar.enableUid(false);
        busbar.setWindowName();
        busbar.checkJob();
        busbar.exec();
    }

    if(catalogType == 2){
        cableHead.setUid(uid.toInt());
        cableHead.setPlacementType(this->placementType);
        cableHead.updateForm(uid.toInt());
        cableHead.enableUid(false);
        cableHead.setWindowName();
        cableHead.exec();
    }

    if(catalogType == 3){
        junction.setUid(uid.toInt());
        junction.setPlacementType(this->placementType);
        junction.updateForm(uid.toInt());
        junction.enableUid(false);
        junction.setWindowName();
        junction.exec();
    }


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

void SearchPlacements::setPlacementType(int placementType){
    this->placementType = placementType;
}

bool SearchPlacements::selectPlacement()
{

    if (!pDB)
        return false;


    int phase_code = ui->comboBox_phase_code->currentIndex();
    int section_type = ui->comboBox_sec_type->currentIndex();

    QString searchMe = ui->lineEdit_search->text();
    if(ui->comboBox_type->currentIndex()!=0 || ui->comboBox_type->currentIndex()!=3)
    searchMe.append('%');

    db::Ref<td::String> refSearchme(20);
    td::String td_searchMe = searchMe.toUtf8();
    refSearchme = td_searchMe;

    td::INT4 td_PlacementType(this->placementType);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select PlacNaming.Id, PlacNaming.Name, Alias_Name, phase_code.Name as Phase_Code, PlacNaming.Description from PlacNaming inner join phase_code on PlacNaming.Phase_Code = phase_code.Id  where (PlacNaming.Id LIKE ? or PlacNaming.Alias_Name LIKE ? or PlacNaming.Name LIKE ? or Phase_Code = ?) and TypeId = ?"));
    db::Params params(pStat->allocParams());


    if(ui->comboBox_type->currentIndex() != 3)
       phase_code = -3;
    if(ui->comboBox_type->currentIndex() != 4)
        section_type = -3;

    params <<refSearchme<<refSearchme<<refSearchme<<phase_code<<td_PlacementType;;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(5);

        columns[0].name = "Id";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 50;

        columns[2].name = "Alias_Name";
        columns[2].tdType = td::nch;
        columns[2].len = 0;

        columns[3].name = "Phase_Code";
        columns[3].tdType = td::nch;
        columns[3].len = 0;

        columns[4].name = "Description";
        columns[4].tdType = td::nch;
        columns[4].len = 0;



        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))

            return false;

        if(rs->rowCount()!=0)
            enableButtons();
        else
            disableButtons();


        checkJob();


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
    JunctionPlacement junction;

    if(catalogType == 1){
        busbar.enableUid(true);
        busbar.setPlacementType(this->placementType);
        busbar.setWindowName();
        busbar.exec();
    }
    if(catalogType == 2){
        cableHead.enableUid(true);
        cableHead.setPlacementType(this->placementType);
        cableHead.setWindowName();
        cableHead.exec();
    }
    if(catalogType == 3){
        junction.enableUid(true);
        junction.setPlacementType(this->placementType);
        junction.setWindowName();
        junction.exec();
    }
}

void SearchPlacements::on_pushButton_delete_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    QString uid = model->index(row, 0).data().toString();

    BusbarPlacement busbar;
    CableHeadPlacement cableHead;
    JunctionPlacement junction;

    if(catalogType == 1){
        busbar.setPlacementType(this->placementType);
        busbar.setWindowName();
        busbar.deleteNaming(uid.toInt());
        busbar.deletePlacement(uid.toInt());
        this->selectPlacement();
        ui->lineEdit_search->setText("");

    }
    if(catalogType == 2){
        cableHead.setPlacementType(this->placementType);
        cableHead.setWindowName();
        cableHead.deleteNaming(uid.toInt());
        cableHead.deletePlacement(uid.toInt());
        this->selectPlacement();
        ui->lineEdit_search->setText("");
    }
    if(catalogType == 3){
        junction.setPlacementType(this->placementType);
        junction.setWindowName();
        junction.deleteNaming(uid.toInt());
        junction.deletePlacement(uid.toInt());
        this->selectPlacement();
        ui->lineEdit_search->setText("");
    }
}



void SearchPlacements::on_lineEdit_search_textChanged()
{
    selectPlacement();
}
