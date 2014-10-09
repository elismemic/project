#include "searchwindowresistorcatalog.h"
#include "ui_searchwindowresistorcatalog.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "project.h"
#include "mymodel.h"
#include <QTableView>
#include <QStandardItem>
#include "reactorbankplacement.h"
#include "reactorcatalog.h"
#include "resistorcatalog.h"
#include "resistorplacement.h"

extern  db::ISQLDatabase *pDB;
extern int JobID;
extern int searchwindowID;
extern int searchwindowJobID;
SearchWindowResistorCatalog::SearchWindowResistorCatalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindowResistorCatalog)
{

    ui->setupUi(this);
    this->setWindowTitle("Search Window Resistor Catalog");
    ui->SWResistorCatalog_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SWResistorCatalog_tableView->setSelectionMode(QTableView::SingleSelection);
    ui->SWResistorCatalog_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->delete_pushButton->setEnabled(false);
    proxy = new QSortFilterProxyModel(this);
    populateModel();
    if(JobID > 0)
    {
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
        ui->new_pushButton->setEnabled(false);
    }

}

SearchWindowResistorCatalog::~SearchWindowResistorCatalog()
{
    delete ui;
}


bool SearchWindowResistorCatalog::populateModel()
{
if (!pDB)
    return false;
//takes it from the base
mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,
                                                                "SELECT ID, Name, JobID from CatalogResistor"));
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


    ui->SWResistorCatalog_tableView->setModel(proxy);
    ui->SWResistorCatalog_tableView->resizeRowsToContents();\
    return true;

}

//combo box 012
int SearchWindowResistorCatalog::getComboBoxIndex()
{
    return ui->SWResistorCatalog_SB_comboBox->currentIndex();

}
//what text is returned
QString SearchWindowResistorCatalog::getSearchPhrase()
{
    return ui->SWResistorCatalog_SP_lineEdit->text();

}

//when line edit changes what to do
void SearchWindowResistorCatalog::on_SWResistorCatalog_SP_lineEdit_textChanged(const QString &arg1)
{

    proxy->setFilterFixedString(arg1);
    populateModel();
}
//when combo box changes what to do
void SearchWindowResistorCatalog::on_SWResistorCatalog_SB_comboBox_currentIndexChanged(int index)
{
    proxy->setFilterFixedString(getSearchPhrase());
    populateModel();
}
//
void SearchWindowResistorCatalog::on_new_pushButton_clicked()
{
    searchwindowID = 0;
    searchwindowJobID = JobID;
    ResistorCatalog resistor;
    resistor.exec();
    populateModel();
}

void SearchWindowResistorCatalog::on_edit_pushButton_clicked()
{
    int row = ui->SWResistorCatalog_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->SWResistorCatalog_tableView->model()->index(row,0).data().toInt();
    searchwindowJobID = ui->SWResistorCatalog_tableView->model()->index(row,2).data().toInt();

    ResistorCatalog resistor;
    resistor.exec();
    populateModel();
}

void SearchWindowResistorCatalog::on_delete_pushButton_clicked()
{

    int row = ui->SWResistorCatalog_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->SWResistorCatalog_tableView->model()->index(row,0).data().toInt();
    populateModel();
}

void SearchWindowResistorCatalog::on_cancel_pushButton_clicked()
{

    close();
}


