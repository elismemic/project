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
    void setPlacementType(int placementType);


private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_edit_clicked();

    void on_comboBox_type_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_new_clicked();


    void on_pushButton_delete_clicked();


    void on_lineEdit_search_textChanged();

private:
    Ui::SearchPlacements *ui;
    int catalogType;
    int placementType;
    MyModel *model;
    QAbstractTableModel *itemModel;

    bool selectVoltage();
    bool selectPhaseCode();
    bool selectSectionType();

    bool selectPlacement();
    void checkJob();
    void enableButtons();
    void disableButtons();
    void selectType();
    int getChosenJobId2(int job);
};

#endif // SEARCHPLACEMENTS_H
