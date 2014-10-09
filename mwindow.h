#ifndef MWINDOW_H
#define MWINDOW_H

#include <QDialog>

namespace Ui {
class mWindow;
}

namespace db
{
    class ISQLDatabase;
}


class mWindow : public QDialog
{
    Q_OBJECT

public:
    explicit mWindow(QWidget *parent = 0);
    ~mWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::mWindow *ui;
    bool connectSQLite();
};

#endif // MWINDOW_H
