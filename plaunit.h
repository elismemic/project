#ifndef PLAUNIT_H
#define PLAUNIT_H

#include <QDialog>
#include "mymodel.h"

namespace Ui {
class plaUnit;
}

class plaUnit : public QDialog
{
    Q_OBJECT

public:
    explicit plaUnit(QWidget *parent = 0);
    ~plaUnit();

    void setSystemID(MyModel *n, int a, int b);
    void setJobID(int jobID);
    void setProducer(MyModel *n, int a, int b);
    void setID(const int n);
    void setDisabledID(const QString n);
    void setName(const QString n, int b);
    void setAliasName(const QString n, int b);
    void setPhaseCode(MyModel* n, int ind, int b);
    void setCatalogType(MyModel* n, int ind, int b);
    void setNodeType(MyModel* n, int ind, int b);
    void setLoadType(MyModel* n, int ind, int b);
    void setLoadDemand(MyModel* n, int ind, int b);
    void setdes(const float n, int b);
    void setr(const float n, int b);
    void setx(const float n, int b);
    void setDescription(const QString n, int b);

    QString systemName();
    int typeID() const;
    QString prodName();
    int id() const;
    QString name() const;
    QString aliasName() const;
    int phaseCode() const;
    int catalogType() const;
    int nodeType() const;
    int loadType() const;
    int loadDemand() const;
    float des() const;
    int grounded() const;
    float r() const;
    float x() const;
    QString description() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::plaUnit *ui;
};

#endif // PLAUNIT_H
