#include "searchwindowreactorbankplacement.h"
#include "ui_searchwindowreactorbankplacement.h"
#include "reactorbankplacement.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "project.h"
#include "mymodel.h"
#include <QTableView>
#include <QStandardItem>
#include "mymodel.h"

extern  db::ISQLDatabase *pDB;
extern int JobID;
extern int searchwindowID;
SearchWindowReactorBankPlacement::SearchWindowReactorBankPlacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindowReactorBankPlacement)
{
    ui->setupUi(this);
    this->setWindowTitle("Search Window Reactor Bank Placement");
    populateModel();
    ui->SWRBP_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SWRBP_tableView->setSelectionMode(QTableView::SingleSelection);
    proxy = new QSortFilterProxyModel(this);
    if(JobID > 0)
    {
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
        ui->new_pushButton->setEnabled(false);
    }

}

SearchWindowReactorBankPlacement::~SearchWindowReactorBankPlacement()
{
    delete ui;
}

QString SearchWindowReactorBankPlacement::getSearchPhrase()
{
    return ui->SWRBP_SP_lineEdit->text();
}

int SearchWindowReactorBankPlacement::getComboBoxIndex()
{
    return ui->SWRBP_SB_comboBox->currentIndex();
}

void SearchWindowReactorBankPlacement::on_SWRBP_SP_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
    populateModel();
}

void SearchWindowReactorBankPlacement::on_SWRBP_SB_comboBox_currentIndexChanged(int index)
{
    proxy->setFilterFixedString(getSearchPhrase());
    populateModel();
}

void SearchWindowReactorBankPlacement::on_new_pushButton_clicked()
{
    searchwindowID = 0;
    ReactorBankPlacement reactorBankPlac;
    reactorBankPlac.exec();
    populateModel();
}

void SearchWindowReactorBankPlacement::on_edit_pushButton_clicked()
{
    int row = ui->SWRBP_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->SWRBP_tableView->model()->index(row,0).data().toInt();
    ReactorBankPlacement reactorBankPlac;
    reactorBankPlac.exec();
    populateModel();
}

void SearchWindowReactorBankPlacement::on_delete_pushButton_clicked()
{
    int row = ui->SWRBP_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->SWRBP_tableView->model()->index(row,0).data().toInt();
    deleteFromJobs();
    deleteReactorBankPlacement();
    populateModel();
}

void SearchWindowReactorBankPlacement::on_cancel_pushButton_clicked()
{
    close();
}


bool SearchWindowReactorBankPlacement::populateModel()
{
    if (!pDB)
        return false;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID, Name, JobID from PlacementReactorBank"));
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


        ui->SWRBP_tableView->setModel(proxy);
        ui->SWRBP_tableView->resizeRowsToContents();

        return true;
}


bool SearchWindowReactorBankPlacement::deleteFromJobs()
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
       }

}
bool SearchWindowReactorBankPlacement::deleteReactorBankPlacement()
{

    int row = ui->SWRBP_tableView->selectionModel()->currentIndex().row();
        searchwindowID = ui->SWRBP_tableView->model()->index(row,0).data().toInt();
        if (!pDB)
            return false;

        td::INT4 delete_searchwindowID(searchwindowID);
        td::INT4 zero(0);

        //start transaction log
        db::Transaction trans(pDB);

        //create statement using parameters which will be provided later
        db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
           "UPDATE PlacementReactorBank SET JobID = ? where ID = ?"));

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
