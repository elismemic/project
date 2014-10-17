#ifndef PLARESISTOR_H
#define PLARESISTOR_H

#include <QDialog>
#include "mymodel.h"

namespace Ui {
class plaResistor;
}

class plaResistor : public QDialog
{
    Q_OBJECT

public:
    explicit plaResistor(QWidget *parent = 0);
    ~plaResistor();

    void setSystemID(MyModel *n, int a, int b);
    void setJobID(int jobID);
    void setProducer(MyModel *n, int a, int b);
    void setID(const int n);
    void setDisabledID(const QString n);
    void setName(const QString n, int b);
    void setAliasName(const QString n, int b);
    void setCatalogType(MyModel* n, int ind, int b);
    void setDescription(const QString n, int b);

    QString systemName();
    int typeID() const;
    QString prodName();
    int ID() const;
    QString name() const;
    QString aliasName() const;
    int idCatalogType() const;
    QString description() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::plaResistor *ui;
};

#endif // PLARESISTOR_H
