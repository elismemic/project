#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
extern int globalJobId;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
        int setJobId();
        int setSysId();

private slots:
    void on_actionBusbars_triggered();

    void on_actionCableHeads_triggered();

    void on_actionJumpers_triggered();

    void on_actionBosnian_triggered();

    void on_actionTurkish_triggered();

    void on_actionEquivalent_Source_triggered();

    void on_actionConnectivity_Node_triggered();

    //void on_actionSearch_Jobs_triggered();

    void on_pushButton_OK_clicked();

    void on_actionAbout_Software_triggered();

    void on_actionBusbar_Section_Vertical_triggered();

    void on_actionBusbar_Section_Horizontal_triggered();

    void on_actionBusbar_Free_Style_triggered();

    void on_actionCable_Had_triggered();

    void on_actionSource_Sink_Connector_triggered();

    void on_actionJumper_z_0_triggered();

private:
    Ui::MainWindow *ui;
    QTranslator trans;
    QString file;
    bool connectSQLite();
    void hideComponents();
    bool checkUser(QString username, QString password);
    void changeLanguageTo(QString lang);
    void changeEvent(QEvent *e);
    void setUserId(QString username);

};

#endif // MAINWINDOW_H
