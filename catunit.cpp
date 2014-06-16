#include "catUnit.h"
#include "ui_catUnit.h"


catUnit::catUnit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::catUnit)
{
    ui->setupUi(this);
}

catUnit::~catUnit()
{
    delete ui;
}

void catUnit::setJobID(const int jobID)
{
    if(jobID == 0)
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Generating Unit Catalog (Job ID: None)");
    }
    else
    {
    QString str = QString::number(jobID);
    this->setWindowTitle("Generating Unit Catalog (Job ID: " + str + ")" );
    }
}

void catUnit::setProducer(MyModel *n, int a)
{
    ui->producerComboBox->setModel(n);
    ui->producerComboBox->setCurrentIndex(a - 1);
}

void catUnit::setID(const int n)
{
    QString qStr = QString::number(n);
    ui->uidLineEdit->setText(qStr);
}

void catUnit::setID2(const QString n)
{
    ui->uidLineEdit->setText(n);
    ui->uidLineEdit->setDisabled(true);
}

void catUnit::setName(const QString n)
{
     ui->nameLineEdit->setText(n);
}

void catUnit::setAliasName(const QString n)
{
     ui->aliasLineEdit->setText(n);
}

void catUnit::setRatedVoltage(MyModel* n, int i)
{
    ui->ratedVoltageComboBox->setModel(n);
    ui->ratedVoltageComboBox->setCurrentIndex(i);
}

void catUnit::setRatedPower(MyModel* n, int i)
{
    ui->ratedPowerComboBox->setModel(n);
    ui->ratedPowerComboBox->setCurrentIndex(i);
}

void catUnit::setNumberOfPhases(MyModel *n, int i)
{
    ui->numberOfPhasesComboBox->setModel(n);
    ui->numberOfPhasesComboBox->setCurrentIndex(i);
}

void catUnit::setConnectionType(MyModel* n, int i)
{
     ui->connectionComboBox->setModel(n);
     ui->connectionComboBox->setCurrentIndex(i);
}

void catUnit::setminOpAcPow(const float n)
{
    QString qStr = QString::number(n);
    ui->pminLineEdit->setText(qStr);
}

void catUnit::setmaxOpAcPow(const float n)
{
    QString qStr = QString::number(n);
    ui->pmaxLineEdit->setText(qStr);
}

void catUnit::setminOpRPow(const float n)
{
    QString qStr = QString::number(n);
    ui->qminLineEdit->setText(qStr);
}

void catUnit::setmaxOpRPow(const float n)
{
    QString qStr = QString::number(n);
    ui->qmaxLineEdit->setText(qStr);
}

void catUnit::setZ0_re(const float n)
{
    QString qStr = QString::number(n);
    ui->steadyRZ0LineEdit->setText(qStr);
}

void catUnit::setZ0_im(const float n)
{
    QString qStr = QString::number(n);
    ui->steadyXZ0LineEdit->setText(qStr);
}

void catUnit::setZ1_re(const float n)
{
    QString qStr = QString::number(n);
    ui->steadyRZ1LineEdit->setText(qStr);
}

void catUnit::setZ1_im(const float n)
{
    QString qStr = QString::number(n);
    ui->steadyXZ1LineEdit->setText(qStr);
}

void catUnit::setZ2_re(const float n)
{
    QString qStr = QString::number(n);
    ui->steadyRZ2LineEdit->setText(qStr);
}

void catUnit::setZ2_im(const float n)
{
    QString qStr = QString::number(n);
    ui->steadyXZ2LineEdit->setText(qStr);
}

void catUnit::setZ0trans_re(const float n)
{
    QString qStr = QString::number(n);
    ui->transientRZ0LineEdit->setText(qStr);
}

void catUnit::setZ0trans_im(const float n)
{
    QString qStr = QString::number(n);
    ui->transientXZ0LineEdit->setText(qStr);
}

void catUnit::setZ1trans_re(const float n)
{
    QString qStr = QString::number(n);
    ui->transientRZ1LineEdit->setText(qStr);
}

void catUnit::setZ1trans_im(const float n)
{
    QString qStr = QString::number(n);
    ui->transientXZ1LineEdit->setText(qStr);
}

void catUnit::setZ2trans_re(const float n)
{
    QString qStr = QString::number(n);
    ui->transientRZ2LineEdit->setText(qStr);
}

void catUnit::setZ2trans_im(const float n)
{
    QString qStr = QString::number(n);
    ui->transientXZ2LineEdit->setText(qStr);
}

void catUnit::setZ0sub_re(const float n)
{
    QString qStr = QString::number(n);
    ui->subtransientRZ0LineEdit->setText(qStr);
}

void catUnit::setZ0sub_im(const float n)
{
    QString qStr = QString::number(n);
    ui->subtransientXZ0LineEdit->setText(qStr);
}

