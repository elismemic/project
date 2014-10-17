#include "browse.h"
#include "ui_browse.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "addcatpla.h"
#include "catconsumer.h"
#include "catunit.h"
#include "catmotor.h"
#include "plamotor.h"
#include "plaunit.h"
#include "plaresistor.h"
#include "browse.h"

extern db::ISQLDatabase *pDB;

browse::browse(int jobID, int refUserJob, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::browse)
{
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    proxy2 = new QSortFilterProxyModel(this);
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox_2->setCurrentIndex(1);
    refJobID = jobID;
    ref2UserJob = refUserJob;
    this->setWindowTitle("Browse Catalogs and Placements (Job ID: " + QString::number(refJobID) + ")");
    select_catalogs(refJobID);
    select_placements(refJobID);
}

browse::~browse()
{
    delete ui;
}

bool browse::select_catalogs(int jobID)
{
    if (!pDB)
        return false;

    td::INT4 insert_jobID(jobID);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT TypeID, CatID, CatName from JobCatalogs WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_jobID;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(3);
        columns[0].name = "TypeID";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "CatID";
        columns[1].tdType = td::int4;
        columns[1].len = 0;

        columns[2].name = "CatName";
        columns[2].tdType = td::nch;
        columns[2].len = 64;

        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))
            return false;

        // true for stripes
        MyModel *model = new MyModel(this, rs, true);

        setCatModel(model);

        return true;
}

bool browse::select_placements(int jobID)
{
    if (!pDB)
        return false;

    td::INT4 insert_jobID(jobID);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT TypeID, CatID, CatName from JobPlacements WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_jobID;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(3);
        columns[0].name = "TypeID";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "CatID";
        columns[1].tdType = td::int4;
        columns[1].len = 0;

        columns[2].name = "CatName";
        columns[2].tdType = td::nch;
        columns[2].len = 64;

        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))
            return false;

        // true for stripes
        MyModel *model = new MyModel(this, rs, true);

        setPlaModel(model);

        return true;
}

MyModel *browse::select_ratedVoltage()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Value from RatedVoltage"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(1);
    columns[0].name = "VALUE";
    columns[0].tdType = td::real8;
    columns[0].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        exit(0);

    MyModel *model = new MyModel(this, rs, true);

    return model;
}

MyModel *browse::select_ratedPower()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Value from RatedPower"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(1);
    columns[0].name = "VALUE";
    columns[0].tdType = td::real8;
    columns[0].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        exit(0);

    MyModel *model = new MyModel(this, rs, true);

    return model;
}

MyModel *browse::select_numberOfPhases()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from NumberOfPhases"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(1);
    columns[0].name = "NAME";
    columns[0].tdType = td::nch;
    columns[0].len = 16;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        exit(0);

    MyModel *model = new MyModel(this, rs, true);

    return model;
}

MyModel *browse::select_connectionType()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT shortName from ConnectionTypePrimary"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(1);
    columns[0].name = "SHORTNAME";
    columns[0].tdType = td::nch;
    columns[0].len = 6;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        exit(0);

    MyModel *model = new MyModel(this, rs, true);

    return model;
}

MyModel *browse::select_catalogType_Motor()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from CatAsynchronousMotor"));

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

MyModel *browse::select_phaseCode()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from PhaseCode"));

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

MyModel *browse::select_catalogType_Unit()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from CatGeneratingUnit"));

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

MyModel *browse::select_catalogType_Shunt()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from CatResistor"));

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

MyModel *browse::select_nodeType()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from NodeType"));

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

MyModel *browse::select_loadType()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from LoadType"));

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

MyModel *browse::select_loadDemand()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from LoadDemandModel"));

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

MyModel *browse::select_producers()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from Producers"));

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

