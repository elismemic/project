#include "busbarplacement.h"
#include "ui_busbarplacement.h"
#include <QAbstractButton>
#include "db/ISQLDataProvider.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "mainwindow.h"

extern db::ISQLDatabase *pDB;
extern int globalJobId;
extern int sysId;

BusbarPlacement::BusbarPlacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BusbarPlacement)
{
    ui->setupUi(this);

    selectCatType();
    selectPhaseCode();
    selectSectionType();
}

void BusbarPlacement::checkJob() {
    if(globalJobId>0){
        ui->lineEdit_sysid->setEnabled(false);
        ui->lineEdit_alias->setEnabled(false);
        ui->lineEdit_name->setEnabled(false);
        ui->lineEdit_uid->setEnabled(false);
        ui->comboBox_bussec->setEnabled(false);
        ui->comboBox_cattype->setEnabled(false);
        ui->comboBox_phasecode->setEnabled(false);
        ui->buttonBox->setEnabled(false);
        ui->textEdit_decr->setEnabled(false);
    }
}

bool BusbarPlacement::selectCatType()
{

    int id;
    td::String name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Id, Name from CatNaming WHERE TypeId = 11"));

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "Id" << id
             << "Name" << name;

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
                ui->comboBox_cattype->addItem(QString::fromUtf8(name.c_str()),QString::number(id));
            }

            std::cout<< "Transaction OK" <<std::endl;
            return true;
        }
}

bool BusbarPlacement::selectSectionType(){

    int id;
    td::String name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Id,Name from section_type"));

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "Id" << id
             << "Name" << name;

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
                ui->comboBox_bussec->addItem(QString::fromUtf8(name.c_str()),QString::number(id));
            }

            std::cout<< "Transaction OK" <<std::endl;
            return true;
        }
}

BusbarPlacement::~BusbarPlacement()
{
    delete ui;
}



bool BusbarPlacement::selectPhaseCode(){
    int id;
    td::String name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Id,Name from phase_code"));

    db::Columns cols(pStat->allocBindColumns(2));
        cols << "Id" << id
             << "Name" << name;

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
                ui->comboBox_phasecode->addItem(QString::fromUtf8(name.c_str()),QString::number(id));
            }

            std::cout<< "Transaction OK" <<std::endl;
            return true;
        }
}


bool BusbarPlacement::insertNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description,int jobId)
{

    if (!pDB)
        return false;

    //td::INT4 td_type(type);
    td::INT4 td_uid(uid);
    td::INT4 td_cattype(cattype);
    td::INT4 td_phasecode(phasecode);
    td::INT4 td_placementType(PlacementType);
    td::INT4 td_jobid(jobId);
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

    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "Insert into PlacNaming VALUES(?,?,?,?,?,?,?,?)"));

    //allocate parameters and bind them to the statement


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params <<td_uid<<refName<<refAlias<<td_cattype<<td_phasecode << refDescription<<td_placementType<<td_jobid;

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


void BusbarPlacement::on_buttonBox_clicked(QAbstractButton *button)
{
    QString name, alias, description;
    int uid, catalogType ,sectionType, phaseCode;

    name = ui->lineEdit_name->text();
    alias = ui->lineEdit_alias->text();
    description = ui->textEdit_decr->toPlainText();

    uid = ui->lineEdit_uid->text().toInt();
    catalogType = ui->comboBox_cattype->currentIndex();
    sectionType = ui->comboBox_bussec->currentIndex();
    phaseCode = ui->comboBox_phasecode->currentIndex();

    if(button->text() == "OK"){
        if(!uidExist(QString::number(uid))){
            insertNaming(uid, name, alias,catalogType,phaseCode,description,globalJobId);
            insertPlacement(uid,PlacementType,globalJobId,sysId,sectionType);
            insertJobPlacements(sysId,globalJobId,PlacementType,uid);
            QMessageBox::information(this,"Status","Saved successfuly");
            this->close();
        }
        else
            {
            updateNaming(uid, name, alias,catalogType,phaseCode,description);
            updatePlacement(uid, sectionType);
            updateJobPlacements(sysId,globalJobId,PlacementType,uid);
            QMessageBox::information(this,"Status","Update Successfully");
            this->close();
            }
    }
    else if(button->text() == "Cancel")
        close();

}


void BusbarPlacement::setUid(int uid){
    ui->lineEdit_uid->setText(QString::number(uid));
}


void BusbarPlacement::enableUid(bool enable){
    ui->lineEdit_uid->setEnabled(enable);
}


