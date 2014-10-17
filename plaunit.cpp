#include "plaunit.h"
#include "ui_plaunit.h"


plaUnit::plaUnit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plaUnit)
{
    ui->setupUi(this);
}

plaUnit::~plaUnit()
{
    delete ui;
}

void plaUnit::setSystemID(MyModel *n, int a, int b)
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

void plaUnit::setJobID(int jobID)
{
    if(jobID == 0)
    {
    // QString str = QString::number(jobID);
    this->setWindowTitle("Generating Unit Placement (Job ID: None)");
    }
    else
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Generating Unit Placement (Job ID: " + str + ")");
    }
}

void plaUnit::setProducer(MyModel *n, int a, int b)
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
    // ui->producerComboBox->setModel(n);
    // ui->producerComboBox->setCurrentIndex(a- 1);
}

void plaUnit::setDisabledID(const QString n)
{
    ui->uidLineEdit->setText(n);
    ui->uidLineEdit->setDisabled(true);
}

void plaUnit::setID(const int n)
{
    QString qStr = QString::number(n);
    ui->uidLineEdit->setText(qStr);
}

void plaUnit::setName(const QString n, int b)
{
     if(b == 1)
         ui->nameLineEdit->setText(n);
     else
     {
         ui->nameLineEdit->setText(n);
         ui->nameLineEdit->setDisabled(true);
     }
}

void plaUnit::setAliasName(const QString n, int b)
{
    if(b == 1)
     ui->aliasLineEdit->setText(n);
    else
    {
        ui->aliasLineEdit->setText(n);
        ui->aliasLineEdit->setDisabled(true);
    }
}

void plaUnit::setPhaseCode(MyModel* n, int ind, int b)
{
    if(b == 1)
    {
        ui->phaseComboBox->setModel(n);
        ui->phaseComboBox->setCurrentIndex(ind);
    }
    else
    {
        ui->phaseComboBox->setModel(n);
        ui->phaseComboBox->setCurrentIndex(ind);
        ui->phaseComboBox->setDisabled(true);
    }
}

void plaUnit::setCatalogType(MyModel* n, int ind, int b)
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

void plaUnit::setNodeType(MyModel* n, int ind, int b)
{

    if(b == 1)
    {
        ui->nodeComboBox->setModel(n);
        ui->nodeComboBox->setCurrentIndex(ind);
    }
    else
    {
        ui->nodeComboBox->setModel(n);
        ui->nodeComboBox->setCurrentIndex(ind);
        ui->nodeComboBox->setDisabled(true);
    }
}

void plaUnit::setLoadType(MyModel* n, int ind, int b)
{
    if(b == 1)
    {
        ui->loadComboBox->setModel(n);
        ui->loadComboBox->setCurrentIndex(ind);
    }
    else
    {
        ui->loadComboBox->setModel(n);
        ui->loadComboBox->setCurrentIndex(ind);
        ui->loadComboBox->setDisabled(true);
    }
}

void plaUnit::setLoadDemand(MyModel* n, int ind, int b)
{
    if(b == 1)
    {
        ui->loadDemandComboBox->setModel(n);
        ui->loadDemandComboBox->setCurrentIndex(ind);
    }
    else
    {
        ui->loadDemandComboBox->setModel(n);
        ui->loadDemandComboBox->setCurrentIndex(ind);
        ui->loadDemandComboBox->setDisabled(true);
    }
}

void plaUnit::setdes(const float n, int b)
{
    if(b == 1)
    {
        QString qStr = QString::number(n);
        ui->desiredLineEdit->setText(qStr);
    }
    else
    {
        QString qStr = QString::number(n);
        ui->desiredLineEdit->setText(qStr);
        ui->desiredLineEdit->setDisabled(true);
    }

}

void plaUnit::setr(const float n, int b)
{
    if(b == 1)
    {
        QString qStr = QString::number(n);
        ui->rLineEdit->setText(qStr);
    }
    else
    {
        QString qStr = QString::number(n);
        ui->rLineEdit->setText(qStr);
        ui->rLineEdit->setDisabled(true);
    }
}

void plaUnit::setx(const float n, int b)
{
    if(b == 1)
    {
        QString qStr = QString::number(n);
        ui->xLineEdit->setText(qStr);
    }
    else
    {
        QString qStr = QString::number(n);
        ui->xLineEdit->setText(qStr);
        ui->xLineEdit->setDisabled(true);
    }
}

void plaUnit::setDescription(const QString n, int b)
{
     if(b == 1)
         ui->descriptionTextEdit->setText(n);
     else
     {
         ui->descriptionTextEdit->setText(n);
         ui->descriptionTextEdit->setDisabled(true);
     }
}


QString plaUnit::systemName()
{
    return ui->systemComboBox->currentText();
}

int plaUnit::typeID() const
{
    return 31;
}

QString plaUnit::prodName()
{
    return ui->producerComboBox->currentText();
}

int plaUnit::id() const
{
    int num = ui->uidLineEdit->text().toInt();
    return num;
}

QString plaUnit::name() const
{
    return ui->nameLineEdit->text();
}

QString plaUnit::aliasName() const
{
    return ui->aliasLineEdit->text();
}

int plaUnit::phaseCode() const
{
   return ui->phaseComboBox->currentIndex();
}

int plaUnit::catalogType() const
{
    return ui->catalogComboBox->currentIndex();
}

int plaUnit::nodeType() const
{
    return ui->nodeComboBox->currentIndex();
}

int plaUnit::loadType() const
{
    return ui->loadComboBox->currentIndex();
}

int plaUnit::loadDemand() const
{
    return ui->loadDemandComboBox->currentIndex();
}

float plaUnit::des() const
{
    float num = ui->desiredLineEdit->text().toFloat();
    return num;
}

int plaUnit::grounded() const
{
    return ui->groundedComboBox->currentIndex();
}

float plaUnit::r() const
{
    float num = ui->rLineEdit->text().toFloat();
    return num;
}

float plaUnit::x() const
{
    float num = ui->xLineEdit->text().toFloat();
    return num;
}

QString plaUnit::description() const
{
    return ui->descriptionTextEdit->toPlainText();
}

void plaUnit::on_buttonBox_accepted()
{
    QDialog::accept();
}

void plaUnit::on_buttonBox_rejected()
{
    QDialog::reject();
}
