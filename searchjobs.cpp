#include "searchjobs.h"
#include "ui_searchjobs.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "newjob.h"
#include "browse.h"
#include "catconsumer.h"
#include "messagebox.h"
#include <QDate>

extern db::ISQLDatabase *pDB;

searchJobs::searchJobs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchJobs)
{
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    ui->comboBox->setCurrentIndex(1);
    select_jobs();

}

searchJobs::~searchJobs()
{
    delete ui;
}

bool searchJobs::select_jobs()
{
    if (!pDB)
        return false;


    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID, Name, UserID, Status, CreationDate, ActivationDate from Jobs"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(6);
        columns[0].name = "Id";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 128;

        columns[2].name = "UserID";
        columns[2].tdType = td::int4;
        columns[2].len = 0;

        columns[3].name = "Status";
        columns[3].tdType = td::int4;
        columns[3].len = 0;

        columns[4].name = "CreationDate";
        columns[4].tdType = td::date;
        columns[4].len = 0;

        columns[5].name = "ActivationDate";
        columns[5].tdType = td::date;
        columns[5].len = 0;

        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))
            return false;

        // true for stripes
        MyModel *model = new MyModel(this, rs, true);

        setModel(model);

        return true;
}

bool searchJobs::select_jobsValues()
{
    if (!pDB)
        return false;

    int id = val.toInt();
    td::INT4 insert_id(id);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID, Name, UserID, Status from Jobs WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_id;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(4);
        columns[0].name = "Id";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 128;

        columns[2].name = "UserID";
        columns[2].tdType = td::int4;
        columns[2].len = 0;

        columns[3].name = "Status";
        columns[3].tdType = td::int4;
        columns[3].len = 0;


        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))
            return false;

        // true for stripes
        MyModel *model = new MyModel(this, rs, true);

        QModelIndex idx = model->index(0,0);
        QString ids = model->data(idx, Qt::DisplayRole).toString();
        idVal = ids.toInt();

        idx = model->index(0,1);
        nameVal = model->data(idx, Qt::DisplayRole).toString();

        idx = model->index(0,2);
        QString owner = model->data(idx, Qt::DisplayRole).toString();
        ownerVal = owner.toInt();

        idx = model->index(0,3);
        QString stat = model->data(idx, Qt::DisplayRole).toString();
        statVal = stat.toInt();


        return true;
}

bool searchJobs::insert_job(int id, QString name, int user, int status, QDate cdate, QDate adate)
{
        td::INT4 insert_id(id);

        db::Ref<td::String> refName(64);

        td::String td_name = name.toUtf8();

        td::INT4 insert_user(user);

        refName = td_name;


        td::INT4 insert_stat(status);

        td::Date insert_cdate(cdate.year(), cdate.month(), cdate.day());
        std::cout << insert_cdate << std::endl;

        if(status == 0)
        adate.setDate(0000,00,00);

        td::Date insert_adate(adate.year(), adate.month(), adate.day());
        std::cout << insert_adate << std::endl;


        //start transaction log
        db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
        db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO Jobs(ID, Name, UserID, Status, CreationDate, ActivationDate) VALUES (?,?,?,?,?,?)"));


        //allocate parameters and bind them to the statement
        db::Params params(pStat->allocParams());
        //bind params
        params << insert_id << refName << insert_user << insert_stat << insert_cdate << insert_adate;


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
            std::cout << "Data inserted" << std::endl;

        if (DebugTrace(1000))
            mu::getTracer() << "Insert finished!\n";
        return bRet;
    }

