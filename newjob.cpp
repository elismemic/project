#include "newjob.h"
#include "ui_newjob.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "searchjobs.h"

extern db::ISQLDatabase *pDB;
extern int userID;

newJob::newJob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newJob)
{
    ui->setupUi(this);
}

newJob::~newJob()
{
    delete ui;
}

void newJob::setEditID(QString id)
{
    ui->lineEdit->setText(id);
    ui->lineEdit->setDisabled(true);
}

void newJob::setID()
{
    searchJobs nj(this);
    ui->lineEdit->setText(nj.updateRandomNumber());
}

void newJob::setName(QString name)
{
    ui->lineEdit_2->setText(name);
}

void newJob::setUser(MyModel *n)
{
    ui->userComboBox->setModel(n);
    ui->userComboBox->setCurrentIndex(userID - 1);
}

void newJob::setCDate()
{
    ui->dateEdit->setDate(QDate::currentDate());
}

void newJob::setADate()
{
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_2->setDisabled(true);
}

int newJob::id() const
{
    int num = ui->lineEdit->text().toInt();
    return num;
}

QString newJob::name() const
{
    return ui->lineEdit_2->text();
}

int newJob::owner() const
{
    return ui->userComboBox->currentIndex();
}

QString newJob::ownerName() const
{
    return ui->userComboBox->currentText();
}

int newJob::status() const
{
    return ui->comboBox->currentIndex();
}

QDate newJob::cdate() const
{
    return ui->dateEdit->date();
}

QDate newJob::adate() const
{
    return ui->dateEdit_2->date();
}

void newJob::on_buttonBox_accepted()
{
    QDialog::accept();
}

void newJob::on_buttonBox_rejected()
{
    this->close();
}

void newJob::on_comboBox_currentIndexChanged(int index)
{
    if(index == 1)
    {
        ui->dateEdit_2->setEnabled(true);
    }
    else if(index == 0)
    {
        ui->dateEdit_2->setDisabled(true);
    }
}
