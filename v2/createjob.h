#ifndef CREATEJOB_H
#define CREATEJOB_H

#include <QDialog>
#include <QAbstractButton>

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
    bool updateForm(int uid);

private slots:
    void on_comboBox_item_type_currentIndexChanged(int index);

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lineEdid_id_textChanged(const QString &arg1);

private:
    Ui::CreateJob *ui;
    db::ISQLDatabase *pDB;
    bool connectSQLite();
    bool uidExist(QString uid);
    bool insertJobs(int Job_Id, QString Job_Name, int Owner, int Status, QString Creation_Date, QString Activation_Date);
    bool updateJobs(int Job_Id, QString Job_Name, int Status, QString Creation_Date, QString Activation_Date);
    bool selectStatus();
};

#endif // CREATEJOB_H