MyModel *browse::select_system()
{
    if (!pDB)
        exit(0);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from Systems"));

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

int browse::select_prodID(QString name)
{
    if (!pDB)
        return false;

    db::Ref<td::String> refName(64);
    td::String td_name = name.toUtf8();
    refName = td_name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID from Producers WHERE Name=?"));

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
    QString ids = model->data(idx, Qt::DisplayRole).toString();
    int id = ids.toInt();

    return id;
}

int browse::select_systemID(QString name)
{
    if (!pDB)
        return false;

    db::Ref<td::String> refName(64);
    td::String td_name = name.toUtf8();
    refName = td_name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID from Systems WHERE Name=?"));

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
    QString ids = model->data(idx, Qt::DisplayRole).toString();
    int id = ids.toInt();

    return id;
}

bool browse::updateConsumer(QString name, QString aliasName, QString description, int ratedVol
                                   , float kp0, float kq0, float kp1, float kq1, float kp2, float kq2)
{

    if (!pDB)
        return false;

    int id = val2.toInt();

    td::INT4 insert_id(id);
    db::Ref<td::String> refName(64);
    db::Ref<td::String> refAliasName(32);
    db::Ref<td::String> refDescription(512);

    td::String td_name = name.toUtf8();
    td::String td_aliasName = aliasName.toUtf8();
    td::String td_description = description.toUtf8();

    refName = td_name;
    refAliasName = td_aliasName;
    refDescription = td_description;

    td::INT4 insert_ratedVol(ratedVol);
    float insert_kp0 = kp0;
    float insert_kq0 = kq0;
    float insert_kp1 = kp1;
    float insert_kq1 = kq1;
    float insert_kp2 = kp2;
    float insert_kq2 = kq2;

    update_catalog(name);
    update_jobCatalog(name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatEnergyConsumer SET Name=?, AliasName=?, Description=?, idRatedVoltage=?, kp0=?, kq0=?, kp1=?, kq1=?, kp2=?, kq2=? WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << refName << refAliasName << refDescription
           << insert_ratedVol
           << insert_kp0
           << insert_kq0
           << insert_kp1
           << insert_kq1
           << insert_kp2
           << insert_kq2
           << insert_id;

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

bool browse::updateUnit(QString name, QString aliasName, QString description, int ratedVol, int ratedPow
                      , int idNoP, int idConType, float minOpAcPow, float maxOpAcPow, float minOpRPow, float maxOpRPow
                      , float Z0_re, float Z0_im, float Z1_re, float Z1_im, float Z2_re , float Z2_im
                      , float Z0trans_re, float Z0trans_im, float Z1trans_re, float Z1trans_im
                      , float Z2trans_re, float Z2trans_im, float Z0sub_re, float Z0sub_im
                      , float Z1sub_re, float Z1sub_im, float Z2sub_re, float Z2sub_im)
{
    if (!pDB)
        return false;

    int id = val2.toInt();

    td::INT4 insert_id(id);
    db::Ref<td::String> refName(64);
    db::Ref<td::String> refAliasName(32);
    db::Ref<td::String> refDescription(512);

    td::String td_name = name.toUtf8();
    td::String td_aliasName = aliasName.toUtf8();
    td::String td_description = description.toUtf8();

    refName = td_name;
    refAliasName = td_aliasName;
    refDescription = td_description;

    td::INT4 insert_ratedVol(ratedVol);
    td::INT4 insert_ratedPow(ratedPow);
    td::INT4 insert_idNoP(idNoP);
    td::INT4 insert_idConType(idConType);
    float insert_minOpAcPow = minOpAcPow;
    float insert_maxOpAcPow = maxOpAcPow;
    float insert_minOpRPow = minOpRPow;
    float insert_maxOpRPow = maxOpRPow;
    float insert_Z0_re = Z0_re;
    float insert_Z0_im = Z0_im;
    float insert_Z1_re = Z1_re;
    float insert_Z1_im = Z1_im;
    float insert_Z2_re = Z2_re;
    float insert_Z2_im = Z2_im;
    float insert_Z0trans_re = Z0trans_re;
    float insert_Z0trans_im = Z0trans_im;
    float insert_Z1trans_re = Z1trans_re;
    float insert_Z1trans_im = Z1trans_im;
    float insert_Z2trans_re = Z2trans_re;
    float insert_Z2trans_im =  Z2trans_im;
    float insert_Z0sub_re =  Z0sub_re;
    float insert_Z0sub_im =  Z0sub_im;
    float insert_Z1sub_re =  Z1sub_re;
    float insert_Z1sub_im =  Z1sub_im;
    float insert_Z2sub_re =  Z2sub_re;
    float insert_Z2sub_im =  Z2sub_im;

    update_catalog(name);
    update_jobCatalog(name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatGeneratingUnit SET Name=?, AliasName=?, Description=?, idRatedVoltage=?, idRatedPower=?, idNumberOfPhases=?, idConnectionType=?, minOpActPow=?, maxOpActPow=?, minOpReActPow=?, maxOpReActPow=?, Z0_re=?, Z0_im=?, Z1_re=?, Z1_im=?, Z2_re=?, Z2_im=?, Z0trans_re=?, Z0trans_im=?, Z1trans_re=?, Z1trans_im=?, Z2trans_re=?, Z2trans_im=?, Z0sub_re=?, Z0sub_im=?, Z1sub_re=?, Z1sub_im=?, Z2sub_re=?, Z2sub_im=? WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << refName << refAliasName << refDescription
           << insert_ratedVol
           << insert_ratedPow
           << insert_idNoP
           << insert_idConType
           << insert_minOpAcPow
           << insert_maxOpAcPow
           << insert_minOpRPow
           << insert_maxOpRPow
           << insert_Z0_re
           << insert_Z0_im
           << insert_Z1_re
           << insert_Z1_im
           << insert_Z2_re
           << insert_Z2_im
           << insert_Z0trans_re
           << insert_Z0trans_im
           << insert_Z1trans_re
           << insert_Z1trans_im
           << insert_Z2trans_re
           << insert_Z2trans_im
           << insert_Z0sub_re
           << insert_Z0sub_im
           << insert_Z1sub_re
           << insert_Z1sub_im
           << insert_Z2sub_re
           << insert_Z2sub_im
           << insert_id ;

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

bool browse::updateMotor(QString name, QString aliasName, QString description, int idRatedVol
                            , int idNoP, float nmp, float pow, float eff, float load, int rpm, float isu, float rx)
{
    if (!pDB)
        return false;

    int id = val2.toInt();

    td::INT4 insert_id(id);
    db::Ref<td::String> refName(64);
    db::Ref<td::String> refAliasName(32);
    db::Ref<td::String> refDescription(512);

    td::String td_name = name.toUtf8();
    td::String td_aliasName = aliasName.toUtf8();
    td::String td_description = description.toUtf8();

    refName = td_name;
    refAliasName = td_aliasName;
    refDescription = td_description;

    td::INT4 insert_idRatedVol(idRatedVol);
    td::INT4 insert_idNoP(idNoP);
    float insert_nmp=nmp;
    float insert_pow = pow;
    float insert_eff=eff;
    float insert_load=load;
    td::INT4 insert_rpm(rpm);
    float insert_isu=isu;
    float insert_rx=rx;

    update_catalog(name);
    update_jobCatalog(name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatAsynchronousMotor SET Name=?, AliasName=?, Description=?, idNumberOfPhases=?, idRatedVoltage=?, nomMechPow=?, powerFactor=?, efficiency=?, loadFactor=?, rpm=?, Isu_In=?, r_x=? WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << refName << refAliasName << refDescription
           << insert_idRatedVol
           << insert_idNoP
           << insert_nmp
           << insert_pow
           << insert_eff
           << insert_load
           << insert_rpm
           << insert_isu
           << insert_rx
           << insert_id;

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

bool browse::updateMotorPla(int systemId, QString name, QString alias, QString desc, int idPhase, int idCatalog, int idConnection)
{
    if (!pDB)
        return false;

    int id = val2.toInt();
    td::INT4 insert_systemId(systemId);
    td::INT4 insert_id(id);

    db::Ref<td::String> refName(64);
    db::Ref<td::String> refAliasName(32);
    db::Ref<td::String> refDescription(512);
    td::String td_name = name.toUtf8();
    td::String td_aliasName = alias.toUtf8();
    td::String td_description = desc.toUtf8();
    refName = td_name;
    refAliasName = td_aliasName;
    refDescription = td_description;

    td::INT4 insert_idPhase(idPhase);
    td::INT4 insert_idCatalog(idCatalog);
    td::INT4 insert_idConnection(idConnection);

    update_placement(systemId, name);
    update_jobPlacement(systemId, name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacAsynchronousMotor SET SystemID=?, Name=?, AliasName=?, Description=?, idPhaseCode=?, idCatalogType=?, idConnectionType=? WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_systemId << refName << refAliasName << refDescription
           << insert_idPhase << insert_idCatalog << insert_idConnection << insert_id;


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

bool browse::updateUnitPlacement(int systemID, QString name, QString aliasName, QString description
                               , int phaseCode, int catalogType, int nodeType, int loadType, int loadDemand
                               , float des, int grounded, float r, float x)
{
    if (!pDB)
        return false;

    int id = val2.toInt();

    td::INT4 insert_systemID(systemID);
    td::INT4 insert_id(id);

    db::Ref<td::String> refName(64);
    db::Ref<td::String> refAliasName(32);
    db::Ref<td::String> refDescription(512);

    td::String td_name = name.toUtf8();
    td::String td_aliasName = aliasName.toUtf8();
    td::String td_description = description.toUtf8();

    refName = td_name;
    refAliasName = td_aliasName;
    refDescription = td_description;
    td::INT4 insert_phaseCode = phaseCode;
    td::INT4 insert_catalogType = catalogType;
    td::INT4 insert_nodeType = nodeType;
    td::INT4 insert_loadType = loadType;
    td::INT4 insert_loadDemand = loadDemand;
    float insert_des = des;
    td::INT4 insert_grounded(grounded);
    float insert_r = r;
    float insert_x = x;

    update_placement(systemID, name);
    update_jobPlacement(systemID, name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacGeneratingUnit SET SystemID=?, Name=?, AliasName=?, Description=?, idPhaseCode=?, idCatalogType=?, idNodeType=?, idLoadType=?, idLoadDemandModel=?, desiredVoltage=?, grounded=?, rGround=?, xGround=? WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_systemID << refName << refAliasName << refDescription
           << insert_phaseCode
           << insert_catalogType
           << insert_nodeType
           << insert_loadType
           << insert_loadDemand
           << insert_des
           << insert_grounded
           << insert_r
           << insert_x
           << insert_id;

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

bool browse::updateShuntResistor(int systemID, QString name, QString aliasName
                                        , QString description, int idCatType)
{
    if (!pDB)
        return false;

    int id = val2.toInt();
    td::INT4 insert_systemID(systemID);
    td::INT4 insert_id(id);

    db::Ref<td::String> refName(64);
    db::Ref<td::String> refAliasName(32);
    db::Ref<td::String> refDescription(512);

    td::String td_name = name.toUtf8();
    td::String td_aliasName = aliasName.toUtf8();
    td::String td_description = description.toUtf8();

    refName = td_name;
    refAliasName = td_aliasName;
    refDescription = td_description;

    td::INT4 insert_idCatType(idCatType);

    update_placement(systemID, name);
    update_jobPlacement(systemID, name);

    //start transaction log
    db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacResistor SET SystemID=?, Name=?, AliasName=?, Description=?, idCatalogType=? WHERE ID=?"));

        //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

        //bind params
    params << insert_systemID
           << refName
           << refAliasName
           << refDescription
           << insert_idCatType
           << insert_id;

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

bool browse::updateJobCons()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    // db::Ref<td::String> refName(64);
    // td::String td_name = oldname.toUtf8();
    // refName = td_name;

    updateJobIDCat();

    //start transaction log
    db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatEnergyConsumer SET JobID=0 WHERE ID=?"));

        //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

        //bind params
    params << insert_id;

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

bool browse::updateJobUnit()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    updateJobIDCat();

    //start transaction log
    db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatGeneratingUnit SET JobID=0 WHERE ID=?"));

        //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

        //bind params
    params << insert_id;

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

bool browse::updateJobMotor()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    updateJobIDCat();

    //start transaction log
    db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatAsynchronousMotor SET JobID=0 WHERE ID=?"));

        //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

        //bind params
    params << insert_id;

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

bool browse::updateJobMotorPla()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    updateJobIDPla();

    //start transaction log
    db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacAsynchronousMotor SET JobID=0 WHERE ID=?"));

        //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

        //bind params
    params << insert_id;

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

bool browse::updateJobUnitPla()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    updateJobIDPla();

    //start transaction log
    db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacGeneratingUnit SET JobID=0 WHERE ID=?"));

        //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

        //bind params
    params << insert_id;

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

bool browse::updateJobResPla()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    updateJobIDPla();

    //start transaction log
    db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacResistor SET JobID=0 WHERE ID=?"));

        //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

        //bind params
    params << insert_id;

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

bool browse::updateJobIDCat()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    db::Ref<td::String> refName(64);
    td::String td_name = oldname.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE JobCatalogs SET JobID=0 WHERE CatID=? AND CatName=?"));

        //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

        //bind params
    params << insert_id << refName;

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

bool browse::updateJobIDPla()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    db::Ref<td::String> refName(64);
    td::String td_name = oldname.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE JobPlacements SET JobID=0 WHERE CatID=? AND CatName=?"));

        //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

        //bind params
    params << insert_id << refName;

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

bool browse::update_catalog(QString name)
{
    if (!pDB)
        return false;

    int id = val2.toInt();
    td::INT4 insert_id(id);

    db::Ref<td::String> refoldName(64);
    td::String td_oldname = oldname.toUtf8();
    refoldName = td_oldname;

    db::Ref<td::String> refName(64);
    td::String td_name = name.toUtf8();
    refName = td_name;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatNaming SET Name=? WHERE ID=? AND Name=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << refName << insert_id << refoldName;

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
        std::cout << "Data updated CatNaming" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool browse::update_placement(int systemID, QString name)
{
    if (!pDB)
        return false;

    int id = val2.toInt();
    td::INT4 insert_system(systemID);
    td::INT4 insert_id(id);

    db::Ref<td::String> refoldName(64);
    td::String td_oldname = oldname.toUtf8();
    refoldName = td_oldname;

    db::Ref<td::String> refName(64);
    td::String td_name = name.toUtf8();
    refName = td_name;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacementNaming SET SystemID=?, Name=? WHERE ID=? AND Name=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_system << refName << insert_id << refoldName;

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
        std::cout << "Data updated PlacementNaming" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool browse::update_jobCatalog(QString catName)
{
    if (!pDB)
        return false;

    int id = val2.toInt();
    td::INT4 insert_id(id);

    db::Ref<td::String> refoldName(64);
    td::String td_oldname = oldname.toUtf8();
    refoldName = td_oldname;

    db::Ref<td::String> refName(64);
    td::String td_name = catName.toUtf8();
    refName = td_name;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE JobCatalogs SET CatName=? WHERE CatID=? AND CatName=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << refName << insert_id << refoldName;

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
        std::cout << "Data updated JobCatalog" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool browse::update_jobPlacement(int systemID, QString catName)
{
    if (!pDB)
        return false;

    int id = val2.toInt();
    td::INT4 insert_id(id);
    td::INT4 insert_system(systemID);

    db::Ref<td::String> refoldName(64);
    td::String td_oldname = oldname.toUtf8();
    refoldName = td_oldname;

    db::Ref<td::String> refName(64);
    td::String td_name = catName.toUtf8();
    refName = td_name;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE JobPlacements SET SystemID=? CatName=? WHERE CatID=? AND CatName=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_system << refName << insert_id << refoldName;

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
        std::cout << "Data updated JobPlacement" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool browse::setConsValues()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID, Name, AliasName, Description, idRatedVoltage, kp0, kq0, kp1, kq1, kp2, kq2, ProducerID from CatEnergyConsumer WHERE ID=?"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_id;

    columns.reserve(12);
    columns[0].name = "Id";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    columns[1].name = "Name";
    columns[1].tdType = td::nch;
    columns[1].len = 64;

    columns[2].name = "AliasName";
    columns[2].tdType = td::nch;
    columns[2].len = 32;

    columns[3].name = "Description";
    columns[3].tdType = td::nch;
    columns[3].len = 512;

    columns[4].name = "idRatedVoltage";
    columns[4].tdType = td::int4;
    columns[4].len = 0;

    columns[5].name = "kp0";
    columns[5].tdType = td::real8;
    columns[5].len = 0;

    columns[6].name = "kq0";
    columns[6].tdType = td::real8;
    columns[6].len = 0;

    columns[7].name = "kp1";
    columns[7].tdType = td::real8;
    columns[7].len = 0;

    columns[8].name = "kq1";
    columns[8].tdType = td::real8;
    columns[8].len = 0;

    columns[9].name = "kp2";
    columns[9].tdType = td::real8;
    columns[9].len = 0;

    columns[10].name = "kq2";
    columns[10].tdType = td::real8;
    columns[10].len = 0;

    columns[11].name = "ProducerID";
    columns[11].tdType = td::int4;
    columns[11].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    QModelIndex idx = model->index(0,1);
    idx = model->index(0,1);
    nameVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,2);
    aliasVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,3);
    descVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,4);
    rVoltVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,5);
    kp0Val = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,6);
    kq0Val = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,7);
    kp1Val = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,8);
    kq1Val = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,9);
    kp2Val = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,10);
    kq2Val = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,11);
    prodVal = model->data(idx, Qt::DisplayRole).toString();


    return true;
}

bool browse::setUnitValues()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID, Name, AliasName, Description, idRatedVoltage, idRatedPower, idNumberOfPhases, idConnectionType, minOpActPow, maxOpActPow, minOpReActPow, maxOpReActPow, Z0_re, Z0_im, Z1_re, Z1_im, Z2_re, Z2_im, Z0trans_re, Z0trans_im, Z1trans_re, Z1trans_im, Z2trans_re, Z2trans_im, Z0sub_re, Z0sub_im, Z1sub_re, Z1sub_im, Z2sub_re, Z2sub_im, ProducerID from CatGeneratingUnit WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_id;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(31);
    columns[0].name = "Id";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    columns[1].name = "Name";
    columns[1].tdType = td::nch;
    columns[1].len = 64;

    columns[2].name = "AliasName";
    columns[2].tdType = td::nch;
    columns[2].len = 32;

    columns[3].name = "Description";
    columns[3].tdType = td::nch;
    columns[3].len = 512;

    columns[4].name = "idRatedVoltage";
    columns[4].tdType = td::int4;
    columns[4].len = 0;

    columns[5].name = "idRatedPower";
    columns[5].tdType = td::int4;
    columns[5].len = 0;

    columns[6].name = "idNumberOfPhases";
    columns[6].tdType = td::int4;
    columns[6].len = 0;

    columns[7].name = "idConnectionType";
    columns[7].tdType = td::int4;
    columns[7].len = 0;

    columns[8].name = "minOpActPow";
    columns[8].tdType = td::real8;
    columns[8].len = 0;

    columns[9].name = "maxOpActPow";
    columns[9].tdType = td::real8;
    columns[9].len = 0;

    columns[10].name = "minOpReActPow";
    columns[10].tdType = td::real8;
    columns[10].len = 0;

    columns[11].name = "maxOpReActPow";
    columns[11].tdType = td::real8;
    columns[11].len = 0;

    columns[12].name = "Z0_re";
    columns[12].tdType = td::real8;
    columns[12].len = 0;

    columns[13].name = "Z0_im";
    columns[13].tdType = td::real8;
    columns[13].len = 0;

    columns[14].name = "Z1_re";
    columns[14].tdType = td::real8;
    columns[14].len = 0;

    columns[15].name = "Z1_im";
    columns[15].tdType = td::real8;
    columns[15].len = 0;

    columns[16].name = "Z2_re";
    columns[16].tdType = td::real8;
    columns[16].len = 0;

    columns[17].name = "Z2_im";
    columns[17].tdType = td::real8;
    columns[17].len = 0;

    columns[18].name = "Z0trans_re";
    columns[18].tdType = td::real8;
    columns[18].len = 0;

    columns[19].name = "Z0trans_im";
    columns[19].tdType = td::real8;
    columns[19].len = 0;

    columns[20].name = "Z1trans_re";
    columns[20].tdType = td::real8;
    columns[20].len = 0;

    columns[21].name = "Z1trans_im";
    columns[21].tdType = td::real8;
    columns[21].len = 0;

    columns[22].name = "Z2trans_re";
    columns[22].tdType = td::real8;
    columns[22].len = 0;

    columns[23].name = "Z2trans_im";
    columns[23].tdType = td::real8;
    columns[23].len = 0;

    columns[24].name = "Z0sub_re";
    columns[24].tdType = td::real8;
    columns[24].len = 0;

    columns[25].name = "Z0sub_im";
    columns[25].tdType = td::real8;
    columns[25].len = 0;

    columns[26].name = "Z1sub_re";
    columns[26].tdType = td::real8;
    columns[26].len = 0;

    columns[27].name = "Z1sub_im";
    columns[27].tdType = td::real8;
    columns[27].len = 0;

    columns[28].name = "Z2sub_re";
    columns[28].tdType = td::real8;
    columns[28].len = 0;

    columns[29].name = "Z2sub_im";
    columns[29].tdType = td::real8;
    columns[29].len = 0;

    columns[30].name = "ProducerID";
    columns[30].tdType = td::int4;
    columns[30].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);


    QModelIndex idx = model->index(0,1);
    idx = model->index(0,1);
    nameVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,2);
    aliasVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,3);
    descVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,4);
    rVoltVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,5);
    rPowVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,6);
    nopVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,7);
    cTypeVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,8);
    minOpAcPowVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,9);
    maxOpAcPowVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,10);
    minOpRPowVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,11);
    maxOpRPowVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,12);
    Z0_reVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,13);
    Z0_imVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,14);
    Z1_reVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,15);
    Z1_imVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,16);
    Z2_reVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,17);
    Z2_imVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,18);
    Z0trans_reVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,19);
    Z0trans_imVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,20);
    Z1trans_reVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,21);
    Z1trans_imVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,22);
    Z2trans_reVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,23);
    Z2trans_imVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,24);
    Z0sub_reVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,25);
    Z0sub_imVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,26);
    Z1sub_reVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,27);
    Z1sub_imVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,28);
    Z2sub_reVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,29);
    Z2sub_imVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,30);
    prodVal = model->data(idx, Qt::DisplayRole).toString();


    return true;
}

