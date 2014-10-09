#ifndef NEWJOB_H
#define NEWJOB_H

#include <QDialog>

namespace Ui {
class newJob;
}
namespace db
{
    class ISQLDatabase;
}

class newJob : public QDialog
{
    Q_OBJECT

public:
    explicit newJob(QWidget *parent = 0);
    ~newJob();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::newJob *ui;
    bool insertJob(QString name);

};

#endif // NEWJOB_H
