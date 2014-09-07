#ifndef JUNCTIONPLACEMENT_H
#define JUNCTIONPLACEMENT_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class JunctionPlacement;
}

namespace db
{
    class ISQLDatabase;
}


class JunctionPlacement : public QDialog
{
    Q_OBJECT

public:
    explicit JunctionPlacement(QWidget *parent = 0);
    ~JunctionPlacement();
    void setUid(int uid);
    void enableUid(bool);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lineEdit_uid_textChanged(const QString &arg1);

private:
    Ui::JunctionPlacement *ui;
    QString oldName;
    bool uidExist(QString uid);//
    bool deleteNaming(int uid);//
    bool insertNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description, int type);//
    bool updateNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description, int type);//
    bool selectPhaseCode();//
    bool updateForm(int uid);//
    bool selectCatType();
};
#endif // JUNCTIONPLACEMENT_H
