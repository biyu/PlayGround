#ifndef CUMOLOGO_H
#define CUMOLOGO_H

#include "CuMoWidget.h"

class CuMoLogo : public CuMoWidget
{
    Q_OBJECT

public:

    CuMoLogo(QPixmap pixmap, QRectF rect, QGraphicsProxyWidget* parent=0);

protected:
    /* Paint function */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget=0);

private:
    /* Pixmap for logo */
    QPixmap p_pixmap;
    /* Geometry rect for logo */
    QRectF p_rect;
};

#endif // CUMOLOGO_H