bool searchJobs::update_job(QString name, int user, int status, QDate cdate, QDate adate)
{
    if (!pDB)
        return false;

    int id = val.toInt();

    td::INT4 insert_id(id);

    db::Ref<td::String> refName(64);
    td::INT4 insert_user(user);
    td::INT4 insert_stat(status);

    td::Date insert_cdate(cdate.year(), cdate.month(), cdate.day());
    std::cout << insert_cdate << std::endl;

    if(status == 0)
    adate.setDate(0000,00,00);

    td::Date insert_adate(adate.year(), adate.month(), adate.day());
    std::cout << insert_adate << std::endl;

    td::String td_name = name.toUtf8();
    refName = td_name;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE Jobs SET Name=?, UserID=?, Status=?, CreationDate=?, ActivationDate=? WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << refName << insert_user << insert_stat << insert_cdate << insert_adate << insert_id;


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
        std::cout << "Data updated" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchJobs::update_status()
{
    if (!pDB)
        return false;

    int id = jobID;

    td::INT4 insert_stat(1);
    td::INT4 insert_id(id);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE Jobs SET Status=? WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_stat << insert_id;


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
        std::cout << "Job Activated" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchJobs::update_aDate(QDate adate)
{
    if (!pDB)
        return false;

    int id = jobID;

    td::Date insert_adate(adate.year(), adate.month(), adate.day());
    std::cout << insert_adate << std::endl;

    td::INT4 insert_id(id);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE Jobs SET ActivationDate=? WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_adate << insert_id;


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
        std::cout << "Date Activated" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchJobs::updateConsJob()
{
    if (!pDB)
        return false;

    int id = jobID;

    td::INT4 insert_id(id);
    td::INT4 insert_newId(0);

    updateJobCatalog();

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatEnergyConsumer SET JobID=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newId << insert_id;


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
        std::cout << "Catalog Released" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchJobs::updateUnitJob()
{
        if (!pDB)
            return false;

        int id = jobID;

        td::INT4 insert_id(id);
        td::INT4 insert_newId(0);

        updateJobCatalog();

        //start transaction log
        db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
        db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatGeneratingUnit SET JobID=? WHERE JobID=?"));

        //allocate parameters and bind them to the statement
        db::Params params(pStat->allocParams());

        //bind params
        params << insert_newId << insert_id;


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
            std::cout << "Catalog Released" << std::endl;

        if (DebugTrace(1000))
            mu::getTracer() << "Insert finished!\n";
        return bRet;
}

bool searchJobs::updateMotorJob()
{
    if (!pDB)
        return false;

    int id = jobID;

    td::INT4 insert_id(id);
    td::INT4 insert_newId(0);

    updateJobCatalog();

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatAsynchronousMotor SET JobID=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newId << insert_id;


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
        std::cout << "Catalog Released" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchJobs::updateMotorPlaJob()
{
    if (!pDB)
        return false;

    int id = jobID;

    td::INT4 insert_id(id);
    td::INT4 insert_newId(0);

    updateJobPlacement();

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacAsynchronousMotor SET JobID=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newId << insert_id;


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
        std::cout << "Placement Released" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchJobs::updateUnitPlacJob()
{
    if (!pDB)
        return false;

    int id = jobID;

    td::INT4 insert_id(id);
    td::INT4 insert_newId(0);

    updateJobPlacement();

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacGeneratingUnit SET JobID=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newId << insert_id;


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
        std::cout << "Placement Released" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchJobs::updateShuntResJob()
{
    if (!pDB)
        return false;

    int id = jobID;

    td::INT4 insert_id(id);
    td::INT4 insert_newId(0);

    updateJobPlacement();

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacResistor SET JobID=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newId << insert_id;


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
        std::cout << "Placement Released" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchJobs::updateJobCatalog()
{
    if (!pDB)
        return false;

    int id = jobID;

    td::INT4 insert_id(id);
    td::INT4 insert_newId(0);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE JobCatalogs SET JobID=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newId << insert_id;


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
        std::cout << "JobCatalog Released" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchJobs::updateJobPlacement()
{
    if (!pDB)
        return false;

    int id = jobID;

    td::INT4 insert_id(id);
    td::INT4 insert_newId(0);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE JobPlacements SET JobID=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newId << insert_id;


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
        std::cout << "JobPlacement Released" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

MyModel *searchJobs::select_user()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from Users"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(1);
    columns[0].name = "NAME";
    columns[0].tdType = td::nch;
    columns[0].len = 64;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        exit(0);

    MyModel *model = new MyModel(this, rs, true);


    return model;
}

int searchJobs::select_ownerID(QString ownerName)
{
    if (!pDB)
        exit(0);

    db::Ref<td::String> refName(64);
    td::String td_name = ownerName.toUtf8();
    refName = td_name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID from Users WHERE Name=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refName;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(1);
    columns[0].name = "ID";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        exit(0);

    MyModel *model = new MyModel(this, rs, true);

    QModelIndex idx = model->index(0,0);
    int id = model->data(idx, Qt::DisplayRole).toInt();

    return id;
}

void searchJobs::setModel(MyModel *n)
{
    proxy->setSourceModel(n);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(1);

    ui->tableView->setModel(proxy);
    ui->tableView->resizeRowsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

}

void searchJobs::on_pushButton_clicked()
{
    select_jobsValues();
    newJob aJob(this);
    aJob.setEditID(QString::number(idVal));
    aJob.setName(nameVal);
    aJob.setUser(select_user());
    aJob.setCDate();
    aJob.setADate();


    if(aJob.exec()==QDialog::Accepted)
    {
        update_job(aJob.name(),select_ownerID(aJob.ownerName()), aJob.status(),aJob.cdate(),aJob.adate());
        select_jobs();
    }

}

void searchJobs::on_newJobPushButton_clicked()
{
    bool exst = false;

    newJob aJob(this);
    aJob.setID("0");
    aJob.setName("New Job 1");
    aJob.setUser(select_user());
    aJob.setCDate();
    aJob.setADate();

    if(aJob.exec()==QDialog::Accepted)
    {
        for(int i=0; i < ui->tableView->model()->rowCount(); i++)
        {
            QModelIndex ind = ui->tableView->model()->index(i,0);
            ui->tableView->selectionModel()->select(ind, QItemSelectionModel::Select);
            int val2 = ui->tableView->model()->data(ind).toInt();

            if(aJob.id() == val2)
            {
                exst = true;
            }
        }

        if(exst == false && aJob.id() != 0)
        {
        insert_job(aJob.id(),aJob.name(),select_ownerID(aJob.ownerName()),aJob.status(),aJob.cdate(),aJob.adate());
        select_jobs();
        }

        if(exst == true)
        {
            messageBox exist(1, this);
            exist.show();
            exist.exec();
        }

        else if(aJob.id() == 0)
        {
            messageBox wrngID(3, this);
            wrngID.show();
            wrngID.exec();
        }

        else
        {
            messageBox exist(0,this);
            exist.show();
            exist.exec();
        }
    }

}

void searchJobs::on_tableView_clicked(const QModelIndex &index)
{
    int inx = index.row();
    QModelIndex ind = ui->tableView->model()->index(inx,0);
    ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val = ui->tableView->model()->data(ind).toString();
    jobID = val.toInt();
}

void searchJobs::on_tableView_doubleClicked(const QModelIndex &index)
{
    select_jobsValues();
    newJob aJob(this);
    aJob.setEditID(QString::number(idVal));
    aJob.setName(nameVal);
    aJob.setUser(select_user());
    aJob.setCDate();
    aJob.setADate();


    if(aJob.exec()==QDialog::Accepted)
    {
        update_job(aJob.name(),select_ownerID(aJob.ownerName()), aJob.status(),aJob.cdate(),aJob.adate());
        select_jobs();
    }
}

void searchJobs::on_pushButton_5_clicked()
{
    browse brw (jobID, this);
    brw.show();
    brw.exec();
}

void searchJobs::on_pushButton_4_clicked()
{
    update_status();
    updateConsJob();
    updateUnitJob();
    updateMotorJob();
    updateMotorPlaJob();
    updateUnitPlacJob();
    updateShuntResJob();
    update_aDate(QDate::currentDate());

    select_jobs();

}

void searchJobs::on_pushButton_6_clicked()
{
    this->close();
}

void searchJobs::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0)
        proxy->setFilterKeyColumn(0);
    else if(index == 1)
        proxy->setFilterKeyColumn(1);
    else if (index == 2)
        proxy->setFilterKeyColumn(2);
    else if (index == 3)
        proxy->setFilterKeyColumn(3);
}

void searchJobs::on_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
}
