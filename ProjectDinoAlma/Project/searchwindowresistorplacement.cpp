#include "searchwindowresistorplacement.h"
#include "ui_searchwindowresistorplacement.h"
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
#include "resistorplacement.h"

extern  db::ISQLDatabase *pDB;
extern int JobID;
extern int searchwindowID;
SearchWindowResistorPlacement::SearchWindowResistorPlacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindowResistorPlacement)
{
    ui->setupUi(this);
    this->setWindowTitle("Search Window Resistor Placement");
    proxy = new QSortFilterProxyModel(this);
    ui->SWResistorPlacement_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SWResistorPlacement_tableView->setSelectionMode(QTableView::SingleSelection);

    populateModel();
    if(JobID > 0)
    {
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
        ui->new_pushButton->setEnabled(false);
    }
}

SearchWindowResistorPlacement::~SearchWindowResistorPlacement()
{
    delete ui;
}

int SearchWindowResistorPlacement::getComboBoxIndex()
{
    return ui->SWResistorPlacement_SB_comboBox->currentIndex();

}

QString SearchWindowResistorPlacement::getSearchPhrase()
{
    return ui->SWResistorPlacement_SP_lineEdit->text();

}

void SearchWindowResistorPlacement::on_new_pushButton_clicked()
{
    searchwindowID = 0;
    ResistorPlacement resPlac;
    resPlac.exec();
    populateModel();
}

void SearchWindowResistorPlacement::on_edit_pushButton_clicked()
{
    ResistorPlacement resPlac;
    resPlac.exec();
    populateModel();
}

void SearchWindowResistorPlacement::on_delete_pushButton_clicked()
{
    int row = ui->SWResistorPlacement_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->SWResistorPlacement_tableView->model()->index(row,0).data().toInt();
    deleteFromJobs();
    deleteResistorPlacement();
    populateModel();
}

void SearchWindowResistorPlacement::on_cancel_pushButton_clicked()
{
    close();
}

void SearchWindowResistorPlacement::on_SWResistorPlacement_SP_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
    populateModel();
}

void SearchWindowResistorPlacement::on_SWResistorPlacement_SB_comboBox_currentIndexChanged(int index)
{
    proxy->setFilterFixedString(getSearchPhrase());
    populateModel();
}

bool SearchWindowResistorPlacement::populateModel()
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


        ui->SWResistorPlacement_tableView->setModel(proxy);
        ui->SWResistorPlacement_tableView->resizeRowsToContents();

        return true;
}


bool SearchWindowResistorPlacement::deleteFromJobs()
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

bool SearchWindowResistorPlacement::deleteResistorPlacement()
{
int row = ui->SWResistorPlacement_tableView->selectionModel()->currentIndex().row();
    searchwindowID = ui->SWResistorPlacement_tableView->model()->index(row,0).data().toInt();
    if (!pDB)
        return false;

    td::INT4 delete_searchwindowID(searchwindowID);
    td::INT4 zero(0);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE PlacementResistor SET JobID = ? where ID = ?"));

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
