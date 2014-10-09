#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "job.h"
#include "user.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QFileDialog"
#include "QMessageBox"
#include <qstring.h>
#include "searchwindowconductor.h"
#include "searchwindowcapacitor.h"
#include "searchwindowbankplacement.h"
#include "conductor.h"
#include "capacitor.h"
#include "capacitorbankplacement.h"

db::ISQLDatabase *pDB = 0;
int userID;
int jobID;
int user_jobID;
bool edit = false;
bool editClicked = true;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connectSQLite();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::connectSQLite()
{
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

void MainWindow::on_actionOpen_triggered()
{
    if(userID)
    {
        job j;
        j.setModal(true);
        j.exec();
        if(edit)
            status = "Current User ID = " + QString::number(userID)+ " Job ID = " + QString::number(jobID) + " User ID of job owner = " + QString::number(user_jobID)+ " Edit Mode";
        else
            status = "Current User ID = " + QString::number(userID)+ " Job ID = " + QString::number(jobID) + " User ID of job owner = " + QString::number(user_jobID)+ " Browse Mode";
        ui->statusbar->showMessage(status);
        setStatusTip(status);
        setStatusBar(ui->statusbar);
    }
    else
        QMessageBox::information(this,"Error ... ","Select user before exploring jobs!");
}

void MainWindow::on_actionOpen_2_triggered()
{
    user u;
    u.setModal(true);
    u.exec();
}

void MainWindow::on_actionCapacitor_triggered()
{

    if(userID)
    {
        SearchWindowCapacitor searchCapacitor;
        searchCapacitor.setModal(true);
        searchCapacitor.exec();
    }
    else
        QMessageBox::information(this,"Error ... ","Please select user.");

}

void MainWindow::on_actionConductor_triggered()
{
    //SearchWindowConductor searchConductor;
    //searchConductor.setModal(true);
    //searchConductor.exec();
}

void MainWindow::on_actionCapPlac_triggered()
{
    //SearchWindowBankPlacement capacitorbankplacement;
    //capacitorbankplacement.setModal(true);
    //capacitorbankplacement.exec();
}
