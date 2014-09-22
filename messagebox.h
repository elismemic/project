#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>

namespace Ui {
class messageBox;
}

class messageBox : public QDialog
{
    Q_OBJECT

public:
    explicit messageBox(int i = 0, QWidget *parent = 0);
    ~messageBox();

    bool checkBox;
    void existMessage();
    void saveMessage();
    void noConnMessage();
    void wrondIDMessage();

private slots:
    void on_ok_clicked();

    void on_checkBox_toggled(bool checked);

private:
    Ui::messageBox *ui;

};

#endif // MESSAGEBOX_H
