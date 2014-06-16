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

void catMotor::setProducer(MyModel *n, int a)
{
    ui->producerComboBox->setModel(n);
    ui->producerComboBox->setCurrentIndex(a- 1);
}

void catMotor::setID(const int n)
{
    QString qStr = QString::number(n);
    ui->uidLineEdit->setText(qStr);
}

void catMotor::setID2(const QString n)
{
    ui->uidLineEdit->setText(n);
    ui->uidLineEdit->setDisabled(true);
}

void catMotor::setName(const QString n)
{
     ui->nameLineEdit->setText(n);
}

void catMotor::setAliasName(const QString n)
{
     ui->aliasLineEdit->setText(n);
}

void catMotor::setRatedVoltage(MyModel *n, int a)
{
    ui->ratedVoltageCombo->setModel(n);
    ui->ratedVoltageCombo->setCurrentIndex(a);
}

void catMotor::setNumberOfPhases(MyModel *n, int a)
{
    ui->numberofphasesCombo->setModel(n);
    ui->numberofphasesCombo->setCurrentIndex(a);
}

void catMotor::setnmp(const float n)
{
    QString qStr = QString::number(n);
    ui->nominalLineEdit->setText(qStr);
}

void catMotor::setpow(const float n)
{
    QString qStr = QString::number(n);
    ui->powerLineEdit->setText(qStr);
}

void catMotor::seteff(const float n)
{
    QString qStr = QString::number(n);
    ui->efficiencyLineEdit->setText(qStr);
}

void catMotor::setload(const float n)
{
    QString qStr = QString::number(n);
    ui->loadLineEdit->setText(qStr);
}

void catMotor::setrpm(const int n)
{
    QString qStr = QString::number(n);
    ui->rpmLineEdit->setText(qStr);
}

void catMotor::setisu(const float n)
{
    QString qStr = QString::number(n);
    ui->istartLineEdit->setText(qStr);
}

void catMotor::setrx(const float n)
{
    QString qStr = QString::number(n);
    ui->rxLineEdit->setText(qStr);
}

void catMotor::setDescription(const QString n)
{
     ui->descriptionTextEdit->setText(n);
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
