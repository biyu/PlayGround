#ifndef SORTINGTEXTVIEW_H
#define SORTINGTEXTVIEW_H

#include <QtCore>
#include <QtGui>
#include "SortingMethods.h"

class SortingTextView : public QTextBrowser, public SortingListner
{
public:
    SortingTextView(SortingMethods* sm);
    void pointUpdate();
    void countInc();

private:
    void init();
    QString generateText();
    void updateText(QString str);

private:
    SortingMethods* _sortMethods;
};

#endif // SORTINGTEXTVIEW_H
