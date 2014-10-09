#ifndef SEARCHWINDOWREACTORCATALOG_H
#define SEARCHWINDOWREACTORCATALOG_H
#include <QDialog>
#include "searchwindowreactorcatalog.h"
#include <QSortFilterProxyModel>


namespace Ui {
class SearchWindowReactorCatalog;
}

namespace db
{
    class ISQLDatabase;
}

class SearchWindowReactorCatalog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindowReactorCatalog(QWidget *parent = 0);
    ~SearchWindowReactorCatalog();
    QString getSearchPhrase();
    int getComboBoxIndex();


private slots:
    void on_SWReactorCatalog_SP_lineEdit_textChanged(const QString &arg1);

    void on_SWReactorCatalog_SB_comboBox_currentIndexChanged(int index);

    void on_new_pushButton_clicked();

    void on_edit_pushButton_clicked();

    void on_delete_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    Ui::SearchWindowReactorCatalog *ui;
    QSortFilterProxyModel *proxy;


    bool populateModel();

};
#endif // SEARCHWINDOWREACTORCATALOG_H

