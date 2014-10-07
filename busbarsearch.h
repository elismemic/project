#ifndef BUSBARSEARCH_H
#define BUSBARSEARCH_H

#include <QDialog>
#include "mymodel.h"
#include <QAbstractItemModel>

namespace Ui {
class BusbarSearch;
}

namespace db
{
    class ISQLDatabase;
}

class BusbarSearch : public QDialog
{
    Q_OBJECT

public:
    explicit BusbarSearch(QWidget *parent = 0);
    void setCatalogType(int);
    ~BusbarSearch();

private slots:
    void on_pushButton_edit_clicked();

    void on_comboBox_type_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_new_clicked();

    void on_lineEdit_search_textChanged();

    void on_comboBox_voltage_currentIndexChanged();

    void on_pushButton_delete_clicked();

private:
    Ui::BusbarSearch *ui;
    int catalogType;
    MyModel *model;
    QAbstractTableModel *itemModel;
    bool updateDatabase(int uid, int type, QString name, QString alias, int voltage, QString description);
    bool selectVoltage();
    bool selectCatalogs(int type);
    void checkJob();
    void enableButtons();
    void disableButtons();
    bool selectPlacement();
    void selectType();

};

#endif // BUSBARSEARCH_H
