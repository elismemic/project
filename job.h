#ifndef JOB_H
#define JOB_H

#include <QDialog>
#include <QSortFilterProxyModel>
namespace Ui {
class job;
}
namespace db
{
    class ISQLDatabase;
}
namespace db
{
    class Recordset;
}
class job : public QDialog
{
    Q_OBJECT

public:
    explicit job(QWidget *parent = 0);
    ~job();

private slots:


    void on_newButton_clicked();

    void on_delButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_editButton_clicked();

    void on_comboBox_currentIndexChanged();

    void on_browseButton_clicked();

    void on_tableView_clicked(const QModelIndex &);



    void on_cancelButton_clicked();

    void on_actButton_clicked();

    void on_radioButton_clicked();

private:
    Ui::job *ui;
    bool populateModel();
    QSortFilterProxyModel *proxy;
    bool activate(int);
    bool actiJobCat(int);

};

#endif // JOB_H
