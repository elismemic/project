#include "job.h"
#include "ui_job.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "newjob.h"
#include "mymodel.h"
#include <QDateTime>

extern db::ISQLDatabase *pDB;
extern int userID;
extern int user_jobID;
extern int jobID;
extern bool edit;
int max = 0;

job::job(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::job)
{
    ui->setupUi(this);
    this->setWindowTitle("Jobs");
    proxy = new QSortFilterProxyModel(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QTableView::SingleSelection);
    populateModel();
    ui->editButton->setEnabled(false);


}

job::~job()
{
    delete ui;

}

bool job::populateModel()
{
if (!pDB)
    return false;
mem::PointerReleaser<db::IStatement> pStat;
if (ui->radioButton->isChecked())
{
    pStat = pDB->createStatement(db::IStatement::DBS_SELECT,
        "SELECT ID, Name, UserID, Status, Creation_date, Activation_date from Jobs");
}
        else
{
    pStat = pDB->createStatement(db::IStatement::DBS_SELECT,
        "SELECT ID, Name, UserID, Status, Creation_date, Activation_date from Jobs WHERE userID = ?");
    td::INT4 user(userID);
    db::Params params(pStat->allocParams());
    params << user;
}


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

        columns[4].name = "Creation_date";
        columns[4].tdType = td::nch;
        columns[4].len = 19;

        columns[5].name = "Activation_date";
        columns[5].tdType = td::nch;
        columns[5].len = 19;


    db::Recordset* rs = new db::Recordset(columns);


    if (!rs->load(pStat.getPtr()))
        return false;


    MyModel *model = new MyModel(this, rs, true);

    proxy->setSourceModel(model);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(ui->comboBox->currentIndex() + 1);


    ui->tableView->setModel(proxy);
    ui->tableView->resizeRowsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    for(int i = 0; i < model->rowCount(); ++i)
    {
        int id = ui->tableView->model()->index(i,0).data().toInt();
        if(id > max) max = id;
    }
    return true;

}

void job::on_newButton_clicked()
{
    newJob ins;
    ins.setModal(true);
    ins.exec();
    populateModel();

}

void job::on_delButton_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    int ID = ui->tableView->model()->index(row,0).data().toInt();
    if( ui->tableView->model()->index(row,2).data().toInt() != userID)
    {
        QMessageBox::information(this,"Deleting the job ...","Unable to delete the job that belongs to another user.");
        return;
    }
    if(ID < 0)
    {
        char* a = "DELETE FROM Jobs WHERE ID = ";
        char buf[10];
        char* b = itoa(ID,buf,10);
        char* statement = (char*)malloc(strlen(a) + strlen(b) + 1);

        if (statement != NULL)
        {
             strcpy(statement, a);
             strcat(statement, b);
        }
        pDB->execDirectly(statement);      
        QMessageBox::information(this,"Deleting...","The job has been deleted!");
    }
    else
        QMessageBox::information(this,"Deleting...","The job cannot be deleted!");
    populateModel();
}

void job::on_lineEdit_textEdited(const QString &arg1)
{
    if(ui->comboBox->currentIndex() == 1)
        proxy->setFilterRegExp(QRegExp("^"+ui->lineEdit->text()+"$"));
    else
        proxy->setFilterFixedString(arg1);

}

void job::on_comboBox_currentIndexChanged()
{

    if(ui->comboBox->currentIndex() == 1)
        proxy->setFilterRegExp(QRegExp("^"+ui->lineEdit->text()+"$"));
    else
        proxy->setFilterFixedString(ui->lineEdit->text());
    populateModel();
}

void job::on_editButton_clicked()
{
   int row = ui->tableView->selectionModel()->currentIndex().row();
   int ID = ui->tableView->model()->index(row,0).data().toInt();
   int user = ui->tableView->model()->index(row,2).data().toInt();
   if(ID < 0 && user == userID)
   {
      jobID = ID;
      user_jobID = user;
      edit = true;
   }
   this->close();
}

void job::on_tableView_clicked(const QModelIndex &index)
{   ui->editButton->setEnabled(false);
    int row = ui->tableView->selectionModel()->currentIndex().row();
    int ID = ui->tableView->model()->index(row,0).data().toInt();
    int user = ui->tableView->model()->index(row,2).data().toInt();
    if(ID < 0 && user == userID)
        ui->editButton->setEnabled(true);
}

void job::on_browseButton_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    jobID = ui->tableView->model()->index(row,0).data().toInt();
    user_jobID = ui->tableView->model()->index(row,2).data().toInt();
    edit = false;
    this->close();

}

void job::on_cancelButton_clicked()
{
    this->close();
}

bool job::activate(int newID)
{
    if (!pDB)
        return false;

    td::INT4 status(1); //0 - status of ACTIVATED jobs

    //activation date
    QDateTime crdate= QDateTime::currentDateTime();
    QString date1 = crdate.toString("yyyy-MM-dd hh:mm:ss");
    db::Ref<td::String> refDate(128);
    td::String td_date = date1.toUtf8();
    refDate = td_date;
    // job id
    int row = ui->tableView->selectionModel()->currentIndex().row();
    td::INT4 id( ui->tableView->model()->index(row,0).data().toInt());
    td::INT4 refid(newID + 1);

    //start transaction log
    db::Transaction trans(pDB);
    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "Update Jobs SET ID = ?, Status = ?, Activation_date = ? WHERE ID = ?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << refid << status << refDate << id;


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
    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}



void job::on_actButton_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    int ID = ui->tableView->model()->index(row,0).data().toInt();
    if( ui->tableView->model()->index(row,2).data().toInt() != userID)
    {
        QMessageBox::information(this,"Activating the job ...","Unable to activate the job that belongs to another user.");
        return;
    }
    bool acti = false;
    if (ID < 0) acti = activate(max);
    if(acti)
          QMessageBox::information(this,"Activating the job ...","Job with ID " + QString::number(ID)+ " has been activated!");
    else
          QMessageBox::information(this,"Activating the job ...","Unable to activate the job");
    populateModel();
}


void job::on_radioButton_clicked()
{
      populateModel();
}
