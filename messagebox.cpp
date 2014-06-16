#include "messagebox.h"
#include "ui_messagebox.h"

messageBox::messageBox(int i, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messageBox)
{
    ui->setupUi(this);

//adsds
    if(i == 1)
    {
        this->setWindowTitle("Error");
        existMessage();
    }
    else if(i == 2)
    {
        this->setWindowTitle("Successful!");
        saveMessage();
    }

    else if(i == 3)
    {
        this->setWindowTitle("Error");
        wrondIDMessage();
    }
    else
    {
        this->setWindowTitle("Error");
        noConnMessage();
    }
}

messageBox::~messageBox()
{
    delete ui;
}

void messageBox::existMessage()
{
    ui->label->setText("This ID already exists !");
}

void messageBox::saveMessage()
{
    ui->label->setText("Form successfully saved into database");
}

void messageBox::noConnMessage()
{
    ui->label->setText("Connection to database failed!");
}

void messageBox::wrondIDMessage()
{
    ui->label->setText("Job Id cannot be 0!");
}

void messageBox::on_buttonBox_accepted()
{
    QDialog::accept();
}

void messageBox::on_buttonBox_rejected()
{
    this->close();
}