bool browse::setMotorValues()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID, Name, AliasName, Description, idNumberOfPhases, idRatedVoltage, nomMechPow, powerFactor, efficiency, loadFactor, rpm, Isu_In, r_x, ProducerID from CatAsynchronousMotor WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_id;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(14);
        columns[0].name = "Id";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 128;

        columns[2].name = "AliasName";
        columns[2].tdType = td::nch;
        columns[2].len = 32;

        columns[3].name = "Description";
        columns[3].tdType = td::nch;
        columns[3].len = 512;

        columns[4].name = "idNumberOfPhases";
        columns[4].tdType = td::int4;
        columns[4].len = 0;

        columns[5].name = "idRatedVoltage";
        columns[5].tdType = td::int4;
        columns[5].len = 0;

        columns[6].name = "nomMechPow";
        columns[6].tdType = td::real8;
        columns[6].len = 0;

        columns[7].name = "powerFactor";
        columns[7].tdType = td::real8;
        columns[7].len = 0;

        columns[8].name = "efficiency";
        columns[8].tdType = td::real8;
        columns[8].len = 0;

        columns[9].name = "loadFactor";
        columns[9].tdType = td::real8;
        columns[9].len = 0;

        columns[10].name = "rpm";
        columns[10].tdType = td::int4;
        columns[10].len = 0;

        columns[11].name = "Isu_In";
        columns[11].tdType = td::real8;
        columns[11].len = 0;

        columns[12].name = "r_x";
        columns[12].tdType = td::real8;
        columns[12].len = 0;

        columns[13].name = "ProducerID";
        columns[13].tdType = td::int4;
        columns[13].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    QModelIndex idx = model->index(0,1);
    idx = model->index(0,1);
    nameVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,2);
    aliasVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,3);
    descVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,4);
    nopVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,5);
    rVoltVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,6);
    nmpVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,7);
    powFVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,8);
    effVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,9);
    loadFVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,10);
    rmpVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,11);
    isuVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,12);
    rxVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,13);
    prodVal = model->data(idx, Qt::DisplayRole).toString();

    return true;
}

