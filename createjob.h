#ifndef CREATEJOB_H
#define CREATEJOB_H

#include <QDialog>
#include <QAbstractButton>
#include <QDate>

namespace Ui {
class CreateJob;
}

namespace db
{
    class ISQLDatabase;
}

class CreateJob : public QDialog
{
    Q_OBJECT

public:
    explicit CreateJob(QWidget *parent = 0);
    ~CreateJob();

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);


private:
    Ui::CreateJob *ui;
    db::ISQLDatabase *pDB;
   // bool connectSQLite();
    bool insertJobs(QString Job_Name);
    };

#endif // CREATEJOB_H
