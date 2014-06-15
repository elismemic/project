#ifndef SEARCHWINDOWCONDUCTOR_H
#define SEARCHWINDOWCONDUCTOR_H

#include <QDialog>
#include <QSortFilterProxyModel>

namespace Ui {
class SearchWindowConductor;
}

namespace db
{
    class Recordset;
}

namespace db
{
    class ISQLDatabase;
}

class SearchWindowConductor : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindowConductor(QWidget *parent = 0);
    ~SearchWindowConductor();

    QString getSearchPhrase();
    int getComboBoxIndex();


private slots:
    void on_searchPhrase_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged();

    void on_new_pushButton_clicked();

    void on_edit_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_delete_pushButton_clicked();

private:
    Ui::SearchWindowConductor *ui;
    QSortFilterProxyModel *proxy;
    bool deleteConductor();
    bool deleteFromJobs();
    bool populateModel();

};

#endif // SEARCHWINDOWCONDUCTOR_H
