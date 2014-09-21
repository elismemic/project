#include "powerss.h"
#include "ui_powerss.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "searchjobs.h"
#include "searchdialog.h"
#include <QFileDialog>

db::ISQLDatabase *pDB = 0;
int userID = 1;

PowerSS::PowerSS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PowerSS)
{
    ui->setupUi(this);
    connectSQLite();

    searchJobs nj(this);

    if(nj.exec() == QDialog::Accepted)
    {
        userJob = nj.setJobIDVal();
        QString qStr = QString::number(nj.setJobIDVal());
        ui->label->setText("Selected job: " + qStr);
    }
    else
        ui->label->setText("Selected job: None");
}

PowerSS::~PowerSS()
{
    delete ui;
}

bool PowerSS::connectSQLite()
{
    if (pDB){
        pDB->release();
    }

    pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);

    //QString file = QFileDialog::getOpenFileName(this,"Open a database");
    //if(!file.isEmpty())

    //if (!pDB->connect(file.toUtf8().constData()))
    if (!pDB->connect("C:/project/project.db3"))
    {
        std::cout << "Cannot connect to database" << std::endl;
        td::String err;
        pDB->getErrorStr(err);
        std::cout << err.c_str() << std::endl;
        pDB->release();
        pDB = 0;
        //messageBox noC(3, this);
        //noC.show();
        //noC.exec();
        return false;
    }
    std::cout << "Connection OK!" << std::endl;
    return true;
}

void PowerSS::on_actionEnergy_Consumer_triggered()
{
    searchDialog cns(1, userJob, this);
    cns.show();
    cns.exec();
}

void PowerSS::on_actionGenerating_Unit_triggered()
{
    searchDialog unt(2, userJob, this);
    unt.show();
    unt.exec();
}

void PowerSS::on_actionAsynchronous_Motor_triggered()
{
    searchDialog mtr(3,userJob, this);
    mtr.show();
    mtr.exec();
}

void PowerSS::on_actionAsynchronous_Motor_Pla_triggered()
{
    searchDialog plaMtr(4,userJob, this);
    plaMtr.show();
    plaMtr.exec();
}

void PowerSS::on_actionGenerating_Unit_Pla_triggered()
{
    searchDialog plaUnt(5,userJob, this);
    plaUnt.show();
    plaUnt.exec();
}

void PowerSS::on_actionShunt_Resistor_Pla_triggered()
{
    searchDialog plaRes(6,userJob, this);
    plaRes.show();
    plaRes.exec();
}

void PowerSS::on_actionSearch_Jobs_triggered()
{
    searchJobs jobDlg (this);
    jobDlg.show();

    if(jobDlg.exec() == QDialog::Accepted)
    {
        userJob = jobDlg.setJobIDVal();
        QString qStr = QString::number(jobDlg.setJobIDVal());
        ui->label->setText("Selected job: " + qStr);
    }
}

