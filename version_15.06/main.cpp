#include "mainwindow.h"
#include <QApplication>
#include <QTransform>
#include <QTranslator>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    //QTranslator translator;
    //translator.load("translation.qm");
    //app.installTranslator(&translator);
    w.show();
    return app.exec();
}
