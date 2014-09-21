#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include <QSortFilterProxyModel>

namespace Ui {
class SearchWindow;
}

namespace db
{
    class Recordset;
}

namespace db
{
    class ISQLDatabase;
}

class SearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = 0);
    ~SearchWindow();

    QString getSearchPhrase();
    int getComboBoxIndex();
private slots:
    void on_Conductor_searchPhrase_lineEdit_textChanged(const QString &arg1);

    void on_Conductor_searchBy_comboBox_currentIndexChanged(int index);

    void on_new_pushButton_clicked();

    void on_edit_pushButton_clicked();

    void on_browse_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    Ui::SearchWindow *ui;
    QSortFilterProxyModel *proxy;
    bool populateModel();
  
};

#endif // SEARCHWINDOW_H
