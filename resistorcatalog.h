#ifndef RESISTOR_H
#define RESISTOR_H

#include <QDialog>

namespace Ui {
class ResistorCatalog;
}

namespace db
{
    class ISQLDatabase;
}

class ResistorCatalog : public QDialog
{
    Q_OBJECT

public:
    explicit ResistorCatalog(QWidget *parent = 0);
    ~ResistorCatalog();

    //getter methods
    QString getName();
    int getID();
    QString getAlias();
    float getRatedVoltage();
    float getR();
    float getX();
    QString getDescription();


    void setName();
    void setID();
    void setAlias();
    void setRatedVoltage();
    void setR();
    void setX();
    void setDescription();

private slots:
    void on_resistorButtons_buttonBox_accepted();

    void on_resistorButtons_buttonBox_rejected();

private:
    Ui::ResistorCatalog *ui;



    bool insertResistorCatalog(QString name, float ratedVoltage, int ID, QString alias, float R,
                                                    float X, QString description);

   bool insertResistorNaming(int typeID,int id, QString name, int producerID);
   bool updateResistorCatalog(QString name, float ratedVoltage, int ID, QString alias, float R,
                                                   float X, QString description);

  bool updateResistorNaming(int typeID,int id, QString name, int producerID);


};

#endif // RESISTOR_H
