#ifndef PLAMOTOR_H
#define PLAMOTOR_H

#include <QDialog>
#include "mymodel.h"

namespace Ui {
class plaMotor;
}

class plaMotor : public QDialog
{
    Q_OBJECT

public:
    explicit plaMotor(QWidget *parent = 0);
    ~plaMotor();

    void setSystemID(MyModel *n, int a, int b);
    void setJobID(int jobID);
    void setProducer(MyModel *n, int a, int b);
    void setID(const int n);
    void setDisabledID(const QString n);
    void setName(const QString n, int b);
    void setAliasName(const QString n, int b);
    void setDescription(const QString n, int b);
    void setPhaseCode(MyModel* n, int ind, int b);
    void setCatalogType(MyModel* n, int ind, int b);
    void setConnectionType(MyModel* n, int ind, int b);

    QString systemName();
    int typeID() const;
    QString prodName();
    int id() const;
    QString name() const;
    QString aliasName() const;
    int idPhaseCode() const;
    int idCatalogType() const;
    int idConnectionType() const;
    QString description() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::plaMotor *ui;
};

#endif // PLAMOTOR_H
