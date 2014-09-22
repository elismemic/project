#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QSortFilterProxyModel>
namespace Ui {
class user;
}
namespace db
{
    class ISQLDatabase;
}
namespace db
{
    class Recordset;
}
class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = 0);
    ~user();

private slots:
    void on_pushButton_clicked();

private:
    Ui::user *ui;


};

#endif // USER_H
