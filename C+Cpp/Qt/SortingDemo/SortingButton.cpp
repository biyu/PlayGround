#include "SortingButton.h"

SortingButton::SortingButton(QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
}

QRectF SortingButton::boundingRect() const
{
    return QRectF(-65, -65, 130, 130);
}

QPainterPath SortingButton::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void SortingButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    bool down = option->state & QStyle::State_Sunken;
    QRectF r = boundingRect();
    QLinearGradient grad(r.topLeft(), r.bottomRight());
    grad.setColorAt(down ? 1 : 0, option->state & QStyle::State_MouseOver ? Qt::red : Qt::darkRed);
    grad.setColorAt(down ? 0 : 1, Qt::darkRed);
    painter->setPen(Qt::darkRed);
    painter->setBrush(grad);
    painter->drawEllipse(r);
    QLinearGradient grad2(r.topLeft(), r.bottomRight());
    grad.setColorAt(down ? 1 : 0, Qt::darkGray);
    grad.setColorAt(down ? 0 : 1, Qt::lightGray);
    painter->setPen(Qt::NoPen);
    painter->setBrush(grad);
    if (down)
        painter->translate(2, 2);
    painter->drawEllipse(r.adjusted(5, 5, -5, -5));
}

void SortingButton::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit pressed();
    update();
}

void SortingButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    update();
}

