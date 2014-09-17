#include "searchdialog.h"
#include "ui_searchdialog.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "searchDialog.h"
#include "catconsumer.h"
#include "catunit.h"
#include "catmotor.h"
#include "plamotor.h"
#include "plaunit.h"
#include "plaresistor.h"
#include "searchjobs.h"
#include "selectjob.h"
#include "messagebox.h"
#include <QDate>

extern db::ISQLDatabase *pDB;
extern bool checkBox;

searchDialog::searchDialog(int a, int refJob, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchDialog)
{
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    ui->comboBox->setCurrentIndex(2);

    refJob2 = refJob;

    if(refJob2 >= 1)
    {
        ui->editPushButton->setDisabled(true);
        ui->newPushButton->setDisabled(true);
    }

    if(a==1)
    {
        select_searchConsumer();
        this->setWindowTitle("Search Energy Consumer Catalog");
    }
    else if(a==2)
    {
        select_searchUnit();
        this->setWindowTitle("Search Generating Unit Catalog");
    }
    else if(a==3)
    {
        select_searchMotor();
        this->setWindowTitle("Search Asynchronous Motor Catalog");
    }
    else if(a==4)
    {
        select_searchMotorPla();
        this->setWindowTitle("Search Asynchronous Motor Placement");
    }
    else if(a==5)
    {
        select_searchUnitPla();
        this->setWindowTitle("Search Generating Unit Placement");
    }
    else if(a==6)
    {
        select_searchShuntRes();
        this->setWindowTitle("Search Shunt Resistor Placement");
    }

    if(a == 1 || a == 2 || a == 3 || a == 4 || a == 5 || a == 6)
    {
        int lastItem = ui->tableView->model()->rowCount();
        if(lastItem >= 1)
        {
            ui->tableView->clicked(ui->tableView->model()->index(lastItem - 1, 0));
        }
    }

}

searchDialog::~searchDialog()
{
    delete ui;
}

//----------------------------------------------------SELECT STATEMENTS---------------------------------
bool searchDialog::select_searchConsumer()
{
    if (!pDB)
        return false;

    int jobId = refJob2;
    td::INT4 insert_jobID(jobId);
    int editFlag = 0;
    td::INT4 insert_editFlag(editFlag);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT JobID, ID, Name, AliasName, Description, idRatedVoltage, kp0, kq0, kp1, kq1, kp2, kq2 from catEnergyConsumer where JobID=? or EditFlag=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_jobID << insert_editFlag;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;

    columns.reserve(12);
    columns[0].name = "JobID";
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

    columns[5].name = "idRatedVoltage";
    columns[5].tdType = td::int4;
    columns[5].len = 0;

    columns[6].name = "kp0";
    columns[6].tdType = td::real8;
    columns[6].len = 0;

    columns[7].name = "kq0";
    columns[7].tdType = td::real8;
    columns[7].len = 0;

    columns[8].name = "kp1";
    columns[8].tdType = td::real8;
    columns[8].len = 0;

    columns[9].name = "kq1";
    columns[9].tdType = td::real8;
    columns[9].len = 0;

    columns[10].name = "kp2";
    columns[10].tdType = td::real8;
    columns[10].len = 0;

    columns[11].name = "kq2";
    columns[11].tdType = td::real8;
    columns[11].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    setModel(0, model);
    chs = 1;

    return true;
}

bool searchDialog::select_searchUnit()
{
    if (!pDB)
        return false;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT JobID, ID, Name, AliasName, Description, idRatedVoltage, idRatedPower, idNumberOfPhases, idConnectionType, minOpActPow, maxOpActPow, minOpReActPow, maxOpReActPow, Z0_re, Z0_im, Z1_re, Z1_im, Z2_re, Z2_im, Z0trans_re, Z0trans_im, Z1trans_re, Z1trans_im, Z2trans_re, Z2trans_im, Z0sub_re, Z0sub_im, Z1sub_re, Z1sub_im, Z2sub_re, Z2sub_im from CatGeneratingUnit"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(31);
    columns[0].name = "JobID";
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

    columns[5].name = "idRatedVoltage";
    columns[5].tdType = td::int4;
    columns[5].len = 0;

    columns[6].name = "idRatedPower";
    columns[6].tdType = td::int4;
    columns[6].len = 0;

    columns[7].name = "idNumberOfPhases";
    columns[7].tdType = td::int4;
    columns[7].len = 0;

    columns[8].name = "idConnectionType";
    columns[8].tdType = td::int4;
    columns[8].len = 0;

    columns[9].name = "minOpActPow";
    columns[9].tdType = td::real8;
    columns[9].len = 0;

    columns[10].name = "maxOpActPow";
    columns[10].tdType = td::real8;
    columns[10].len = 0;

    columns[11].name = "minOpReActPow";
    columns[11].tdType = td::real8;
    columns[11].len = 0;

    columns[12].name = "maxOpReActPow";
    columns[12].tdType = td::real8;
    columns[12].len = 0;

    columns[13].name = "Z0_re";
    columns[13].tdType = td::real8;
    columns[13].len = 0;

    columns[14].name = "Z0_im";
    columns[14].tdType = td::real8;
    columns[14].len = 0;

    columns[15].name = "Z1_re";
    columns[15].tdType = td::real8;
    columns[15].len = 0;

    columns[16].name = "Z1_im";
    columns[16].tdType = td::real8;
    columns[16].len = 0;

    columns[17].name = "Z2_re";
    columns[17].tdType = td::real8;
    columns[17].len = 0;

    columns[18].name = "Z2_im";
    columns[18].tdType = td::real8;
    columns[18].len = 0;

    columns[19].name = "Z0trans_re";
    columns[19].tdType = td::real8;
    columns[19].len = 0;

    columns[20].name = "Z0trans_im";
    columns[20].tdType = td::real8;
    columns[20].len = 0;

    columns[21].name = "Z1trans_re";
    columns[21].tdType = td::real8;
    columns[21].len = 0;

    columns[22].name = "Z1trans_im";
    columns[22].tdType = td::real8;
    columns[22].len = 0;

    columns[23].name = "Z2trans_re";
    columns[23].tdType = td::real8;
    columns[23].len = 0;

    columns[24].name = "Z2trans_im";
    columns[24].tdType = td::real8;
    columns[24].len = 0;

    columns[25].name = "Z0sub_re";
    columns[25].tdType = td::real8;
    columns[25].len = 0;

    columns[26].name = "Z0sub_im";
    columns[26].tdType = td::real8;
    columns[26].len = 0;

    columns[27].name = "Z1sub_re";
    columns[27].tdType = td::real8;
    columns[27].len = 0;

    columns[28].name = "Z1sub_im";
    columns[28].tdType = td::real8;
    columns[28].len = 0;

    columns[29].name = "Z2sub_re";
    columns[29].tdType = td::real8;
    columns[29].len = 0;

    columns[30].name = "Z2sub_im";
    columns[30].tdType = td::real8;
    columns[30].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    setModel(0, model);

    chs=2;

    return true;
}

bool searchDialog::select_searchMotor()
{
    if (!pDB)
        return false;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT JobID, ID, Name, AliasName, Description, idNumberOfPhases, idRatedVoltage, nomMechPow, powerFactor, efficiency, loadFactor, rpm, Isu_In, r_x from CatAsynchronousMotor"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(14);
    columns[0].name = "JobID";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    columns[1].name = "Id";
    columns[1].tdType = td::int4;
    columns[1].len = 0;

    columns[2].name = "Name";
    columns[2].tdType = td::nch;
    columns[2].len = 128;

    columns[3].name = "AliasName";
    columns[3].tdType = td::nch;
    columns[3].len = 32;

    columns[4].name = "Description";
    columns[4].tdType = td::nch;
    columns[4].len = 512;

    columns[5].name = "idNumberOfPhases";
    columns[5].tdType = td::int4;
    columns[5].len = 0;

    columns[6].name = "idRatedVoltage";
    columns[6].tdType = td::int4;
    columns[6].len = 0;

    columns[7].name = "nomMechPow";
    columns[7].tdType = td::real8;
    columns[7].len = 0;

    columns[8].name = "powerFactor";
    columns[8].tdType = td::real8;
    columns[8].len = 0;

    columns[9].name = "efficiency";
    columns[9].tdType = td::real8;
    columns[9].len = 0;

    columns[10].name = "loadFactor";
    columns[10].tdType = td::real8;
    columns[10].len = 0;

    columns[11].name = "rpm";
    columns[11].tdType = td::int4;
    columns[11].len = 0;

    columns[12].name = "Isu_In";
    columns[12].tdType = td::real8;
    columns[12].len = 0;

    columns[13].name = "r_x";
    columns[13].tdType = td::real8;
    columns[13].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    setModel(0, model);

    chs=3;

    return true;
}

