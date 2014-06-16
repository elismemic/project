#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include "mymodel.h"

namespace Ui {
class searchDialog;
}

class searchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchDialog(int a = 0, QWidget *parent = 0);
    ~searchDialog();

    QSortFilterProxyModel *proxy;

    QString val;
    QString val2;
    int proxComInd;
    QString oldname;
    QString oldname2;

    QString nameVal, aliasVal, descVal, rVoltVal, kp0Val, kq0Val, kp1Val
    , kq1Val, kp2Val, kq2Val, rPowVal, nopVal, cTypeVal, minOpAcPowVal
    , maxOpAcPowVal, minOpRPowVal, maxOpRPowVal, Z0_reVal, Z0_imVal
    , Z1_reVal, Z1_imVal, Z2_reVal, Z2_imVal, Z0trans_reVal, Z0trans_imVal
    , Z1trans_reVal, Z1trans_imVal, Z2trans_reVal, Z2trans_imVal
    , Z0sub_reVal, Z0sub_imVal, Z1sub_reVal, Z1sub_imVal, Z2sub_reVal
    , Z2sub_imVal, nmpVal, powFVal, effVal, loadFVal, rmpVal
    , isuVal, rxVal, phaseCVal, catTVal, nodeTVal, loadTVal
    , loadDMVal, dVoltVal, groundVal, rGroundVal, xGroundVal, prodVal, systemVal;

    int chs;
    int consJobID;
    int unitJobID;
    int motorJobID;
    int motorPlaJobID;
    int unitPlaJobID;
    int resPlaJobID;

    void setModel(int i, MyModel *n);

    void catConsClicked(int jobID);
    void catUnitClicked(int jobID);
    void catMotorClicked(int jobID);
    void plaMotorClicked(int jobID);
    void plaUnitClicked(int jobID);
    void plaResistorClicked(int jobID);

    void catConsEdtClicked();
    void catUnitEdtClicked();
    void catMotorEdtClicked();
    void plaMotorEdtClicked();
    void plaUnitEdtClicked();
    void plaResistorEdtClicked();


private slots:
    void on_newPushButton_clicked();

    void on_editPushButton_clicked();

    void on_cancelPushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::searchDialog *ui;

    bool select_searchConsumer();
    bool select_searchUnit();
    bool select_searchMotor();
    bool select_searchMotorPla();
    bool select_searchUnitPla();
    bool select_searchShuntRes();

    bool setConsValues();
    bool setUnitValues();
    bool setMotorValues();
    bool setMotorPlaValues();
    bool setUnitPlaValues();
    bool setResPlaValues();

    bool insert_catalog(int typeID, int prodID, int id, QString name);
    bool insert_placement(int systemID, int typeID, int prodID, int id, QString name);

    bool insert_jobCatalog(int jobID, int typeID, int catID, QString name);
    bool insert_jobPlacement(int systemID, int jobID, int typeID, int catID, QString name);

    MyModel *searchDialog::select_ratedVoltage();
    MyModel *searchDialog::select_ratedPower();
    MyModel *searchDialog::select_numberOfPhases();
    MyModel *searchDialog::select_connectionType();
    MyModel *searchDialog::select_catalogType_Motor();
    MyModel *searchDialog::select_phaseCode();
    MyModel *searchDialog::select_catalogType_Unit();
    MyModel *searchDialog::select_catalogType_Shunt();
    MyModel *searchDialog::select_nodeType();
    MyModel *searchDialog::select_loadType();
    MyModel *searchDialog::select_loadDemand();
    MyModel *searchDialog::select_producers();
    MyModel *searchDialog::select_system();
    int select_catJobID(int id);
    int select_plaJobID(int id);
    int select_prodID(QString name);
    int select_systemID(QString name);

    bool insert_consumer(int jobID, int typeID, int prodID, int id, QString name, QString aliasName
                         , QString description, int ratedVol, float kp0, float kq0, float kp1, float kq1
                         , float kp2, float kq2);
    bool insert_unit(int jobID, int typeID, int prodID, int id, QString name, QString aliasName
                          , QString description, int ratedVol, int ratedPow, int idNoP, int idConType
                          , float minOpAcPow, float maxOpAcPow, float minOpRPow, float maxOpRPow
                          , float Z0_re, float Z0_im, float Z1_re, float Z1_im, float Z2_re , float Z2_im
                          , float Z0trans_re, float Z0trans_im, float Z1trans_re, float Z1trans_im
                          , float Z2trans_re, float Z2trans_im, float Z0sub_re, float Z0sub_im
                          , float Z1sub_re, float Z1sub_im, float Z2sub_re, float Z2sub_im);
    bool insert_motor(int jobID, int typeID, int prodID, int id, QString name, QString aliasName, QString description, int idRatedVol
                          , int idNoP, float nmp, float pow, float eff, float load, int rpm, float isu, float rx);
    bool insert_motorPla(int systemId, int jobID, int typeID, int prodID, int id
                          , QString name, QString alias, QString desc, int idPhase, int idCatalog, int idConnection);
    bool insert_unitPlacement(int systemID, int jobID, int typeID, int prodID, int id, QString name, QString aliasName, QString description
                          , int phaseCode, int catalogType, int nodeType, int loadType, int loadDemand
                          , float des, int grounded, float r, float x);
    bool insert_shuntResistor(int systemID, int jobID, int typeID, int prodID, int id, QString name, QString aliasName
                          , QString description, int idCatType);

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

    friend class browse;
};

#endif // SEARCHDIALOG_H
