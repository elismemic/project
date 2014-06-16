#include "searchwindowcapacitor.h"
#include "ui_searchwindowcapacitor.h"
#include <QTableView>
#include <QStandardItem>
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "project.h"
#include "capacitor.h"
#include "conductor.h"
#include "capacitorbankplacement.h"
#include "mymodel.h"

extern db::ISQLDatabase *pDB;
extern int searchwindowID;
extern int JobID;
SearchWindowCapacitor::SearchWindowCapacitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindowCapacitor)
{
    ui->setupUi(this);
    this->setWindowTitle("Capacitor Catalog Search");
    proxy = new QSortFilterProxyModel(this);
    populateModel();
    ui->capacitor_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->capacitor_tableView->setSelectionMode(QTableView::SingleSelection);
    if(JobID > 0)
    {
        ui->new_pushButton->setEnabled(false);
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
    }
}

SearchWindowCapacitor::~SearchWindowCapacitor()
{
    delete ui;
}

QString SearchWindowCapacitor::getSearchPhrase()
{
    return ui->Capacitor_searchPhrase_lineEdit->text();
}

int SearchWindowCapacitor::getComboBoxIndex()
{
    return ui->Capacitor_searchBy_comboBox->currentIndex();
}

bool SearchWindowCapacitor::populateModel()
{
if (!pDB)
    return false;


mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,
                                  "SELECT ID, Name, JobID FROM CatalogCapacitor"));


cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(3);
    columns[0].name = "ID";
    columns[0].tdType = td::int4;
    columns[0].len = 0;

    columns[1].name = "Name";
    columns[1].tdType = td::nch;
    columns[1].len = 0;

    columns[2].name = "JobID";
    columns[2].tdType = td::int4;
    columns[2].len = 0;



    db::Recordset* rs = new db::Recordset(columns);

    rs->rowCount();
    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, true);

    //change stripe color
    /*td::Color c;
    c.setColor(20,150,20);
    model->setStripeColor(c);*/
    proxy->setSourceModel(model);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(getComboBoxIndex());

    ui->capacitor_tableView->setModel(proxy);
    ui->capacitor_tableView->resizeRowsToContents();
    return true;

}

void SearchWindowCapacitor::on_Capacitor_searchPhrase_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
    populateModel();

}

void SearchWindowCapacitor::on_Capacitor_searchBy_comboBox_currentIndexChanged()
{
    proxy->setFilterFixedString(getSearchPhrase());
    populateModel();
}

void SearchWindowCapacitor::on_new_pushButton_clicked()
{
    searchwindowID = 0;
    Capacitor capacitor;
    capacitor.exec();
}

void SearchWindowCapacitor::on_edit_pushButton_clicked()
{
    int row = ui->capacitor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->capacitor_tableView->model()->index(row,0).data().toInt();
    Capacitor capacitor;
    capacitor.exec();

}


void SearchWindowCapacitor::on_cancel_pushButton_clicked()
{
    close();
}

void SearchWindowCapacitor::on_delete_pushButton_clicked()
{
    int row = ui->capacitor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->capacitor_tableView->model()->index(row,0).data().toInt();
    deleteFromJobs();
    deleteCapacitor();
}

bool SearchWindowCapacitor::deleteCapacitor()
{

    if (!pDB)
        return false;

    td::INT4 delete_searchwindowID(searchwindowID);
    td::INT4 zero(0);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE CatalogCapacitor SET JobID = ? where ID = ?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << zero << delete_searchwindowID;


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
    return bRet;
}

bool SearchWindowCapacitor::deleteFromJobs()
{
    if (!pDB)
        return false;

    td::INT4 delete_searchwindowID(searchwindowID);
    td::INT4 zero(0);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE JobCatalogs SET JobID = ? where CatID = ?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << zero << delete_searchwindowID;


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
    return bRet;
}
