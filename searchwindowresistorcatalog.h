#ifndef SEARCHWINDOWRESISTORCATALOG_H
#define SEARCHWINDOWRESISTORCATALOG_H

#include <QDialog>
#include "searchwindowresistorcatalog.h"
#include <QSortFilterProxyModel>



namespace Ui {
class SearchWindowResistorCatalog;
}


class SearchWindowResistorCatalog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindowResistorCatalog(QWidget *parent = 0);
    ~SearchWindowResistorCatalog();

    int getComboBoxIndex();
    QString getSearchPhrase();


private slots:
    void on_SWResistorCatalog_SP_lineEdit_textChanged(const QString &arg1);

    void on_SWResistorCatalog_SB_comboBox_currentIndexChanged(int index);



    void on_new_pushButton_clicked();

    void on_edit_pushButton_clicked();

    void on_delete_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    Ui::SearchWindowResistorCatalog *ui;
    QSortFilterProxyModel *proxy;

    bool populateModel();

};

#endif // SEARCHWINDOWRESISTORCATALOG_H




