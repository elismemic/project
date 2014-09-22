#include "powerss.h"
#include "searchjobs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PowerSS w;
    w.show();
    return a.exec();

}
