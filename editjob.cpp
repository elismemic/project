#include "editjob.h"
#include "ui_editjob.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mainwindow.h"
#include "QFileDialog"
#include "QMessageBox
#include "newjob.h"
#include "mymodel.h"


extern db::ISQLDatabase *pDB;
extern int userID;

editJob::editJob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editJob)
{
    ui->setupUi(this);
    ui->catalogs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->catalogs->setSelectionMode(QTableView::SingleSelection);
    ui->placements->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->placements->setSelectionMode(QTableView::SingleSelection);
    populateModelCat();
    populateModelPla();
}
bool editJob::populateModelCat()
{
if (!pDB)
    return false;


mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT TypeID, ID, Name, ProducerID from CatNaming"));


cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(4);
        columns[0].name = "Type ID";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "ID";
        columns[1].tdType = td::int4;
        columns[1].len = 0;

        columns[2].name = "Name";
        columns[2].tdType = td::nch;
        columns[2].len = 128;

        columns[3].name = "Producer ID";
        columns[3].tdType = td::int4;
        columns[3].len = 0;

    db::Recordset* rs = new db::Recordset(columns);

   // QMessageBox::information(this,"...",QString::number(rs->rowCount()));
    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);


    ui->catalogs->setModel(model);
    ui->catalogs->resizeRowsToContents();
    ui->catalogs->horizontalHeader()->setStretchLastSection(true);

    return true;
}

bool editJob::populateModelPla()
{
if (!pDB)
    return false;

mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,
    "SELECT SystemID, TypeID, ID, Name, ProducerID from PlacementNaming"));


cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(5);

        columns[0].name = "System ID";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Type ID";
        columns[1].tdType = td::int4;
        columns[1].len = 0;

        columns[2].name = "ID";
        columns[2].tdType = td::int4;
        columns[2].len = 0;

        columns[3].name = "Name";
        columns[3].tdType = td::nch;
        columns[3].len = 128;

        columns[4].name = "Producer ID";
        columns[4].tdType = td::int4;
        columns[4].len = 0;

    db::Recordset* rs = new db::Recordset(columns);


    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);


    ui->placements->setModel(model);
    ui->placements->resizeRowsToContents();
    ui->placements->horizontalHeader()->setStretchLastSection(true);

    return true;

}
editJob::~editJob()
{
    delete ui;
}