bool browse::setMotorPlaValues()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT SystemID, ID, Name, AliasName, Description, idPhaseCode, idCatalogType, idConnectionType, ProducerID from PlacAsynchronousMotor WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_id;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(9);
        columns[0].name = "SystemID";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Id";
        columns[1].tdType = td::int4;
        columns[1].len = 0;

        columns[2].name = "Name";
        columns[2].tdType = td::nch;
        columns[2].len = 64;

        columns[3].name = "AliasName";
        columns[3].tdType = td::nch;
        columns[3].len = 32;

        columns[4].name = "Description";
        columns[4].tdType = td::nch;
        columns[4].len = 512;

        columns[5].name = "idPhaseCode";
        columns[5].tdType = td::int4;
        columns[5].len = 0;

        columns[6].name = "idCatalogType";
        columns[6].tdType = td::int4;
        columns[6].len = 0;

        columns[7].name = "idConnectionType";
        columns[7].tdType = td::int4;
        columns[7].len = 0;

        columns[8].name = "ProducerID";
        columns[8].tdType = td::int4;
        columns[8].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    QModelIndex idx = model->index(0,1);
    idx = model->index(0,2);
    nameVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,3);
    aliasVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,4);
    descVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,5);
    phaseCVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,6);
    catTVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,7);
    cTypeVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,0);
    systemVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,8);
    prodVal = model->data(idx, Qt::DisplayRole).toString();

    return true;
}

