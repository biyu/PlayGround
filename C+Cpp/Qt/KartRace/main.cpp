#include <QtGui/QApplication>
#include "b2worldview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(time(0));

    B2WorldView view;
    view.show();

    return a.exec();
}
