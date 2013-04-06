#include <QtGui>
#include <QtCore>
#include "CuMoAppManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CuMoAppManager appManager;
    appManager.load();

    //#if defined(Q_WS_S60)
    //    mainMenu.showMaximized();
    //#else
    //    mainMenu.show();
    //#endif

    return a.exec();
}
