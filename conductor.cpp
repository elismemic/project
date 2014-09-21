#include "conductor.h"
#include "ui_conductor.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mymodel.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include "QMessageBox"
#include "QFileDialog"

extern db::ISQLDatabase *pDB;
extern int searchwindowID;
extern int searchwindowJobID;
extern int JobID;
extern bool editable;
extern bool editClicked;
Conductor::Conductor(QWidget *parent) :
 QDialog(parent),
 ui(new Ui::Conductor)
{
        ui->setupUi(this);
        this->setWindowTitle("Conductor Catalog");
        if(editClicked == true)
        {
         QString s = QString::number(searchwindowID);
         ui->conductorID_lineEdit_2->setText(s);
         ui->conductorID_lineEdit_2->setEnabled(false);
         selectConductor();
         editClicked = false;
         //selectConductor();
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

void Conductor::setRatedVoltage(float a)
{
    QString s = QString::number(a);
    ui->conductorRatedVoltage_comboBox->setCurrentText(s);
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

void Conductor::setSectionType(QString a)
{
    ui->conductorSectionTypecomboBox_2->setCurrentText(a);
}

void Conductor::setComment(QString a)
{
    ui->conductor_comment_plainTextEdit->setPlainText(a);
}

void Conductor::setNumberOfPhases(QString a)
{
    ui->conductorNumberOfPhasescomboBox->setCurrentText(a);
}

void Conductor::selectConductor()
{
    td::INT4 insert_ID(searchwindowID);
    td::INT4 insert_JobID(searchwindowJobID);

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_SELECT,
       "Select Name,Alias,NumberOfPhases,RatedVoltage,R,X,G,B,R0,X0,G0,B0,ShortTermRating,MediumTermRating,LongTermRating,Description,SectionType FROM CatalogConductor WHERE ID = ? AND JobID = ?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_ID << insert_JobID;


    cnt::SafeFullVector<db::CPPColumnDesc> columns;
        columns.reserve(17);
        columns[0].name = "Name";
        columns[0].tdType = td::nch;
        columns[0].len = 0;

        columns[1].name = "Alias";
        columns[1].tdType = td::nch;
        columns[1].len = 0;

        columns[2].name = "NumberOfPhases";
        columns[2].tdType = td::nch;
        columns[2].len = 0;

        columns[3].name = "RatedVoltage";
        columns[3].tdType = td::real8;
        columns[3].len = 0;

        columns[4].name = "R";
        columns[4].tdType = td::real8;
        columns[4].len = 0;

        columns[5].name = "X";
        columns[5].tdType = td::real8;
        columns[5].len = 0;

        columns[6].name = "G";
        columns[6].tdType = td::real8;
        columns[6].len = 0;

        columns[7].name = "B";
        columns[7].tdType = td::real8;
        columns[7].len = 0;

        columns[8].name = "R0";
        columns[8].tdType = td::real8;
        columns[8].len = 0;

        columns[9].name = "X0";
        columns[9].tdType = td::real8;
        columns[9].len = 0;

        columns[10].name = "G0";
        columns[10].tdType = td::real8;
        columns[10].len = 0;

        columns[11].name = "B0";
        columns[11].tdType = td::real8;
        columns[11].len = 0;

        columns[12].name = "ShortTermRating";
        columns[12].tdType = td::real8;
        columns[12].len = 0;

        columns[13].name = "MediumTermRating";
        columns[13].tdType = td::real8;
        columns[13].len = 0;

        columns[14].name = "LongTermRating";
        columns[14].tdType = td::real8;
        columns[14].len = 0;

        columns[15].name = "Description";
        columns[15].tdType = td::nch;
        columns[15].len = 0;

        columns[16].name = "SectionType";
        columns[16].tdType = td::nch;
        columns[16].len = 0;

        db::Recordset* rs = new db::Recordset(columns);

        if (!rs->load(pStat.getPtr()))
            exit(0);

        MyModel *model = new MyModel(this, rs, true);

        QModelIndex idx = model->index(0,0);
            QString name = model->data(idx, Qt::DisplayRole).toString();
            setName(name);


            idx = model->index(0,1);
            QString alias = model->data(idx, Qt::DisplayRole).toString();
            setAlias(alias);


            idx = model->index(0,2);
            QString NoOfPh = model->data(idx, Qt::DisplayRole).toString();
            setNumberOfPhases(NoOfPh);


            idx = model->index(0,3);
            float ratedVoltage = model->data(idx, Qt::DisplayRole).toFloat();
            setRatedVoltage(ratedVoltage);


            idx = model->index(0,4);
            float R = model->data(idx, Qt::DisplayRole).toFloat();
            setR(R);


            idx = model->index(0,5);
            float X = model->data(idx, Qt::DisplayRole).toFloat();
            setX(X);


            idx = model->index(0,6);
            float G = model->data(idx, Qt::DisplayRole).toFloat();
            setG(G);

            idx = model->index(0,7);
            float B = model->data(idx, Qt::DisplayRole).toFloat();
            setB(B);

            idx = model->index(0,8);
            float R0 = model->data(idx, Qt::DisplayRole).toFloat();
            setR0(R0);


            idx = model->index(0,9);
            float X0 = model->data(idx, Qt::DisplayRole).toFloat();
            setX0(X0);


            idx = model->index(0,10);
            float G0 = model->data(idx, Qt::DisplayRole).toFloat();
            setG0(G0);

            idx = model->index(0,11);
            float B0 = model->data(idx, Qt::DisplayRole).toFloat();
            setB0(B0);


            idx = model->index(0,12);
            float STR = model->data(idx, Qt::DisplayRole).toFloat();
            setShortRating(STR);


            idx = model->index(0,13);
            float MTR = model->data(idx, Qt::DisplayRole).toFloat();
            setMediumRating(MTR);


            idx = model->index(0,14);
            float LTR = model->data(idx, Qt::DisplayRole).toFloat();
            setLongRating(LTR);


            idx = model->index(0,15);
            QString description = model->data(idx, Qt::DisplayRole).toString();
            setComment(description);

            idx = model->index(0,16);
            QString section = model->data(idx, Qt::DisplayRole).toString();
            setSectionType(section);

}

bool Conductor::updateConductor(int ID, QString name, QString alias, QString numberOfPhases,float ratedVoltage,
                                float R, float X, float G, float B, float R0, float X0, float G0, float B0,
                               float shortRating, float mediumRating, float longRating, QString comment,QString sectionType
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
    db::Ref<td::String> refSectionType(50);

    td::String td_name = name.toUtf8();
    td::String td_numberOfPhases = numberOfPhases.toUtf8();
    td::String td_alias = alias.toUtf8();
    td::String td_comment = comment.toUtf8();
    td::String td_sectionType = sectionType.toUtf8();


    refName = td_name;
    refAlias = td_alias;
    refComment = td_comment;
    refnumberOfPhases = td_numberOfPhases;
    refSectionType = td_sectionType;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE CatalogConductor SET JobID=?,TypeID=?,Name=?,Alias=?,NumberOfPhases=?,RatedVoltage=?,R=?,X=?,G=?,B=?,R0=?,X0=?,G0=?,B0=?,ShortTermRating=?,MediumTermRating=?,LongTermRating=?,Description=?,SectionType=? WHERE ID=?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_JobID << insert_TypeID << refName << refAlias << refnumberOfPhases << ratedVoltage << R << X
           << G << B << R0 << X0 << G0 << B0 << shortRating << mediumRating << longRating << refComment << refSectionType << insert_ID;


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
        QMessageBox::information(this,"Database Info","Data Updated");

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}



bool Conductor::updateConductorNaming(int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(4);
    td::INT4 insert_ID(id);
    td::INT4 insert_producerID(producerID);

    db::Ref<td::String> refName(50);
    td::String td_name = name.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_UPDATE,
       "UPDATE CatNaming SET TypeID=?,Name=?,ProducerID=? WHERE ID=?"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_TypeID << refName << insert_producerID << insert_ID;


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

    if (DebugTrace(1000))
        mu::getTracer() << "Update finished!\n";
    return bRet;
}



bool Conductor::insertConductor(int ID, QString name, QString alias, QString numberOfPhases,float ratedVoltage,
                                float R, float X, float G, float B, float R0, float X0, float G0, float B0,
                               float shortRating, float mediumRating, float longRating, QString comment,QString sectionType
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
    db::Ref<td::String> refSectionType(50);

    td::String td_name = name.toUtf8();
    td::String td_numberOfPhases = numberOfPhases.toUtf8();
    td::String td_alias = alias.toUtf8();
    td::String td_comment = comment.toUtf8();
    td::String td_sectionType = sectionType.toUtf8();


    refName = td_name;
    refAlias = td_alias;
    refComment = td_comment;
    refnumberOfPhases = td_numberOfPhases;
    refSectionType = td_sectionType;

    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO CatalogConductor(JobID,TypeID,ID,Name,Alias,NumberOfPhases,RatedVoltage,R,X,G,B,R0,X0,G0,B0,ShortTermRating,MediumTermRating,LongTermRating,Description,SectionType) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_JobID << insert_TypeID << insert_ID << refName << refAlias << refnumberOfPhases << ratedVoltage << R << X
           << G << B << R0 << X0 << G0 << B0 << shortRating << mediumRating << longRating << refComment << refSectionType;


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



bool Conductor::insertConductorNaming(int typeID,int id, QString name, int producerID)
{
    td::INT4 insert_TypeID(4);
    td::INT4 insert_ID(id);
    td::INT4 insert_producerID(producerID);

    db::Ref<td::String> refName(50);
    td::String td_name = name.toUtf8();
    refName = td_name;


    //start transaction log
    db::Transaction trans(pDB);

    //create statement using parameters which will be provided later
    db::StatementPtr pStat(pDB->createStatement(db::IStatement::DBS_INSERT,
       "INSERT INTO CatNaming(TypeID,ID,Name,ProducerID) VALUES (?,?,?,?)"));


    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());
    //bind params
    params << insert_TypeID << insert_ID << refName << insert_producerID;


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

    if (DebugTrace(1000))
        mu::getTracer() << "Insert finished!\n";
    return bRet;
}



void Conductor::on_buttonBox_accepted()
{

    if(searchwindowID != 0)
    {
        if(updateConductorNaming(4,searchwindowID,getName(),1))
       {
            updateConductor( searchwindowID,getName(),
                        getAlias(), getNoOfPhases(),getRatedVoltage(),
                                 getR(), getX(), getG(), getB(), getR0(), getX0(), getG0(), getB0(),
                                getShortRating(), getMediumRating(), getLongRating(), getComment(),getSectionType()
                                );
            close();

        }
        else{
            QMessageBox::information(this,"Information","Could not update data!");
        }

    }
    else
    {
        if(insertConductorNaming(4,getID(),getName(),1))
        {
        insertConductor( getID(),getName(),
                    getAlias(), getNoOfPhases(),getRatedVoltage(),
                             getR(), getX(), getG(), getB(), getR0(), getX0(), getG0(), getB0(),
                            getShortRating(), getMediumRating(), getLongRating(), getComment(),getSectionType()
                            );
        close();
        }
        else
        {
            QMessageBox::information(this,"Information","Could not insert data - ID already exists!");
        }
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
