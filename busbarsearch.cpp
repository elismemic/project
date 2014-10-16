#include "busbarsearch.h"
#include "ui_busbarsearch.h"
#include "cablehead.h"
#include "junction.h"
#include <QAbstractButton>
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mymodel.h"
#include "busbar.h"
#include <QAbstractItemModel>
#include "mainwindow.h"
#include "QMessageBox"

extern int globalJobId;
extern int chosenJobId=0;

extern db::ISQLDatabase *pDB;


BusbarSearch::BusbarSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BusbarSearch)
{
    ui->setupUi(this);
    selectVoltage();
    selectType();
    checkJob();
    ui->comboBox_voltage->setVisible(false);

    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_edit->setEnabled(false);

}

BusbarSearch::~BusbarSearch()
{
    delete ui;
}

void BusbarSearch::enableButtons(){
    ui->pushButton_delete->setEnabled(true);
    ui->pushButton_edit->setEnabled(true);
}

void BusbarSearch::disableButtons(){
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_edit->setEnabled(false);

}

void BusbarSearch::checkJob() {
    if(globalJobId>0){
        ui->pushButton_new->setEnabled(false);
        ui->pushButton_delete->setEnabled(false);
    }
}


void BusbarSearch::selectType()
{
    ui->comboBox_type->addItem("Id",0);
    ui->comboBox_type->addItem("Name",1);
    ui->comboBox_type->addItem("Alias Name",2);
    ui->comboBox_type->addItem("Rated Voltage",3);
}


void BusbarSearch::on_comboBox_type_currentIndexChanged(int index)
{
    if(index == 3){
        ui->lineEdit_search->setVisible(false);
        ui->comboBox_voltage->setVisible(true);
        if(catalogType == 1)
            selectCatalogs(11);
        if(catalogType == 2)
            selectCatalogs(12);
        if(catalogType == 3)
            selectCatalogs(13);
    }else{
        ui->lineEdit_search->setVisible(true);
        ui->comboBox_voltage->setVisible(false);
    }
}

int BusbarSearch::getChosenJobId(int job)
{
    chosenJobId=job;
    return chosenJobId;
}

void BusbarSearch::on_pushButton_edit_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    QString uid = model->index(row, 0).data().toString();
    QString jobid = model->index(row, 5).data().toString();
    getChosenJobId(jobid.toInt());

    if(jobid.toInt()<0 && jobid.toInt()!=globalJobId){
        QMessageBox::information(this,"Authority info","Can not edit");
        Busbar busbar;
        CableHead cableHead;
        Junction junction;

        if(catalogType == 1){
            busbar.setUid(uid.toInt());
            busbar.enableUid(false);
            busbar.checkJob();
            busbar.disableButtons();
            busbar.exec();
        }
        if(catalogType == 2){
            cableHead.setUid(uid.toInt());
            cableHead.enableUid(false);
            cableHead.checkJob();
            cableHead.disableButtons();
            cableHead.exec();
        }
        if(catalogType == 3){
            junction.setUid(uid.toInt());
            junction.enableUid(false);
            junction.checkJob();
            junction.disableButtons();
            junction.exec();
        }
    }

    else
    {
    Busbar busbar;
    CableHead cableHead;
    Junction junction;

    if(catalogType == 1){
        busbar.setUid(uid.toInt());
        busbar.enableUid(false);
        busbar.checkJob();
        busbar.exec();
    }
    if(catalogType == 2){
        cableHead.setUid(uid.toInt());
        cableHead.enableUid(false);
        cableHead.checkJob();
        cableHead.exec();
    }
    if(catalogType == 3){
        junction.setUid(uid.toInt());
        junction.enableUid(false);
        junction.checkJob();
        junction.exec();
    }

}
}


