#include "SortingView.h"

SortingView::SortingView(QGraphicsScene *scene, SortingMethods *sm) : QGraphicsView(scene)
        , _sortMethods(sm), _duration(200), _count(0)
{
    _sortMethods->addListner(this);
    _aGroup = new QParallelAnimationGroup();
    _counter = new QGraphicsSimpleTextItem();
    QObject::connect(_aGroup, SIGNAL(finished()), _sortMethods, SLOT(startSort()));
    createSortingItems();
    createCounter();
}

void SortingView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void SortingView::createCounter()
{
    _counter->setPos(10, -880);
    _counter->setFont(QFont("Times", 25, QFont::Bold));
    countUpdate();
    this->scene()->addItem(_counter);
}

void SortingView::createSortingItems()
{
    QList<int> xl = _sortMethods->getPointXList();
    for(int i=0; i<xl.length(); i++)
    {
        QRectF rect(-4.0, -4.0, 8.0, 8.0);
        SortingItem* st = new SortingItem(rect);
        _sortItems.append(st);
        st->setPos(xl.at(i)*8.0, -i*8.0);
        this->scene()->addItem(st);

        QPropertyAnimation *anim = new QPropertyAnimation(st, "x");
        anim->setDuration(_duration+i);
        anim->setEasingCurve(QEasingCurve::Linear/*InOutBack*/);
        _aGroup->addAnimation(anim);
    }
}

void SortingView::pointUpdate()                 // listner of Model(Sorting Methods)
{
    QList<int> xl = _sortMethods->getPointXList();       // sorted list for x of points
    for(int i=0; i<xl.length(); i++)
    {
        QPropertyAnimation* tmpA = (QPropertyAnimation*) _aGroup->animationAt(i);
        tmpA->setStartValue(_sortItems.at(i)->x());
        tmpA->setEndValue(xl.at(i)*8.0);
    }
    _aGroup->start();
}

void SortingView::changeDuration(int duration)
{
    _duration = duration;
    for(int i=0; i<_aGroup->animationCount(); i++)
    {
        QPropertyAnimation* tmpA = (QPropertyAnimation*) _aGroup->animationAt(i);
        tmpA->setDuration(_duration+i);
    }
}

void SortingView::countUpdate()
{
    _nCount.setNum(_count);
    _counter->setText("Sort Count: "+_nCount);

}

void SortingView::countInc()
{
    _count++;
    countUpdate();
}

void SortingView::resetCounter()
{
    _count = 0;
    countUpdate();
}
