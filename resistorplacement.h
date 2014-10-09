#ifndef RESISTORPLACEMENT_H
#define RESISTORPLACEMENT_H

#include <QDialog>

namespace Ui {
class ResistorPlacement;
}

namespace db
{
    class ISQLDatabase;
}

class ResistorPlacement : public QDialog
{
    Q_OBJECT

public:
    explicit ResistorPlacement(QWidget *parent = 0);
    ~ResistorPlacement();

    //getter methods
    QString getName();
    QString getAlias();
    int getSystemID();
    int getID();
    QString getCatalogType();
    QString getDescription();


private slots:
    void on_resistorPButtons_buttonBox_accepted();

    void on_resistorPButtons_buttonBox_rejected();

private:
    Ui::ResistorPlacement *ui;

        bool insertResistorPlacement(QString description,QString name,QString alias,QString catalogType, int systemID,
                                  int ID);

        bool insertPlacNaming(int typeID,int id, QString name, int producerID);

        bool updateResistorPlacement(QString description,QString name,QString alias,QString catalogType, int systemID,
                                  int ID);

        bool updatePlacNaming(int typeID,int id, QString name, int producerID);
};

#endif // RESISTORPLACEMENT_H
