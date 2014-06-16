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
    QString str = QString::number(jobID);
    this->setWindowTitle("Energy Consumer Catalog (Job ID: None)");
    }
    else
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Energy Consumer Catalog (Job ID: " + str + ")");
    }
}

void catConsumer::setProducer(MyModel *n, int a)
{
    ui->producerComboBox->setModel(n);
    ui->producerComboBox->setCurrentIndex(a - 1);
}

void catConsumer::setID(const int n)
{
    QString qStr = QString::number(n);
    ui->uidLineEdit->setText(qStr);
}

void catConsumer::setID2(const QString n)
{
    ui->uidLineEdit->setText(n);
    ui->uidLineEdit->setDisabled(true);
}

void catConsumer::setName(const QString n)
{
     ui->nameLineEdit->setText(n);
}

void catConsumer::setAliasName(const QString n)
{
     ui->aliasLineEdit->setText(n);
}

void catConsumer::setDescription(const QString n)
{
     ui->descriptionTextEdit->setText(n);
}

void catConsumer::setRatedVoltage(MyModel *n, int ind)
{
    ui->ratedVoltageCombo->setModel(n);
    ui->ratedVoltageCombo->setCurrentIndex(ind);
}

void catConsumer::setKP0(const float n)
{
    QString qStr = QString::number(n);
    ui->kP0LineEdit->setText(qStr);
}

void catConsumer::setKQ0(const float n)
{
    QString qStr = QString::number(n);
    ui->kQ0LineEdit->setText(qStr);
}

void catConsumer::setKP1(const float n)
{
    QString qStr = QString::number(n);
    ui->kP1LineEdit->setText(qStr);
}

void catConsumer::setKQ1(const float n)
{
    QString qStr = QString::number(n);
    ui->kQ1LineEdit->setText(qStr);
}

void catConsumer::setKP2(const float n)
{
    QString qStr = QString::number(n);
    ui->kP2LineEdit->setText(qStr);
}

void catConsumer::setKQ2(const float n)
{
    QString qStr = QString::number(n);
    ui->kQ2LineEdit->setText(qStr);
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
