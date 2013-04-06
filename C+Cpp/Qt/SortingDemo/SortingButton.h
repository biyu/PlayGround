#ifndef SORTINGBUTTON_H
#define SORTINGBUTTON_H

#include <QtGui>

class SortingButton : public QGraphicsWidget
{
    Q_OBJECT
public:
    SortingButton(QGraphicsItem *parent = 0);    
    QRectF boundingRect() const;                        // [pure virtual]
    QPainterPath shape() const;                         // [virtual]
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);    // [pure virtual]

signals:
    void pressed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);   // When press or release mouse, button will be updated (repaint)
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
};

#endif // SORTINGBUTTON_H
