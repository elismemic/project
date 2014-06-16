#ifndef SEARCHWINDOWRESISTORPLACEMENT_H
#define SEARCHWINDOWRESISTORPLACEMENT_H

#include <QDialog>
#include "searchwindowresistorplacement.h"
#include <QSortFilterProxyModel>

namespace Ui {
class SearchWindowResistorPlacement;
}
namespace db
{
    class Recordset;
}
namespace db
{
    class ISQLDatabase;
}

class SearchWindowResistorPlacement : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindowResistorPlacement(QWidget *parent = 0);
    ~SearchWindowResistorPlacement();
    int getComboBoxIndex();
    QString getSearchPhrase();
    bool deleteFromJobs();
    bool deleteResistorPlacement();

private slots:
    void on_new_pushButton_clicked();

    void on_edit_pushButton_clicked();

    void on_delete_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_SWResistorPlacement_SP_lineEdit_textChanged(const QString &arg1);

    void on_SWResistorPlacement_SB_comboBox_currentIndexChanged(int index);

private:
    Ui::SearchWindowResistorPlacement *ui;
    QSortFilterProxyModel *proxy;


    bool populateModel();

};


#endif // SEARCHWINDOWRESISTORPLACEMENT_H
