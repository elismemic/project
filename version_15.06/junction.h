#ifndef JUNCTION_H
#define JUNCTION_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class Junction;
}
namespace db
{
    class ISQLDatabase;
}
class Junction : public QDialog
{
    Q_OBJECT

public:
    explicit Junction(QWidget *parent = 0);
    ~Junction();
    void setUid(int uid);
    void enableUid(bool);
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lineEditUid_textChanged(const QString &arg1);
private:
    Ui::Junction *ui;
    QString oldName;
    bool updateCatalog(int id, int typeId);
    bool insertNaming(int uid, QString name, QString alias, int voltage, QString description,int typeId);
    bool updateNaming(int uid, QString name, QString alias, int voltage, QString description, int typeId);
    bool insertCatalog(int id, int typeId, int junction);
    bool selectVoltage();
    bool deleteNaming(int uid);
    bool deleteCatalog(int uid);
    bool uidExist(QString uid);
    bool updateForm(int uid);
    bool selectJunction();

};

#endif // JUNCTION_H