void catUnit::setZ1sub_re(const float n)
{
    QString qStr = QString::number(n);
    ui->subtransientRZ1LineEdit->setText(qStr);
}

void catUnit::setZ1sub_im(const float n)
{
    QString qStr = QString::number(n);
    ui->subtransientXZ1LineEdit->setText(qStr);
}

void catUnit::setZ2sub_re(const float n)
{
    QString qStr = QString::number(n);
    ui->subtransientRZ2LineEdit->setText(qStr);
}

void catUnit::setZ2sub_im(const float n)
{
    QString qStr = QString::number(n);
    ui->subtransientXZ2LineEdit->setText(qStr);
}

void catUnit::setDescription(const QString n)
{
     ui->descriptionTextEdit->setText(n);
}

int catUnit::typeID() const
{
    return 18;
}

QString catUnit::prodName()
{
    return ui->producerComboBox->currentText();
}

int catUnit::id() const
{
    int num = ui->uidLineEdit->text().toInt();
    return num;
}

QString catUnit::name() const
{
    return ui->nameLineEdit->text();
}

QString catUnit::aliasName() const
{
    return ui->aliasLineEdit->text();
}

int catUnit::idRatedVol() const
{
    return ui->ratedVoltageComboBox->currentIndex();
}

int catUnit::idRatedPower() const
{
    return ui->ratedPowerComboBox->currentIndex();
}

int catUnit::idNumberOfPhases() const
{
    return  ui->numberOfPhasesComboBox->currentIndex();
}

int catUnit::idConnectionType() const
{
    return ui->connectionComboBox->currentIndex();
}

float catUnit::minOpAcPow() const
{
    float num = ui->pminLineEdit->text().toFloat();
    return num;
}

float catUnit::maxOpAcPow() const
{
    float num = ui->pmaxLineEdit->text().toFloat();
    return num;
}

float catUnit::minOpRPow() const
{
    float num = ui->qminLineEdit->text().toFloat();
    return num;
}

float catUnit::maxOpRPow() const
{
    float num = ui->qmaxLineEdit->text().toFloat();
    return num;
}
float catUnit::Z0_re() const
{
    float num = ui->steadyRZ0LineEdit->text().toFloat();
    return num;
}

float catUnit::Z0_im() const
{
    float num = ui->steadyXZ0LineEdit->text().toFloat();
    return num;
}

float catUnit::Z1_re() const
{
    float num = ui->steadyRZ1LineEdit->text().toFloat();
    return num;
}

float catUnit::Z1_im() const
{
    float num = ui->steadyXZ1LineEdit->text().toFloat();
    return num;
}
float catUnit::Z2_re() const
{
    float num = ui->steadyRZ2LineEdit->text().toFloat();
    return num;
}

float catUnit::Z2_im() const
{
    float num = ui->steadyXZ2LineEdit->text().toFloat();
    return num;
}

float catUnit::Z0trans_re() const
{
    float num = ui->transientRZ0LineEdit->text().toFloat();
    return num;
}

float catUnit::Z0trans_im() const
{
    float num = ui->transientXZ0LineEdit->text().toFloat();
    return num;
}

float catUnit::Z1trans_re() const
{
    float num = ui->transientRZ1LineEdit->text().toFloat();
    return num;
}

float catUnit::Z1trans_im() const
{
    float num = ui->transientXZ1LineEdit->text().toFloat();
    return num;
}

float catUnit::Z2trans_re() const
{
    float num = ui->transientRZ2LineEdit->text().toFloat();
    return num;
}

float catUnit::Z2trans_im() const
{
    float num = ui->transientXZ2LineEdit->text().toFloat();
    return num;
}

float catUnit::Z0sub_re() const
{
    float num = ui->subtransientRZ0LineEdit->text().toFloat();
    return num;
}

float catUnit::Z0sub_im() const
{
    float num = ui->subtransientXZ0LineEdit->text().toFloat();
    return num;
}

float catUnit::Z1sub_re() const
{
    float num = ui->subtransientRZ1LineEdit->text().toFloat();
    return num;
}

float catUnit::Z1sub_im() const
{
    float num = ui->subtransientXZ1LineEdit->text().toFloat();
    return num;
}

float catUnit::Z2sub_re() const
{
    float num = ui->subtransientRZ2LineEdit->text().toFloat();
    return num;
}

float catUnit::Z2sub_im() const
{
    float num = ui->subtransientXZ2LineEdit->text().toFloat();
    return num;
}

QString catUnit::description() const
{
    return ui->descriptionTextEdit->toPlainText();
}

void catUnit::on_buttonBox_accepted()
{
    QDialog::accept();
}

void catUnit::on_buttonBox_rejected()
{
    QDialog::reject();
}
