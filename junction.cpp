#include "junction.h"
#include "ui_junction.h"
#include <QAbstractButton>
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mainwindow.h"

extern db::ISQLDatabase *pDB;
extern int globalJobId;


Junction::Junction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Junction)
{
    ui->setupUi(this);
    //connectSQLite();
    selectVoltage();
    selectJunction();

}

Junction::~Junction()
{
    delete ui;
}

void Junction::checkJob() {
    if(globalJobId>0){
        ui->lineEditAlias->setEnabled(false);
        ui->lineEditName->setEnabled(false);
        ui->lineEditUid->setEnabled(false);
        ui->comboBoxRatedVoltage->setEnabled(false);
        ui->comboBox_junction->setEnabled(false);
        ui->textEditDescription->setEnabled(false);
        ui->buttonBox->setEnabled(false);

    }
}

void Junction::setUid(int uid){
    ui->lineEditUid->setText(QString::number(uid));
}

bool Junction::insertCatalog(int id, int typeId, int junction)
{

    if (!pDB)
        return false;


    td::INT4 td_id(id);
    td::INT4 td_typeId(typeId);
    td::INT4 td_junction(junction);
    td::INT4 td_jobId(globalJobId);

    db::Transaction trans(pDB);
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "Insert into CatJunction(Id,TypeId,JobId,JunctionType,EditFlag) values(?,?,?,?,0)"));
    db::Params params(pStat->allocParams());
    //bind params
    params <<td_id<<td_typeId<<td_jobId<<td_junction;

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

bool Junction::insertNaming(int uid, QString name, QString alias, int voltage, QString description, int jobId)
{

    if (!pDB)
        return false;

    td::INT4 td_uid(uid);
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
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO CatNaming VALUES (?,?,?,?,?,13,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << td_uid << refName << refAlias <<td_voltage <<refDescription<<td_job;

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


bool Junction::updateNaming(int uid, QString name, QString alias, int voltage, QString description)
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
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "UPDATE CatNaming SET Name = ?, Alias_Name = ?, Rated_Voltage = ?, Description = ? WHERE Id = ?"));


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

bool Junction::selectJunction()
{
    if (!pDB){
         std::cout<< "Transaction failed not pDB" <<std::endl;
         return false;}

    int id;
    td::String junction;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Id,Name from junction_type"));

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "Id" << id
             << "Name" << junction;

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
                ui->comboBox_junction->addItem(QString::fromUtf8(junction.c_str()),QString::number(id));
            }

            std::cout<< "Transaction OK" <<std::endl;
            return true;
        }
}



void Junction::on_buttonBox_clicked(QAbstractButton *button){

    QString name, alias, description;
    int uid,junction, ratedVoltage,type;

    type = 0;
    name = ui->lineEditName->text();
    alias = ui->lineEditAlias->text();
    description = ui->textEditDescription->toPlainText();

    uid = ui->lineEditUid->text().toInt();
    ratedVoltage = ui->comboBoxRatedVoltage->currentIndex();
    junction= ui->comboBox_junction->currentIndex();

    if(button->text() == "Save"){
        if(!uidExist(QString::number(uid))){
            insertNaming(uid, name, alias,ratedVoltage,description,globalJobId);
            insertCatalog(uid,13,junction);
            insertJobCatalogs(globalJobId,13,uid);
            std::cout<<"insert called"<<std::endl;
            this->close();
        }else{
            updateNaming(uid,name, alias,ratedVoltage,description);
            updateJobCatalogs(globalJobId,13,uid);
            //updateCatalog(uid,13,junction);
            std::cout<<"updating databse"<<std::endl;
            this->close();
        }
    }

    else if(button->text() == "Cancel")
        close();
    else if(button->text() == "Discard")
        if(uid>=0){
            deleteCatalog(uid);
            deleteNaming(uid);
            deleteJobCatalogs(uid);
            this->close();
        }
}

bool Junction::uidExist(QString uid){


    db::Ref<td::String> refUid(20);
    td::String td_uid = uid.toUtf8();
    refUid = td_uid;

   // td::INT4 Id;
    td::String name;
    td::String aliasName;
    td::String description;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select Id, Name, Alias_name, Rated_Voltage, Description from  CatNaming where Id = ? and Tp"));
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

void Junction::enableUid(bool enable){
    ui->lineEditUid->setEnabled(enable);
}

bool Junction::selectVoltage()
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

bool Junction::updateForm(int uid){

    if (!pDB){
             std::cout<< "Transaction failed, Database Connection not Created" <<std::endl;
             return false;}

        td::StringUTF8 name, alias, description;
        int ratedVoltage;

        mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"select Name, Alias_Name, Rated_Voltage, Description from CatNaming where CatNaming.Id = ? and CatNaming.TypeId = 13"));

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

                if(pStat->moveNext()){
                    ui->lineEditName->setText(QString::fromUtf8(name.c_str()));
                    ui->lineEditAlias->setText(QString::fromUtf8(alias.c_str()));
                    ui->comboBoxRatedVoltage->setCurrentIndex(ratedVoltage);
                    ui->textEditDescription->setText(QString::fromUtf8(description.c_str()));
                    std::cout<<ratedVoltage;
                }else{
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

bool Junction::deleteNaming(int uid){

    //bool bRet = pDB->execDirectly("DELETE FROM test_tab2");

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"DELETE FROM CatNaming where Id = ? and TypeId = 13"));

    db::Params params(pStat->allocParams());
        params << uid;
    if(pStat->execute()){
        std::cout<<"Deleted Successfully"<<std::endl;
        return true;
    }else
        std::cout<<"Could not Delete"<<std::endl;

    return false;

}

bool Junction::deleteCatalog(int uid){


    td::INT4 Uid(uid);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"Update CatJunction SET EditFlag=1 where Id = ?"));

    db::Params params(pStat->allocParams());
        params << Uid;

    if(pStat->execute()){
        std::cout<<"Deleted Successfully"<<std::endl;
        return true;
    }else
        std::cout<<"Could not Delete"<<std::endl;

    return false;

}

void Junction::on_lineEditUid_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty()){
    int id = ui->lineEditUid->text().toInt();
    updateForm(id);
    }
}

bool Junction::updateJobCatalogs(int jobId, int typeId, int catId){
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

bool Junction::insertJobCatalogs(int jobId,int typeId, int catId){

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

bool Junction::deleteJobCatalogs(int uid){

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
