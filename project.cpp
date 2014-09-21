#include "project.h"
#include "ui_project.h"
#include "QMessageBox"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QFileDialog"
#include "searchwindowconductor.h"
#include "searchwindowcapacitor.h"
#include "searchwindowbankplacement.h"
#include "conductor.h"
#include "capacitor.h"
#include "capacitorbankplacement.h"

extern db::ISQLDatabase *pDB=0;
extern int JobID = 0;
extern bool editable = true;
extern bool editClicked = false;
Project::Project(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Project)
{
    ui->setupUi(this);
    connectSQLite();
}

Project::~Project()
{
    delete ui;
}

int Project::getJobId()
{
    JobID = ui->lineEdit->text().toInt();
    return JobID;
}

bool Project::connectSQLite()
{
    if (pDB)
        pDB->release();

        QString file = QFileDialog::getOpenFileName(this,"Open a database","C:/","Database files (*.db *.db3)");
        pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);
        //give path for our database
    if (!pDB->connect(file.toUtf8().constData()))
    {
        QMessageBox::information(this,"Info","Could not connect to database");
        td::String err;
        pDB->getErrorStr(err);
        std::cout << err.c_str() << std::endl;
        pDB->release();
        pDB = 0;
        return false;
    }
        QMessageBox::information(this,"Info","Connection OK");
    return true;
}

void Project::on_actionConductor_triggered()
{
    SearchWindowConductor searchConductor;
    searchConductor.setModal(true);
    searchConductor.exec();
}

void Project::on_actionCapacitor_triggered()
{
    SearchWindowCapacitor searchCapacitor;
    searchCapacitor.setModal(true);
    searchCapacitor.exec();
}

void Project::on_actionCapacitor_Bank_Placement_triggered()
{
    SearchWindowBankPlacement capacitorbankplacement;
    capacitorbankplacement.setModal(true);
    capacitorbankplacement.exec();
}

void Project::on_lineEdit_textChanged(const QString &arg1)
{
    JobID = ui->lineEdit->text().toInt();
}
