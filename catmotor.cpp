#include "catmotor.h"
#include "ui_catmotor.h"


catMotor::catMotor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::catMotor)
{
    ui->setupUi(this);
}

catMotor::~catMotor()
{
    delete ui;
}

void catMotor::setJobID(int jobID)
{
    if(jobID == 0)
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Asynchronous Motor Catalog (Job ID: None)");
    }
    else
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Asynchronous Motor Catalog (Job ID: " + str + ")");
    }
}

void catMotor::setProducer(MyModel *n, int a, int b)
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

void catMotor::setID(const int n)
{
    QString qStr = QString::number(n);
    ui->uidLineEdit->setText(qStr);
}

void catMotor::setDisabledID(const QString n)
{
    ui->uidLineEdit->setText(n);
    ui->uidLineEdit->setDisabled(true);
}

void catMotor::setName(const QString n, int b)
{
    if(b == 1)
     ui->nameLineEdit->setText(n);
    else
    {
        ui->nameLineEdit->setText(n);
        ui->nameLineEdit->setDisabled(true);
    }

}

void catMotor::setAliasName(const QString n, int b)
{
    if(b == 1)
     ui->aliasLineEdit->setText(n);
    else
    {
        ui->aliasLineEdit->setText(n);
        ui->aliasLineEdit->setDisabled(true);
    }
}

void catMotor::setRatedVoltage(MyModel *n, int a, int b)
{
    if(b == 1)
    {
    ui->ratedVoltageCombo->setModel(n);
    ui->ratedVoltageCombo->setCurrentIndex(a);
    }
    else
    {
    ui->ratedVoltageCombo->setModel(n);
    ui->ratedVoltageCombo->setCurrentIndex(a);
    ui->ratedVoltageCombo->setDisabled(true);
    }
}

void catMotor::setNumberOfPhases(MyModel *n, int a, int b)
{
    if(b == 1)
    {
    ui->numberofphasesCombo->setModel(n);
    ui->numberofphasesCombo->setCurrentIndex(a);
    }
    else
    {
    ui->numberofphasesCombo->setModel(n);
    ui->numberofphasesCombo->setCurrentIndex(a);
    ui->numberofphasesCombo->setDisabled(true);
    }
}

void catMotor::setnmp(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->nominalLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->nominalLineEdit->setText(qStr);
    ui->nominalLineEdit->setDisabled(true);
    }
}

void catMotor::setpow(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->powerLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->powerLineEdit->setText(qStr);
    ui->powerLineEdit->setDisabled(true);
    }
}

void catMotor::seteff(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->efficiencyLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->efficiencyLineEdit->setText(qStr);
    ui->efficiencyLineEdit->setDisabled(true);
    }
}

void catMotor::setload(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->loadLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->loadLineEdit->setText(qStr);
    ui->loadLineEdit->setDisabled(true);
    }
}

void catMotor::setrpm(const int n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->rpmLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->rpmLineEdit->setText(qStr);
    ui->rpmLineEdit->setDisabled(true);
    }
}

void catMotor::setisu(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->istartLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->istartLineEdit->setText(qStr);
    ui->istartLineEdit->setDisabled(true);
    }
}

void catMotor::setrx(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->rxLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->rxLineEdit->setText(qStr);
    ui->rxLineEdit->setDisabled(true);
    }
}

void catMotor::setDescription(const QString n, int b)
{
    if(b == 1)
     ui->descriptionTextEdit->setText(n);
    else
    {
        ui->descriptionTextEdit->setText(n);
        ui->descriptionTextEdit->setDisabled(true);
    }
}

int catMotor::typeID() const
{
    return 19;
}

QString catMotor::prodName()
{
    return ui->producerComboBox->currentText();
}

int catMotor::id() const
{
    int num = ui->uidLineEdit->text().toInt();
    return num;
}

QString catMotor::name() const
{
    return ui->nameLineEdit->text();
}

QString catMotor::aliasName() const
{
    return ui->aliasLineEdit->text();
}

int catMotor::idRatedVol() const
{
    return ui->ratedVoltageCombo->currentIndex();
}

int catMotor::idNumberOfPhases() const
{
    return ui->numberofphasesCombo->currentIndex();
}

float catMotor::nmp() const
{
    float num = ui->nominalLineEdit->text().toFloat();
    return num;
}

float catMotor::pow() const
{
    float num = ui->powerLineEdit->text().toFloat();
    return num;
}

float catMotor::eff() const
{
    float num = ui->efficiencyLineEdit->text().toFloat();
    return num;
}
float catMotor::load() const
{
    float num = ui->loadLineEdit->text().toFloat();
    return num;
}
int catMotor::rpm() const
{
    int num = ui->rpmLineEdit->text().toInt();
    return num;
}
float catMotor::isu() const
{
    float num = ui->istartLineEdit->text().toFloat();
    return num;
}
float catMotor::rx() const
{
    float num = ui->rxLineEdit->text().toFloat();
    return num;
}

QString catMotor::description() const
{
    return ui->descriptionTextEdit->toPlainText();
}

void catMotor::on_buttonBox_accepted()
{
    QDialog::accept();
}

void catMotor::on_buttonBox_rejected()
{
    QDialog::reject();
}
