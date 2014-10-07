#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "searchplacements.h"
#include "busbar.h"
#include "junction.h"
#include "busbarsearch.h"
#include "cablehead.h"
#include "db/Recordset.h"
//#include "jobs.h"
#include <QTranslator>
#include "db/ISQLDataProvider.h"
#include <QMessageBox>
#include <QFileDialog>

db::ISQLDatabase *pDB=0;
int user;
extern int globalJobId=0;
extern int sysId=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    trans.load("translationEn.qm");
    QApplication::instance()->installTranslator(&trans);
    ui->pushButton_OK->setEnabled(true);
    ui->menuBar->setVisible(false);
    connectSQLite();
    std::cout<<"job id is: "<<globalJobId;
}

int MainWindow::setJobId() {
    globalJobId = ui->lineEdit_JobId->text().toInt();
        return globalJobId;
}

int MainWindow::setSysId() {
    sysId = ui->lineEdit_SysId->text().toInt();
        return sysId;
}

bool MainWindow::connectSQLite(){

    if (pDB)
           pDB->release();

           QString file = QFileDialog::getOpenFileName(this,"Open a database","C:/","Database files (*.db *.db3)");
           pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);
           //give path for our database
       if (!pDB->connect(file.toUtf8().constData()))
       {
           QMessageBox::information(this,"Connection status","Could not connect to database");
           td::String err;
           pDB->getErrorStr(err);
           std::cout << err.c_str() << std::endl;
           pDB->release();
           pDB = 0;
           return false;
       }
           QMessageBox::information(this,"Connection status","Connection OK");
       return true;

}


bool MainWindow::checkUser(QString username, QString password){


    db::Ref<td::String> refUsername(20);
    td::String td_username = username.toUtf8();
    refUsername = td_username;

    db::Ref<td::String> refPass(20);
    td::String td_pass = password.toUtf8();
    refPass = td_pass;


    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select Id, Name from  Users where Name = ? and  Password = ?"));
    db::Params params(pStat->allocParams());
    params <<refUsername<<refPass;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(1);

        columns[0].name = "Name";
        columns[0].tdType = td::nch;
        columns[0].len = 0;


        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))
            return false;

        if(rs->rowCount()!=0)
            return true;
        else
            return false;

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionBusbars_triggered()
{
    BusbarSearch myDialog;
    myDialog.setCatalogType(1);
    myDialog.exec();
}

void MainWindow::on_actionCableHeads_triggered()
{
    BusbarSearch myDialog;
    myDialog.setCatalogType(2);
    myDialog.exec();
}

void MainWindow::on_actionJumpers_triggered()
{
    BusbarSearch myDialog;
    myDialog.setCatalogType(3);
    myDialog.exec();
}


void MainWindow::changeLanguageTo(QString lang)
{
    trans.load(lang);
}

void MainWindow::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
          }
    QMainWindow::changeEvent(e);
}

void MainWindow::on_actionTurkish_triggered()
{
    changeLanguageTo("translationEn.qm");
}

void MainWindow::on_actionBosnian_triggered()
{
    changeLanguageTo("translation.qm");
}

void MainWindow::on_actionEquivalent_Source_triggered()
{
    SearchPlacements search;
    search.setCatalogType(1);
    search.setPlacementType(20);
    search.exec();
}

void MainWindow::on_actionConnectivity_Node_triggered()
{
    SearchPlacements search;
    search.setCatalogType(2);
    search.setPlacementType(24);
    search.exec();
}

/*void MainWindow::on_actionSearch_Jobs_triggered()
{
    Jobs jobs;
    jobs.exec();
}*/

void MainWindow::on_pushButton_OK_clicked()
{
    setJobId();
    setSysId();
    QString username = ui->lineEdit_username->text();

            setUserId(username);
            hideComponents();
            ui->menuBar->setVisible(true);

}


void MainWindow::on_actionAbout_Software_triggered()
{
    QMessageBox::information(this,"About Software","Software is being developed by Students at International University of Sarajevo");
}

void MainWindow::setUserId(QString username)
{
    if (!pDB){
         std::cout<< "Transaction failed, Database Connection not Created" <<std::endl;}

    int id;

    db::Ref<td::String> refName(20);
    td::String td_name = username.toUtf8();
    refName = td_name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"Select ID from Users where Name = ?"));

    db::Params params(pStat->allocParams());
        params <<refName;

    db::Columns cols(pStat->allocBindColumns(1));
        cols << "ID" << id;

        if (!pStat->execute())
            {
                std::cout << "testSelect2 - Exec NOT ok\n";
                td::StringUTF8 strErr;
                pStat->getErrorStr(strErr);
                std::cout << strErr.c_str() << std::endl;
            }

        if(pStat->moveNext()){
             user = id;
        }
user = id;
}

void MainWindow::on_actionBusbar_Section_Vertical_triggered()
{
    SearchPlacements search;
    search.setCatalogType(1);
    search.setPlacementType(21);
    search.exec();
}

void MainWindow::on_actionBusbar_Section_Horizontal_triggered()
{
    SearchPlacements search;
    search.setCatalogType(1);
    search.setPlacementType(22);
    search.exec();
}

void MainWindow::on_actionBusbar_Free_Style_triggered()
{
    SearchPlacements search;
    search.setCatalogType(1);
    search.setPlacementType(23);
    search.exec();
}

void MainWindow::on_actionCable_Had_triggered()
{
    SearchPlacements search;
    search.setCatalogType(2);
    search.setPlacementType(25);
    search.exec();
}

void MainWindow::on_actionSource_Sink_Connector_triggered()
{
    SearchPlacements search;
    search.setCatalogType(2);
    search.setPlacementType(26);
    search.exec();
}

void MainWindow::on_actionJumper_z_0_triggered()
{
    SearchPlacements search;
    search.setCatalogType(3);
    search.setPlacementType(39);
    search.exec();
}

void MainWindow::hideComponents(){
    ui->label_name->setVisible(false);
    ui->label_password->setVisible(false);
    ui->label_JobId->setVisible(false);
    ui->lineEdit_username->setVisible(false);
    ui->lineEdit_password->setVisible(false);
    ui->lineEdit_JobId->setVisible(false);
    ui->lineEdit_SysId->setVisible(false);
    ui->pushButton_OK->setVisible(false);
    ui->label_SysId->setVisible(false);
}

