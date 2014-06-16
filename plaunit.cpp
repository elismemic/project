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

void plaUnit::setSystemID(MyModel *n, int a)
{
    ui->systemComboBox->setModel(n);
    ui->systemComboBox->setCurrentIndex(a- 1);
}

void plaUnit::setJobID(int jobID)
{
    if(jobID == 0)
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Generating Unit Placement (Job ID: None)");
    }
    else
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Generating Unit Placement (Job ID: " + str + ")");
    }
}

void plaUnit::setProducer(MyModel *n, int a)
{
    ui->producerComboBox->setModel(n);
    ui->producerComboBox->setCurrentIndex(a- 1);
}

void plaUnit::setID2(const QString n)
{
    ui->uidLineEdit->setText(n);
    ui->uidLineEdit->setDisabled(true);
}

void plaUnit::setID(const int n)
{
    QString qStr = QString::number(n);
    ui->uidLineEdit->setText(qStr);
}

void plaUnit::setName(const QString n)
{
     ui->nameLineEdit->setText(n);
}

void plaUnit::setAliasName(const QString n)
{
     ui->aliasLineEdit->setText(n);
}

void plaUnit::setPhaseCode(MyModel *n, int a)
{
    ui->phaseComboBox->setModel(n);
    ui->phaseComboBox->setCurrentIndex(a);
}

void plaUnit::setCatalogType(MyModel *n, int a)
{
    ui->catalogComboBox->setModel(n);
    ui->catalogComboBox->setCurrentIndex(a);
}

void plaUnit::setNodeType(MyModel *n, int a)
{
    ui->nodeComboBox->setModel(n);
    ui->nodeComboBox->setCurrentIndex(a);
}

void plaUnit::setLoadType(MyModel *n, int a)
{
    ui->loadComboBox->setModel(n);
    ui->loadComboBox->setCurrentIndex(a);
}

void plaUnit::setLoadDemand(MyModel *n, int a)
{
    ui->loadDemandComboBox->setModel(n);
    ui->loadDemandComboBox->setCurrentIndex(a);
}

void plaUnit::setdes(const float n)
{
    QString qStr = QString::number(n);
    ui->desiredLineEdit->setText(qStr);
}

void plaUnit::setr(const float n)
{
    QString qStr = QString::number(n);
    ui->rLineEdit->setText(qStr);
}

void plaUnit::setx(const float n)
{
    QString qStr = QString::number(n);
    ui->xLineEdit->setText(qStr);
}

void plaUnit::setDescription(const QString n)
{
     ui->descriptionTextEdit->setText(n);
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
