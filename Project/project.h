#define PROJECT_H

#include <QMainWindow>


namespace Ui {
class Project;
}
namespace db
{
    class ISQLDatabase;
}

class Project : public QMainWindow
{
    Q_OBJECT

public:
    explicit Project(QWidget *parent = 0);
    ~Project();
    int getJobId();

private slots:
 void on_actionConductor_triggered();
 void on_actionCapacitor_triggered();
 void on_actionCapacitor_Bank_Placement_triggered();

 void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Project *ui;


    bool connectSQLite();
};


