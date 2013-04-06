#include "SortingItem.h"

SortingItem::SortingItem(QRectF &rect):QGraphicsRectItem(rect)
{
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}


void SortingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::black));
    painter->drawRect(rect());
}
