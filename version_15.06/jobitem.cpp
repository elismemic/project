#include "jobitem.h"
#include "ui_jobitem.h"
#include "db/ISQLDataProvider.h"

extern db::ISQLDatabase *pDB;

JobItem::JobItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JobItem)
{
    ui->setupUi(this);
    addType();
}

void JobItem::setFields(){
    ui->comboBox_item->setEnabled(false);
    ui->lineEdit_Id->setEnabled(false);
    ui->lineEdit_Name->setEnabled(false);
    ui->lineEdit_Id->setText(QString::number(jobID));
    ui->lineEdit_Name->setText(jobName);
}

JobItem::~JobItem()
{
    delete ui;
}

void JobItem::addType()
{
    ui->comboBox_type->addItem("Busbar Catalog",0);
    ui->comboBox_type->addItem("Cable Head Catalog",1);
    ui->comboBox_type->addItem("Junction Catalog",2);
    ui->comboBox_type->addItem("Busbar Placement",3);
    ui->comboBox_type->addItem("Cable Head Placement",4);
    ui->comboBox_type->addItem("Junction Placement",5);
}


bool JobItem::selectCatalog(int index)
{
    if (!pDB){
         std::cout<< "Transaction failed not pDB" <<std::endl;
         return false;}

    td::String Name;

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name from CatNaming where TypeId = ?"));
    db::Params params(pStat->allocParams());
    params << index;

    db::Columns cols(pStat->allocBindColumns(1));
        cols << "Name" << Name;

        if (!pStat->execute())
            {
                std::cout << "testSelect2 - Exec NOT ok\n";
                td::StringUTF8 strErr;
                pStat->getErrorStr(strErr);
                std::cout << strErr.c_str() << std::endl;
                return false;
            }
            else{

            int counter = 0;
            while (pStat->moveNext())
            {
                ui->comboBox_item->addItem(QString::fromUtf8(Name.c_str()),QString::number(counter));
                counter++;
            }


            return true;
        }
}

void JobItem::setJobId(int jobId)
{
    jobID = jobId;
}

void JobItem::setJobName(QString name){
    jobName = name;
}

void JobItem::on_comboBox_type_currentIndexChanged(int index)
{
    ui->comboBox_item->setEnabled(true);
    ui->comboBox_item->clear();
    switch(index){
    case 0: selectCatalog(11);break;
    case 1: selectCatalog(12);break;
    case 2: selectCatalog(13);break;
    //needs to finish for others
    }
}
