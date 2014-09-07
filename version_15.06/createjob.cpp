#include "createjob.h"
#include "ui_createjob.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"

CreateJob::CreateJob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateJob)
{
    ui->setupUi(this);
    connectSQLite();
    selectStatus();

}

CreateJob::~CreateJob()
{
    delete ui;
}


bool CreateJob::connectSQLite()
{
    pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);

    if (!pDB->connect("C:/Users/nevres/Downloads/project.db"))
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

}



bool CreateJob::selectStatus(){

    int id;
    td::String status;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID,Name from Status"));

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "ID" << id
             << "Name" << status;

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
                ui->comboBox_status->addItem(QString::fromUtf8(status.c_str()),QString::number(id));
            }

            std::cout<< "Transaction OK" <<std::endl;
            return true;
        }
}


bool CreateJob::insertJobs(int Job_Id, QString Job_Name, int Owner, int Status, QString Creation_Date, QString Activation_Date)
{

    if (!pDB)
        return false;

    td::INT4 td_JobId(Job_Id);
    td::INT4 td_Owner(Owner);
    td::INT4 td_Status(Status);

    db::Ref<td::String> refName(20);
    td::String td_name = Job_Name.toUtf8();
    refName = td_name;

    db::Ref<td::String> refCD(20);
    td::String td_CD = Creation_Date.toUtf8();
    refCD = td_CD;

    db::Ref<td::String> refAD(20);
    td::String td_AD = Activation_Date.toUtf8();
    refAD = td_AD;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO Jobs VALUES(?,?,?,?,?,?)"));
    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << td_JobId << refName <<td_Owner <<td_Status<<refCD<<refAD;

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


void CreateJob::on_comboBox_item_type_currentIndexChanged(int index)
{
    //selectItemName(index);
}



bool CreateJob::updateForm(int uid){

    if (!pDB){
         std::cout<< "Transaction failed, Database Connection not Created" <<std::endl;
         return false;}

    td::StringUTF8 name, creationDate, activDate;
    int status;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"select Name, Status, Creation_date, Activation_date from Jobs where ID = ?"));

    db::Params params(pStat->allocParams());
        params << uid;

    db::Columns cols(pStat->allocBindColumns(4));
        cols << "Name" << name
             << "Status" << status
             << "Creation_date" << creationDate
             << "Activation_date"<<activDate;

        if (!pStat->execute())
            {
                std::cout << "testSelect2 - Exec NOT ok\n";
                td::StringUTF8 strErr;
                pStat->getErrorStr(strErr);
                std::cout << strErr.c_str() << std::endl;
                return false;
            }
            else{

            if(pStat->moveNext())
            {

                ui->lineEdid_id->setText(QString::number(uid));
                ui->lineEdit_name->setText(name.c_str());
                ui->comboBox_status->setCurrentIndex(status);
                ui->lineEdit_createDate->setText(creationDate.c_str());
                ui->lineEdit_activateDate->setText(activDate.c_str());

            }else
            {

                ui->lineEdit_name->setText("");
                ui->comboBox_status->setCurrentIndex(0);
                ui->lineEdit_createDate->setText("2000/01/01");
                ui->lineEdit_activateDate->setText("2000/01/01");
            }
        }
        std::cout<< "Transaction OK" <<std::endl;

        return true;
}

void CreateJob::on_buttonBox_clicked(QAbstractButton *button)
{
    QString name;
    QString creationDate, activationDate;
    int uid, owner,status;

    uid = ui->lineEdid_id->text().toInt();
    name = ui->lineEdit_name->text();
    //need to change according to current user
    owner = 0;
    status = ui->comboBox_status->currentIndex();
    creationDate = ui->lineEdit_createDate->text();
    activationDate = ui->lineEdit_activateDate->text();

    if(button->text() == "OK"){
        if(!uidExist(QString::number(uid))){
            insertJobs(uid,name,owner,status,creationDate, activationDate);
            std::cout<<"insert called"<<std::endl;
        }else{
            updateJobs(uid,name,status,creationDate, activationDate);
            std::cout<<"update called"<<std::endl;
            }
        }
    else if(button->text() == "Cancel")
        close();
}

bool CreateJob::uidExist(QString uid){

    db::Ref<td::String> refUid(20);
    td::String td_uid = uid.toUtf8();
    refUid = td_uid;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select ID from Jobs where ID = ?"));
    db::Params params(pStat->allocParams());
    params <<refUid;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(1);

        columns[0].name = "ID";
        columns[0].tdType = td::int4;
        columns[0].len = 0;


        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))
            return false;

        if(rs->rowCount()!=0)
            return true;
        else
            return false;

}

void CreateJob::on_lineEdid_id_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty()){
    int id = ui->lineEdid_id->text().toInt();
    updateForm(id);
    }
}

bool CreateJob::updateJobs(int Job_Id, QString Job_Name, int Status, QString Creation_Date, QString Activation_Date)
{
    if (!pDB)
        return false;

    td::INT4 td_JobId(Job_Id);
    td::INT4 td_Status(Status);

    db::Ref<td::String> refName(20);
    td::String td_name = Job_Name.toUtf8();
    refName = td_name;


    db::Ref<td::String> refCD(20);
    td::String td_CD = Creation_Date.toUtf8();
    refCD = td_CD;

    db::Ref<td::String> refAD(20);
    td::String td_AD = Activation_Date.toUtf8();
    refAD = td_AD;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "UPDATE Jobs SET Name = ?, Status = ?, Creation_date = ?, Activation_date = ? WHERE ID = ?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refName << td_Status <<refCD<<refAD<<td_JobId;

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
