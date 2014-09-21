#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include <QDialog>

namespace Ui
{
    class Conductor;
}

namespace db
{
    class ISQLDatabase;
}
class Conductor : public QDialog
{
    Q_OBJECT

public:
    explicit Conductor(QWidget *parent = 0);
    ~Conductor();
    int getID();
    QString getName();
    QString getAlias();
    QString getSectionType();
    float getRatedVoltage();
    QString getNoOfPhases();
    float getR();
    float getX();
    float getG();
    float getB();
    float getR0();
    float getX0();
    float getG0();
    float getB0();
    float getShortRating();
    float getMediumRating();
    float getLongRating();
    QString getComment();



    void setID(int a);
    void setName(QString a);
    void setAlias(QString a);
    void setR(float a);
    void setX(float a);
    void setG(float a);
    void setB(float a);
    void setR0(float a);
    void setX0(float a);
    void setG0(float a);
    void setB0(float a);

    void setShortRating(float a);
    void setMediumRating(float a);
    void setLongRating(float a);
    void setNumberOfPhases(QString a);
    void setRatedVoltage(float a);
    void setSectionType(QString a);

    void setComment(QString a);

    void selectConductor();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::Conductor *ui;

    bool insertConductor(int ID, QString name, QString alias, QString numberOfPhases,float ratedVoltage,
                        float R, float X, float G, float B, float R0, float X0, float G0, float B0,
                       float shortRating, float mediumRating, float longRating, QString comment,QString sectionType
                       );
    bool insertConductorNaming(int typeID,int ID, QString name, int producerID);

    bool updateConductor(int ID, QString name, QString alias, QString numberOfPhases,float ratedVoltage,
                        float R, float X, float G, float B, float R0, float X0, float G0, float B0,
                       float shortRating, float mediumRating, float longRating, QString comment,QString sectionType
                       );
    bool updateConductorNaming(int typeID,int ID, QString name, int producerID);

};

#endif // CONDUCTOR_H