bool searchDialog::select_searchMotorPla()
{
    if (!pDB)
        return false;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT JobID, SystemID, ID, Name, AliasName, Description, idPhaseCode, idCatalogType, idConnectionType from PlacAsynchronousMotor"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(9);
    columns[0].name = "JobID";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    columns[1].name = "SystemID";
    columns[1].tdType = td::int4;
    columns[1].len = 0;

    columns[2].name = "Id";
    columns[2].tdType = td::int4;
    columns[2].len = 0;

    columns[3].name = "Name";
    columns[3].tdType = td::nch;
    columns[3].len = 64;

    columns[4].name = "AliasName";
    columns[4].tdType = td::nch;
    columns[4].len = 32;

    columns[5].name = "Description";
    columns[5].tdType = td::nch;
    columns[5].len = 512;

    columns[6].name = "idPhaseCode";
    columns[6].tdType = td::int4;
    columns[6].len = 0;

    columns[7].name = "idCatalogType";
    columns[7].tdType = td::int4;
    columns[7].len = 0;

    columns[8].name = "idConnectionType";
    columns[8].tdType = td::int4;
    columns[8].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    setModel(1, model);

    chs=4;
    return true;
}

bool searchDialog::select_searchUnitPla()
{
    if (!pDB)
        return false;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT JobID, SystemID, ID, Name, AliasName, Description, idPhaseCode, idCatalogType, idNodeType, idLoadType, idLoadDemandModel, desiredVoltage, grounded, rGround, xGround from PlacGeneratingUnit"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(15);
    columns[0].name = "JobID";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    columns[1].name = "SystemID";
    columns[1].tdType = td::int4;
    columns[1].len = 0;

    columns[2].name = "Id";
    columns[2].tdType = td::int4;
    columns[2].len = 0;

    columns[3].name = "Name";
    columns[3].tdType = td::nch;
    columns[3].len = 64;

    columns[4].name = "AliasName";
    columns[4].tdType = td::nch;
    columns[4].len = 32;

    columns[5].name = "Description";
    columns[5].tdType = td::nch;
    columns[5].len = 512;

    columns[6].name = "idPhaseCode";
    columns[6].tdType = td::int4;
    columns[6].len = 0;

    columns[7].name = "idCatalogType";
    columns[7].tdType = td::int4;
    columns[7].len = 0;

    columns[8].name = "idNodeType";
    columns[8].tdType = td::int4;
    columns[8].len = 0;

    columns[9].name = "idLoadType";
    columns[9].tdType = td::int4;
    columns[9].len = 0;

    columns[10].name = "idLoadDemandModel";
    columns[10].tdType = td::int4;
    columns[10].len = 0;

    columns[11].name = "desiredVoltage";
    columns[11].tdType = td::real8;
    columns[11].len = 0;

    columns[12].name = "grounded";
    columns[12].tdType = td::int4;
    columns[12].len = 0;

    columns[13].name = "rGround";
    columns[13].tdType = td::real8;
    columns[13].len = 0;

    columns[14].name = "xGround";
    columns[14].tdType = td::real8;
    columns[14].len = 0;


    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    MyModel *model = new MyModel(this, rs, true);

    setModel(1, model);
    chs=5;
    return true;
}

bool searchDialog::select_searchShuntRes()
{
    if (!pDB)
        return false;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT JobID, SystemID, ID, Name, AliasName, Description, idCatalogType from PlacResistor"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(7);
    columns[0].name = "JobID";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    columns[1].name = "SystemID";
    columns[1].tdType = td::int4;
    columns[1].len = 0;

    columns[2].name = "Id";
    columns[2].tdType = td::int4;
    columns[2].len = 0;

    columns[3].name = "Name";
    columns[3].tdType = td::nch;
    columns[3].len = 64;

    columns[4].name = "AliasName";
    columns[4].tdType = td::nch;
    columns[4].len = 32;

    columns[5].name = "Description";
    columns[5].tdType = td::nch;
    columns[5].len = 512;

    columns[6].name = "idCatalogType";
    columns[6].tdType = td::int4;
    columns[6].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    setModel(1, model);
    chs=6;
    return true;
}

//----------------------------------------------------SELECT COMBOBOX-----------------------------------
MyModel *searchDialog::select_ratedVoltage()
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

MyModel *searchDialog::select_ratedPower()
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

MyModel *searchDialog::select_numberOfPhases()
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

MyModel *searchDialog::select_connectionType()
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

MyModel *searchDialog::select_catalogType_Motor()
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

MyModel *searchDialog::select_phaseCode()
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

MyModel *searchDialog::select_catalogType_Unit()
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

MyModel *searchDialog::select_catalogType_Shunt()
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

MyModel *searchDialog::select_nodeType()
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

MyModel *searchDialog::select_loadType()
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

MyModel *searchDialog::select_loadDemand()
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

MyModel *searchDialog::select_producers()
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

MyModel *searchDialog::select_system()
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

int searchDialog::select_catJobID(int id)
{
    if (!pDB)
        exit(0);

    int jobID;
    td::INT4 insert_id(id);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT JobID from JobCatalogs WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_id;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(1);
    columns[0].name = "JobID";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        exit(0);

    MyModel *model = new MyModel(this, rs, true);

    QModelIndex idx = model->index(0,0);
    QString ids = model->data(idx, Qt::DisplayRole).toString();
    jobID = ids.toInt();

    return jobID;
}

int searchDialog::select_plaJobID(int id)
{
    if (!pDB)
        exit(0);

    int jobID;
    td::INT4 insert_id(id);

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT JobID from JobPlacements WHERE CatID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_id;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(1);
    columns[0].name = "JobID";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        exit(0);

    MyModel *model = new MyModel(this, rs, true);

    QModelIndex idx = model->index(0,0);
    QString ids = model->data(idx, Qt::DisplayRole).toString();
    jobID = ids.toInt();

    return jobID;
}

int searchDialog::select_prodID(QString name)
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

int searchDialog::select_systemID(QString name)
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

