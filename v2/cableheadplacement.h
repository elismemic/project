#ifndef CABLEHEADPLACEMENT_H
#define CABLEHEADPLACEMENT_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class CableHeadPlacement;
}

namespace db
{
    class ISQLDatabase;
}


class CableHeadPlacement : public QDialog
{
    Q_OBJECT

public:
    explicit CableHeadPlacement(QWidget *parent = 0);
    ~CableHeadPlacement();
    void setUid(int uid);
    void enableUid(bool);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lineEdit_uid_textChanged(const QString &arg1);

private:
    Ui::CableHeadPlacement *ui;
   // db::ISQLDatabase *pDB;
    QString oldName;
    bool uidExist(QString uid);//
    bool deleteNaming(int uid);//
    bool insertNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description, int type);//
    bool updateNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description, int type);//
    bool selectPhaseCode();//
    bool updateForm(int uid);//
    bool selectSectionType(); //
    bool selectCatType();
};


#endif // CABLEHEADPLACEMENT_H
