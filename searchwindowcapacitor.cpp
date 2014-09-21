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
extern int searchwindowJobID;
extern int JobID;
extern bool editable;
extern bool editClicked;
SearchWindowCapacitor::SearchWindowCapacitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindowCapacitor)
{

    editClicked = false;
    ui->setupUi(this);
    ui->delete_pushButton->setEnabled(false);
    this->setWindowTitle("Capacitor Catalog Search");
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
    searchwindowJobID = JobID;
    Capacitor capacitor;
    capacitor.exec();
    populateModel();

}

void SearchWindowCapacitor::on_edit_pushButton_clicked()
{
    editClicked = true;
    int row = ui->capacitor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->capacitor_tableView->model()->index(row,0).data().toInt();
    searchwindowJobID = ui->capacitor_tableView->model()->index(row,2).data().toInt();
    Capacitor capacitor;
    capacitor.exec();
    populateModel();
    ui->capacitor_tableView->selectRow(row);
}


void SearchWindowCapacitor::on_cancel_pushButton_clicked()
{
    close();
}

void SearchWindowCapacitor::on_delete_pushButton_clicked()
{
    int row = ui->capacitor_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->capacitor_tableView->model()->index(row,0).data().toInt();
    searchwindowJobID = ui->capacitor_tableView->model()->index(row,2).data().toInt();
    deleteFromCapacitor();
    deleteFromNaming();
    populateModel();
    ui->delete_pushButton->setEnabled(false);
}

bool SearchWindowCapacitor::deleteFromCapacitor()
{

    if (!pDB)
        return false;

    char *a = "Delete from CatalogCapacitor where ID = ";
    char buff[10];
    char *b = itoa(searchwindowID,buff,10);
    char *c = (char*)malloc(strlen(a)+strlen(b)+1);
    if(c != NULL)
    {
        strcpy(c,a);
        strcpy(c,b);
    }
   pDB->execDirectly(c);
   return true;
}

bool SearchWindowCapacitor::deleteFromNaming()
{
    if (!pDB)
        return false;

    char *a = "Delete from CatNaming where ID = ";
    char buff[10];
    char *b = itoa(searchwindowID,buff,10);
    char *c = (char*)malloc(strlen(a)+strlen(b)+1);
    if(c != NULL)
    {
        strcpy(c,a);
        strcpy(c,b);
    }
   pDB->execDirectly(c);
   return true;
}

void SearchWindowCapacitor::on_capacitor_tableView_clicked(const QModelIndex &index)
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