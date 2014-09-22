#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
namespace db
{
    class ISQLDatabase;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionOpen_2_triggered();

private:
    Ui::MainWindow *ui;
    bool connectSQLite();
    QString status;

};

#endif // MAINWINDOW_H
