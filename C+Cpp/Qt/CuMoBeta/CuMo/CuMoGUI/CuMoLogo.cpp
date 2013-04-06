#include "CuMoLogo.h"

CuMoLogo::CuMoLogo(QPixmap pixmap, QRectF rect, QGraphicsProxyWidget* parent)
    : CuMoWidget(parent), p_pixmap(pixmap), p_rect(rect)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    this->setAttribute(Qt::WA_OpaquePaintEvent);
    this->setGeometry(p_rect);
    //    this->setAcceptedMouseButtons(Qt::LeftButton);
    //    QObject::connect(this, SIGNAL(sig_startRotation()), this, SLOT(slt_startRotation()));
}

void CuMoLogo::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(QRect(0, 0, p_rect.width(), p_rect.height()), p_pixmap);
}
