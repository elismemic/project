#include "mwindow.h"
#include "ui_mwindow.h"
#include "job.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QFileDialog"
#include "QMessageBox"

db::ISQLDatabase *pDB = 0;
int userID = 10;

mWindow::mWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mWindow)

{
    ui->setupUi(this);
    connectSQLite();
}

mWindow::~mWindow()
{
    delete ui;
}

bool mWindow::connectSQLite()
{
    if (pDB)
        pDB->release();

        QString file = QFileDialog::getOpenFileName(this,"Open a database","C:/","Database files (*.db *.db3)");
        pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);
        //give path for our database
    if (!pDB->connect(file.toUtf8().constData()))
    {
        QMessageBox::information(this,"Connection status","Could not connect to database");
        td::String err;
        pDB->getErrorStr(err);
        std::cout << err.c_str() << std::endl;
        pDB->release();
        pDB = 0;
        return false;
    }
        QMessageBox::information(this,"Connection status","Connection OK");
    return true;
}
void mWindow::on_pushButton_clicked()
{
    job j;
    j.setModal(true);
    j.exec();
}
