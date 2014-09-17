#ifndef CATMOTOR_H
#define CATMOTOR_H

#include <QDialog>
#include "mymodel.h"

namespace Ui {
class catMotor;
}

class catMotor : public QDialog
{
    Q_OBJECT

public:
    explicit catMotor(QWidget *parent = 0);
    ~catMotor();

    void setJobID(int jobID);
    void setProducer(MyModel *n, int a, int b);
    void setID(const int n);
    void setDisabledID(const QString n);
    void setName(const QString n, int b);
    void setAliasName(const QString n, int b);
    void setRatedVoltage(MyModel *n, int a, int b);
    void setNumberOfPhases(MyModel *n, int a, int b);
    void setnmp(const float n, int b);
    void setpow(const float n, int b);
    void seteff(const float n, int b);
    void setload(const float n, int b);
    void setrpm(const int n, int b);
    void setisu(const float n, int b);
    void setrx(const float n, int b);
    void setDescription(const QString n, int b);

    int typeID() const;
    QString prodName();
    int id() const;
    QString name() const;
    QString aliasName() const;
    int idRatedVol() const;
    int idNumberOfPhases() const;
    float nmp() const;
    float pow() const;
    float eff() const;
    float load() const;
    int rpm() const;
    float isu() const;
    float rx() const;
    QString description() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::catMotor *ui;
};

#endif // CATMOTOR_H
