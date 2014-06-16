#include "searchwindowresistorcatalog.h"
#include "ui_searchwindowresistorcatalog.h"
#include <QTableView>
#include <QStandardItem>
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "project.h"
#include "mymodel.h"
#include <QTableView>
#include <QStandardItem>

#include "resistorcatalog.h"

extern  db::ISQLDatabase *pDB;
extern int JobID;
extern int searchwindowID;
SearchWindowResistorCatalog::SearchWindowResistorCatalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindowResistorCatalog)
{
    ui->setupUi(this);
    this->setWindowTitle("Search Window Resistor Catalog");
    populateModel();

    ui->SWResistorCatalog_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SWResistorCatalog_tableView->setSelectionMode(QTableView::SingleSelection);
    proxy = new QSortFilterProxyModel(this);

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

mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID, Name, JobID from CatalogResistor"));
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
    ui->SWResistorCatalog_tableView->resizeRowsToContents();

    return true;

}


int SearchWindowResistorCatalog::getComboBoxIndex()
{
    return ui->SWResistorCatalog_SB_comboBox->currentIndex();

}

QString SearchWindowResistorCatalog::getSearchPhrase()
{
    return ui->SWResistorCatalog_SP_lineEdit->text();

}

bool SearchWindowResistorCatalog::deleteFromJobs()
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
       }

}
bool SearchWindowResistorCatalog::deleteResistorCatalog()
{

    int row = ui->SWResistorCatalog_tableView->selectionModel()->currentIndex().row();
        searchwindowID = ui->SWResistorCatalog_tableView->model()->index(row,0).data().toInt();
        if (!pDB)
            return false;

        td::INT4 delete_searchwindowID(searchwindowID);
        td::INT4 zero(0);

        //start transaction log
        db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
        db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
           "UPDATE CatalogResistor SET JobID = ? where ID = ?"));

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




void SearchWindowResistorCatalog::on_SWResistorCatalog_SP_lineEdit_textChanged(const QString &arg1)
{

    proxy->setFilterFixedString(arg1);
    populateModel();
}

void SearchWindowResistorCatalog::on_SWResistorCatalog_SB_comboBox_currentIndexChanged(int index)
{
    proxy->setFilterFixedString(getSearchPhrase());
    populateModel();
}

void SearchWindowResistorCatalog::on_new_pushButton_clicked()
{
    searchwindowID = 0;
    ResistorCatalog resistor;
    resistor.exec();
    populateModel();
}

void SearchWindowResistorCatalog::on_edit_pushButton_clicked()
{
    int row = ui->SWResistorCatalog_tableView->selectionModel()->currentIndex().row();
        searchwindowID = ui->SWResistorCatalog_tableView->model()->index(row,0).data().toInt();

    ResistorCatalog resistor;
    resistor.exec();
    populateModel();
}

void SearchWindowResistorCatalog::on_delete_pushButton_clicked()
{

    int row = ui->SWResistorCatalog_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->SWResistorCatalog_tableView->model()->index(row,0).data().toInt();

    deleteFromJobs();
    deleteResistorCatalog();
    populateModel();
}

void SearchWindowResistorCatalog::on_cancel_pushButton_clicked()
{

    close();
}
