#ifndef CATUNIT_H
#define CATUNIT_H

#include <QDialog>
#include "mymodel.h"

namespace Ui {
class catUnit;
}

class catUnit : public QDialog
{
    Q_OBJECT

public:
    explicit catUnit(QWidget *parent = 0);
    ~catUnit();

    void setJobID(int jobID);
    void setProducer(MyModel *n, int a, int b);
    void setID(const int n);
    void setDisabledID(const QString n);
    void setName(const QString n, int b);
    void setAliasName(const QString n, int b);
    void setRatedVoltage(MyModel *n, int i, int b);
    void setRatedPower(MyModel *n, int i, int b);
    void setNumberOfPhases(MyModel *n, int i, int b);
    void setConnectionType(MyModel *n, int i, int b);
    void setminOpAcPow(const float n, int b);
    void setmaxOpAcPow(const float n, int b);
    void setminOpRPow(const float n, int b);
    void setmaxOpRPow(const float n, int b);
    void setZ0_re(const float n, int b);
    void setZ0_im(const float n, int b);
    void setZ1_re(const float n, int b);
    void setZ1_im(const float n, int b);
    void setZ2_re(const float n, int b);
    void setZ2_im(const float n, int b);
    void setZ0trans_re(const float n, int b);
    void setZ0trans_im(const float n, int b);
    void setZ1trans_re(const float n, int b);
    void setZ1trans_im(const float n, int b);
    void setZ2trans_re(const float n, int b);
    void setZ2trans_im(const float n, int b);
    void setZ0sub_re(const float n, int b);
    void setZ0sub_im(const float n, int b);
    void setZ1sub_re(const float n, int b);
    void setZ1sub_im(const float n, int b);
    void setZ2sub_re(const float n, int b);
    void setZ2sub_im(const float n, int b);
    void setDescription(const QString n, int b);

    int typeID() const;
    QString prodName();
    int id() const;
    QString name() const;
    QString aliasName() const;
    int idRatedVol() const;
    int idRatedPower() const;
    int idNumberOfPhases() const;
    int idConnectionType() const;
    float minOpAcPow() const;
    float maxOpAcPow() const;
    float minOpRPow() const;
    float maxOpRPow() const;
    float Z0_re() const;
    float Z0_im() const;
    float Z1_re() const;
    float Z1_im() const;
    float Z2_re() const;
    float Z2_im() const;
    float Z0trans_re() const;
    float Z0trans_im() const;
    float Z1trans_re() const;
    float Z1trans_im() const;
    float Z2trans_re() const;
    float Z2trans_im() const;
    float Z0sub_re() const;
    float Z0sub_im() const;
    float Z1sub_re() const;
    float Z1sub_im() const;
    float Z2sub_re() const;
    float Z2sub_im() const;
    QString description() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::catUnit *ui;
};

#endif // CATUNIT_H
