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

void plaMotor::setSystemID(MyModel *n, int a, int b)
{
    if(b == 1)
    {
        ui->systemComboBox->setModel(n);
        ui->systemComboBox->setCurrentIndex(a);
    }
    else
    {
        ui->systemComboBox->setModel(n);
        ui->systemComboBox->setCurrentIndex(a);
        ui->systemComboBox->setDisabled(true);
    }

}

void plaMotor::setJobID(int jobID)
{
    if(jobID == 0)
    {
    // QString str = QString::number(jobID);
    this->setWindowTitle("Asynchronous Motor Placement (Job ID: None)");
    }
    else
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Asynchronous Motor Placement (Job ID: " + str + ")");
    }
}

void plaMotor::setProducer(MyModel *n, int a, int b)
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

void plaMotor::setName(const QString n, int b)
{
     if(b == 1)
         ui->nameLineEdit->setText(n);
     else
     {
         ui->nameLineEdit->setText(n);
         ui->nameLineEdit->setDisabled(true);
     }
}

void plaMotor::setAliasName(const QString n, int b)
{
    if(b == 1)
     ui->aliasLineEdit->setText(n);
    else
    {
        ui->aliasLineEdit->setText(n);
        ui->aliasLineEdit->setDisabled(true);
    }
}

void plaMotor::setPhaseCode(MyModel* n, int ind, int b)
{    
     if(b == 1)
     {
         ui->phaseCodeCombo->setModel(n);
         ui->phaseCodeCombo->setCurrentIndex(ind);
     }
     else
     {
         ui->phaseCodeCombo->setModel(n);
         ui->phaseCodeCombo->setCurrentIndex(ind);
         ui->phaseCodeCombo->setDisabled(true);
     }

}

void plaMotor::setCatalogType(MyModel* n, int ind, int b)
{
     if(b == 1)
     {
         ui->catalogTypeCombo->setModel(n);
         ui->catalogTypeCombo->setCurrentIndex(ind);
     }
     else
     {
         ui->catalogTypeCombo->setModel(n);
         ui->catalogTypeCombo->setCurrentIndex(ind);
         ui->catalogTypeCombo->setDisabled(true);
     }
}

void plaMotor::setConnectionType(MyModel* n, int ind, int b)
{

     if(b == 1)
     {
         ui->connectionTypeCombo->setModel(n);
         ui->connectionTypeCombo->setCurrentIndex(ind);
     }
     else
     {
         ui->connectionTypeCombo->setModel(n);
         ui->connectionTypeCombo->setCurrentIndex(ind);
         ui->connectionTypeCombo->setDisabled(true);
     }

}

void plaMotor::setDescription(const QString n, int b)
{
     if(b == 1)
         ui->descriptionTextEdit->setText(n);
     else
     {
         ui->descriptionTextEdit->setText(n);
         ui->descriptionTextEdit->setDisabled(true);
     }
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