bool browse::setUnitPlaValues()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT SystemID, ID, Name, AliasName, Description, idPhaseCode, idCatalogType, idNodeType, idLoadType, idLoadDemandModel, desiredVoltage, grounded, rGround, xGround, ProducerID from PlacGeneratingUnit WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_id;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(15);

    columns[0].name = "SystemID";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    columns[1].name = "Id";
    columns[1].tdType = td::int4;
    columns[1].len = 0;

    columns[2].name = "Name";
    columns[2].tdType = td::nch;
    columns[2].len = 64;

    columns[3].name = "AliasName";
    columns[3].tdType = td::nch;
    columns[3].len = 32;

    columns[4].name = "Description";
    columns[4].tdType = td::nch;
    columns[4].len = 512;

    columns[5].name = "idPhaseCode";
    columns[5].tdType = td::int4;
    columns[5].len = 0;

    columns[6].name = "idCatalogType";
    columns[6].tdType = td::int4;
    columns[6].len = 0;

    columns[7].name = "idNodeType";
    columns[7].tdType = td::int4;
    columns[7].len = 0;

    columns[8].name = "idLoadType";
    columns[8].tdType = td::int4;
    columns[8].len = 0;

    columns[9].name = "idLoadDemandModel";
    columns[9].tdType = td::int4;
    columns[9].len = 0;

    columns[10].name = "desiredVoltage";
    columns[10].tdType = td::real8;
    columns[10].len = 0;

    columns[11].name = "grounded";
    columns[11].tdType = td::int4;
    columns[11].len = 0;

    columns[12].name = "rGround";
    columns[12].tdType = td::real8;
    columns[12].len = 0;

    columns[13].name = "xGround";
    columns[13].tdType = td::real8;
    columns[13].len = 0;

    columns[14].name = "ProducerID";
    columns[14].tdType = td::int4;
    columns[14].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    QModelIndex idx = model->index(0,1);
    idx = model->index(0,2);
    nameVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,3);
    aliasVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,4);
    descVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,5);
    phaseCVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,6);
    catTVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,7);
    nodeTVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,8);
    loadTVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,9);
    loadDMVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,10);
    dVoltVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,11);
    groundVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,12);
    rGroundVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,13);
    xGroundVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,0);
    systemVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,14);
    prodVal = model->data(idx, Qt::DisplayRole).toString();

    return true;
}

