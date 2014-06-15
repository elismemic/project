#include "conductor.h"
#include "ui_conductor.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QMessageBox"
#include "QFileDialog"

extern db::ISQLDatabase *pDB;
extern int searchwindowID;
extern int JobID;
Conductor::Conductor(QWidget *parent) :
 QDialog(parent),
 ui(new Ui::Conductor)
{
        ui->setupUi(this);
        this->setWindowTitle("Conductor Catalog");
        if(searchwindowID != 0)
        {
         QString s = QString::number(searchwindowID);
         ui->conductorID_lineEdit_2->setText(s);
         ui->conductorID_lineEdit_2->setEnabled(false);
        }
}



Conductor::~Conductor()
{
    delete ui;
}
//getters methods for accessing widgets inputs
int Conductor::getID()
{
    return ui->conductorID_lineEdit_2->text().toInt();
}

QString Conductor::getName()
{
    return ui->lineEdit_3->text();
}

QString Conductor::getAlias()
{
    return ui->lineEdit_4->text();
}

QString Conductor::getSectionType()
{
    return ui->conductorSectionTypecomboBox_2->currentText();
}

float Conductor::getRatedVoltage()
{
    return ui->conductorRatedVoltage_comboBox->currentText().toFloat();
}

QString Conductor::getNoOfPhases()
{
    return ui->conductorNumberOfPhasescomboBox->currentText();
}

float Conductor::getR()
{
    return ui->conductor_R_lineEdit->text().toFloat();
}

float Conductor::getX()
{
    return ui->conductor_X_lineEdit->text().toFloat();
}

float Conductor::getG()
{
    return ui->conductor_G_lineEdit->text().toFloat();
}

float Conductor::getB()
{
    return ui->conductor_B_lineEdit->text().toFloat();
}

float Conductor::getR0()
{
    return ui->conductor_R0_lineEdit->text().toFloat();
}

float Conductor::getX0()
{
    return ui->conductor_X0_lineEdit->text().toFloat();
}

float Conductor::getG0()
{
    return ui->conductorG0_lineEdit->text().toFloat();
}

float Conductor::getB0()
{
    return ui->conductor_B0_lineEdit->text().toFloat();
}

float Conductor::getShortRating()
{
    return ui->conductor_shortrating_lineEdit->text().toFloat();
}

float Conductor::getMediumRating()
{
    return ui->conductor_mediumrating_lineEdit->text().toFloat();
}

float Conductor::getLongRating()
{
    return ui->conductor_longrating_lineEdit->text().toFloat();
}

QString Conductor::getComment()
{
    return ui->conductor_comment_plainTextEdit->toPlainText();
}


//reset all widgets' values to nothing in case of discard button clicked

void Conductor::setID(int a)
{
    QString s = QString::number(a);
    ui->conductorID_lineEdit_2->setText(s);
}

void Conductor::setName(QString a)
{
    ui->lineEdit_3->setText(a);
}

void Conductor::setAlias(QString a)
{
    ui->lineEdit_4->setText(a);
}


void Conductor::setR(float a)
{
    QString s = QString::number(a);
    ui->conductor_R_lineEdit->setText(s);
}

void Conductor::setX(float a)
{
    QString s = QString::number(a);
    ui->conductor_X_lineEdit->setText(s);
}

void Conductor::setG(float a)
{
    QString s = QString::number(a);
    ui->conductor_G_lineEdit->setText(s);
}

void Conductor::setB(float a)
{
    QString s = QString::number(a);
    ui->conductor_B_lineEdit->setText(s);
}

void Conductor::setR0(float a)
{
    QString s = QString::number(a);
    ui->conductor_R0_lineEdit->setText(s);
}

void Conductor::setX0(float a)
{
    QString s = QString::number(a);
    ui->conductor_X0_lineEdit->setText(s);
}

void Conductor::setG0(float a)
{
    QString s = QString::number(a);
    ui->conductorG0_lineEdit->setText(s);
}

void Conductor::setB0(float a)
{
    QString s = QString::number(a);
    ui->conductor_B0_lineEdit->setText(s);
}

void Conductor::setShortRating(float a)
{
    QString s = QString::number(a);
    ui->conductor_shortrating_lineEdit->setText(s);
}

void Conductor::setMediumRating(float a)
{
    QString s = QString::number(a);
    ui->conductor_mediumrating_lineEdit->setText(s);
}

void Conductor::setLongRating(float a)
{
    QString s = QString::number(a);
    ui->conductor_longrating_lineEdit->setText(s);
}

void Conductor::setComment(QString a)
{
    ui->conductor_comment_plainTextEdit->setPlainText(a);
}




bool Conductor::insertConductor(int ID, QString name, QString alias, QString numberOfPhases,float ratedVoltage,
                                float R, float X, float G, float B, float R0, float X0, float G0, float B0,
                               float shortRating, float mediumRating, float longRating, QString comment
                   )
{
    if (!pDB)
        return false;
    td::INT4 insert_ID(ID);
    td::INT4 insert_TypeID(4);
    td::INT4 insert_JobID(JobID);

    db::Ref<td::String> refName(50);
    db::Ref<td::String> refAlias(50);
    db::Ref<td::String> refnumberOfPhases(50);
    db::Ref<td::String> refComment(200);

    td::String td_name = name.toUtf8();
    td::String td_numberOfPhases = numberOfPhases.toUtf8();
    td::String td_alias = alias.toUtf8();
    td::String td_comment = comment.toUtf8();


    refName = td_name;
    refAlias = td_alias;
    refComment = td_comment;
    refnumberOfPhases = td_numberOfPhases;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO CatalogConductor(JobID,TypeID,ID,Name,Alias,NumberOfPhases,RatedVoltage,R,X,G,B,R0,X0,G0,B0,ShortTermRating,MediumTermRating,LongTermRating,Description) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_JobID << insert_TypeID << insert_ID << refName << refAlias << refnumberOfPhases << ratedVoltage << R << X
           << G << B << R0 << X0 << G0 << B0 << shortRating << mediumRating << longRating << refComment;


    if (!pStat->execute())
    {
        td::String strErr;
        pStat->getErrorStr(strErr);
        if (DebugTrace(1000))
            mu::getTracer() << strErr;
        //rollback will be called
        return false;
    }

    //commit transaction
    bool  bRet = trans.commit();
    if (bRet)
        QMessageBox::information(this,"Database Info","Data Inserted");

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}


void Conductor::on_buttonBox_accepted()
{

    if(searchwindowID != 0)
    {
       insertConductor( searchwindowID,getName(),
                   getAlias(), getNoOfPhases(),getRatedVoltage(),
                            getR(), getX(), getG(), getB(), getR0(), getX0(), getG0(), getB0(),
                           getShortRating(), getMediumRating(), getLongRating(), getComment()
                           );
       close();
    }
    else
    {
        insertConductor( getID(),getName(),
                    getAlias(), getNoOfPhases(),getRatedVoltage(),
                             getR(), getX(), getG(), getB(), getR0(), getX0(), getG0(), getB0(),
                            getShortRating(), getMediumRating(), getLongRating(), getComment()
                            );
        close();
    }
}



void Conductor::on_buttonBox_rejected()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Discard","Are you sure you want to discard all changes made?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        close();
    }

}
