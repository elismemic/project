#include "capacitor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Capacitor w;
    w.show();

    return a.exec();
}
