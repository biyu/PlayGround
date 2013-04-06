#include <QtGui/QApplication>
#include <QtCore>
#include "JBlockerMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JBlockerMainWindow w;

#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
