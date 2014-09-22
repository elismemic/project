#include "selectjob.h"
#include "ui_selectjob.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "newjob.h"
#include <QDate>
extern db::ISQLDatabase *pDB;

selectJob::selectJob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectJob)
{
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    ui->comboBox->setCurrentIndex(1);
    select_jobs();
}

selectJob::~selectJob()
{
    delete ui;
}

bool selectJob::select_jobs()
{
    if (!pDB)
        return false;


    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT ID, Name, UserID, Status, CreationDate, ActivationDate from Jobs"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(6);
        columns[0].name = "Id";
        columns[0].tdType = td::int4;
        columns[0].len = 0;

        columns[1].name = "Name";
        columns[1].tdType = td::nch;
        columns[1].len = 128;

        columns[2].name = "UserID";
        columns[2].tdType = td::int4;
        columns[2].len = 0;

        columns[3].name = "Status";
        columns[3].tdType = td::int4;
        columns[3].len = 0;

        columns[4].name = "CreationDate";
        columns[4].tdType = td::date;
        columns[4].len = 0;

        columns[5].name = "ActivationDate";
        columns[5].tdType = td::date;
        columns[5].len = 0;

        db::Recordset* rs = new db::Recordset(columns);


        if (!rs->load(pStat.getPtr()))
            return false;

        // true for stripes
        MyModel *model = new MyModel(this, rs, true);

        setModel(model);

        return true;
}

void selectJob::setModel(MyModel *n)
{
    proxy->setSourceModel(n);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(1);

    ui->tableView->setModel(proxy);
    ui->tableView->resizeRowsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void selectJob::on_tableView_doubleClicked(const QModelIndex &index)
{
    QDialog::accept();
    int inx = index.row();
    QModelIndex ind = ui->tableView->model()->index(inx,0);
    ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val = ui->tableView->model()->data(ind).toString();
    jobID = val.toInt();
    returnJobID();
    this->close();
}

int selectJob::returnJobID()
{
    return jobID;
}

void selectJob::on_tableView_clicked(const QModelIndex &index)
{
    int inx = index.row();
    QModelIndex ind = ui->tableView->model()->index(inx,0);
    ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select);
    val = ui->tableView->model()->data(ind).toString();
    jobID = val.toInt();
}

void selectJob::on_buttonBox_accepted()
{
    QDialog::accept();
}

void selectJob::on_buttonBox_rejected()
{
    this->close();
}

void selectJob::on_comboBox_currentIndexChanged(int index)
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

void selectJob::on_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
}
