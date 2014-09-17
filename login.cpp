#include "login.h"
#include "ui_login.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "mymodel.h"
#include "powerss.h"

extern db::ISQLDatabase *pDB;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Sign In");
    this->ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    check = true;
}

Login::~Login()
{
    delete ui;
}

bool Login::checkCredentials()
{
    if (!pDB)
        exit(0);

    /*db::Ref<td::String> refUser(64);
    td::String td_user = username.toUtf8();
    refUser = td_user;

    db::Ref<td::String> refPass(64);
    td::String td_pass = password.toUtf8();
    refPass = td_pass;*/

    mem::PointerReleaser<db::IStatement> pStat(pDB->createStatement(db::IStatement::DBS_SELECT, "SELECT Name, Password from Users"));

    cnt::SafeFullVector<db::CPPColumnDesc> columns;
    columns.reserve(2);
    columns[0].name = "Name";
    columns[0].tdType = td::nch;
    columns[0].len = 64;

    columns[1].name = "Password";
    columns[1].tdType = td::nch;
    columns[1].len = 32;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        exit(0);

    MyModel *model = new MyModel(this, rs, true);

    for(int i = 0; i < model->rowCount(); i++)
    {
        QModelIndex idx = model->index(i,1);
        QString ids = model->data(idx, Qt::DisplayRole).toString();

        QModelIndex idx2 = model->index(i,2);
        QString ids2 = model->data(idx2, Qt::DisplayRole).toString();

        if(ui->lineEdit->text() == ids && ui->lineEdit_2->text() == ids2)
            check = true;

    }

    return check;
}

void Login::on_pushButton_clicked()
{
    if(check == true)
    {
        PowerSS start;
        start.show();
    }
}

void Login::on_pushButton_2_clicked()
{
    this->close();
}
