#ifndef SEARCHPLACEMENTS_H
#define SEARCHPLACEMENTS_H

#include <QDialog>
#include "mymodel.h"
#include <QAbstractItemModel>

namespace Ui {
class SearchPlacements;
}

namespace db
{
    class ISQLDatabase;
}

class SearchPlacements : public QDialog
{
    Q_OBJECT

public:
    explicit SearchPlacements(QWidget *parent = 0);
    void setCatalogType(int);
    ~SearchPlacements();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_edit_clicked();

    void on_comboBox_type_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_new_clicked();

private:
    Ui::SearchPlacements *ui;
    int catalogType;
    MyModel *model;
    QAbstractTableModel *itemModel;
    db::ISQLDatabase *pDB;

    bool updateDatabase(int uid, int type, QString name, QString alias, int voltage, QString description);
    bool selectVoltage();
    bool selectPhaseCode();
    bool selectSectionType();
    bool connectSQLite();

    bool selectBusbarPlacement();
    bool selectCableHeadPlacement();
    bool selectJunctionPlacement();

    void enableButtons();
    void disableButtons();
    bool selectPlacement();
    void selectType();

};

#endif // SEARCHPLACEMENTS_H
