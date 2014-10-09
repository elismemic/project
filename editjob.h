#ifndef EDITJOB_H
#define EDITJOB_H

#include <QDialog>

namespace Ui {
class editJob;
}
namespace db
{
    class ISQLDatabase;
}
namespace db
{
    class Recordset;
}
class editJob : public QDialog
{
    Q_OBJECT

public:
    explicit editJob(QWidget *parent = 0);
    ~editJob();

private:
    Ui::editJob *ui;
    bool populateModelCat();
    bool updateModelCat(QString);
    bool populateModelPla();
    bool updateModelPla(QString);
};

#endif // EDITJOB_H