bool browse::setResPlaValues()
{
    if (!pDB)
        return false;

    int id = catID;
    td::INT4 insert_id(id);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT SystemID, ID, Name, AliasName, Description, idCatalogType, ProducerID from PlacResistor WHERE ID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_id;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(7);
        columns[0].name = "SystemID";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Id";
        columns[1].tdType = td::int4;
        columns[1].len = 0;

        columns[2].name = "Name";
        columns[2].tdType = td::nch;
        columns[2].len = 64;

        columns[3].name = "AliasName";
        columns[3].tdType = td::nch;
        columns[3].len = 32;

        columns[4].name = "Description";
        columns[4].tdType = td::nch;
        columns[4].len = 512;

        columns[5].name = "idCatalogType";
        columns[5].tdType = td::int4;
        columns[5].len = 0;

        columns[6].name = "ProducerID";
        columns[6].tdType = td::int4;
        columns[6].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    QModelIndex idx = model->index(0,1);
    idx = model->index(0,2);
    nameVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,3);
    aliasVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,4);
    descVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,5);
    catTVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,0);
    systemVal = model->data(idx, Qt::DisplayRole).toString();

    idx = model->index(0,6);
    prodVal = model->data(idx, Qt::DisplayRole).toString();

    return true;
}

void browse::setCatModel(MyModel *n)
{
    proxy->setSourceModel(n);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(1);

    ui->catalogTableView->setModel(proxy);
    ui->catalogTableView->resizeRowsToContents();
    ui->catalogTableView->horizontalHeader()->setStretchLastSection(true);
}

void browse::setPlaModel(MyModel *n)
{
    proxy2->setSourceModel(n);
    proxy2->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy2->setFilterKeyColumn(1);

    ui->placTableView->setModel(proxy2);
    ui->placTableView->resizeRowsToContents();
    ui->placTableView->horizontalHeader()->setStretchLastSection(true);
}

void browse::on_pushButton_3_clicked()
{
    addCatPla add (refJobID, this);

    if(add.exec() == QDialog::Accepted)
    {
    select_catalogs(refJobID);
    select_placements(refJobID);
    }
}

void browse::on_catalogTableView_clicked(const QModelIndex &index)
{
    int inx = index.row();
    QModelIndex ind = ui->catalogTableView->model()->index(inx,0);
    ui->catalogTableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val = ui->catalogTableView->model()->data(ind).toString();
    typeID = val.toInt();

    QModelIndex ind2 = ui->catalogTableView->model()->index(inx,1);
    ui->catalogTableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val2 = ui->catalogTableView->model()->data(ind2).toString();
    catID = val2.toInt();

    QModelIndex ind3 = ui->catalogTableView->model()->index(inx,2);
    ui->catalogTableView->selectionModel()->select(index, QItemSelectionModel::Select);
    oldname = ui->catalogTableView->model()->data(ind3).toString();
}

void browse::on_placTableView_clicked(const QModelIndex &index)
{
    int inx = index.row();
    QModelIndex ind = ui->placTableView->model()->index(inx,0);
    ui->placTableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val = ui->placTableView->model()->data(ind).toString();
    typeID = val.toInt();

    QModelIndex ind2 = ui->placTableView->model()->index(inx,1);
    ui->placTableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val2 = ui->placTableView->model()->data(ind2).toString();
    catID = val2.toInt();

    QModelIndex ind3 = ui->catalogTableView->model()->index(inx,2);
    ui->catalogTableView->selectionModel()->select(index, QItemSelectionModel::Select);
    oldname = ui->catalogTableView->model()->data(ind3).toString();
}

void browse::on_pushButton_2_clicked()
{
    this->close();
}

void browse::on_pushButton_clicked()
{
    if(typeID == 17)
    {
        catConsEdtClicked();
    }

    else if(typeID == 18)
    {
        catUnitEdtClicked();
    }

    else if(typeID == 19)
    {
        catMotorEdtClicked();
    }

    else if(typeID == 33)
    {
        plaMotorEdtClicked();
    }

    else if(typeID == 31)
    {
        plaUnitEdtClicked();
    }

    else if(typeID == 34)
    {
        plaResistorEdtClicked();
    }
}

