#include "addcatpla.h"
#include "ui_addcatpla.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"

extern db::ISQLDatabase *pDB;

addCatPla::addCatPla(int jobID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addCatPla)
{
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    proxy2 = new QSortFilterProxyModel(this);
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox_2->setCurrentIndex(1);
    refJobID = jobID;
    this->setWindowTitle("Add Catalog and Placement (Job ID: " + QString::number(refJobID) + ")");
    select_catalogs();
    select_placements();
    catInd = false;
    plaInd = false;
}

addCatPla::~addCatPla()
{
    delete ui;
}

bool addCatPla::select_catalogs()
{
    if (!pDB)
        return false;

    td::INT4 insert_jobID(0);

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

bool addCatPla::select_placements()
{
    if (!pDB)
        return false;

    td::INT4 insert_jobID(0);

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

bool addCatPla::updateConsJob()
{
    if (!pDB)
        return false;

    td::INT4 insert_id(catID);
    td::INT4 insert_newId(refJobID);

    updateJobCatalog();

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatEnergyConsumer SET JobID=? WHERE ID=?"));

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

bool addCatPla::updateUnitJob()
{
        if (!pDB)
            return false;

        td::INT4 insert_id(catID);
        td::INT4 insert_newId(refJobID);

        updateJobCatalog();

        //start transaction log
        db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
        db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatGeneratingUnit SET JobID=? WHERE ID=?"));

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

bool addCatPla::updateMotorJob()
{
    if (!pDB)
        return false;


    td::INT4 insert_id(catID);
    td::INT4 insert_newId(refJobID);

    updateJobCatalog();

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE CatAsynchronousMotor SET JobID=? WHERE ID=?"));

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

bool addCatPla::updateMotorPlaJob()
{
    if (!pDB)
        return false;

    td::INT4 insert_id(catID);
    td::INT4 insert_newId(refJobID);

    updateJobPlacement();

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacAsynchronousMotor SET JobID=? WHERE ID=?"));

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

bool addCatPla::updateUnitPlacJob()
{
    if (!pDB)
        return false;

    td::INT4 insert_id(catID);
    td::INT4 insert_newId(refJobID);

    updateJobPlacement();

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacGeneratingUnit SET JobID=? WHERE ID=?"));

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

bool addCatPla::updateShuntResJob()
{
    if (!pDB)
        return false;

    td::INT4 insert_id(catID);
    td::INT4 insert_newId(refJobID);

    updateJobPlacement();

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE PlacResistor SET JobID=? WHERE ID=?"));

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

bool addCatPla::updateJobCatalog()
{
    if (!pDB)
        return false;

    db::Ref<td::String> refName(64);
    td::String td_name = name.toUtf8();
    refName = td_name;

    td::INT4 insert_id(catID);
    td::INT4 insert_newId(refJobID);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE JobCatalogs SET JobID=? WHERE CatID=? AND CatName=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newId << insert_id << refName;


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

bool addCatPla::updateJobPlacement()
{
    if (!pDB)
        return false;

    db::Ref<td::String> refName(64);
    td::String td_name = name.toUtf8();
    refName = td_name;
    td::INT4 insert_id(catID);
    td::INT4 insert_newId(refJobID);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE, "UPDATE JobPlacements SET JobID=? WHERE CatID=? AND CatName=?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << insert_newId << insert_id << refName;


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


void addCatPla::setCatModel(MyModel *n)
{
    proxy->setSourceModel(n);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(1);

    ui->catalogTableView->setModel(proxy);
    ui->catalogTableView->resizeRowsToContents();
    ui->catalogTableView->horizontalHeader()->setStretchLastSection(true);
}

void addCatPla::setPlaModel(MyModel *n)
{
    proxy2->setSourceModel(n);
    proxy2->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy2->setFilterKeyColumn(1);

    ui->placTableView->setModel(proxy2);
    ui->placTableView->resizeRowsToContents();
    ui->placTableView->horizontalHeader()->setStretchLastSection(true);
}


void addCatPla::on_pushButton_clicked()
{
    if(catInd == true)
    {
    updateConsJob();
    updateUnitJob();
    updateMotorJob();
    select_catalogs();
    }
    else if(plaInd == true)
    {
    updateMotorPlaJob();
    updateUnitPlacJob();
    updateShuntResJob();
    select_placements();
    }

    //QDialog::accept();
}

void addCatPla::on_pushButton_2_clicked()
{
    QDialog::accept();
}

void addCatPla::on_catalogTableView_clicked(const QModelIndex &index)
{
    catInd = true;
    plaInd = false;

    int inx = index.row();
    QModelIndex ind = ui->catalogTableView->model()->index(inx,1);
    ui->catalogTableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val = ui->catalogTableView->model()->data(ind).toString();
    catID = val.toInt();

    QModelIndex ind2 = ui->catalogTableView->model()->index(inx,2);
    ui->catalogTableView->selectionModel()->select(index, QItemSelectionModel::Select);
    name = ui->catalogTableView->model()->data(ind2).toString();
}

void addCatPla::on_placTableView_clicked(const QModelIndex &index)
{
    plaInd = true;
    catInd = false;

    int inx = index.row();
    QModelIndex ind = ui->placTableView->model()->index(inx,1);
    ui->placTableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val = ui->placTableView->model()->data(ind).toString();
    catID = val.toInt();

    QModelIndex ind2 = ui->placTableView->model()->index(inx,2);
    ui->placTableView->selectionModel()->select(index, QItemSelectionModel::Select);
    name = ui->placTableView->model()->data(ind2).toString();
}

void addCatPla::on_comboBox_currentIndexChanged(int index)
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

void addCatPla::on_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
}

void addCatPla::on_comboBox_2_currentIndexChanged(int index)
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

void addCatPla::on_lineEdit_2_textChanged(const QString &arg1)
{
    proxy2->setFilterFixedString(arg1);
}

void addCatPla::on_catalogTableView_doubleClicked(const QModelIndex &index)
{
    updateConsJob();
    updateUnitJob();
    updateMotorJob();
    select_catalogs();
}

void addCatPla::on_placTableView_activated(const QModelIndex &index)
{
    updateMotorPlaJob();
    updateUnitPlacJob();
    updateShuntResJob();
    select_placements();
}
