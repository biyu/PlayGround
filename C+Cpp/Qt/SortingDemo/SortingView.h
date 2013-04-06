#ifndef SORTINGVIEW_H
#define SORTINGVIEW_H

#include <QtCore>
#include <QtGui>
#include "SortingItem.h"
#include "SortingMethods.h"

class SortingView : public QGraphicsView, public SortingListner
{
    Q_OBJECT

public:
    SortingView(QGraphicsScene *scene, SortingMethods* sm);
    void pointUpdate();                 // Interface; Pure virtual function for SortingListner
    void resetCounter();

public slots:
    void changeDuration(int duration);
    void countInc();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void createCounter();
    void createSortingItems();
    void countUpdate();

private:
    QList<SortingItem*> _sortItems;
    SortingMethods* _sortMethods;
    QParallelAnimationGroup* _aGroup;     // Animate Property
    QGraphicsSimpleTextItem* _counter;
    int _duration;
    int _count;
    QString _nCount;
};

#endif // SORTINGVIEW_H
