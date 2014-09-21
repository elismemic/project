#ifndef SELECTJOB_H
#define SELECTJOB_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include "mymodel.h"

namespace Ui {
class selectJob;
}

class selectJob : public QDialog
{
    Q_OBJECT

public:
    explicit selectJob(QWidget *parent = 0);
    ~selectJob();

    QSortFilterProxyModel *proxy;

    QString val;
    int jobID;

    int returnJobID();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_comboBox_currentIndexChanged(int index);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::selectJob *ui;
    bool select_jobs();
    void setModel(MyModel *n);
};

#endif // SELECTJOB_H
