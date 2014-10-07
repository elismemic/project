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

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    int jobID;
    QString jobName;
    Ui::JobItem *ui;
    int type;
    bool selectCatalog(int index);
    void addType();
    bool insertJobPlacement(int jobId, int typeId, int placId, int systemId);
    int getCatalogId(QString name, int type);
    bool insertJobCatalogs(int jobId, int typeId, int catId);
    bool updateCatalogs(int Id, int type, int jobId);
    bool isItemAvailable(int typeId, int catId);
};

#endif // JOBITEM_H


