#ifndef BUSBARPLACEMENT_H
#define BUSBARPLACEMENT_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class BusbarPlacement;
}

namespace db
{
    class ISQLDatabase;
}


class BusbarPlacement : public QDialog
{
    Q_OBJECT

public:
    explicit BusbarPlacement(QWidget *parent = 0);
    ~BusbarPlacement();
    void setUid(int uid);
    void enableUid(bool);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lineEdit_uid_textChanged(const QString &arg1);

private:
    Ui::BusbarPlacement *ui;
    db::ISQLDatabase *pDB;
    QString oldName;
    bool connectSQLite();
    bool insertDatabase(int uid, QString name, QString alias, int catalogType, int sectionType, int phaseCode, QString description);
    bool updateDatabase(int uid, QString name, QString alias, int catalogType, int sectionType, int phaseCode, QString description);
    bool uidExist(QString uid);
    bool selectCatalog();
    bool deleteNaming();
    bool insertNaming(QString name);
    bool updateNaming(QString name, QString oldName);
    bool selectPhaseCode();
    bool updateForm(int uid);
    bool selectSectionType();
    bool insertNaming(int type ,QString name);
};


#endif // BUSBARPLACEMENT_H
