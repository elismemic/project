#include "newjob.h"
#include "ui_newjob.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include <QDateTime>

extern db::ISQLDatabase *pDB;
extern int userID;

newJob::newJob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newJob)
{
    ui->setupUi(this);

}

newJob::~newJob()
{
    delete ui;
}
bool newJob::insertJob(QString name)
{
    if (!pDB)
        return false;
    QTime time = QTime::currentTime();

    qsrand((uint)time.msec());
    int jobid = -((qrand() % 1000) + 2);

    td::INT4 user(userID);
    td::INT4 id(jobid);
    td::INT4 status(0); //0 - status of IN-WORK jobs

    db::Ref<td::String> refName(128);
    td::String td_name = name.toUtf8();
    refName = td_name;

    //creation date
    QDateTime crdate= QDateTime::currentDateTime();
    QString date1 = crdate.toString("yyyy-MM-dd hh:mm:ss");
    db::Ref<td::String> refDate(128);
    td::String td_date = date1.toUtf8();
    refDate = td_date;
    //activation date - should be Null now
    QString date2 = "Not activated";
    db::Ref<td::String> refDate2(128);
    td::String td_date2 = date2.toUtf8();
    refDate2 = td_date2;

    //start transaction log
    db::Transaction trans(pDB);
    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO Jobs(ID, Name, UserID, Status, Creation_date, Activation_date) VALUES (?,?,?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << id << refName << user << status << refDate << refDate2;


    if (!pStat->execute())
    {
        td::String strErr;
        pStat->getErrorStr(strErr);
        if (DebugTrace(1000))
            mu::getTracer() << strErr;
        //rollback will be called
        return false;
    }

    //commit transaction
    bool  bRet = trans.commit();
    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;


}

void newJob::on_pushButton_clicked()
{
    if(!insertJob(ui->lineEdit->text()))
            QMessageBox::information(this,"Creating new job ...","The job could not be created!");
    else
            QMessageBox::information(this,"Creating new job ...","The job is created");
    this->close();

}

void newJob::on_pushButton_2_clicked()
{
    this->close();
}