bool BusbarSearch::selectCatalogs(int type)
{

    if (!pDB)
        return false;

    QString searchMe = ui->lineEdit_search->text();
    if(ui->comboBox_type->currentIndex()!=0)
    searchMe.append('%');
    int searchMeRatedVoltage = ui->comboBox_voltage->currentIndex();

    if(ui->comboBox_type->currentIndex() != 3)
        searchMeRatedVoltage = -3;
    else{
        searchMe.append("%");
    }

    db::Ref<td::String> refSearchme(20);
    td::String td_searchMe = searchMe.toUtf8();
    //td::INT4 td_jobId;

    refSearchme = td_searchMe;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select CatNaming.Id, CatNaming.Name, Alias_Name, rated_voltage.Name as Rated_Voltage, CatNaming.Description, CatNaming.JobId from CatNaming inner join rated_voltage on CatNaming.Rated_Voltage = rated_voltage.Id  where (CatNaming.Id = ? or CatNaming.Name LIKE ? or Alias_Name LIKE ? or CatNaming.Rated_Voltage = ?) and TypeId = ? "));
    db::Params params(pStat->allocParams());

    params <<refSearchme<<refSearchme<<refSearchme<<searchMeRatedVoltage<<type;

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

        columns[3].name = "Rated_Voltage";
        columns[3].tdType = td::nch;
        columns[3].len = 0;

        columns[4].name = "Description";
        columns[4].tdType = td::nch;
        columns[4].len = 0;

        columns[5].name = "JobId";
        columns[5].tdType = td::int4;
        columns[5].len = 0;

       // db::Columns cols(pStat->allocBindColumns(1));
           // cols << "JobId" << td_jobId;




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

void BusbarSearch::setCatalogType(int type){
    catalogType = type;
}

bool BusbarSearch::selectVoltage()
{
    if (!pDB){
         std::cout<< "Transaction failed not pDB" <<std::endl;
         return false;}

    int id;
    double voltage;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Id,Voltage from rated_voltage"));

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "Id" << id
             << "Voltage" << voltage;

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
                ui->comboBox_voltage->addItem(QString::number(voltage),QString::number(id));
            }

            std::cout<< "Transaction OK" <<id<<voltage<<std::endl;
            return true;
        }
}


void BusbarSearch::on_pushButton_clicked()
{
    close();
}

void BusbarSearch::on_pushButton_new_clicked()
{

    if(globalJobId>0)
        QMessageBox::information(this,"Authority info","Job is activated");

else{

    Busbar busbar;
    CableHead cableHead;
    Junction junction;

    if(catalogType == 1){
        busbar.enableUid(true);
        busbar.checkJob();
        busbar.exec();
    }
    else if(catalogType == 2){
        cableHead.enableUid(true);
        cableHead.checkJob();
        cableHead.exec();
    }
    else if(catalogType == 3){
        junction.enableUid(true);
        junction.checkJob();
        junction.exec();
    }
}
    }

void BusbarSearch::on_lineEdit_search_textChanged()
{
    if(catalogType == 1)
        selectCatalogs(11);
    if(catalogType == 2)
        selectCatalogs(12);
    if(catalogType == 3)
        selectCatalogs(13);
}

void BusbarSearch::on_comboBox_voltage_currentIndexChanged()
{
    if(catalogType == 1)
        selectCatalogs(11);
    if(catalogType == 2)
        selectCatalogs(12);
    if(catalogType == 3)
        selectCatalogs(13);
}

void BusbarSearch::on_pushButton_delete_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    int uid = model->index(row, 0).data().toString().toInt();
    QString jobid = model->index(row, 5).data().toString();

    if(jobid.toInt()<0 && jobid.toInt()!=globalJobId){

        QMessageBox::information(this,"Authority info","Can not delete");

        ui->lineEdit_search->setText("");
    }
    else{

    Busbar busbar;
    CableHead cableHead;
    Junction junction;

    if(catalogType == 1){
        busbar.deleteCatalog(uid);
        //busbar.deleteNaming(uid);
    }
    else if(catalogType == 2){
        cableHead.deleteCatalog(uid);
        //cableHead.deleteNaming(uid);
    }
    else if(catalogType == 3){
        junction.deleteCatalog(uid);
        //junction.deleteNaming(uid);
    }

    ui->lineEdit_search->setText("");
}
    }


