#include "cablehead.h"
#include <QAbstractButton>
#include "ui_cablehead.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mainwindow.h"
#include "busbarsearch.h"

extern db::ISQLDatabase *pDB;
extern int globalJobId;
extern int chosenJobId;

CableHead::CableHead(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CableHead)
{
    ui->setupUi(this);
    selectVoltage();
    QValidator *validator = new QIntValidator(100, 9999, this);
    ui->lineEditUid->setValidator(validator);

}

CableHead::~CableHead()
{
    delete ui;
}

void CableHead::setUid(int uid){
    ui->lineEditUid->setText(QString::number(uid));
}

void CableHead::checkJob() {
    if(globalJobId>0){
        ui->lineEditAlias->setEnabled(false);
        ui->lineEditName->setEnabled(false);
        ui->lineEditUid->setEnabled(false);
        ui->comboBoxRatedVoltage->setEnabled(false);
        ui->textEditDescription->setEnabled(false);
        ui->buttonBox->setEnabled(false);

    }
}

bool CableHead::insertCatalog(int id, int typeId,int flag)
{

    if (!pDB)
        return false;


    td::INT4 td_id(id);
    td::INT4 td_flag(flag);
    td::INT4 td_typeId(typeId);
    td::INT4 td_jobId(globalJobId);

    db::Transaction trans(pDB);
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "Insert into CatCableHead(Id,TypeId,JobId,EditFlag) values(?,?,?,?)"));
    db::Params params(pStat->allocParams());
    //bind params
    params <<td_id<<td_typeId<<td_jobId<<td_flag;

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




bool CableHead::insertNaming(int uid, QString name, QString alias, int voltage, QString description,int jobId,int flag)
{

    if (!pDB)
        return false;

    td::INT4 td_uid(uid);
    td::INT4 td_flag(flag);
    td::INT4 td_job(jobId);
    //td::INT4 td_typeid(typeId);
    td::INT4 td_voltage(voltage);

    db::Ref<td::String> refName(20);
    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refDescription(200);

    td::String td_name = name.toUtf8();
    td::String td_alias = alias.toUtf8();
    td::String td_description = description.toUtf8();

    refName = td_name;
    refAlias = td_alias;
    refDescription = td_description;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO CatNaming VALUES (?,?,?,?,?,12,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << td_uid << refName << refAlias <<td_voltage <<refDescription<<td_job<<td_flag;

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

    std::cout<<td_voltage<<std::endl;
    return bRet;
}


bool CableHead::updateNaming(int uid, QString name, QString alias, int voltage, QString description)
{

    if (!pDB)
        return false;

    td::INT4 td_uid(uid);
    td::INT4 td_voltage(voltage);

    db::Ref<td::String> refName(20);
    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refDescription(200);

    td::String td_name = name.toUtf8();
    td::String td_alias = alias.toUtf8();
    td::String td_description = description.toUtf8();

    refName = td_name;
    refAlias = td_alias;
    refDescription = td_description;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "UPDATE CatNaming SET Name = ?, Alias_Name = ?, Rated_Voltage = ?, Description = ? WHERE Id = ? and CatNaming.TypeId = 12"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refName << refAlias <<td_voltage <<refDescription<<td_uid;

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

    std::cout<<td_voltage<<std::endl;
    return bRet;
}

void CableHead::on_buttonBox_clicked(QAbstractButton *button){

    QString name, alias, description;
    int uid, ratedVoltage,type;

    type = 0;
    name = ui->lineEditName->text();
    alias = ui->lineEditAlias->text();
    description = ui->textEditDescription->toPlainText();

    uid = ui->lineEditUid->text().toInt();
    ratedVoltage = ui->comboBoxRatedVoltage->currentIndex();


    if(button->text() == "Save"){
        if(!uidExist(QString::number(uid))){
            insertNaming(uid, name, alias,ratedVoltage,description,globalJobId,0);
            insertCatalog(uid,12,0);
            insertJobCatalogs(globalJobId,12,uid);
            std::cout<<"insert called"<<std::endl;
            this->close();
        }else if (globalJobId==chosenJobId){
            updateNaming(uid,name, alias,ratedVoltage,description);
            updateJobCatalogs(globalJobId,12,uid);
            //updateCatalog(uid,12);
            std::cout<<"updating databse"<<std::endl;
            this->close();
        }
        else{
            insertNaming(uid, name, alias,ratedVoltage,description,globalJobId,chosenJobId);
            insertCatalog(uid,12,chosenJobId);
            this->close();
        }
    }

    else if(button->text() == "Cancel")
        close();

}

bool CableHead::uidExist(QString uid){


    db::Ref<td::String> refUid(20);
    td::String td_uid = uid.toUtf8();
    refUid = td_uid;

    //td::INT4 Id;
    td::String name;
    td::String aliasName;
    td::String description;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select Id, Name, Alias_name, Rated_Voltage, Description from  CatNaming where Id = ? and CatNaming.TypeId = 12"));
    db::Params params(pStat->allocParams());
    params <<refUid;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(4);

        columns[0].name = "Id";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 50;

        columns[2].name = "Alias_Name";
        columns[2].tdType = td::nch;
        columns[2].len = 0;

        columns[3].name = "Description";
        columns[3].tdType = td::nch;
        columns[3].len = 0;


        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))
            return false;

        if(rs->rowCount()!=0)
            return true;
        else
            return false;

}

