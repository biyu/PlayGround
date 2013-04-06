#include "CuMoCoverFlowItem.h"

CuMoCoverFlowItem::CuMoCoverFlowItem(QImage* image, QString text, QRectF geometry, int index, QGraphicsProxyWidget* parent)
    : CuMoWidget(parent), p_image(image), p_mirrorImage(0), p_text(text), p_geometry(geometry), p_index(index)
{
    // qDebug() << "+ " << __PRETTY_FUNCTION__;
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    /* Initial the geometry of items */
    this->setGeometry(p_geometry);
}

QRectF CuMoCoverFlowItem::getInitGeometry()
{
    return p_geometry;
}

int CuMoCoverFlowItem::getIndex()
{
    return p_index;
}

void CuMoCoverFlowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Set Painter Features

    painter->setClipRect(this->rect());

    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setRenderHint(QPainter::Antialiasing);

    // draw image
    QRectF target(10, 10, this->rect().width()-20, this->rect().height()*0.6 -10);
    painter->drawImage(target, *p_image, p_image->rect());

    // draw mirror image
    if(!p_mirrorImage) {
        p_mirrorImage = mirrorImage(p_image);
    }

    QRectF mTarget(target.x(), target.y()+target.height(), target.width(), target.height());
    painter->drawImage(mTarget, *p_mirrorImage, p_mirrorImage->rect());

    painter->save();
    painter->setPen(Qt::white);
    painter->setFont(QFont(painter->font().family(), 12, QFont::Bold));
    // int titleWidth = painter->fontMetrics().width(QString("KARETA KID"));
    QRectF textRect(mTarget.x()+10, mTarget.y()+10, mTarget.width()-20, mTarget.height()*2/3-20);
    painter->drawText(textRect, Qt::AlignCenter | Qt::TextWordWrap, p_text);
    painter->restore();
}

QImage* CuMoCoverFlowItem::mirrorImage(const QImage* image)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    QImage *tmpImage = new QImage(image->mirrored(false, true));

    QPoint p1, p2;
    p2.setY(tmpImage->height());

    QLinearGradient gradient(p1, p2);
    gradient.setColorAt(0, QColor(0, 0, 0, 100));
    gradient.setColorAt(1, Qt::transparent);

    QPainter p;
    p.begin(tmpImage);
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.fillRect(0, 0, tmpImage->width(), tmpImage->height(), gradient);
    p.end();

    return(tmpImage);
}
