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

    void existMessage();
    void saveMessage();
    void noConnMessage();
    void wrondIDMessage();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::messageBox *ui;
};

#endif // MESSAGEBOX_H
