#ifndef SEARCHJOBS_H
#define SEARCHJOBS_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include "mymodel.h"

namespace Ui {
class searchJobs;
}

class searchJobs : public QDialog
{
    Q_OBJECT

public:
    explicit searchJobs(QWidget *parent = 0);
    ~searchJobs();

    QSortFilterProxyModel *proxy;

    QString val;
    int jobID;
    int idVal;
    QString nameVal;
    int ownerVal;
    int statVal;
    int refUserJob;
    QString negJobID;
    int setJobIDVal();
    bool jobDbl;

private slots:
    void on_pushButton_clicked();

    void on_newJobPushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::searchJobs *ui;
    bool select_jobs();
    bool select_jobsValues();
    bool insert_job(int id, QString name, int user, int status, QDate cdate, QDate adate);
    bool update_job(int id, QString name, int user, int status, QDate cdate, QDate adate);
    bool update_activatedJob(int id, QString name, int user, int status, QDate cdate, QDate adate);
    bool update_editFlag(int jobID);
    bool update_status();
    bool update_aDate(QDate adate);
    MyModel *searchJobs::select_user();
    int select_ownerID(QString ownerName);
    void setModel(MyModel *n);
    QVariant getUserName(int userID);

    bool updateConsJob(int newJ);
    bool updateUnitJob();
    bool updateMotorJob();
    bool updateMotorPlaJob();
    bool updateUnitPlacJob();
    bool updateShuntResJob();
    bool updateJobCatalog(int newJ);
    bool updateJobPlacement();
    bool update_jobPlacementJobID(int oldJobID, int newJobID);

    QString updateRandomNumber();
    int getJobID();

    friend class searchDialog;
    friend class newJob;
};

#endif // SEARCHJOBS_H
