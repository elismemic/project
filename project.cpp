#include "project.h"
#include "ui_project.h"
#include "reactorbankplacement.h"
#include "reactorcatalog.h"
#include "resistorcatalog.h"
#include "resistorplacement.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QFileDialog"
#include "QMessageBox"
#include "searchwindowreactorbankplacement.h"
#include "searchwindowreactorcatalog.h"
#include "searchwindowresistorcatalog.h"
#include "searchwindowresistorplacement.h"

extern db::ISQLDatabase *pDB=0;
extern int JobID = 0;

Project::Project(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Project)
{


    ui->setupUi(this);
    connectSQLite();
}

Project::~Project()
{
    delete ui;
}

bool Project::connectSQLite()
{

    if (pDB)
        pDB->release();
    QString file = QFileDialog::getOpenFileName(this,"Open a database");
    pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);
        //give path for our database
    if (!pDB->connect(file.toUtf8().constData()))
    {
        QMessageBox::information(this,"Info","Cannot Connect");
        td::String err;
        pDB->getErrorStr(err);
        std::cout << err.c_str() << std::endl;
        pDB->release();
        pDB = 0;
        return false;
    }
   QMessageBox::information(this,"Info","Connection OK");
    return true;
}


void Project::on_actionResistor_triggered()
{


    SearchWindowResistorCatalog resistor;
    resistor.setModal(true);
    resistor.exec();
}

void Project::on_actionReactor_triggered()
{

    SearchWindowReactorCatalog reactor;
    reactor.setModal(true);
    reactor.exec();
}

void Project::on_actionReactorBankPlacement_triggered()
{
    SearchWindowReactorBankPlacement reactorBankPlacement;
    reactorBankPlacement.setModal(true);
    reactorBankPlacement.exec();
}

void Project::on_actionResistorPlacement_triggered()
{

    SearchWindowResistorPlacement resistorPlacement;
    resistorPlacement.setModal(true);
    resistorPlacement.exec();
}

void Project::on_lineEdit_textChanged(const QString &arg1)
{
    JobID = ui->lineEdit->text().toInt();
}
