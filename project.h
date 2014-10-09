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

private slots:


 void on_actionResistor_triggered();

 void on_actionReactor_triggered();

 void on_actionReactorBankPlacement_triggered();

 void on_actionResistorPlacement_triggered();

 void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Project *ui;
    int getJobID();


    bool connectSQLite();
};