void browse::catConsEdtClicked()
{
    setConsValues();
    catConsumer catCons(this);
    catCons.setJobID(refJobID);
    catCons.setProducer(select_producers(), prodVal.toInt(), 1);
    catCons.setDisabledID(val2);
    catCons.setName(nameVal, 1);
    catCons.setAliasName(aliasVal, 1);
    catCons.setRatedVoltage(select_ratedVoltage(), rVoltVal.toInt(), 1);
    catCons.setKP0(kp0Val.toFloat(), 1);
    catCons.setKQ0(kq0Val.toFloat(), 1);
    catCons.setKP1(kp1Val.toFloat(), 1);
    catCons.setKQ1(kq1Val.toFloat(), 1);
    catCons.setKP2(kp2Val.toFloat(), 1);
    catCons.setKQ2(kq2Val.toFloat(), 1);
    catCons.setDescription(descVal, 1);

    if (catCons.exec() == QDialog::Accepted)
    {
        updateConsumer( catCons.name()
                      , catCons.aliasName()
                      , catCons.description()
                      , catCons.idRatedVol()
                      , catCons.kP0()
                      , catCons.kQ0()
                      , catCons.kP1()
                      , catCons.kQ1()
                      , catCons.kP2()
                      , catCons.kQ2());
        select_catalogs(refJobID);
        select_placements(refJobID);
    }
}

void browse::catUnitEdtClicked()
{
    setUnitValues();
    catUnit unitCatalog(this);
    unitCatalog.setJobID(refJobID);
    unitCatalog.setProducer(select_producers(), prodVal.toInt(), 0);
    unitCatalog.setDisabledID(val2);
    unitCatalog.setName(nameVal, 0);
    unitCatalog.setAliasName(aliasVal, 0);
    unitCatalog.setRatedVoltage(select_ratedVoltage(), rVoltVal.toInt(), 0);
    unitCatalog.setRatedPower(select_ratedPower(), rPowVal.toInt(), 0);
    unitCatalog.setNumberOfPhases(select_numberOfPhases(), nopVal.toInt(), 0);
    unitCatalog.setConnectionType(select_connectionType(), cTypeVal.toInt(), 0);
    unitCatalog.setminOpAcPow(minOpAcPowVal.toFloat(), 0);
    unitCatalog.setmaxOpAcPow(maxOpAcPowVal.toFloat(), 0);
    unitCatalog.setminOpRPow(minOpRPowVal.toFloat(), 0);
    unitCatalog.setmaxOpRPow(maxOpRPowVal.toFloat(), 0);
    unitCatalog.setZ0_re(Z0_reVal.toFloat(), 0);
    unitCatalog.setZ0_im(Z0_imVal.toFloat(), 0);
    unitCatalog.setZ1_re(Z1_reVal.toFloat(), 0);
    unitCatalog.setZ1_im(Z1_imVal.toFloat(), 0);
    unitCatalog.setZ2_re(Z2_reVal.toFloat(), 0);
    unitCatalog.setZ2_im(Z2_imVal.toFloat(), 0);
    unitCatalog.setZ0trans_re(Z0trans_reVal.toFloat(), 0);
    unitCatalog.setZ0trans_im(Z0trans_imVal.toFloat(), 0);
    unitCatalog.setZ1trans_re(Z1trans_reVal.toFloat(), 0);
    unitCatalog.setZ1trans_im(Z1trans_imVal.toFloat(), 0);
    unitCatalog.setZ2trans_re(Z2trans_reVal.toFloat(), 0);
    unitCatalog.setZ2trans_im(Z2trans_imVal.toFloat(), 0);
    unitCatalog.setZ0sub_re(Z0sub_reVal.toFloat(), 0);
    unitCatalog.setZ0sub_im(Z0sub_imVal.toFloat(), 0);
    unitCatalog.setZ1sub_re(Z1sub_reVal.toFloat(), 0);
    unitCatalog.setZ1sub_im(Z1sub_imVal.toFloat(), 0);
    unitCatalog.setZ2sub_re(Z2sub_reVal.toFloat(), 0);
    unitCatalog.setZ2sub_im(Z2sub_imVal.toFloat(), 0);
    unitCatalog.setDescription(descVal, 0);

    if (unitCatalog.exec() == QDialog::Accepted)
    {
        updateUnit(unitCatalog.name()
                  , unitCatalog.aliasName()
                  , unitCatalog.description()
                  , unitCatalog.idRatedVol()
                  , unitCatalog.idRatedPower()
                  , unitCatalog.idNumberOfPhases()
                  , unitCatalog.idConnectionType()
                  , unitCatalog.minOpAcPow()
                  , unitCatalog.maxOpAcPow()
                  , unitCatalog.minOpRPow()
                  , unitCatalog.maxOpRPow()
                  , unitCatalog.Z0_re()
                  , unitCatalog.Z0_im()
                  , unitCatalog.Z1_re()
                  , unitCatalog.Z1_im()
                  , unitCatalog.Z2_re()
                  , unitCatalog.Z2_im()
                  , unitCatalog.Z0trans_re()
                  , unitCatalog.Z0trans_im()
                  , unitCatalog.Z1trans_re()
                  , unitCatalog.Z1trans_im()
                  , unitCatalog.Z2trans_re()
                  , unitCatalog.Z2trans_im()
                  , unitCatalog.Z0sub_re()
                  , unitCatalog.Z0sub_im()
                  , unitCatalog.Z1sub_re()
                  , unitCatalog.Z1sub_im()
                  , unitCatalog.Z2sub_re()
                  , unitCatalog.Z2sub_im());
        select_catalogs(refJobID);
        select_placements(refJobID);
    }
}

void browse::catMotorEdtClicked()
{
    setMotorValues();
    catMotor motorCatalog(this);
    motorCatalog.setJobID(refJobID);
    motorCatalog.setProducer(select_producers(), prodVal.toInt(), 1);
    motorCatalog.setDisabledID(val2);
    motorCatalog.setName(nameVal, 1);
    motorCatalog.setAliasName(aliasVal, 1);
    motorCatalog.setNumberOfPhases(select_numberOfPhases(), nopVal.toInt(), 1);
    motorCatalog.setRatedVoltage(select_ratedVoltage(), rVoltVal.toInt(), 1);
    motorCatalog.setnmp(nmpVal.toFloat(), 1);
    motorCatalog.setpow(powFVal.toFloat(), 1);
    motorCatalog.seteff(effVal.toFloat(), 1);
    motorCatalog.setload(loadFVal.toFloat(), 1);
    motorCatalog.setrpm(rmpVal.toFloat(), 1);
    motorCatalog.setisu(isuVal.toFloat(), 1);
    motorCatalog.setrx(rxVal.toFloat(), 1);
    motorCatalog.setDescription(descVal, 1);

    if (motorCatalog.exec() == QDialog::Accepted)
    {
        updateMotor(motorCatalog.name()
                   , motorCatalog.aliasName()
                   , motorCatalog.description()
                   , motorCatalog.idRatedVol()
                   , motorCatalog.idNumberOfPhases()
                   , motorCatalog.nmp()
                   , motorCatalog.pow()
                   , motorCatalog.eff()
                   , motorCatalog.load()
                   , motorCatalog.rpm()
                   , motorCatalog.isu()
                   , motorCatalog.rx());
        select_catalogs(refJobID);
        select_placements(refJobID);
    }
}

