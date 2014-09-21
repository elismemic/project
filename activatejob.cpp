#include "activatejob.h"
#include "ui_activatejob.h"

activatejob::activatejob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::activatejob)
{
    ui->setupUi(this);
}

activatejob::~activatejob()
{
    delete ui;
}
