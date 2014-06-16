#ifndef CATCONSUMER_H
#define CATCONSUMER_H

#include <QDialog>
#include "mymodel.h"

namespace Ui {
class catConsumer;
}

class catConsumer : public QDialog
{
    Q_OBJECT

public:
    explicit catConsumer(QWidget *parent = 0);
    ~catConsumer();

    void setJobID(int jobID);
    void setProducer(MyModel *n, int a);
    void setID(const int n);
    void setID2(const QString n);
    void setName(const QString n);
    void setAliasName(const QString n);
    void setRatedVoltage(MyModel *n, int ind);
    void setKP0(const float n);
    void setKQ0(const float n);
    void setKP1(const float n);
    void setKQ1(const float n);
    void setKP2(const float n);
    void setKQ2(const float n);
    void setDescription(const QString n);

    int typeID() const;
    QString prodName();
    int id() const;
    QString name() const;
    QString aliasName() const;
    int idRatedVol() const;
    float kP0() const;
    float kQ0() const;
    float kP1() const;
    float kQ1() const;
    float kP2() const;
    float kQ2() const;
    QString description() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::catConsumer *ui;
};

#endif // CATCONSUMER_H
