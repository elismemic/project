#include "searchwindowbankplacement.h"
#include "ui_searchwindowbankplacement.h"
#include <QTableView>
#include <QStandardItem>
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "project.h"
#include "mymodel.h"
#include "capacitorbankplacement.h"
#include <QTableView>
#include <QStandardItem>

extern db::ISQLDatabase *pDB;
extern int searchwindowID = 0;
extern int searchwindowJobID = 0;
extern int JobID;
extern bool editable;
extern bool editClicked;
SearchWindowBankPlacement::SearchWindowBankPlacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindowBankPlacement)
{
    editClicked = false;

    ui->setupUi(this);
    ui->delete_pushButton->setEnabled(false);
    this->setWindowTitle("Capacitor Bank Placement Search");
    ui->capacitor_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    proxy = new QSortFilterProxyModel(this);
    populateModel();
    ui->capacitor_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->capacitor_tableView->setSelectionMode(QTableView::SingleSelection);
    ui->edit_pushButton->setEnabled(false);
    if(JobID > 0)
    {
        ui->new_pushButton->setEnabled(false);
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
    }

}

QString SearchWindowBankPlacement::getSearchPhrase()
{
    return ui->Placement_searchPhrase_lineEdit->text();
}

int SearchWindowBankPlacement::getComboBoxIndex()
{
    return ui->Placement_searchBy_comboBox->currentIndex();
}

SearchWindowBankPlacement::~SearchWindowBankPlacement()
{
    delete ui;
}


bool SearchWindowBankPlacement::populateModel()
{
if (!pDB)
    return false;

mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID, Name, JobID from CapacitorBankPlacement"));


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

    ui->capacitor_tableView->setModel(proxy);
    ui->capacitor_tableView->resizeRowsToContents();
    return true;

}

void SearchWindowBankPlacement::on_Placement_searchPhrase_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
    populateModel();
}

void SearchWindowBankPlacement::on_Placement_searchBy_comboBox_currentIndexChanged()
{
    proxy->setFilterFixedString(getSearchPhrase());
    populateModel();
}

void SearchWindowBankPlacement::on_new_pushButton_clicked()
{
    searchwindowID = 0;
    searchwindowJobID = JobID;
    CapacitorBankPlacement bankPlacement;
    bankPlacement.exec();
    populateModel();
}

void SearchWindowBankPlacement::on_edit_pushButton_clicked()
{
    editClicked = true;
    int row = ui->capacitor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->capacitor_tableView->model()->index(row,0).data().toInt();
    searchwindowJobID = ui->capacitor_tableView->model()->index(row,2).data().toInt();
    CapacitorBankPlacement bankPlacement;
    bankPlacement.exec();
    populateModel();
    ui->capacitor_tableView->selectRow(row);
}

void SearchWindowBankPlacement::on_cancel_pushButton_clicked()
{
    close();
}

void SearchWindowBankPlacement::on_delete_pushButton_clicked()
{
    int row = ui->capacitor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->capacitor_tableView->model()->index(row,0).data().toInt();
    searchwindowJobID = ui->capacitor_tableView->model()->index(row,2).data().toInt();
    //deleteFromJobs();
    deleteCapacitorBank();
    populateModel();
}


bool SearchWindowBankPlacement::deleteCapacitorBank()
{

    int row = ui->capacitor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->capacitor_tableView->model()->index(row,0).data().toInt();
    searchwindowJobID = ui->capacitor_tableView->model()->index(row,2).data().toInt();
    if (!pDB)
        return false;

    char *a = "Delete from JobPlacements where JobID = ";
    char buff[10];
    char *b = itoa(JobID,buff,10);
    char *c = (char*)malloc(strlen(a)+strlen(b)+1);
    if(c != NULL)
    {
        strcpy(c,a);
        strcpy(c,b);
    }
   pDB->execDirectly(c);
   populateModel();

}

bool SearchWindowBankPlacement::deleteFromJobs()
{
    if (!pDB)
        return false;

    td::INT4 delete_searchwindowID(searchwindowID);
    td::INT4 zero(0);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE JobPlacements SET JobID = ? where CatID = ?"));

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

void SearchWindowBankPlacement::on_capacitor_tableView_clicked(const QModelIndex &index)
{
    ui->delete_pushButton->setEnabled(false);
    if(JobID < 0)
    {
    ui->edit_pushButton->setEnabled(true);
    }
    int inx = index.row();


     QModelIndex ind = ui->capacitor_tableView->model()->index(inx,2);


     ui->capacitor_tableView->selectionModel()->select(index, QItemSelectionModel::Select);


     QString val = ui->capacitor_tableView->model()->data(ind).toString();


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