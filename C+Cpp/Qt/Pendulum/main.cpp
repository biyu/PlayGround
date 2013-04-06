#include <QtGui/QApplication>
#include "Pendulum.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Pendulum p;
    p.show();
    p.start();


//#if defined(Q_WS_S60)
//    w.showMaximized();
//#else
//    w.show();
//#endif

    return a.exec();
}
