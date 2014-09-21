#include "searchwindowconductor.h"
#include "ui_searchwindowconductor.h"
#include <QTableView>
#include <QStandardItem>
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "project.h"
#include "mymodel.h"
#include "conductor.h"
#include <QTableView>
#include <QStandardItem>

extern db::ISQLDatabase *pDB;
extern int searchwindowID;
extern int searchwindowJobID;
extern int JobID;
extern bool editable;
extern bool editClicked;
SearchWindowConductor::SearchWindowConductor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindowConductor)
{

    editClicked = false;
    ui->setupUi(this);
    ui->delete_pushButton->setEnabled(false);
    ui->conductor_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setWindowTitle("Conductor Catalog Search");
    proxy = new QSortFilterProxyModel(this);
    populateModel();
    ui->conductor_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->conductor_tableView->setSelectionMode(QTableView::SingleSelection);
    ui->edit_pushButton->setEnabled(false);
    if(JobID > 0)
    {
        ui->new_pushButton->setEnabled(false);
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
    }
}

SearchWindowConductor::~SearchWindowConductor()
{
    delete ui;
}


QString SearchWindowConductor::getSearchPhrase()
{
    return ui->searchPhrase_lineEdit->text();
}

int SearchWindowConductor::getComboBoxIndex()
{
    return ui->comboBox->currentIndex();
}

bool SearchWindowConductor::populateModel()
 {
     if (!pDB)
         return false;

     mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,
                                                                    "SELECT ID, Name, JobID from CatalogConductor"));
     //db::Params params(pStat->allocParams());
     //params << cijenaMinLimit << cijenaMaxLimit;

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

         ui->conductor_tableView->setModel(proxy);
         ui->conductor_tableView->resizeRowsToContents();

         return true;
 }

void SearchWindowConductor::on_searchPhrase_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
    populateModel();
}

void SearchWindowConductor::on_comboBox_currentIndexChanged()
{
    proxy->setFilterFixedString(getSearchPhrase());
    populateModel();
}

void SearchWindowConductor::on_new_pushButton_clicked()
{
    searchwindowID = 0;
    searchwindowJobID = JobID;
    Conductor conductor;
    conductor.exec();
    populateModel();
}

void SearchWindowConductor::on_edit_pushButton_clicked()
{
    editClicked = true;
    int row = ui->conductor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->conductor_tableView->model()->index(row,0).data().toInt();
    searchwindowJobID = ui->conductor_tableView->model()->index(row,2).data().toInt();
    Conductor conductor;
    conductor.exec();
    populateModel();
    ui->conductor_tableView->selectRow(row);

}

void SearchWindowConductor::on_cancel_pushButton_clicked()
{
    close();
}


void SearchWindowConductor::on_delete_pushButton_clicked()
{
    int row = ui->conductor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->conductor_tableView->model()->index(row,0).data().toInt();
    //deleteFromJobs();
    deleteConductor();
    populateModel();

}

bool SearchWindowConductor::deleteConductor()
{

    int row = ui->conductor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->conductor_tableView->model()->index(row,0).data().toInt();
    if (!pDB)
        return false;

    td::INT4 delete_searchwindowID(searchwindowID);
    td::INT4 zero(0);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE CatalogConductor SET JobID = ? where ID = ?"));

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

bool SearchWindowConductor::deleteFromJobs()
{
    int row = ui->conductor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->conductor_tableView->model()->index(row,0).data().toInt();
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

void SearchWindowConductor::on_conductor_tableView_clicked(const QModelIndex &index)
{
    ui->delete_pushButton->setEnabled(false);
    if(JobID < 0)
    {
    ui->edit_pushButton->setEnabled(true);
    }
    int inx = index.row();


     QModelIndex ind = ui->conductor_tableView->model()->index(inx,2);


     ui->conductor_tableView->selectionModel()->select(index, QItemSelectionModel::Select);


     QString val = ui->conductor_tableView->model()->data(ind).toString();


     searchwindowJobID = val.toInt();

     if(((searchwindowJobID != JobID) && (searchwindowJobID <= 0)) || (editable == false))
       {
           ui->edit_pushButton->setEnabled(false);
       }
     if((searchwindowJobID == JobID) && (searchwindowJobID < 0))
     {
         ui->delete_pushButton->setEnabled(true);
     }
}
