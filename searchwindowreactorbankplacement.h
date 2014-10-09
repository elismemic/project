#ifndef SEARCHWINDOWREACTORBANKPLACEMENT_H
#define SEARCHWINDOWREACTORBANKPLACEMENT_H

#include <QDialog>
#include "searchwindowreactorbankplacement.h"
#include <QSortFilterProxyModel>


namespace Ui {
class SearchWindowReactorBankPlacement;
}
namespace db
{
    class Recordset;
}
namespace db
{
    class ISQLDatabase;
}

class SearchWindowReactorBankPlacement : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindowReactorBankPlacement(QWidget *parent = 0);
    ~SearchWindowReactorBankPlacement();
    QString getSearchPhrase();
    int getComboBoxIndex();


private slots:
    void on_SWRBP_SP_lineEdit_textChanged(const QString &arg1);

    void on_SWRBP_SB_comboBox_currentIndexChanged(int index);

    void on_new_pushButton_clicked();

    void on_edit_pushButton_clicked();

    void on_delete_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    Ui::SearchWindowReactorBankPlacement *ui;
    QSortFilterProxyModel *proxy;


    bool populateModel();

};

#endif // SEARCHWINDOWREACTORBANKPLACEMENT_H