//----------------------------------------------------INSERT STATEMENTS---------------------------------
bool searchDialog::insert_consumer(int jobID, int typeID, int prodID, int id, QString name, QString aliasName, QString description, int ratedVol
                                   , float kp0, float kq0, float kp1, float kq1, float kp2, float kq2)
{
    if (!pDB)
        return false;

    td::INT4 insert_job(jobID);
    td::INT4 insert_type(typeID);
    td::INT4 insert_prod(prodID);

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

    td::INT4 insert_edit(1);

    insert_catalog(typeID, prodID, id, name);
    //update_catalog(name);
    insert_jobCatalog(jobID, typeID, id, name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO CatEnergyConsumer(JobID, TypeID, ProducerID, ID, Name, AliasName, Description, idRatedVoltage, kp0, kq0, kp1, kq1, kp2, kq2, EditFlag) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_job << insert_type << insert_prod
           << insert_id << refName << refAliasName << refDescription
           << insert_ratedVol
           << insert_kp0
           << insert_kq0
           << insert_kp1
           << insert_kq1
           << insert_kp2
           << insert_kq2
           << insert_edit;

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

bool searchDialog::insert_unit(int jobID, int typeID, int prodID, int id, QString name, QString aliasName, QString description, int ratedVol, int ratedPow
                               , int idNoP, int idConType, float minOpAcPow, float maxOpAcPow, float minOpRPow, float maxOpRPow
                               , float Z0_re, float Z0_im, float Z1_re, float Z1_im, float Z2_re , float Z2_im
                               , float Z0trans_re, float Z0trans_im, float Z1trans_re, float Z1trans_im
                               , float Z2trans_re, float Z2trans_im, float Z0sub_re, float Z0sub_im
                               , float Z1sub_re, float Z1sub_im, float Z2sub_re, float Z2sub_im)
{
    if (!pDB)
        return false;

    td::INT4 insert_job(jobID);
    td::INT4 insert_type(typeID);
    td::INT4 insert_prod(prodID);

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

    insert_catalog(typeID, prodID, id, name);
    insert_jobCatalog(jobID, typeID, id, name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO CatGeneratingUnit(JobID, TypeID, ProducerID, ID, Name, AliasName, Description, idRatedVoltage, idRatedPower, idNumberOfPhases, idConnectionType, minOpActPow, maxOpActPow, minOpReActPow, maxOpReActPow, Z0_re, Z0_im, Z1_re, Z1_im, Z2_re, Z2_im, Z0trans_re, Z0trans_im, Z1trans_re, Z1trans_im, Z2trans_re, Z2trans_im, Z0sub_re, Z0sub_im, Z1sub_re, Z1sub_im, Z2sub_re, Z2sub_im) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_job << insert_type << insert_prod
           << insert_id << refName << refAliasName << refDescription
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
           << insert_Z2sub_im;

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

bool searchDialog::insert_motor(int jobID, int typeID, int prodID, int id, QString name, QString aliasName, QString description, int idRatedVol
                                , int idNoP, float nmp, float pow, float eff, float load, int rpm, float isu, float rx)
{
    if (!pDB)
        return false;

    td::INT4 insert_job(jobID);
    td::INT4 insert_type(typeID);
    td::INT4 insert_prod(prodID);

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

    insert_catalog(typeID, prodID, id, name);
    insert_jobCatalog(jobID, typeID, id, name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO CatAsynchronousMotor(JobID, TypeID, ProducerID, ID, Name, AliasName, Description, idNumberOfPhases, idRatedVoltage, nomMechPow, powerFactor, efficiency, loadFactor, rpm, Isu_In, r_x) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_job << insert_type << insert_prod
           << insert_id << refName << refAliasName << refDescription
           << insert_idRatedVol
           << insert_idNoP
           << insert_nmp
           << insert_pow
           << insert_eff
           << insert_load
           << insert_rpm
           << insert_isu
           << insert_rx;

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

bool searchDialog::insert_motorPla(int systemId, int jobID, int typeID, int prodID, int id, QString name
                                   , QString alias, QString desc, int idPhase, int idCatalog, int idConnection)
{
    if (!pDB)
        return false;

    td::INT4 insert_systemId(systemId);
    td::INT4 insert_job(jobID);
    td::INT4 insert_type(typeID);
    td::INT4 insert_prod(prodID);

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

    insert_placement(systemId, typeID, prodID, id, name);
    insert_jobPlacement(systemId, jobID, typeID, id, name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO PlacAsynchronousMotor(SystemID, JobID, TypeID, ProducerID, ID, Name, AliasName, Description, idPhaseCode, idCatalogType, idConnectionType) VALUES (?,?,?,?,?,?,?,?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_systemId << insert_job << insert_type << insert_prod
           << insert_id << refName << refAliasName << refDescription
           << insert_idPhase << insert_idCatalog << insert_idConnection;


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

bool searchDialog::insert_unitPlacement(int systemID, int jobID, int typeID, int prodID, int id, QString name, QString aliasName, QString description
                                        , int phaseCode, int catalogType, int nodeType, int loadType, int loadDemand
                                        , float des, int grounded, float r, float x)
{
    if (!pDB)
        return false;

    td::INT4 insert_systemID(systemID);
    td::INT4 insert_job(jobID);
    td::INT4 insert_type(typeID);
    td::INT4 insert_prod(prodID);

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

    float insert_des = des;
    td::INT4 insert_phaseCode = phaseCode;
    td::INT4 insert_catalogType = catalogType;
    td::INT4 insert_nodeType = nodeType;
    td::INT4 insert_loadType = loadType;
    td::INT4 insert_loadDemand = loadDemand;
    td::INT4 insert_grounded = grounded;
    float insert_r = r;
    float insert_x = x;

    insert_placement(systemID, typeID, prodID, id, name);
    insert_jobPlacement(systemID, jobID, typeID, id, name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO PlacGeneratingUnit(SystemID, JobID, TypeID, ProducerID, ID, Name, AliasName, Description, idPhaseCode, idCatalogType, idNodeType, idLoadType, idLoadDemandModel, desiredVoltage, grounded, rGround, xGround) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_systemID << insert_job << insert_type << insert_prod
           << insert_id << refName << refAliasName << refDescription
           << insert_phaseCode
           << insert_catalogType
           << insert_nodeType
           << insert_loadType
           << insert_loadDemand
           << insert_des
           << insert_grounded
           << insert_r
           << insert_x;

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

bool searchDialog::insert_shuntResistor(int systemID, int jobID, int typeID, int prodID, int id, QString name, QString aliasName
                                        , QString description, int idCatType)
{
    if (!pDB)
        return false;

    td::INT4 insert_systemID(systemID);
    td::INT4 insert_job(jobID);
    td::INT4 insert_type(typeID);
    td::INT4 insert_prod(prodID);

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

    insert_placement(systemID, typeID, prodID, id, name);
    insert_jobPlacement(systemID, jobID, typeID, id, name);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO PlacResistor(SystemID, JobID, TypeID, ProducerID, ID, Name, AliasName, Description, idCatalogType) VALUES (?,?,?,?,?,?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_systemID << insert_job << insert_type << insert_prod
           << insert_id
           << refName
           << refAliasName
           << refDescription
           << insert_idCatType;

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

bool searchDialog::insert_catalog(int typeID, int prodID, int id, QString name)
{
    if (!pDB)
        return false;

    td::INT4 insert_type(typeID);
    td::INT4 insert_prod(prodID);
    td::INT4 insert_id(id);
    db::Ref<td::String> refName(64);
    td::String td_name = name.toUtf8();
    refName = td_name;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO CatNaming(TypeID, ProducerID, ID, Name) VALUES (?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_type << insert_prod << insert_id << refName;

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
        std::cout << "Data inserted into CatNaming" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchDialog::insert_placement(int systemID, int typeID, int prodID, int id, QString name)
{
    if (!pDB)
        return false;

    td::INT4 insert_systemID(systemID);
    td::INT4 insert_type(typeID);
    td::INT4 insert_prod(prodID);
    td::INT4 insert_id(id);
    db::Ref<td::String> refName(64);
    td::String td_name = name.toUtf8();
    refName = td_name;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO PlacementNaming(SystemID, TypeID, ProducerID, ID, Name) VALUES (?,?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_systemID << insert_type << insert_prod << insert_id << refName;

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
        std::cout << "Data inserted into PlaNaming" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchDialog::insert_jobCatalog(int jobID, int typeID, int catID, QString catName)
{
    if (!pDB)
        return false;

    td::INT4 insert_jobID(jobID);
    td::INT4 insert_type(typeID);
    td::INT4 insert_catID(catID);
    db::Ref<td::String> refName(64);
    td::String td_name = catName.toUtf8();
    refName = td_name;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO JobCatalogs(JobID, TypeID, CatID, CatName) VALUES (?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind parameters
    params << insert_jobID << insert_type << insert_catID << refName;

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
        std::cout << "Data inserted into JobCatalogs" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

bool searchDialog::insert_jobPlacement(int systemID, int jobID, int typeID, int catID, QString catName)
{
    if (!pDB)
        return false;

    td::INT4 insert_systemID(systemID);
    td::INT4 insert_jobID(jobID);
    td::INT4 insert_type(typeID);
    td::INT4 insert_catID(catID);
    db::Ref<td::String> refName(64);
    td::String td_name = catName.toUtf8();
    refName = td_name;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT, "INSERT INTO JobPlacements(SystemID, JobID, TypeID, CatID, CatName) VALUES (?,?,?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_systemID << insert_jobID << insert_type << insert_catID << refName;

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
        std::cout << "Data inserted into JobPlacements" << std::endl;

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}

//-----------------------------------------------UPDATE STATEMENTS-------------------------------------
bool searchDialog::updateConsumer(QString name, QString aliasName, QString description, int ratedVol
                                  , float kp0, float kq0, float kp1, float kq1, float kp2, float kq2)
{

    if (!pDB)
        return false;

    int id = val.toInt();
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
    update_jobCatalog(0, name);

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

bool searchDialog::updateUnit(QString name, QString aliasName, QString description, int ratedVol, int ratedPow
                              , int idNoP, int idConType, float minOpAcPow, float maxOpAcPow, float minOpRPow, float maxOpRPow
                              , float Z0_re, float Z0_im, float Z1_re, float Z1_im, float Z2_re , float Z2_im
                              , float Z0trans_re, float Z0trans_im, float Z1trans_re, float Z1trans_im
                              , float Z2trans_re, float Z2trans_im, float Z0sub_re, float Z0sub_im
                              , float Z1sub_re, float Z1sub_im, float Z2sub_re, float Z2sub_im)
{
    if (!pDB)
        return false;

    int id = val.toInt();

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
    update_jobCatalog(0, name);

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

bool searchDialog::updateMotor(QString name, QString aliasName, QString description, int idRatedVol
                               , int idNoP, float nmp, float pow, float eff, float load, int rpm, float isu, float rx)
{
    if (!pDB)
        return false;

    int id = val.toInt();

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
    update_jobCatalog(0, name);

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

bool searchDialog::updateMotorPla(int systemId, QString name, QString alias, QString desc, int idPhase, int idCatalog, int idConnection)
{
    if (!pDB)
        return false;

    int id = val.toInt();
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

bool searchDialog::updateUnitPlacement(int systemID, QString name, QString aliasName, QString description
                                       , int phaseCode, int catalogType, int nodeType, int loadType, int loadDemand
                                       , float des, int grounded, float r, float x)
{
    if (!pDB)
        return false;

    int id = val.toInt();

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

bool searchDialog::updateShuntResistor(int systemID, QString name, QString aliasName
                                       , QString description, int idCatType)
{
    if (!pDB)
        return false;

    int id = val.toInt();
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

bool searchDialog::update_catalog(QString name)
{
    if (!pDB)
        return false;

    int id = val.toInt();
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

bool searchDialog::update_placement(int systemID, QString name)
{
    if (!pDB)
        return false;

    int id = val.toInt();
    td::INT4 insert_system(systemID);
    td::INT4 insert_id(id);

    db::Ref<td::String> refoldName(64);
    td::String td_oldname = oldname2.toUtf8();
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

bool searchDialog::update_jobCatalog(int jobId, QString catName)
{
    if (!pDB)
        return false;

    int jobId2 = jobId;
    int id = val.toInt();

    td::INT4 insert_job(jobId2);
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
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE JobCatalogs SET JobID=?, CatName=? WHERE CatID=? AND CatName=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_job << refName << insert_id << refoldName;

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

bool searchDialog::update_jobCatalogJobID(int oldJobID, int newJobID)
{
    if (!pDB)
        return false;

    int oldJobId = oldJobID;
    td::INT4 insert_oldJobID(oldJobId);
    int newJobId = newJobID;
    td::INT4 insert_newJobID(newJobId);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE JobCatalogs SET JobID=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newJobID << insert_oldJobID;

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

bool searchDialog::update_jobPlacement(int systemID, QString catName)
{
    if (!pDB)
        return false;

    int id = val.toInt();
    td::INT4 insert_id(id);
    td::INT4 insert_system(systemID);

    db::Ref<td::String> refoldName(64);
    td::String td_oldname = oldname2.toUtf8();
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

bool searchDialog::update_consJobIdEditFlag(int oldJobID, int newJobID)
{
    if (!pDB)
        return false;

    int oldJobId = oldJobID;
    td::INT4 insert_oldJobID(oldJobId);
    int newJobId = newJobID;
    td::INT4 insert_newJobID(newJobId);
    td::INT4 insert_editFlag(0);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatEnergyConsumer SET JobID=?, EditFlag=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newJobID << insert_editFlag << insert_oldJobID;

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

bool searchDialog::updateConsEditFlag(int jobID, int EditFlag)
{
    if (!pDB)
        return false;

    int oldJobId = jobID;
    td::INT4 insert_oldJobID(oldJobId);
    int editFlag = EditFlag;
    td::INT4 insert_editFlag(editFlag);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatEnergyConsumer SET EditFlag=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_editFlag << insert_oldJobID;

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

bool searchDialog::updateConsEditFlagAfterAct(int oldEditFlag, int newEditFlag)
{
    if (!pDB)
        return false;

    int oldEditFlag2 = oldEditFlag;
    td::INT4 insert_oldEditFlag(oldEditFlag2);

    int newEditFlag2 = newEditFlag;
    td::INT4 insert_newEditFlag(newEditFlag2);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatEnergyConsumer SET EditFlag=? WHERE EditFlag=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newEditFlag << insert_oldEditFlag;

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

bool searchDialog::update_unitJobIdEditFlag(int oldJobID, int newJobID)
{
    if (!pDB)
        return false;

    int oldJobId = oldJobID;
    td::INT4 insert_oldJobID(oldJobId);
    int newJobId = newJobID;
    td::INT4 insert_newJobID(newJobId);
    td::INT4 insert_editFlag(0);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatGeneratingUnit SET JobID=?, EditFlag=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newJobID << insert_editFlag << insert_oldJobID;

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

bool searchDialog::updateUnitEditFlag(int jobID, int EditFlag)
{
    if (!pDB)
        return false;

    int oldJobId = jobID;
    td::INT4 insert_oldJobID(oldJobId);
    int editFlag = EditFlag;
    td::INT4 insert_editFlag(editFlag);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatGeneratingUnit SET EditFlag=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_editFlag << insert_oldJobID;

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

bool searchDialog::updateUnitEditFlagAfterAct(int oldEditFlag, int newEditFlag)
{
    if (!pDB)
        return false;

    int oldEditFlag2 = oldEditFlag;
    td::INT4 insert_oldEditFlag(oldEditFlag2);

    int newEditFlag2 = newEditFlag;
    td::INT4 insert_newEditFlag(newEditFlag2);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatGeneratingUnit SET EditFlag=? WHERE EditFlag=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newEditFlag << insert_oldEditFlag;

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

bool searchDialog::update_motorJobIdEditFlag(int oldJobID, int newJobID)
{
    if (!pDB)
        return false;

    int oldJobId = oldJobID;
    td::INT4 insert_oldJobID(oldJobId);
    int newJobId = newJobID;
    td::INT4 insert_newJobID(newJobId);
    td::INT4 insert_editFlag(0);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatAsynchronousMotor SET JobID=?, EditFlag=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newJobID << insert_editFlag << insert_oldJobID;

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

bool searchDialog::updateMotorEditFlag(int jobID, int EditFlag)
{
    if (!pDB)
        return false;

    int oldJobId = jobID;
    td::INT4 insert_oldJobID(oldJobId);
    int editFlag = EditFlag;
    td::INT4 insert_editFlag(editFlag);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatAsynchronousMotor SET EditFlag=? WHERE JobID=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_editFlag << insert_oldJobID;

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

bool searchDialog::updateMotorEditFlagAfterAct(int oldEditFlag, int newEditFlag)
{
    if (!pDB)
        return false;

    int oldEditFlag2 = oldEditFlag;
    td::INT4 insert_oldEditFlag(oldEditFlag2);

    int newEditFlag2 = newEditFlag;
    td::INT4 insert_newEditFlag(newEditFlag2);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatAsynchronousMotor SET EditFlag=? WHERE EditFlag=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newEditFlag << insert_oldEditFlag;

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

//-------------------------------------------SET FUCTIONS------------------------------------------
bool searchDialog::setConsValues()
{
    if (!pDB)
        return false;

    int id = val.toInt();
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

bool searchDialog::setUnitValues()
{
    if (!pDB)
        return false;

    int id = val.toInt();
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

bool searchDialog::setMotorValues()
{
    if (!pDB)
        return false;

    int id = val.toInt();
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

bool searchDialog::setMotorPlaValues()
{
    if (!pDB)
        return false;

    int id = val2.toInt();
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

bool searchDialog::setUnitPlaValues()
{
    if (!pDB)
        return false;

    int id = val2.toInt();
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

bool searchDialog::setResPlaValues()
{
    if (!pDB)
        return false;

    int id = val2.toInt();
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

void searchDialog::setModel(int i, MyModel *n)
{
    proxComInd = i;

    if(i == 0)
    {
        proxy->setSourceModel(n);
        proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxy->setFilterKeyColumn(2);

        ui->tableView->setModel(proxy);
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
    }

    else
    {
        proxy->setSourceModel(n);
        proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxy->setFilterKeyColumn(3);

        ui->tableView->setModel(proxy);
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
    }
}

void searchDialog::on_newPushButton_clicked()
{

    if(chs == 1)
    {
        catConsClicked(refJob2);
    }

    else if(chs==2)
    {
        catUnitClicked(refJob2);
    }

    else if(chs == 3)
    {
        catMotorClicked(refJob2);
    }

    else if(chs == 4)
    {
        plaMotorClicked(refJob2);
    }

    else if(chs == 5)
    {
        plaUnitClicked(refJob2);
    }

    else if(chs == 6)
    {
        plaResistorClicked(refJob2);
    }
}

void searchDialog::catConsClicked(int jobID)
{
    bool exst = false;

    catConsumer catCons(this);
    if(preJob == 0)
        preJob = jobID;
        catCons.setJobID(preJob);
        catCons.setProducer(select_producers(), 0, 1);
        catCons.setID(0);
        catCons.setName("Energy Consumer Catalog", 1);
        catCons.setAliasName("eCons", 1);
        catCons.setRatedVoltage(select_ratedVoltage(), 0, 1);
        catCons.setKP0(0, 1);
        catCons.setKQ0(0, 1);
        catCons.setKP1(0, 1);
        catCons.setKQ1(0, 1);
        catCons.setKP2(0, 1);
        catCons.setKQ2(0, 1);
        catCons.setDescription("This is an Energy Consumer Catalog", 1);

    if (catCons.exec() == QDialog::Accepted)
    {

        for(int i=0; i < ui->tableView->model()->rowCount(); i++)
        {
            QModelIndex ind = ui->tableView->model()->index(i,1);
            ui->tableView->selectionModel()->select(ind, QItemSelectionModel::Select);
            int val2 = ui->tableView->model()->data(ind).toInt();

            if(catCons.id() == val2)
            {
                exst = true;
            }
        }

        if(exst == false)
        {
            //int randJ = updateRandomNumber().toInt();
            insert_consumer(preJob
                            , catCons.typeID()
                            , select_prodID(catCons.prodName())
                            , catCons.id()
                            , catCons.name()
                            , catCons.aliasName()
                            , catCons.description()
                            , catCons.idRatedVol()
                            , catCons.kP0()
                            , catCons.kQ0()
                            , catCons.kP1()
                            , catCons.kQ1()
                            , catCons.kP2()
                            , catCons.kQ2());

            //searchJobs nj(this);
            //nj.insert_job(randJ, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), 0);
            //nj.update_job(preJob, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), randJ);
            //preJob = randJ;

            select_searchConsumer();
        }

        if(exst == true)
        {
            messageBox exist(1, this);
            exist.show();
            exist.exec();
        }
        else
        {
            if(checkBox == false)
            {
                messageBox exist(2,this);
                exist.show();
                if(exist.exec() == QDialog::Accepted)
                {
                    if(exist.checkBox == true)
                    checkBox = true;
                }
            }
        }

    }

    /*else
    {
        if(exst == false)
        {
            insert_consumer(jobID
                            , catCons.typeID()
                            , 1
                            , catCons.id()
                            , catCons.name()
                            , catCons.aliasName()
                            , catCons.description()
                            , catCons.idRatedVol()
                            , catCons.kP0()
                            , catCons.kQ0()
                            , catCons.kP1()
                            , catCons.kQ1()
                            , catCons.kP2()
                            , catCons.kQ2());
            select_searchConsumer();
        }
    }*/

    int lastItem = ui->tableView->model()->rowCount();
    if(lastItem >= 1)
    {
        ui->tableView->clicked(ui->tableView->model()->index(lastItem - 1, 0));
    }

}

void searchDialog::catUnitClicked(int jobID)
{
    bool exst = false;

    catUnit unitCatalog(this);
    if(preJob == 0)
        preJob = jobID;
    unitCatalog.setJobID(jobID);
    unitCatalog.setProducer(select_producers(), 0, 1);
    unitCatalog.setID(0);
    unitCatalog.setName("Generating Unit Catalog", 1);
    unitCatalog.setAliasName("gUnitCat", 1);
    unitCatalog.setRatedVoltage(select_ratedVoltage(), 0, 1);
    unitCatalog.setRatedPower(select_ratedPower(), 0, 1);
    unitCatalog.setNumberOfPhases(select_numberOfPhases(), 0, 1);
    unitCatalog.setConnectionType(select_connectionType(), 0, 1);
    unitCatalog.setminOpAcPow(0, 1);
    unitCatalog.setmaxOpAcPow(0, 1);
    unitCatalog.setminOpRPow(0, 1);
    unitCatalog.setmaxOpRPow(0, 1);
    unitCatalog.setZ0_re(0, 1);
    unitCatalog.setZ0_im(0, 1);
    unitCatalog.setZ1_re(0, 1);
    unitCatalog.setZ1_im(0, 1);
    unitCatalog.setZ2_re(0, 1);
    unitCatalog.setZ2_im(0, 1);
    unitCatalog.setZ0trans_re(0, 1);
    unitCatalog.setZ0trans_im(0, 1);
    unitCatalog.setZ1trans_re(0, 1);
    unitCatalog.setZ1trans_im(0, 1);
    unitCatalog.setZ2trans_re(0, 1);
    unitCatalog.setZ2trans_im(0, 1);
    unitCatalog.setZ0sub_re(0, 1);
    unitCatalog.setZ0sub_im(0, 1);
    unitCatalog.setZ1sub_re(0, 1);
    unitCatalog.setZ1sub_im(0, 1);
    unitCatalog.setZ2sub_re(0, 1);
    unitCatalog.setZ2sub_im(0, 1);
    unitCatalog.setDescription("This is a Generating Unit Catalog", 1);

    if (unitCatalog.exec() == QDialog::Accepted)
    {

        for(int i=0; i < ui->tableView->model()->rowCount(); i++)
        {

            QModelIndex ind = ui->tableView->model()->index(i,1);
            ui->tableView->selectionModel()->select(ind, QItemSelectionModel::Select);
            int val2 = ui->tableView->model()->data(ind).toInt();

            if(unitCatalog.id() == val2)
            {
                exst = true;
            }
        }

        if(exst == false)
        {
           // int randJ = updateRandomNumber().toInt();
            insert_unit(preJob
                        , unitCatalog.typeID()
                        , select_prodID(unitCatalog.prodName())
                        , unitCatalog.id()
                        , unitCatalog.name()
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

            //searchJobs nj(this);
           // nj.insert_job(randJ, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), 0);
            select_searchUnit();
        }

        if(exst == true)
        {
            messageBox exist(1, this);
            exist.show();
            exist.exec();
        }
        else
        {
            if(checkBox == false)
            {
                messageBox exist(2,this);
                exist.show();
                if(exist.exec() == QDialog::Accepted)
                {
                    if(exist.checkBox == true)
                    checkBox = true;
                }
            }
        }
    }

   /* else
    {
        if(exst == false)
        {
            insert_unit(jobID
                        , unitCatalog.typeID()
                        , 1
                        , unitCatalog.id()
                        , unitCatalog.name()
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
        }
    }*/

    int lastItem = ui->tableView->model()->rowCount();
    if(lastItem >= 1)
    {
        ui->tableView->clicked(ui->tableView->model()->index(lastItem - 1, 0));
    }
}

void searchDialog::catMotorClicked(int jobID)
{
    bool exst = false;

    catMotor motorCatalog(this);
    if(preJob == 0)
        preJob = jobID;
    motorCatalog.setJobID(preJob);
    motorCatalog.setProducer(select_producers(), 0, 1);
    motorCatalog.setID(0);
    motorCatalog.setName("Asynchronous Motor Catalog", 1);
    motorCatalog.setAliasName("aMotorCat", 1);
    motorCatalog.setNumberOfPhases(select_numberOfPhases(), 0, 1);
    motorCatalog.setRatedVoltage(select_ratedVoltage(), 0, 1);
    motorCatalog.setnmp(0, 1);
    motorCatalog.setpow(0, 1);
    motorCatalog.seteff(0, 1);
    motorCatalog.setload(0, 1);
    motorCatalog.setrpm(0, 1);
    motorCatalog.setisu(0, 1);
    motorCatalog.setrx(0, 1);
    motorCatalog.setDescription("This is an Asynchronous Motor Catalog", 1);

    if (motorCatalog.exec() == QDialog::Accepted)
    {
        for(int i=0; i < ui->tableView->model()->rowCount(); i++)
        {

            QModelIndex ind = ui->tableView->model()->index(i,1);
            ui->tableView->selectionModel()->select(ind, QItemSelectionModel::Select);
            int val2 = ui->tableView->model()->data(ind).toInt();

            if(motorCatalog.id() == val2)
            {
                exst = true;
            }
        }

        if(exst == false)
        {
            //int randJ = updateRandomNumber().toInt();
            insert_motor(preJob
                         , motorCatalog.typeID()
                         , select_prodID(motorCatalog.prodName())
                         , motorCatalog.id()
                         , motorCatalog.name()
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
           // searchJobs nj(this);
            //nj.insert_job(randJ, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), 0);
            select_searchMotor();

        }

        if(exst == true)
        {
            messageBox exist(1, this);
            exist.show();
            exist.exec();
        }
        else
        {
            if(checkBox == false)
            {
                messageBox exist(2,this);
                exist.show();
                if(exist.exec() == QDialog::Accepted)
                {
                    if(exist.checkBox == true)
                    checkBox = true;
                }
            }
        }

    }
   /* else
    {
        if(exst == false)
        {
            insert_motor(jobID
                         , motorCatalog.typeID()
                         , 1
                         , motorCatalog.id()
                         , motorCatalog.name()
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
            select_searchConsumer();
        }
    }*/

    int lastItem = ui->tableView->model()->rowCount();
    if(lastItem >= 1)
    {
        ui->tableView->clicked(ui->tableView->model()->index(lastItem - 1, 0));
    }
}

void searchDialog::plaMotorClicked(int jobID)
{
    bool exst = false;

    plaMotor motorPlac(this);
    motorPlac.setSystemID(select_system(), 0);
    motorPlac.setJobID(jobID);
    motorPlac.setProducer(select_producers(), 0);
    motorPlac.setID(0);
    motorPlac.setName("Asynchronous Motor Placement");
    motorPlac.setAliasName("aMotorPla");
    motorPlac.setDescription("This is an Asynchronous Motor Placement");
    motorPlac.setPhaseCode(select_phaseCode(), 0);
    motorPlac.setCatalogType(select_catalogType_Motor(), 0);
    motorPlac.setConnectionType(select_connectionType(), 0);

    if (motorPlac.exec() == QDialog::Accepted)
    {
        for(int i=0; i < ui->tableView->model()->rowCount(); i++)
        {

            QModelIndex ind = ui->tableView->model()->index(i,2);
            ui->tableView->selectionModel()->select(ind, QItemSelectionModel::Select);
            int val2 = ui->tableView->model()->data(ind).toInt();

            if(motorPlac.id() == val2)
            {
                exst = true;
            }
        }

        if(exst == false)
        {
            int randJ = updateRandomNumber().toInt();
            insert_motorPla(select_systemID(motorPlac.systemName())
                            , randJ
                            , motorPlac.typeID()
                            , select_prodID(motorPlac.prodName())
                            , motorPlac.id()
                            , motorPlac.name()
                            , motorPlac.aliasName()
                            , motorPlac.description()
                            , motorPlac.idPhaseCode()
                            , motorPlac.idCatalogType()
                            , motorPlac.idConnectionType());
            searchJobs nj(this);
            nj.insert_job(randJ, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), 0);
            select_searchMotorPla();
        }

        if(exst == true)
        {
            messageBox exist(1, this);
            exist.show();
            exist.exec();
        }
        else
        {
            if(checkBox == false)
            {
                messageBox exist(2,this);
                exist.show();
                if(exist.exec() == QDialog::Accepted)
                {
                    if(exist.checkBox == true)
                    checkBox = true;
                }
            }
        }
    }

    else
    {
        if(exst == false)
        {
            insert_motorPla(select_systemID(motorPlac.systemName())
                            , updateRandomNumber().toInt()
                            , motorPlac.typeID()
                            , 1
                            , motorPlac.id()
                            , motorPlac.name()
                            , motorPlac.aliasName()
                            , motorPlac.description()
                            , motorPlac.idPhaseCode()
                            , motorPlac.idCatalogType()
                            , motorPlac.idConnectionType());
        }
    }


    int lastItem = ui->tableView->model()->rowCount();
    if(lastItem >= 1)
    {
        ui->tableView->clicked(ui->tableView->model()->index(lastItem - 1, 0));
    }
}

void searchDialog::plaUnitClicked(int jobID)
{
    bool exst = false;

    plaUnit unitPlacement(this);
    unitPlacement.setSystemID(select_system(), 0);
    unitPlacement.setJobID(jobID);
    unitPlacement.setProducer(select_producers(), 0);
    unitPlacement.setID(0);
    unitPlacement.setName("Generating Unit Placement");
    unitPlacement.setAliasName("gUnitPla");
    unitPlacement.setDescription("This is a Generating Unit Placement");
    unitPlacement.setPhaseCode(select_phaseCode(), 0);
    unitPlacement.setCatalogType(select_catalogType_Unit(), 0);
    unitPlacement.setNodeType(select_nodeType(), 0);
    unitPlacement.setLoadType(select_loadType(), 0);
    unitPlacement.setLoadDemand(select_loadDemand(), 0);
    unitPlacement.setdes(0);
    unitPlacement.setr(0);
    unitPlacement.setx(0);

    if (unitPlacement.exec() == QDialog::Accepted)
    {
        for(int i=0; i < ui->tableView->model()->rowCount(); i++)
        {

            QModelIndex ind = ui->tableView->model()->index(i,2);
            ui->tableView->selectionModel()->select(ind, QItemSelectionModel::Select);
            int val2 = ui->tableView->model()->data(ind).toInt();

            if(unitPlacement.id() == val2)
            {
                exst = true;
            }
        }

        if(exst == false)
        {
            int randJ = updateRandomNumber().toInt();
            insert_unitPlacement(select_systemID(unitPlacement.systemName())
                                 , randJ
                                 , unitPlacement.typeID()
                                 , select_prodID(unitPlacement.prodName())
                                 , unitPlacement.id()
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
            searchJobs nj(this);
            nj.insert_job(randJ, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), 0);
            select_searchUnitPla();
        }

        if(exst == true)
        {
            messageBox exist(1, this);
            exist.show();
            exist.exec();
        }
        else
        {
            if(checkBox == false)
            {
                messageBox exist(2,this);
                exist.show();
                if(exist.exec() == QDialog::Accepted)
                {
                    if(exist.checkBox == true)
                    checkBox = true;
                }
            }
        }
    }

    else
    {
        if(exst == false)
        {
            insert_unitPlacement(select_systemID(unitPlacement.systemName())
                                 , updateRandomNumber().toInt()
                                 , unitPlacement.typeID()
                                 , 1
                                 , unitPlacement.id()
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
        }
    }

}

void searchDialog::plaResistorClicked(int jobID)
{
    bool exst = false;

    plaResistor shuntResistor(this);
    shuntResistor.setJobID(jobID);
    shuntResistor.setProducer(select_producers(), 0);
    shuntResistor.setSystemID(select_system(), 0);
    shuntResistor.setID(0);
    shuntResistor.setName("Resistor Placement");
    shuntResistor.setAliasName("resPla");
    shuntResistor.setDescription("This is a Resistor Placement");
    shuntResistor.setCatalogType(select_catalogType_Shunt(), 0);

    if ( shuntResistor.exec() == QDialog::Accepted)
    {
        for(int i=0; i < ui->tableView->model()->rowCount(); i++)
        {

            QModelIndex ind = ui->tableView->model()->index(i,2);
            ui->tableView->selectionModel()->select(ind, QItemSelectionModel::Select);
            int val2 = ui->tableView->model()->data(ind).toInt();

            if(shuntResistor.ID() == val2)
            {
                exst = true;
            }
        }

        if(exst == false)
        {
            int randJ = updateRandomNumber().toInt();
            insert_shuntResistor( select_systemID(shuntResistor.systemName())
                                  , randJ
                                  , shuntResistor.typeID()
                                  , select_prodID(shuntResistor.prodName())
                                  , shuntResistor.ID()
                                  , shuntResistor.name()
                                  , shuntResistor.aliasName()
                                  , shuntResistor.description()
                                  , shuntResistor.idCatalogType());
            searchJobs nj(this);
            nj.insert_job(randJ, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), 0);
            select_searchShuntRes();
        }

        if(exst == true)
        {
            messageBox exist(1, this);
            exist.show();
            exist.exec();
        }
        else
        {
            if(checkBox == false)
            {
                messageBox exist(2,this);
                exist.show();
                if(exist.exec() == QDialog::Accepted)
                {
                    if(exist.checkBox == true)
                    checkBox = true;
                }
            }
        }
    }

    else
    {
        if(exst == false)
        {
            insert_shuntResistor( select_systemID(shuntResistor.systemName())
                                  , updateRandomNumber().toInt()
                                  , shuntResistor.typeID()
                                  , 1
                                  , shuntResistor.ID()
                                  , shuntResistor.name()
                                  , shuntResistor.aliasName()
                                  , shuntResistor.description()
                                  , shuntResistor.idCatalogType());
        }
    }
}

void searchDialog::on_editPushButton_clicked()
{

    if(chs == 1)
    {
        catConsEdtClicked();
    }

    else if(chs==2)
    {
        catUnitEdtClicked();
    }

    else if(chs == 3)
    {
        catMotorEdtClicked();
    }

    else if(chs == 4)
    {
        plaMotorEdtClicked();
    }

    else if(chs == 5)
    {
        plaUnitEdtClicked();
    }

    else if(chs == 6)
    {
        plaResistorEdtClicked();
    }
}

void searchDialog::catConsEdtClicked()
{
    setConsValues();
    catConsumer catCons(this);
    int oldJobID = jobVal.toInt();//select_catJobID(val.toInt());

    if(jobVal.toInt() >=1 && jobVal.toInt() == refJob2)
    {
        catCons.setJobID(refJob2);
        catCons.setProducer(select_producers(), prodVal.toInt(), 0);
        catCons.setDisabledID(val);
        catCons.setName(nameVal, 0);
        catCons.setAliasName(aliasVal, 0);
        catCons.setRatedVoltage(select_ratedVoltage(), rVoltVal.toInt(), 0);
        catCons.setKP0(kp0Val.toFloat(), 0);
        catCons.setKQ0(kq0Val.toFloat(), 0);
        catCons.setKP1(kp1Val.toFloat(), 0);
        catCons.setKQ1(kq1Val.toFloat(), 0);
        catCons.setKP2(kp2Val.toFloat(), 0);
        catCons.setKQ2(kq2Val.toFloat(), 0);
        catCons.setDescription(descVal, 0);

        if (catCons.exec() == QDialog::Accepted)
        {

        }
    }

    else if(jobVal.toInt() >=1 && jobVal.toInt() != refJob2)
    {
        catCons.setJobID(refJob2);
        catCons.setProducer(select_producers(), prodVal.toInt(), 1);
        catCons.setDisabledID(val);
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
            //int randJ = updateRandomNumber().toInt();
            insert_consumer(refJob2
                            , catCons.typeID()
                            , select_prodID(catCons.prodName())
                            , val.toInt()
                            , catCons.name()
                            , catCons.aliasName()
                            , catCons.description()
                            , catCons.idRatedVol()
                            , catCons.kP0()
                            , catCons.kQ0()
                            , catCons.kP1()
                            , catCons.kQ1()
                            , catCons.kP2()
                            , catCons.kQ2());

            updateConsEditFlag(oldJobID, refJob2);

            searchJobs nj(this);
            nj.insert_job(refJob2, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), 0);
            //nj.update_job(oldJobID, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), randJ);
            select_searchConsumer();
            oldJobID = jobVal.toInt();
        }
    }

    else if(jobVal.toInt() <=0 && jobVal.toInt() == refJob2)
    {
        catCons.setJobID(refJob2);
        catCons.setProducer(select_producers(), prodVal.toInt(), 1);
        catCons.setDisabledID(val);
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
            updateConsumer(catCons.name()
                        , catCons.aliasName()
                        , catCons.description()
                        , catCons.idRatedVol()
                        , catCons.kP0()
                        , catCons.kQ0()
                        , catCons.kP1()
                        , catCons.kQ1()
                        , catCons.kP2()
                        , catCons.kQ2());
            select_searchConsumer();
        }
    }

    else if(jobVal.toInt() <= 0 && jobVal.toInt() != refJob2)
    {
        catCons.setJobID(oldJobID);
        catCons.setProducer(select_producers(), prodVal.toInt(), 0);
        catCons.setDisabledID(val);
        catCons.setName(nameVal, 0);
        catCons.setAliasName(aliasVal, 0);
        catCons.setRatedVoltage(select_ratedVoltage(), rVoltVal.toInt(), 0);
        catCons.setKP0(kp0Val.toFloat(), 0);
        catCons.setKQ0(kq0Val.toFloat(), 0);
        catCons.setKP1(kp1Val.toFloat(), 0);
        catCons.setKQ1(kq1Val.toFloat(), 0);
        catCons.setKP2(kp2Val.toFloat(), 0);
        catCons.setKQ2(kq2Val.toFloat(), 0);
        catCons.setDescription(descVal, 0);

        if (catCons.exec() == QDialog::Accepted)
        {

        }
    }

}

void searchDialog::catUnitEdtClicked()
{
    setUnitValues();
    catUnit unitCatalog(this);
    int oldJobID = jobVal.toInt();//select_catJobID(val.toInt());

    if(jobVal.toInt() >=1)
    {
    unitCatalog.setJobID(refJob2);
    unitCatalog.setProducer(select_producers(), prodVal.toInt(), 1);
    unitCatalog.setDisabledID(val);
    unitCatalog.setName(nameVal, 1);
    unitCatalog.setAliasName(aliasVal, 1);
    unitCatalog.setRatedVoltage(select_ratedVoltage(), rVoltVal.toInt(), 1);
    unitCatalog.setRatedPower(select_ratedPower(), rPowVal.toInt(), 1);
    unitCatalog.setNumberOfPhases(select_numberOfPhases(), nopVal.toInt(), 1);
    unitCatalog.setConnectionType(select_connectionType(), cTypeVal.toInt(), 1);
    unitCatalog.setminOpAcPow(minOpAcPowVal.toFloat(), 1);
    unitCatalog.setmaxOpAcPow(maxOpAcPowVal.toFloat(), 1);
    unitCatalog.setminOpRPow(minOpRPowVal.toFloat(), 1);
    unitCatalog.setmaxOpRPow(maxOpRPowVal.toFloat(), 1);
    unitCatalog.setZ0_re(Z0_reVal.toFloat(), 1);
    unitCatalog.setZ0_im(Z0_imVal.toFloat(), 1);
    unitCatalog.setZ1_re(Z1_reVal.toFloat(), 1);
    unitCatalog.setZ1_im(Z1_imVal.toFloat(), 1);
    unitCatalog.setZ2_re(Z2_reVal.toFloat(), 1);
    unitCatalog.setZ2_im(Z2_imVal.toFloat(), 1);
    unitCatalog.setZ0trans_re(Z0trans_reVal.toFloat(), 1);
    unitCatalog.setZ0trans_im(Z0trans_imVal.toFloat(), 1);
    unitCatalog.setZ1trans_re(Z1trans_reVal.toFloat(), 1);
    unitCatalog.setZ1trans_im(Z1trans_imVal.toFloat(), 1);
    unitCatalog.setZ2trans_re(Z2trans_reVal.toFloat(), 1);
    unitCatalog.setZ2trans_im(Z2trans_imVal.toFloat(), 1);
    unitCatalog.setZ0sub_re(Z0sub_reVal.toFloat(), 1);
    unitCatalog.setZ0sub_im(Z0sub_imVal.toFloat(), 1);
    unitCatalog.setZ1sub_re(Z1sub_reVal.toFloat(), 1);
    unitCatalog.setZ1sub_im(Z1sub_imVal.toFloat(), 1);
    unitCatalog.setZ2sub_re(Z2sub_reVal.toFloat(), 1);
    unitCatalog.setZ2sub_im(Z2sub_imVal.toFloat(), 1);
    unitCatalog.setDescription(descVal, 1);

    if (unitCatalog.exec() == QDialog::Accepted)
    {
        insert_unit(refJob2
                    , unitCatalog.typeID()
                    , select_prodID(unitCatalog.prodName())
                    , unitCatalog.id()
                    , unitCatalog.name()
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

        updateUnitEditFlag(oldJobID, refJob2);

        searchJobs nj(this);
        nj.insert_job(refJob2, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), 0);
        //nj.update_job(oldJobID, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), randJ);
        oldJobID = jobVal.toInt();
        select_searchUnit();
        }
    }
    else if(jobVal.toInt() >=1 || jobVal.toInt() == refJob2)
    {
        unitCatalog.setJobID(refJob2);
        unitCatalog.setProducer(select_producers(), prodVal.toInt(), 1);
        unitCatalog.setDisabledID(val);
        unitCatalog.setName(nameVal, 1);
        unitCatalog.setAliasName(aliasVal, 1);
        unitCatalog.setRatedVoltage(select_ratedVoltage(), rVoltVal.toInt(), 1);
        unitCatalog.setRatedPower(select_ratedPower(), rPowVal.toInt(), 1);
        unitCatalog.setNumberOfPhases(select_numberOfPhases(), nopVal.toInt(), 1);
        unitCatalog.setConnectionType(select_connectionType(), cTypeVal.toInt(), 1);
        unitCatalog.setminOpAcPow(minOpAcPowVal.toFloat(), 1);
        unitCatalog.setmaxOpAcPow(maxOpAcPowVal.toFloat(), 1);
        unitCatalog.setminOpRPow(minOpRPowVal.toFloat(), 1);
        unitCatalog.setmaxOpRPow(maxOpRPowVal.toFloat(), 1);
        unitCatalog.setZ0_re(Z0_reVal.toFloat(), 1);
        unitCatalog.setZ0_im(Z0_imVal.toFloat(), 1);
        unitCatalog.setZ1_re(Z1_reVal.toFloat(), 1);
        unitCatalog.setZ1_im(Z1_imVal.toFloat(), 1);
        unitCatalog.setZ2_re(Z2_reVal.toFloat(), 1);
        unitCatalog.setZ2_im(Z2_imVal.toFloat(), 1);
        unitCatalog.setZ0trans_re(Z0trans_reVal.toFloat(), 1);
        unitCatalog.setZ0trans_im(Z0trans_imVal.toFloat(), 1);
        unitCatalog.setZ1trans_re(Z1trans_reVal.toFloat(), 1);
        unitCatalog.setZ1trans_im(Z1trans_imVal.toFloat(), 1);
        unitCatalog.setZ2trans_re(Z2trans_reVal.toFloat(), 1);
        unitCatalog.setZ2trans_im(Z2trans_imVal.toFloat(), 1);
        unitCatalog.setZ0sub_re(Z0sub_reVal.toFloat(), 1);
        unitCatalog.setZ0sub_im(Z0sub_imVal.toFloat(), 1);
        unitCatalog.setZ1sub_re(Z1sub_reVal.toFloat(), 1);
        unitCatalog.setZ1sub_im(Z1sub_imVal.toFloat(), 1);
        unitCatalog.setZ2sub_re(Z2sub_reVal.toFloat(), 1);
        unitCatalog.setZ2sub_im(Z2sub_imVal.toFloat(), 1);
        unitCatalog.setDescription(descVal, 1);

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
            select_searchUnit();
        }
    }

    else if(jobVal.toInt() <= 0)
    {
        unitCatalog.setJobID(refJob2);
        unitCatalog.setProducer(select_producers(), prodVal.toInt(), 0);
        unitCatalog.setDisabledID(val);
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

        }
    }

}

void searchDialog::catMotorEdtClicked()
{
    setMotorValues();
    catMotor motorCatalog(this);
    int oldJobID = jobVal.toInt();//select_catJobID(val.toInt());

    if(jobVal.toInt() >=1)
    {
        motorCatalog.setJobID(refJob2);
        motorCatalog.setProducer(select_producers(), prodVal.toInt(), 1);
        motorCatalog.setDisabledID(val);
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
            insert_motor(refJob2
                         , motorCatalog.typeID()
                         , select_prodID(motorCatalog.prodName())
                         , motorCatalog.id()
                         , motorCatalog.name()
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

            updateMotorEditFlag(oldJobID, refJob2);

            searchJobs nj(this);
            nj.insert_job(refJob2, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), 0);
            //nj.update_job(oldJobID, "Ali", 2, 0, QDate::currentDate(), QDate::currentDate(), randJ);
            select_searchMotor();
            oldJobID = jobVal.toInt();
        }
    }
        else if(jobVal.toInt() >=1 || jobVal.toInt() == refJob2)
        {
            motorCatalog.setJobID(refJob2);
            motorCatalog.setProducer(select_producers(), prodVal.toInt(), 1);
            motorCatalog.setDisabledID(val);
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
                select_searchMotor();
            }
        }

        else if(jobVal.toInt() <= 0)
        {
            motorCatalog.setJobID(refJob2);
            motorCatalog.setProducer(select_producers(), prodVal.toInt(), 0);
            motorCatalog.setDisabledID(val);
            motorCatalog.setName(nameVal, 0);
            motorCatalog.setAliasName(aliasVal, 0);
            motorCatalog.setNumberOfPhases(select_numberOfPhases(), nopVal.toInt(), 0);
            motorCatalog.setRatedVoltage(select_ratedVoltage(), rVoltVal.toInt(), 0);
            motorCatalog.setnmp(nmpVal.toFloat(), 0);
            motorCatalog.setpow(powFVal.toFloat(), 0);
            motorCatalog.seteff(effVal.toFloat(), 0);
            motorCatalog.setload(loadFVal.toFloat(), 0);
            motorCatalog.setrpm(rmpVal.toFloat(), 0);
            motorCatalog.setisu(isuVal.toFloat(), 0);
            motorCatalog.setrx(rxVal.toFloat(), 0);
            motorCatalog.setDescription(descVal, 0);
            if (motorCatalog.exec() == QDialog::Accepted)
            {

            }
        }

}

void searchDialog::plaMotorEdtClicked()
{
    setMotorPlaValues();
    plaMotor motorPlac(this);
    motorPlac.setJobID(select_plaJobID(val2.toInt()));
    motorPlac.setSystemID(select_system(), systemVal.toInt());
    motorPlac.setProducer(select_producers(), prodVal.toInt());
    motorPlac.setDisabledID(val2);
    motorPlac.setName(nameVal);
    motorPlac.setAliasName(aliasVal);
    motorPlac.setDescription(descVal);
    motorPlac.setPhaseCode(select_phaseCode(), phaseCVal.toInt());
    motorPlac.setCatalogType(select_catalogType_Motor(), catTVal.toInt());
    motorPlac.setConnectionType(select_connectionType(), cTypeVal.toInt());

    if (motorPlac.exec() == QDialog::Accepted)
    {
        updateMotorPla(select_systemID(motorPlac.systemName())
                       , motorPlac.name()
                       , motorPlac.aliasName()
                       , motorPlac.description()
                       , motorPlac.idPhaseCode()
                       , motorPlac.idCatalogType()
                       , motorPlac.idConnectionType());
        select_searchMotorPla();
    }
}

void searchDialog::plaUnitEdtClicked()
{
    setUnitPlaValues();
    plaUnit unitPlacement(this);
    unitPlacement.setJobID(select_plaJobID(val2.toInt()));
    unitPlacement.setSystemID(select_system(), systemVal.toInt());
    unitPlacement.setProducer(select_producers(), prodVal.toInt());
    unitPlacement.setDisabledID(val2);
    unitPlacement.setName(nameVal);
    unitPlacement.setAliasName(aliasVal);
    unitPlacement.setDescription(descVal);
    unitPlacement.setPhaseCode(select_phaseCode(), phaseCVal.toInt());
    unitPlacement.setCatalogType(select_catalogType_Unit(), catTVal.toInt());
    unitPlacement.setNodeType(select_nodeType(), nodeTVal.toInt());
    unitPlacement.setLoadType(select_loadType(), loadTVal.toInt());
    unitPlacement.setLoadDemand(select_loadDemand(), loadDMVal.toInt());
    unitPlacement.setdes(dVoltVal.toFloat());
    unitPlacement.setr(rGroundVal.toFloat());
    unitPlacement.setx(xGroundVal.toFloat());

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
        select_searchUnitPla();

    }
}

void searchDialog::plaResistorEdtClicked()
{
    setResPlaValues();
    plaResistor shuntResistor(this);
    shuntResistor.setJobID(select_plaJobID(val2.toInt()));
    shuntResistor.setSystemID(select_system(),systemVal.toInt());
    shuntResistor.setProducer(select_producers(), prodVal.toInt());
    shuntResistor.setDisabledID(val2);
    shuntResistor.setName(nameVal);
    shuntResistor.setAliasName(aliasVal);
    shuntResistor.setDescription(descVal);
    shuntResistor.setCatalogType(select_catalogType_Shunt(), catTVal.toInt());

    if ( shuntResistor.exec() == QDialog::Accepted)
    {
        updateShuntResistor( select_systemID(shuntResistor.systemName())
                             , shuntResistor.name()
                             , shuntResistor.aliasName()
                             , shuntResistor.description()
                             , shuntResistor.idCatalogType());
        select_searchShuntRes();
    }
}

void searchDialog::on_cancelPushButton_clicked()
{
    this->close();
}

void searchDialog::on_tableView_clicked(const QModelIndex &index)
{
    int inxJobID = index.row();
    QModelIndex indJobID = ui->tableView->model()->index(inxJobID, 0);
    ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select);
    jobVal = ui->tableView->model()->data(indJobID).toString();

    int inxID = index.row();
    QModelIndex indID = ui->tableView->model()->index(inxID, 1);
    ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val = ui->tableView->model()->data(indID).toString();

    int inxSys = index.row();
    QModelIndex indSys = ui->tableView->model()->index(inxSys, 2);
    ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val2 = ui->tableView->model()->data(indSys).toString();

    QModelIndex ind3 = ui->tableView->model()->index(inxID,2);
    ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select);
    oldname = ui->tableView->model()->data(ind3).toString();

    QModelIndex ind4 = ui->tableView->model()->index(inxSys,3);
    ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select);
    oldname2 = ui->tableView->model()->data(ind4).toString();
}

void searchDialog::on_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
}

void searchDialog::on_comboBox_currentIndexChanged(int index)
{
    if(proxComInd == 0)
    {
        if (index == 0)
            proxy->setFilterKeyColumn(0);
        else if(index == 1)
            proxy->setFilterKeyColumn(1);
        else if (index == 2)
            proxy->setFilterKeyColumn(2);
        else if (index == 3)
            proxy->setFilterKeyColumn(3);
        else if (index == 4)
            proxy->setFilterKeyColumn(4);
    }
    else
    {
        if (index == 0)
            proxy->setFilterKeyColumn(1);
        else if(index == 1)
            proxy->setFilterKeyColumn(2);
        else if (index == 2)
            proxy->setFilterKeyColumn(3);
        else if (index == 3)
            proxy->setFilterKeyColumn(4);
        else if (index == 4)
            proxy->setFilterKeyColumn(5);
    }

}

void searchDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    index;

    if(chs == 1)
    {
        catConsEdtClicked();
    }

    else if(chs==2)
    {
        catUnitEdtClicked();
    }

    else if(chs == 3)
    {
        catMotorEdtClicked();
    }

    else if(chs == 4)
    {
        plaMotorEdtClicked();
    }

    else if(chs == 5)
    {
        plaUnitEdtClicked();
    }

    else if(chs == 6)
    {
        plaResistorEdtClicked();
    }
}

QString searchDialog::updateRandomNumber()
{
    int high = -1000;

    qsrand((unsigned)time(0));
    negJobID = QString::number(0 - (qrand() % high));

    return negJobID;
}

