#ifndef JOBS_H
#define JOBS_H
#include <QDialog>
#include "mymodel.h"
#include <QAbstractItemModel>

namespace Ui {
class Jobs;
}

namespace db
{
    class ISQLDatabase;
}

class Jobs : public QDialog
{
    Q_OBJECT

public:
    explicit Jobs(QWidget *parent = 0);
    ~Jobs();

private slots:

    void on_comboBox_type_currentIndexChanged(int index);

    void on_pushButton_search_clicked();

    void on_pushButton_browse_clicked();

    void on_tableView_browse_clicked(const QModelIndex &index);

    void on_pushButton_new_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();


    void on_pushButton_cancel_clicked();

    void on_pushButton_item_clicked();

private:
    Ui::Jobs *ui;
    MyModel *model;
    MyModel *model2;
    QAbstractTableModel *itemModel;
    db::ISQLDatabase *pDB;
    void selectType();
    int getUidByName(QString name);
    bool selectStatus();
    bool selectOwner();
    bool updateTableView();
    bool browseJob();
    void enableButtons();
    void disableButtons();
    bool connectSQLite();

};

#endif // JOBS_H