void browse::plaMotorEdtClicked()
{
    setMotorPlaValues();
    plaMotor motorPlac(this);
    motorPlac.setJobID(refJobID);
    motorPlac.setSystemID(select_system(), systemVal.toInt(), 1);
    motorPlac.setProducer(select_producers(), prodVal.toInt(), 1);
    motorPlac.setDisabledID(val2);
    motorPlac.setName(nameVal, 1);
    motorPlac.setAliasName(aliasVal, 1);
    motorPlac.setDescription(descVal, 1);
    motorPlac.setPhaseCode(select_phaseCode(), phaseCVal.toInt(), 1);
    motorPlac.setCatalogType(select_catalogType_Motor(), catTVal.toInt(), 1);
    motorPlac.setConnectionType(select_connectionType(), cTypeVal.toInt(), 1);

    if (motorPlac.exec() == QDialog::Accepted)
    {
        updateMotorPla(select_systemID(motorPlac.systemName())
                      , motorPlac.name()
                      , motorPlac.aliasName()
                      , motorPlac.description()
                      , motorPlac.idPhaseCode()
                      , motorPlac.idCatalogType()
                      , motorPlac.idConnectionType());
        select_catalogs(refJobID);
        select_placements(refJobID);
    }
}

void browse::plaUnitEdtClicked()
{
    setUnitPlaValues();
    plaUnit unitPlacement(this);
    unitPlacement.setJobID(refJobID);
    unitPlacement.setSystemID(select_system(), systemVal.toInt(), 1);
    unitPlacement.setProducer(select_producers(), prodVal.toInt(), 1);
    unitPlacement.setDisabledID(val2);
    unitPlacement.setName(nameVal, 1);
    unitPlacement.setAliasName(aliasVal, 1);
    unitPlacement.setDescription(descVal, 1);
    unitPlacement.setPhaseCode(select_phaseCode(), phaseCVal.toInt(), 1);
    unitPlacement.setCatalogType(select_catalogType_Unit(), catTVal.toInt(), 1);
    unitPlacement.setNodeType(select_nodeType(), nodeTVal.toInt(), 1);
    unitPlacement.setLoadType(select_loadType(), loadTVal.toInt(), 1);
    unitPlacement.setLoadDemand(select_loadDemand(), loadDMVal.toInt(), 1);
    unitPlacement.setdes(dVoltVal.toFloat(), 1);
    unitPlacement.setr(rGroundVal.toFloat(), 1);
    unitPlacement.setx(xGroundVal.toFloat(), 1);

    if (unitPlacement.exec() == QDialog::Accepted)
    {
        updateUnitPlacement(select_systemID(unitPlacement.systemName())
                           , unitPlacement.name()
                           , unitPlacement.aliasName()
                           , unitPlacement.description()
                           , unitPlacement.phaseCode()
                           , unitPlacement.catalogType()
                           , unitPlacement.nodeType()
                           , unitPlacement.loadType()
                           , unitPlacement.loadDemand()
                           , unitPlacement.des()
                           , unitPlacement.grounded()
                           , unitPlacement.r()
                           , unitPlacement.x());
        select_catalogs(refJobID);
        select_placements(refJobID);

    }
}

void browse::plaResistorEdtClicked()
{
    setResPlaValues();
    plaResistor shuntResistor(this);
    shuntResistor.setJobID(refJobID);
    shuntResistor.setSystemID(select_system(), systemVal.toInt(), 1);
    shuntResistor.setProducer(select_producers(), prodVal.toInt(), 1);
    shuntResistor.setDisabledID(val2);
    shuntResistor.setName(nameVal, 1);
    shuntResistor.setAliasName(aliasVal, 1);
    shuntResistor.setDescription(descVal, 1);
    shuntResistor.setCatalogType(select_catalogType_Shunt(), catTVal.toInt(), 1);

         if ( shuntResistor.exec() == QDialog::Accepted)
         {
             updateShuntResistor( select_systemID(shuntResistor.systemName())
                                 , shuntResistor.name()
                                 , shuntResistor.aliasName()
                                 , shuntResistor.description()
                                 , shuntResistor.idCatalogType());
             select_catalogs(refJobID);
             select_placements(refJobID);
         }
}

void browse::on_comboBox_currentIndexChanged(int index)
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

void browse::on_comboBox_2_currentIndexChanged(int index)
{
    if (index == 0)
        proxy2->setFilterKeyColumn(0);
    else if(index == 1)
        proxy2->setFilterKeyColumn(1);
    else if (index == 2)
        proxy2->setFilterKeyColumn(2);
    else if (index == 3)
        proxy2->setFilterKeyColumn(3);
}

void browse::on_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
}

void browse::on_lineEdit_2_textChanged(const QString &arg1)
{
    proxy2->setFilterFixedString(arg1);
}

void browse::on_pushButton_4_clicked()
{
    if(typeID == 17)
    {
        updateJobCons();
        select_catalogs(refJobID);
    }

    else if(typeID == 18)
    {
        updateJobUnit();
        select_catalogs(refJobID);
    }

    else if(typeID == 19)
    {
        updateJobMotor();
        select_catalogs(refJobID);
    }

    else if(typeID == 33)
    {
        updateJobMotorPla();
        select_placements(refJobID);
    }

    else if(typeID == 31)
    {
        updateJobUnitPla();
        select_placements(refJobID);
    }

    else if(typeID == 34)
    {
        updateJobResPla();
        select_placements(refJobID);
    }
}
