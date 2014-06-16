#ifndef SEARCHWINDOWBANKPLACEMENT_H
#define SEARCHWINDOWBANKPLACEMENT_H

#include <QDialog>
#include <QSortFilterProxyModel>

namespace Ui {
class SearchWindowBankPlacement;
}

namespace db
{
    class Recordset;
}

namespace db
{
    class ISQLDatabase;
}

class SearchWindowBankPlacement : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindowBankPlacement(QWidget *parent = 0);
    ~SearchWindowBankPlacement();
    QString getSearchPhrase();
    int getComboBoxIndex();

private slots:
    void on_Placement_searchPhrase_lineEdit_textChanged(const QString &arg1);

    void on_Placement_searchBy_comboBox_currentIndexChanged();

    void on_new_pushButton_clicked();

    void on_edit_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_delete_pushButton_clicked();

private:
    Ui::SearchWindowBankPlacement *ui;
    QSortFilterProxyModel *proxy;
    bool populateModel();
    bool deleteCapacitorBank();
    bool deleteFromJobs();
};

#endif // SEARCHWINDOWBANKPLACEMENT_H
