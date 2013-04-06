#include "SortingItem.h"
#include "SortingView.h"
#include "SortingControl.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    SortingControl sc;
    sc.show();

    return app.exec();

}
