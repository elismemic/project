#ifndef ACTIVATEJOB_H
#define ACTIVATEJOB_H

#include <QDialog>

namespace Ui {
class activatejob;
}

class activatejob : public QDialog
{
    Q_OBJECT

public:
    explicit activatejob(QWidget *parent = 0);
    ~activatejob();

private:
    Ui::activatejob *ui;
};

#endif // ACTIVATEJOB_H
