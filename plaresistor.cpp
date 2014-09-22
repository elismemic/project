#include "plaresistor.h"
#include "ui_plaresistor.h"


plaResistor::plaResistor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plaResistor)
{
    ui->setupUi(this);
}

plaResistor::~plaResistor()
{
    delete ui;
}

void plaResistor::setSystemID(MyModel *n, int a, int b)
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

void plaResistor::setJobID(int jobID)
{
    if(jobID == 0)
    {
    // QString str = QString::number(jobID);
    this->setWindowTitle("Shunt Resistor Placement (Job ID: None)");
    }
    else
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Shunt Resistor Placement (Job ID: " + str + ")");
    }
}

void plaResistor::setProducer(MyModel *n, int a, int b)
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

void plaResistor::setID(const int n)
{
    QString qStr = QString::number(n);
    ui->uidLineEdit->setText(qStr);
}

void plaResistor::setDisabledID(const QString n)
{
    ui->uidLineEdit->setText(n);
    ui->uidLineEdit->setDisabled(true);
}

void plaResistor::setName(const QString n, int b)
{
     if(b == 1)
         ui->nameLineEdit->setText(n);
     else
     {
         ui->nameLineEdit->setText(n);
         ui->nameLineEdit->setDisabled(true);
     }
}

void plaResistor::setAliasName(const QString n, int b)
{
    if(b == 1)
     ui->aliasLineEdit->setText(n);
    else
    {
        ui->aliasLineEdit->setText(n);
        ui->aliasLineEdit->setDisabled(true);
    }
}

void plaResistor::setCatalogType(MyModel* n, int ind, int b)
{
     if(b == 1)
     {
         ui->catalogComboBox->setModel(n);
         ui->catalogComboBox->setCurrentIndex(ind);
     }
     else
     {
         ui->catalogComboBox->setModel(n);
         ui->catalogComboBox->setCurrentIndex(ind);
         ui->catalogComboBox->setDisabled(true);
     }
}

void plaResistor::setDescription(const QString n, int b)
{
     if(b == 1)
         ui->descriptionTextEdit->setText(n);
     else
     {
         ui->descriptionTextEdit->setText(n);
         ui->descriptionTextEdit->setDisabled(true);
     }
}

QString plaResistor::systemName()
{
    return ui->systemComboBox->currentText();
}

int plaResistor::typeID() const
{
    return 34;
}

QString plaResistor::prodName()
{
    return ui->producerComboBox->currentText();
}

int plaResistor::ID() const
{
    int num = ui->uidLineEdit->text().toInt();
    return num;
}

QString plaResistor::name() const
{
    return ui->nameLineEdit->text();
}

QString plaResistor::aliasName() const
{
    return ui->aliasLineEdit->text();
}

int plaResistor::idCatalogType() const
{
    int num = 1 + ui->catalogComboBox->currentIndex();
    return num;
}

QString plaResistor::description() const
{
    return ui->descriptionTextEdit->toPlainText();
}

void plaResistor::on_buttonBox_accepted()
{
    QDialog::accept();
}

void plaResistor::on_buttonBox_rejected()
{
    QDialog::reject();
}