void CableHead::enableUid(bool enable){
    ui->lineEditUid->setEnabled(enable);
}

bool CableHead::selectVoltage()
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
                ui->comboBoxRatedVoltage->addItem(QString::number(voltage),QString::number(id));
            }

            std::cout<< "Transaction OK" <<id<<voltage<<std::endl;
            return true;
        }
}

bool CableHead::updateForm(int uid){

    if (!pDB){
         std::cout<< "Transaction failed, Database Connection not Created" <<std::endl;
         return false;}

    td::StringUTF8 name, alias, description;
    int ratedVoltage;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"select Name, Alias_Name, Rated_Voltage, Description from CatNaming where CatNaming.Id = ? and CatNaming.TypeId = 12"));

    db::Params params(pStat->allocParams());
        params << uid;
        std::cout<<uid;

    db::Columns cols(pStat->allocBindColumns(4));
        cols << "Name" << name
             << "Alias_Name" << alias
             << "Rated_Voltage" << ratedVoltage
             << "Description" << description;

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
                ui->lineEditName->setText(QString::fromUtf8(name.c_str()));
                ui->lineEditAlias->setText(QString::fromUtf8(alias.c_str()));
                ui->comboBoxRatedVoltage->setCurrentIndex(ratedVoltage);
                ui->textEditDescription->setText(QString::fromUtf8(description.c_str()));
                std::cout<<ratedVoltage;
            }else
            {
                ui->lineEditName->setText("");
                ui->lineEditAlias->setText("");
                ui->comboBoxRatedVoltage->setCurrentIndex(0);
                ui->textEditDescription->setText("");
            }
        }
        std::cout<< "Transaction OK" <<std::endl;
        oldName = QString::fromUtf8(name.c_str());

        return true;
}

bool CableHead::deleteNaming(int uid){

    //bool bRet = pDB->execDirectly("DELETE FROM test_tab2");

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"UPDATE CatNaming SET EditFlag=1 where Id = ? and TypeId = 12"));

    db::Params params(pStat->allocParams());
        params << uid;
    if(pStat->execute()){
        std::cout<<"Deleted Successfully"<<std::endl;
        return true;
    }else
        std::cout<<"Could not Delete"<<std::endl;

    return false;

}

bool CableHead::deleteCatalog(int uid){



    td::INT4 Uid(uid);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"Update CatCableHead SET EditFlag=1 where Id = ?"));

    db::Params params(pStat->allocParams());
        params << Uid;

    if(pStat->execute()){
        std::cout<<"Deleted Successfully"<<std::endl;
        return true;
    }else
        std::cout<<"Could not Delete"<<std::endl;

    return false;
}

void CableHead::on_lineEditUid_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty()){
    int id = ui->lineEditUid->text().toInt();
    updateForm(id);
    }
}

bool CableHead::updateJobCatalogs(int jobId, int typeId, int catId){
    if (!pDB)
        return false;

    td::INT4 td_catId(catId);
    td::INT4 td_jobId(jobId);
    td::INT4 td_typeId(typeId);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "UPDATE JobCatalogs SET JobID = ? WHERE CatID = ? and TypeID = ?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << td_jobId << td_catId <<td_typeId;

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

bool CableHead::insertJobCatalogs(int jobId,int typeId, int catId){

    if (!pDB)
        return false;

    td::INT4 td_catId(catId);
    td::INT4 td_typeId(typeId);
    td::INT4 td_jobId(jobId);

    db::Transaction trans(pDB);
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "Insert into JobCatalogs(JobID,TypeID,CatID) values(?,?,?)"));
    db::Params params(pStat->allocParams());
    //bind params
    params <<td_jobId<<td_typeId<<td_catId;

    if (!pStat->execute())
    {
        td::String strErr;
        pStat->getErrorStr(strErr);
        if (DebugTrace(1000))
            mu::getTracer() << strErr;
        //rollback will be called
        return false;
    }

    bool  bRet = trans.commit();
    if (bRet)
        std::cout << "Data inserted" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";

    return bRet;
}

bool CableHead::deleteJobCatalogs(int uid){

    td::INT4 Uid(uid);
    td::INT4 jobId(globalJobId);
    td::INT4 typeId(13);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"DELETE FROM JobCatalogs where JobID = ? and TypeID = ? and CatID = ?"));

    db::Params params(pStat->allocParams());
        params << jobId<<typeId<<Uid;

    if(pStat->execute()){
        std::cout<<"Deleted Successfully"<<std::endl;
        return true;
    }else
        std::cout<<"Could not Delete"<<std::endl;

    return false;
}

void CableHead::disableButtons()
{
    ui->lineEditAlias->setEnabled(false);
    ui->lineEditName->setEnabled(false);
    ui->lineEditUid->setEnabled(false);
    ui->comboBoxRatedVoltage->setEnabled(false);
    ui->textEditDescription->setEnabled(false);
    ui->buttonBox->setEnabled(false);
}
