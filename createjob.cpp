#include "createjob.h"
#include "ui_createjob.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mainwindow.h"

extern db::ISQLDatabase *pDB;
extern int user;

CreateJob::CreateJob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateJob)
{
    ui->setupUi(this);
    //connectSQLite();
}

CreateJob::~CreateJob()
{
    delete ui;
}


/*bool CreateJob::connectSQLite()
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

}*/



bool CreateJob::insertJobs(QString Job_Name)
{

    if (!pDB)
        return false;

    db::Ref<td::String> refName(20);
    td::String td_name = Job_Name.toUtf8();
    refName = td_name;

    td::String td_ActivDate = "----/--/--";
    db::Ref<td::String> refActivDate(20);
    refActivDate = td_ActivDate;

    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    td::INT4 id = (rand() % ((1000 + 1) - 0) + 0);
    id = id - 2000;

    td::String status = "IN WORK";
    db::Ref<td::String> refStatus(20);
    refStatus = status;

    td::String date = QDate::currentDate().toString("yyyy/MM/dd").toUtf8();
    db::Ref<td::String> refDate(20);
    refDate = date;

    td::INT4 zero(user);

    //start transaction log
    db::Transaction trans(pDB);


    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO Jobs VALUES(?,?,?,?,?,?)"));
    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << id << refName << zero <<refStatus << refDate<< refActivDate;

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
    if (bRet)
        std::cout << "Data Updated" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Updating finished!\n";

    return bRet;
}




void CreateJob::on_buttonBox_clicked(QAbstractButton *button)
{
    QString name;

    name = ui->lineEdit_name->text();

    if(button->text() == "OK"){
        insertJobs(name);
        std::cout<<"insert called"<<std::endl;
    }
    else if(button->text() == "Cancel")
        close();
}


