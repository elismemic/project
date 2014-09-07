#ifndef JOBITEM_H
#define JOBITEM_H

#include <QDialog>

namespace Ui {
class JobItem;
}

namespace db
{
    class ISQLDatabase;
}

class JobItem : public QDialog
{
    Q_OBJECT

public:
    explicit JobItem(QWidget *parent = 0);
    ~JobItem();
    void setJobId(int jobId);
    void setJobName(QString name);
    void setFields();

private slots:
    void on_comboBox_type_currentIndexChanged(int index);

private:
    int jobID;
    QString jobName;
    Ui::JobItem *ui;
    bool selectCatalog(int index);
    void addType();
};

#endif // JOBITEM_H


