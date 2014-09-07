#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "searchplacements.h"
#include "busbar.h"
#include "junction.h"
#include "busbarsearch.h"
#include "cablehead.h"
#include "db/Recordset.h"
#include "jobs.h"
#include <QTranslator>
#include "db/ISQLDataProvider.h"
#include <QMessageBox>
#include <QFileDialog>

db::ISQLDatabase *pDB;

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
}


bool MainWindow::connectSQLite(){

if (pDB)
    pDB->release();

    pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);
    //give path for our database
//if (!pDB->connect(file.toUtf8().constData()))

 if(!pDB->connect("C:/Users/nevres/Downloads/project.db")){
    QMessageBox::information(this,"Connection status","Could not connect to database");
    td::String err;
    pDB->getErrorStr(err);
    std::cout << err.c_str() << std::endl;
    pDB->release();
    pDB = 0;
    return false;
}else
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
    search.exec();
}

void MainWindow::on_actionConnectivity_Node_triggered()
{
    SearchPlacements search;
    search.setCatalogType(2);
    search.exec();
}

void MainWindow::on_actionSearch_Jobs_triggered()
{
    Jobs jobs;
    jobs.exec();
}

void MainWindow::on_pushButton_OK_clicked()
{
    //QString user = ui->lineEdit_username->text();
    //QString password = ui->lineEdit_password->text();
    //if(connectSQLite())
      //  if(checkUser(user,password)){
            ui->centralWidget->setVisible(false);
            ui->menuBar->setVisible(true);
//}
        //else
          //  QMessageBox::information(this,"LogIn Status","Could not Authenticate User, Try Again");
}

void MainWindow::on_pushButton_DB_clicked()
{
    file = QFileDialog::getOpenFileName(this,"Open a database","C:/","Database files (*.db *.db3)");
    ui->pushButton_OK->setEnabled(true);
}

void MainWindow::on_actionAbout_Software_triggered()
{
    QMessageBox::information(this,"About Software","Software is being developed by Students at International University of Sarajevo");
}
