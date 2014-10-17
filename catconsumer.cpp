#include "catConsumer.h"
#include "ui_catConsumer.h"

catConsumer::catConsumer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::catConsumer)
{
    ui->setupUi(this);
}

catConsumer::~catConsumer()
{
    delete ui;
}

void catConsumer::setJobID(int jobID)
{
    if(jobID == 0)
    {
    // QString str = QString::number(jobID);
    this->setWindowTitle("Energy Consumer Catalog (Job ID: None)");
    }
    else
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Energy Consumer Catalog (Job ID: " + str + ")");
    }
}

void catConsumer::setProducer(MyModel *n, int a, int b)
{
    if(b == 1)
    {
        ui->producerComboBox->setModel(n);
        ui->producerComboBox->setCurrentIndex(a);
    }
    else
    {
        ui->producerComboBox->setModel(n);
        ui->producerComboBox->setCurrentIndex(a);
        ui->producerComboBox->setDisabled(true);
    }
}

void catConsumer::setID(const int n)
{
    QString qStr = QString::number(n);
    ui->uidLineEdit->setText(qStr);
}

void catConsumer::setDisabledID(const QString n)
{
    ui->uidLineEdit->setText(n);
    ui->uidLineEdit->setDisabled(true);
}

void catConsumer::setName(const QString n, int b)
{
    if(b == 1)
        ui->nameLineEdit->setText(n);
    else
    {
        ui->nameLineEdit->setText(n);
        ui->nameLineEdit->setDisabled(true);
    }
}

void catConsumer::setAliasName(const QString n, int b)
{
    if(b == 1)
     ui->aliasLineEdit->setText(n);
    else
    {
        ui->aliasLineEdit->setText(n);
        ui->aliasLineEdit->setDisabled(true);
    }
}

void catConsumer::setDescription(const QString n, int b)
{
    if(b == 1)
        ui->descriptionTextEdit->setText(n);
    else
    {
        ui->descriptionTextEdit->setText(n);
        ui->descriptionTextEdit->setDisabled(true);
    }
}

void catConsumer::setRatedVoltage(MyModel *n, int ind, int b)
{
    if(b == 1)
    {
        ui->ratedVoltageCombo->setModel(n);
        ui->ratedVoltageCombo->setCurrentIndex(ind);
    }
    else
    {
        ui->ratedVoltageCombo->setModel(n);
        ui->ratedVoltageCombo->setCurrentIndex(ind);
        ui->ratedVoltageCombo->setDisabled(true);
    }
}

void catConsumer::setKP0(const float n, int b)
{
    if(b == 1)
    {
        QString qStr = QString::number(n);
        ui->kP0LineEdit->setText(qStr);
    }
    else
    {
        QString qStr = QString::number(n);
        ui->kP0LineEdit->setText(qStr);
        ui->kP0LineEdit->setDisabled(true);
    }

}

void catConsumer::setKQ0(const float n, int b)
{
    if(b == 1)
    {
        QString qStr = QString::number(n);
        ui->kQ0LineEdit->setText(qStr);
    }
    else
    {
        QString qStr = QString::number(n);
        ui->kQ0LineEdit->setText(qStr);
        ui->kQ0LineEdit->setDisabled(true);
    }
}

void catConsumer::setKP1(const float n, int b)
{
    if(b == 1)
    {
        QString qStr = QString::number(n);
        ui->kP1LineEdit->setText(qStr);
    }
    else
    {
        QString qStr = QString::number(n);
        ui->kP1LineEdit->setText(qStr);
        ui->kP1LineEdit->setDisabled(true);
    }
}

void catConsumer::setKQ1(const float n, int b)
{
    if(b == 1)
    {
        QString qStr = QString::number(n);
        ui->kQ1LineEdit->setText(qStr);
    }
    else
    {
        QString qStr = QString::number(n);
        ui->kQ1LineEdit->setText(qStr);
        ui->kQ1LineEdit->setDisabled(true);
    }
}

void catConsumer::setKP2(const float n, int b)
{
    if(b == 1)
    {
        QString qStr = QString::number(n);
        ui->kP2LineEdit->setText(qStr);
    }
    else
    {
        QString qStr = QString::number(n);
        ui->kP2LineEdit->setText(qStr);
        ui->kP2LineEdit->setDisabled(true);
    }
}

void catConsumer::setKQ2(const float n, int b)
{
    if(b == 1)
    {
        QString qStr = QString::number(n);
        ui->kQ2LineEdit->setText(qStr);
    }
    else
    {
        QString qStr = QString::number(n);
        ui->kQ2LineEdit->setText(qStr);
        ui->kQ2LineEdit->setDisabled(true);
    }
}

int catConsumer::typeID() const
{
    return 17;
}

QString catConsumer::prodName()
{
    return ui->producerComboBox->currentText();
}

int catConsumer::id() const
{
    int num = ui->uidLineEdit->text().toInt();
    return num;
}

QString catConsumer::name() const
{
    return ui->nameLineEdit->text();
}

QString catConsumer::aliasName() const
{
    return ui->aliasLineEdit->text();
}

QString catConsumer::description() const
{
    return ui->descriptionTextEdit->toPlainText();
}

int catConsumer::idRatedVol() const
{
    return ui->ratedVoltageCombo->currentIndex();
}

float catConsumer::kP0() const
{
    float num = ui->kP0LineEdit->text().toFloat();
    return num;
}
float catConsumer::kQ0() const
{
    float num = ui->kQ0LineEdit->text().toFloat();
    return num;
}
float catConsumer::kP1() const
{
    float num = ui->kP1LineEdit->text().toFloat();
    return num;
}
float catConsumer::kQ1() const
{
    float num = ui->kQ1LineEdit->text().toFloat();
    return num;
}
float catConsumer::kP2() const
{
    float num = ui->kP2LineEdit->text().toFloat();
    return num;
}
float catConsumer::kQ2() const
{
    float num = ui->kQ2LineEdit->text().toFloat();
    return num;
}

void catConsumer::on_buttonBox_accepted()
{
    QDialog::accept();
}

void catConsumer::on_buttonBox_rejected()
{
    QDialog::reject();
}
