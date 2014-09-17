#ifndef BROWSE_H
#define BROWSE_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include "mymodel.h"

namespace Ui {
class browse;
}

class browse : public QDialog
{
    Q_OBJECT

public:
    explicit browse(int jobID = 0, int refUserJob = 0, QWidget *parent = 0);
    ~browse();

    QSortFilterProxyModel *proxy;
    QSortFilterProxyModel *proxy2;

    QString val;
    QString val2;
    int typeID;
    int catID;
    QString oldname;

    QString nameVal, aliasVal, descVal, rVoltVal, kp0Val, kq0Val, kp1Val
    , kq1Val, kp2Val, kq2Val, rPowVal, nopVal, cTypeVal, minOpAcPowVal
    , maxOpAcPowVal, minOpRPowVal, maxOpRPowVal, Z0_reVal, Z0_imVal
    , Z1_reVal, Z1_imVal, Z2_reVal, Z2_imVal, Z0trans_reVal, Z0trans_imVal
    , Z1trans_reVal, Z1trans_imVal, Z2trans_reVal, Z2trans_imVal
    , Z0sub_reVal, Z0sub_imVal, Z1sub_reVal, Z1sub_imVal, Z2sub_reVal
    , Z2sub_imVal, nmpVal, powFVal, effVal, loadFVal, rmpVal
    , isuVal, rxVal, phaseCVal, catTVal, nodeTVal, loadTVal
    , loadDMVal, dVoltVal, groundVal, rGroundVal, xGroundVal, prodVal, systemVal;

    void setCatModel(MyModel *n);
    void setPlaModel(MyModel *n);

    void catConsEdtClicked();
    void catUnitEdtClicked();
    void catMotorEdtClicked();
    void plaMotorEdtClicked();
    void plaUnitEdtClicked();
    void plaResistorEdtClicked();

    int refJobID;
    int ref2UserJob;

private slots:
    void on_pushButton_3_clicked();

    void on_placTableView_clicked(const QModelIndex &index);

    void on_catalogTableView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

private:
    Ui::browse *ui;

    bool select_catalogs(int jobID);
    bool select_placements(int jobID);

    bool setConsValues();
    bool setUnitValues();
    bool setMotorValues();
    bool setMotorPlaValues();
    bool setUnitPlaValues();
    bool setResPlaValues();

    MyModel *browse::select_ratedVoltage();
    MyModel *browse::select_ratedPower();
    MyModel *browse::select_numberOfPhases();
    MyModel *browse::select_connectionType();
    MyModel *browse::select_catalogType_Motor();
    MyModel *browse::select_phaseCode();
    MyModel *browse::select_catalogType_Unit();
    MyModel *browse::select_catalogType_Shunt();
    MyModel *browse::select_nodeType();
    MyModel *browse::select_loadType();
    MyModel *browse::select_loadDemand();
    MyModel *browse::select_producers();
    MyModel *browse::select_system();
    int select_prodID(QString name);
    int select_systemID(QString name);


    bool updateConsumer(QString name, QString aliasName, QString description, int ratedVol
                          , float kp0, float kq0, float kp1, float kq1, float kp2, float kq2);
    bool updateUnit(QString name, QString aliasName, QString description, int ratedVol, int ratedPow
                          , int idNoP, int idConType, float minOpAcPow, float maxOpAcPow, float minOpRPow, float maxOpRPow
                          , float Z0_re, float Z0_im, float Z1_re, float Z1_im, float Z2_re , float Z2_im
                          , float Z0trans_re, float Z0trans_im, float Z1trans_re, float Z1trans_im
                          , float Z2trans_re, float Z2trans_im, float Z0sub_re, float Z0sub_im
                          , float Z1sub_re, float Z1sub_im, float Z2sub_re, float Z2sub_im);
    bool updateMotor(QString name, QString aliasName, QString description, int idRatedVol
                          , int idNoP, float nmp, float pow, float eff, float load, int rpm, float isu, float rx);
    bool updateMotorPla(int systemId, QString name, QString alias, QString desc,int idPhase, int idCatalog, int idConnection);
    bool updateUnitPlacement(int systemID, QString name, QString aliasName, QString description
                          , int phaseCode, int catalogType, int nodeType, int loadType, int loadDemand
                          , float des, int grounded, float r, float x);
    bool updateShuntResistor(int systemID, QString name, QString aliasName
                          , QString description, int idCatType);
    bool update_catalog(QString name);
    bool update_placement(int systemID, QString name);
    bool update_jobCatalog(QString catName);
    bool update_jobPlacement(int systemID, QString catName);

    bool updateJobCons();
    bool updateJobUnit();
    bool updateJobMotor();
    bool updateJobMotorPla();
    bool updateJobUnitPla();
    bool updateJobResPla();
    bool updateJobIDCat();
    bool updateJobIDPla();

};

#endif // BROWSE_H
