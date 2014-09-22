#include "user.h"
#include "ui_user.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "mymodel.h"
#include <QDateTime>
#include <QString>

extern db::ISQLDatabase *pDB;
extern int userID;


user::user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    this->setWindowTitle("User");

}

user::~user()
{
    delete ui;
}
/*
bool user::createUser(QString name,QString pass, int user_id)
{
    if (!pDB)
        return false;



    td::INT4 id(user_id);


    db::Ref<td::String> refName(128);
    td::String td_name = name.toUtf8();
    refName = td_name;

    db::Ref<td::String> refPass(32);
    td::String td_pass = pass.toUtf8();
    refPass = td_pass;

    //start transaction log
    db::Transaction trans(pDB);
    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO Users(ID, Name, Password) VALUES (?,?,?)"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << id << refName << refPass;


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
*/

void user::on_pushButton_clicked()
{
    userID = ui->lineEdit->text().toInt();

    this->close();
}
