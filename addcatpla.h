#ifndef ADDCATPLA_H
#define ADDCATPLA_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include "mymodel.h"

namespace Ui {
class addCatPla;
}

class addCatPla : public QDialog
{
    Q_OBJECT

public:
    explicit addCatPla(int jobID = 0, QWidget *parent = 0);
    ~addCatPla();

    QSortFilterProxyModel *proxy;
    QSortFilterProxyModel *proxy2;

    int refJobID;
    QString val;
    int catID;
    QString name;
    bool catInd;
    bool plaInd;

    void setCatModel(MyModel *n);
    void setPlaModel(MyModel *n);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_catalogTableView_clicked(const QModelIndex &index);

    void on_placTableView_clicked(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(int index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_catalogTableView_doubleClicked(const QModelIndex &index);

    void on_placTableView_activated(const QModelIndex &index);

private:
    Ui::addCatPla *ui;

    bool select_catalogs();
    bool select_placements();

    bool updateConsJob();
    bool updateUnitJob();
    bool updateMotorJob();
    bool updateMotorPlaJob();
    bool updateUnitPlacJob();
    bool updateShuntResJob();
    bool updateJobCatalog();
    bool updateJobPlacement();
};

#endif // ADDCATPLA_H
