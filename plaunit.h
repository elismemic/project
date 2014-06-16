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

    void setSystemID(MyModel *n, int a);
    void setJobID(int jobID);
    void setProducer(MyModel *n, int a);
    void setID(const int n);
    void setID2(const QString n);
    void setName(const QString n);
    void setAliasName(const QString n);
    void setPhaseCode(MyModel *n, int a);
    void setCatalogType(MyModel *n, int a);
    void setNodeType(MyModel *n, int a);
    void setLoadType(MyModel *n, int a);
    void setLoadDemand(MyModel *n, int a);
    void setdes(const float n);
    void setr(const float n);
    void setx(const float n);
    void setDescription(const QString n);

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
