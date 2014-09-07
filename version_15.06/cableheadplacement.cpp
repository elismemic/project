#include "cableheadplacement.h"
#include "ui_cableheadplacement.h"
#include <QAbstractButton>
#include "db/ISQLDataProvider.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "db/Recordset.h"
#include "td/Variant.h"


CableHeadPlacement::CableHeadPlacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CableHeadPlacement)
{
    ui->setupUi(this);
    connectSQLite();
    selectCatalog();
    selectPhaseCode();
    selectSectionType();
}

bool CableHeadPlacement::selectSectionType(){

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

CableHeadPlacement::~CableHeadPlacement()
{
    delete ui;
}



bool CableHeadPlacement::selectPhaseCode(){
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

bool CableHeadPlacement::insertDatabase(int uid, QString name, QString alias, int catalogType, int sectionType, int phaseCode, QString description)
{

    if (!pDB)
        return false;

    td::INT4 td_uid(uid);
    td::INT4 td_sectionType(sectionType);
    td::INT4 td_catalogType(catalogType);
    td::INT4 td_phaseCode(phaseCode);

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
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO cable_head_placement VALUES (?,?,?,?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << td_uid << refName << refAlias << td_catalogType <<td_sectionType<< td_phaseCode <<refDescription;

    if (!pStat->execute())
    {
        td::String strErr;
        pStat->getErrorStr(strErr);
        if (DebugTrace(1000))
            mu::getTracer() << strErr;
        //rollback will be called
        std::cout << "Data insertinon failed" << std::endl;
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


bool CableHeadPlacement::selectCatalog()
{

    int id;
    td::String name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Id,Name from cable_head_catalog"));

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


bool CableHeadPlacement::connectSQLite()
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

bool CableHeadPlacement::insertNaming(int type, QString name)
{

    if (!pDB)
        return false;

    td::INT4 td_type(type);


    db::Ref<td::String> refName(20);

    td::String td_name = name.toUtf8();

    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later

    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "Insert into naming(Name, Type) values(?,?)"));

    //allocate parameters and bind them to the statement


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params <<refName << td_type;

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


void CableHeadPlacement::on_buttonBox_clicked(QAbstractButton *button)
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
        insertDatabase( uid, name, alias, catalogType, sectionType, phaseCode, description);
        //insertNaming(1,name);
        }else
            updateDatabase(uid,name,alias,catalogType ,sectionType, phaseCode, description);
    }
    else if(button->text() == "Cancel")
        close();

}


void CableHeadPlacement::setUid(int uid){
    ui->lineEdit_uid->setText(QString::number(uid));
}


void CableHeadPlacement::enableUid(bool enable){
    ui->lineEdit_uid->setEnabled(enable);
}


bool CableHeadPlacement::uidExist(QString uid){


    db::Ref<td::String> refUid(20);
    td::String td_uid = uid.toUtf8();
    refUid = td_uid;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "select Id from  cable_head_placement where Id = ?"));
    db::Params params(pStat->allocParams());
    params <<refUid;

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

bool CableHeadPlacement::updateDatabase(int uid, QString name, QString alias, int catalogType, int sectionType, int phaseCode, QString description)
{


    if (!pDB)
        return false;

    td::INT4 td_uid(uid);
    td::INT4 td_sectionType(sectionType);
    td::INT4 td_catalogType(catalogType);
    td::INT4 td_phaseCode(phaseCode);

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
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "UPDATE cable_head_placement SET Name = ?, Alias_Name = ?, Catalog_Type = ?, Section_Type = ?, Phase_Code = ?, Description = ? WHERE Id = ?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refName << refAlias << td_catalogType <<td_sectionType<< td_phaseCode <<refDescription<<td_uid;


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



bool CableHeadPlacement::updateForm(int uid){

    if (!pDB){
         std::cout<< "Transaction failed, Database Connection not Created" <<std::endl;
         return false;}

    td::StringUTF8 name, alias, description;
    int catalogType, sectionType, phaseCode;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,"select Name, Alias_Name, Catalog_Type,Section_Type, Phase_Code, Description from cable_head_placement where cable_head_placement.Id = ?"));

    db::Params params(pStat->allocParams());
        params << uid;
        std::cout<<uid;

    db::Columns cols(pStat->allocBindColumns(6));
        cols << "Name" << name
             << "Alias_Name" << alias
             << "Catalog_Type" << catalogType
             << "Section_Type" << sectionType
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
        std::cout<< "Transaction OK" <<std::endl;
        return true;
}

void CableHeadPlacement::on_lineEdit_uid_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty()){
    int id = ui->lineEdit_uid->text().toInt();
    updateForm(id);
    }
}
