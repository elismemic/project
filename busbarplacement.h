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
    void setWindowName();
    void checkJob();

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lineEdit_uid_textChanged(const QString &arg1);


private:
    Ui::BusbarPlacement *ui;
    QString oldName;
    int PlacementType;
    bool uidExist(QString uid);
    bool updateJobPlacements(int sysId, int jobId, int typeId, int placId);
    bool insertJobPlacements(int sysId, int jobId, int typeId, int placId);
    bool insertNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description);//
    bool updateNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description);//
    bool updatePlacement(int uid, int sectionType);
    bool selectPhaseCode();
    bool selectSectionType();
    bool selectCatType();
    bool insertPlacement(int id, int typeId, int jobId, int sysId, int secType);
};


#endif // BUSBARPLACEMENT_H
