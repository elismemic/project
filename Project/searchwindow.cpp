#include "searchwindowconductor.h"
#include "ui_searchwindow.h"
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

SearchWindow::SearchWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Conductor Catalog Search");
    proxy = new QSortFilterProxyModel(this);
    populateModel();
}

SearchWindow::~SearchWindow()
{
    delete ui;
}


QString SearchWindow::getSearchPhrase()
{
    return ui->searchPhrase_lineEdit->text();
}

int SearchWindow::getComboBoxIndex()
{
    return ui->comboBox->currentIndex();
}

bool SearchWindow::populateModel()
 {
     if (!pDB)
         return false;

     mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT,
                                                                    "SELECT ID, Name, Alias from CatalogConductor"));
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

         columns[2].name = "Alias";
         columns[2].tdType = td::nch;
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

         ui->tableView->setModel(proxy);
         ui->tableView->resizeRowsToContents();

         return true;
 }


void SearchWindow::on_Conductor_searchPhrase_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
    populateModel();

}

void SearchWindow::on_Conductor_searchBy_comboBox_currentIndexChanged(int index)
{
    proxy->setFilterFixedString(getSearchPhrase());
    populateModel();
}



void SearchWindow::on_new_pushButton_clicked()
{
    Conductor conductor;
    conductor.exec();
}

void SearchWindow::on_edit_pushButton_clicked()
{

}

void SearchWindow::on_browse_pushButton_clicked()
{

}

void SearchWindow::on_cancel_pushButton_clicked()
{
    close();
}
