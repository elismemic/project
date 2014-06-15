#ifndef SEARCHWINDOWCAPACITOR_H
#define SEARCHWINDOWCAPACITOR_H

#include <QDialog>
#include <QSortFilterProxyModel>

namespace Ui {
class SearchWindowCapacitor;
}
namespace db
{
    class Recordset;
}
namespace db
{
    class ISQLDatabase;
}

class SearchWindowCapacitor : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindowCapacitor(QWidget *parent = 0);
    ~SearchWindowCapacitor();

    QString getSearchPhrase();
    int getComboBoxIndex();



private slots:
    void on_Capacitor_searchPhrase_lineEdit_textChanged(const QString &arg1);

    void on_Capacitor_searchBy_comboBox_currentIndexChanged();

    void on_new_pushButton_clicked();

    void on_edit_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_delete_pushButton_clicked();

private:
    Ui::SearchWindowCapacitor *ui;
    QSortFilterProxyModel *proxy;
    bool populateModel();
    bool deleteCapacitor();
    bool deleteFromJobs();

};

#endif // SEARCHWINDOWCAPACITOR_H
