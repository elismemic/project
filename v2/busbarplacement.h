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
    void setPlacementType(int PlacementType);
    bool updateForm(int uid);//
    bool deleteNaming(int uid);//
    bool deletePlacement(int uid);

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lineEdit_uid_textChanged(const QString &arg1);


private:
    Ui::BusbarPlacement *ui;
    QString oldName;
    int PlacementType;
    bool uidExist(QString uid);
    bool insertNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description, int type);//
    bool updateNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description, int type);//
    bool updatePlacement(int uid, int sectionType);
    bool selectPhaseCode();
    bool selectSectionType();
    bool selectCatType();
    bool insertPlacement(int id, int typeId, int secType);
};


#endif // BUSBARPLACEMENT_H
