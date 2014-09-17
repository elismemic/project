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

void catUnit::setProducer(MyModel *n, int a, int b)
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

void catUnit::setID(const int n)
{
    QString qStr = QString::number(n);
    ui->uidLineEdit->setText(qStr);
}

void catUnit::setDisabledID(const QString n)
{
    ui->uidLineEdit->setText(n);
    ui->uidLineEdit->setDisabled(true);
}

void catUnit::setName(const QString n, int b)
{
    if(b == 1)
     ui->nameLineEdit->setText(n);
    else
    {
        ui->nameLineEdit->setText(n);
        ui->nameLineEdit->setDisabled(true);
    }
}

void catUnit::setAliasName(const QString n, int b)
{
    if(b == 1)
     ui->aliasLineEdit->setText(n);
    else
    {
        ui->aliasLineEdit->setText(n);
        ui->aliasLineEdit->setDisabled(true);
    }
}

void catUnit::setRatedVoltage(MyModel* n, int i, int b)
{
    if(b == 1)
    {
    ui->ratedVoltageComboBox->setModel(n);
    ui->ratedVoltageComboBox->setCurrentIndex(i);
    }
    else
    {
        ui->ratedVoltageComboBox->setModel(n);
        ui->ratedVoltageComboBox->setCurrentIndex(i);
        ui->ratedVoltageComboBox->setDisabled(true);
    }
}

void catUnit::setRatedPower(MyModel* n, int i, int b)
{
    if(b == 1)
    {
    ui->ratedPowerComboBox->setModel(n);
    ui->ratedPowerComboBox->setCurrentIndex(i);
    }
    else
    {
        ui->ratedPowerComboBox->setModel(n);
        ui->ratedPowerComboBox->setCurrentIndex(i);
        ui->ratedPowerComboBox->setDisabled(true);
    }

}

void catUnit::setNumberOfPhases(MyModel *n, int i, int b)
{
    if(b == 1)
    {
    ui->numberOfPhasesComboBox->setModel(n);
    ui->numberOfPhasesComboBox->setCurrentIndex(i);
    }
    else
    {
        ui->numberOfPhasesComboBox->setModel(n);
        ui->numberOfPhasesComboBox->setCurrentIndex(i);
        ui->numberOfPhasesComboBox->setDisabled(true);
    }
}

void catUnit::setConnectionType(MyModel* n, int i, int b)
{
    if(b == 1)
    {
     ui->connectionComboBox->setModel(n);
     ui->connectionComboBox->setCurrentIndex(i);
    }
    else
    {
     ui->connectionComboBox->setModel(n);
     ui->connectionComboBox->setCurrentIndex(i);
     ui->connectionComboBox->setDisabled(true);
    }
}

void catUnit::setminOpAcPow(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->pminLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->pminLineEdit->setText(qStr);
    ui->pminLineEdit->setDisabled(true);
    }
}

void catUnit::setmaxOpAcPow(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->pmaxLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->pmaxLineEdit->setText(qStr);
    ui->pmaxLineEdit->setDisabled(true);
    }
}

void catUnit::setminOpRPow(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->qminLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->qminLineEdit->setText(qStr);
    ui->qminLineEdit->setDisabled(true);
    }
}

void catUnit::setmaxOpRPow(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->qmaxLineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->qmaxLineEdit->setText(qStr);
    ui->qmaxLineEdit->setDisabled(true);
    }

}

void catUnit::setZ0_re(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->steadyRZ0LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->steadyRZ0LineEdit->setText(qStr);
    ui->steadyRZ0LineEdit->setDisabled(true);
    }
}

void catUnit::setZ0_im(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->steadyXZ0LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->steadyXZ0LineEdit->setText(qStr);
    ui->steadyXZ0LineEdit->setDisabled(true);
    }
}

void catUnit::setZ1_re(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->steadyRZ1LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->steadyRZ1LineEdit->setText(qStr);
    ui->steadyRZ1LineEdit->setDisabled(true);
    }
}

void catUnit::setZ1_im(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->steadyXZ1LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->steadyXZ1LineEdit->setText(qStr);
    ui->steadyXZ1LineEdit->setDisabled(true);
    }
}

void catUnit::setZ2_re(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->steadyRZ2LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->steadyRZ2LineEdit->setText(qStr);
    ui->steadyRZ2LineEdit->setDisabled(true);
    }
}

void catUnit::setZ2_im(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->steadyXZ2LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->steadyXZ2LineEdit->setText(qStr);
    ui->steadyXZ2LineEdit->setDisabled(true);
    }
}

void catUnit::setZ0trans_re(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->transientRZ0LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->transientRZ0LineEdit->setText(qStr);
    ui->transientRZ0LineEdit->setDisabled(true);
    }
}

void catUnit::setZ0trans_im(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->transientXZ0LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->transientXZ0LineEdit->setText(qStr);
    ui->transientXZ0LineEdit->setDisabled(true);
    }
}

void catUnit::setZ1trans_re(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->transientRZ1LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->transientRZ1LineEdit->setText(qStr);
    ui->transientRZ1LineEdit->setDisabled(true);
    }
}

void catUnit::setZ1trans_im(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->transientXZ1LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->transientXZ1LineEdit->setText(qStr);
    ui->transientXZ1LineEdit->setDisabled(true);
    }
}

void catUnit::setZ2trans_re(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->transientRZ2LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->transientRZ2LineEdit->setText(qStr);
    ui->transientRZ2LineEdit->setDisabled(true);
    }
}

void catUnit::setZ2trans_im(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->transientXZ2LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->transientXZ2LineEdit->setText(qStr);
    ui->transientXZ2LineEdit->setDisabled(true);
    }
}

void catUnit::setZ0sub_re(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->subtransientRZ0LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->subtransientRZ0LineEdit->setText(qStr);
    ui->subtransientRZ0LineEdit->setDisabled(true);
    }
}

void catUnit::setZ0sub_im(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->subtransientXZ0LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->subtransientXZ0LineEdit->setText(qStr);
    ui->subtransientXZ0LineEdit->setDisabled(true);
    }
}

void catUnit::setZ1sub_re(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->subtransientRZ1LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->subtransientRZ1LineEdit->setText(qStr);
    ui->subtransientRZ1LineEdit->setDisabled(true);
    }
}

void catUnit::setZ1sub_im(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->subtransientXZ1LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->subtransientXZ1LineEdit->setText(qStr);
    ui->subtransientXZ1LineEdit->setDisabled(true);
    }
}

void catUnit::setZ2sub_re(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->subtransientRZ2LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->subtransientRZ2LineEdit->setText(qStr);
    ui->subtransientRZ2LineEdit->setDisabled(true);
    }
}

void catUnit::setZ2sub_im(const float n, int b)
{
    if(b == 1)
    {
    QString qStr = QString::number(n);
    ui->subtransientXZ2LineEdit->setText(qStr);
    }
    else
    {
    QString qStr = QString::number(n);
    ui->subtransientXZ2LineEdit->setText(qStr);
    ui->subtransientXZ2LineEdit->setDisabled(true);
    }
}

void catUnit::setDescription(const QString n, int b)
{
    if(b == 1)
     ui->descriptionTextEdit->setText(n);
    else
    {
        ui->descriptionTextEdit->setText(n);
        ui->descriptionTextEdit->setDisabled(true);
    }
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
