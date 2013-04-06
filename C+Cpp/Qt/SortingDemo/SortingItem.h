#ifndef SORTINGITEM_H
#define SORTINGITEM_H

#include <QtGui>
#include <QtCore>

class SortingItem : public QObject, public QGraphicsRectItem        // Rectangles for displaying in scene
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    SortingItem(QRectF& rect);
    void paint ( QPainter * painter,
                 const QStyleOptionGraphicsItem * option,
                 QWidget * widget = 0 );
};

#endif // SORTINGITEM_H
