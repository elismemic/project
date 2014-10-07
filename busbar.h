#ifndef BUSBAR_H
#define BUSBAR_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class Busbar;
}
namespace db
{
    class ISQLDatabase;
}
class Busbar : public QDialog
{
    Q_OBJECT

public:
    explicit Busbar(QWidget *parent = 0);
    ~Busbar();
    void setUid(int uid);
    void enableUid(bool);
    bool deleteNaming(int uid);
    bool deleteCatalog(int uid);
    bool deleteJobCatalogs(int uid);
    void checkJob();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lineEditUid_textChanged(const QString &arg1);
private:
    Ui::Busbar *ui;
    QString oldName;

    bool insertJobCatalogs(int jobId,int typeId, int catId);
    bool updateJobCatalogs(int jobId, int typeId, int catId);
    bool updateCatalog(int id, int typeId);
    bool insertNaming(int uid, QString name, QString alias, int voltage, QString description);
    bool updateNaming(int uid, QString name, QString alias, int voltage, QString description);
    bool insertCatalog(int id, int typeId);
    bool selectVoltage();
    bool uidExist(QString uid);
    bool updateForm(int uid);
};

#endif // BUSBAR_H