bool BusbarPlacement::uidExist(QString uid){


    db::Ref<td::String> refUid(20);
    td::String td_uid = uid.toUtf8();
    refUid = td_uid;

    td::INT4 placementType(PlacementType);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select Id from PlacNaming where Id = ? and TypeId = ?"));
    db::Params params(pStat->allocParams());
    params <<refUid<< placementType;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(1);

        columns[0].name = "Id";
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



bool BusbarPlacement::updateForm(int uid){

    if (!pDB){
         std::cout<< "Transaction failed, Database Connection not Created" <<std::endl;
         return false;}

    td::INT4 placementType(PlacementType);

    td::StringUTF8 name, alias, description;
    int catalogType, phaseCode, sectionType;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"select Name, Alias_Name, Catalog_Type, Phase_Code, SectionType, Description from  PlacNaming inner join PlacBusbar on PlacNaming.[Id] = PlacBusbar.Id where PlacNaming.Id = ? and PlacNaming.TypeId=?"));

    db::Params params(pStat->allocParams());
        params << uid<<placementType;
        std::cout<<uid<<placementType;

    db::Columns cols(pStat->allocBindColumns(6));
        cols << "Name" << name
             << "Alias_Name" << alias
             << "Catalog_Type" << catalogType
             << "SectionType"<<sectionType
             << "Phase_Code" <<phaseCode
             << "Description" <<description;

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
                ui->lineEdit_name->setText(QString::fromUtf8(name.c_str()));
                ui->lineEdit_alias->setText(QString::fromUtf8(alias.c_str()));
                ui->comboBox_cattype->setCurrentIndex(catalogType);
                ui->comboBox_bussec->setCurrentIndex(sectionType);
                ui->comboBox_phasecode->setCurrentIndex(phaseCode);
                ui->textEdit_decr->setText(QString::fromUtf8(description.c_str()));
            }else
            {
                ui->lineEdit_name->setText("");
                ui->lineEdit_alias->setText("");
                ui->comboBox_cattype->setCurrentIndex(0);
                ui->comboBox_bussec->setCurrentIndex(0);
                ui->comboBox_phasecode->setCurrentIndex(0);
                ui->textEdit_decr->setText("");
            }
        }

        oldName = QString::fromUtf8(name.c_str());
        std::cout<< "Transaction OK" <<std::endl;
        return true;
}

void BusbarPlacement::on_lineEdit_uid_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty()){
    int id = ui->lineEdit_uid->text().toInt();
    updateForm(id);
    }
}


bool BusbarPlacement::updatePlacement(int uid, int sectionType){

    if (!pDB)
        return false;

    td::INT4 td_uid(uid);
    td::INT4 td_sectionType(sectionType);

    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "UPDATE PlacBusbar SET SectionType = ? WHERE Id = ? and TypeId = ?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params <<td_sectionType<<td_uid<<PlacementType;

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

bool BusbarPlacement::updateNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description)
{

    if (!pDB)
        return false;

    td::INT4 td_uid(uid);
    td::INT4 td_cattype(cattype);
    td::INT4 td_phasecode(phasecode);

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
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "UPDATE PlacNaming SET Name = ?, Alias_Name = ?, Catalog_Type = ?,Phase_Code=?, Description = ? WHERE Id = ? and TypeId = ?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refName << refAlias <<td_cattype<< td_phasecode <<refDescription<<td_uid<<PlacementType;

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

void BusbarPlacement::setPlacementType(int PlacementType)
{
    this->PlacementType = PlacementType;
}

bool BusbarPlacement::insertPlacement(int id, int typeId,int jobId, int sysId, int sectype)
{

    if (!pDB)
        return false;


    td::INT4 td_id(id);
    td::INT4 td_jobId(jobId);
    td::INT4 td_sysId(sysId);
    td::INT4 td_typeId(typeId);
    td::INT4 td_sectype(sectype);

    db::Transaction trans(pDB);
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "Insert into PlacBusbar(Id,TypeId,JobId,SystemId,SectionType,EditFlag) values(?,?,?,?,?,0)"));
    db::Params params(pStat->allocParams());
    //bind params
    params <<td_id<<td_typeId<<td_jobId<<td_sysId<<td_sectype;

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

bool BusbarPlacement::deletePlacement(int uid){

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"UPDATE PlacBusbar SET EditFlag=1 where Id = ? and TypeId = ?"));

    db::Params params(pStat->allocParams());
        params << uid<<PlacementType;
    if(pStat->execute()){
        std::cout<<"Deleted Successfully"<<std::endl;
        return true;
    }else
        std::cout<<"Could not Delete"<<std::endl;

    return false;
}

bool BusbarPlacement::deleteNaming(int uid){

    //bool bRet = pDB->execDirectly("DELETE FROM test_tab2");


    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"DELETE FROM PlacNaming where Id = ? and TypeId = ?"));

    db::Params params(pStat->allocParams());
        params << uid<< PlacementType;

    if(pStat->execute()){
        std::cout<<"Deleted Successfully"<<std::endl;
        return true;
    }else
        std::cout<<"Could not Delete"<<std::endl;

    return false;

}

void BusbarPlacement::setWindowName() {
    if(PlacementType==20)
       setWindowTitle("Equivalent Source");
    if(PlacementType==21)
       this->setWindowTitle("Busbar Section Vertical");
    if(PlacementType==22)
       this->setWindowTitle("Busbar Section Horizontal");
    if(PlacementType==23)
       this->setWindowTitle("Busbar Section Free Style");
}

bool BusbarPlacement::updateJobPlacements(int sysId, int jobId, int typeId, int placId){
    if (!pDB)
        return false;

    td::INT4 td_placId(placId);
    td::INT4 td_jobId(jobId);
    td::INT4 td_typeId(typeId);
    td::INT4 td_sysId(sysId);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "UPDATE JobPlacements SET SystemID = ? AND JobID = ? WHERE PlacID = ? AND TypeID = ?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params <<td_sysId << td_jobId << td_placId <<td_typeId;

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

bool BusbarPlacement::insertJobPlacements(int sysId,int jobId,int typeId, int placId){

    if (!pDB)
        return false;

    td::INT4 td_placId(placId);
    td::INT4 td_typeId(typeId);
    td::INT4 td_jobId(jobId);
    td::INT4 td_sysId(sysId);

    db::Transaction trans(pDB);
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "Insert into JobPlacements(SystemID,JobID,TypeID,PlacID) values(?,?,?,?)"));
    db::Params params(pStat->allocParams());
    //bind params
    params <<td_sysId<<td_jobId<<td_typeId<<td_placId;

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
