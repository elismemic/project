#include "plamotor.h"
#include "ui_plamotor.h"


plaMotor::plaMotor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plaMotor)
{
    ui->setupUi(this);
}

plaMotor::~plaMotor()
{
    delete ui;
}

void plaMotor::setSystemID(MyModel *n, int a)
{
    ui->systemComboBox->setModel(n);
    ui->systemComboBox->setCurrentIndex(a);
}

void plaMotor::setJobID(int jobID)
{
    if(jobID == 0)
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Asynchronous Motor Placement (Job ID: None)");
    }
    else
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Asynchronous Motor Placement (Job ID: " + str + ")");
    }
}

void plaMotor::setProducer(MyModel *n, int a)
{
    ui->producerComboBox->setModel(n);
    ui->producerComboBox->setCurrentIndex(a- 1);
}

void plaMotor::setID(const int n)
{
    QString qStr = QString::number(n);
    ui->uidLineEdit->setText(qStr);
}

void plaMotor::setDisabledID(const QString n)
{
    ui->uidLineEdit->setText(n);
    ui->uidLineEdit->setDisabled(true);
}

void plaMotor::setName(const QString n)
{
     ui->nameLineEdit->setText(n);
}

void plaMotor::setAliasName(const QString n)
{
     ui->aliasLineEdit->setText(n);
}

void plaMotor::setPhaseCode(MyModel* n, int a)
{
     ui->phaseCodeCombo->setModel(n);
     ui->phaseCodeCombo->setCurrentIndex(a);
}

void plaMotor::setCatalogType(MyModel* n, int a)
{
     ui->catalogTypeCombo->setModel(n);
     ui->catalogTypeCombo->setCurrentIndex(a);
}

void plaMotor::setConnectionType(MyModel* n, int a)
{
     ui->connectionTypeCombo->setModel(n);
     ui->connectionTypeCombo->setCurrentIndex(a);
}

void plaMotor::setDescription(const QString n)
{
     ui->descriptionTextEdit->setText(n);
}

QString plaMotor::systemName()
{
    return ui->systemComboBox->currentText();
}

int plaMotor::typeID() const
{
    return 33;
}

QString plaMotor::prodName()
{
    return ui->producerComboBox->currentText();
}

int plaMotor::id() const
{
    int num = ui->uidLineEdit->text().toInt();
    return num;
}

QString plaMotor::name() const
{
    return ui->nameLineEdit->text();
}

QString plaMotor::aliasName() const
{
    return ui->aliasLineEdit->text();
}

int plaMotor::idPhaseCode() const
{
    return ui->phaseCodeCombo->currentIndex();
}

int plaMotor::idCatalogType() const
{
    return ui->catalogTypeCombo->currentIndex();
}

int plaMotor::idConnectionType() const
{
    return ui->connectionTypeCombo->currentIndex();
}

QString plaMotor::description() const
{
    return ui->descriptionTextEdit->toPlainText();
}

void plaMotor::on_buttonBox_accepted()
{
    QDialog::accept();
}

void plaMotor::on_buttonBox_rejected()
{
    QDialog::reject();
}
