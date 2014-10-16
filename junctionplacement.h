#ifndef JunctionPlacement_H
#define JunctionPlacement_H

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
    Ui::JunctionPlacement *ui;
    QString oldName;
    int PlacementType;
    bool uidExist(QString uid);
    bool updateJobPlacements(int sysId, int jobId, int typeId, int placId);
    bool insertJobPlacements(int sysId, int jobId, int typeId, int placId);
    bool insertNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description,int jobid);//
    bool updateNaming(int uid, QString name, QString alias, int cattype, int phasecode, QString description);//
    //bool updatePlacement(int uid, int sectionType);
    bool selectPhaseCode();
    bool selectCatType();
    bool insertPlacement(int id, int typeId, int jobId, int sysId);
};


#endif // JunctionPlacement_H
