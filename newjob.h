#ifndef NEWJOB_H
#define NEWJOB_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include "mymodel.h"

namespace Ui {
class newJob;
}

class newJob : public QDialog
{
    Q_OBJECT

public:
    explicit newJob(QWidget *parent = 0);
    ~newJob();

    void setEditID(QString id);
    void setID(QString id);
    void setName(QString name);
    void setUser(MyModel *n);
    void setCDate();
    void setADate();

    int id() const;
    QString name() const;
    int owner() const;
    QString ownerName() const;
    int status() const;
    QDate cdate() const;
    QDate adate() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::newJob *ui;

};

#endif // NEWJOB_H
