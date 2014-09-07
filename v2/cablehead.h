
#ifndef CABLEHEAD_H
#define CABLEHEAD_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class CableHead;
}
namespace db
{
    class ISQLDatabase;
}
class CableHead : public QDialog
{
    Q_OBJECT

public:
    explicit CableHead(QWidget *parent = 0);
    ~CableHead();
    void setUid(int uid);
    void enableUid(bool);
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lineEditUid_textChanged(const QString &arg1);
private:
    Ui::CableHead *ui;
    QString oldName;
    bool insertCatalog(int id, int typeId);
    bool insertNaming(int uid, QString name, QString alias, int voltage, QString description,int typeId);
    bool updateNaming(int uid, QString name, QString alias, int voltage, QString description, int typeId);
    bool selectVoltage();
    bool uidExist(QString uid);
    bool deleteNaming(int uid);
    bool updateForm(int uid);
    bool deleteCatalog(int uid);
};

#endif // CABLEHEAD_H
