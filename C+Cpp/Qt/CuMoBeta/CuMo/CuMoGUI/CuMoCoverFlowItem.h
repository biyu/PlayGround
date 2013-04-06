#ifndef CUMOCOVERFLOWITEM_H
#define CUMOCOVERFLOWITEM_H

#include <QtGui>
#include <QtCore>
#include "CuMoWidget.h"
#include "CuMoCommon.h"

class CuMoCoverFlowItem : public CuMoWidget
{
    Q_OBJECT

public:

    CuMoCoverFlowItem(QImage* image, QString text, QRectF geometry, int index, QGraphicsProxyWidget* parent=0);
    /* Get initial geometry rect of the item */
    QRectF getInitGeometry();
    /* Get index of the item */
    int getIndex();

protected:
    /* Paint function */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget=0);
    /* Mouse events reactions*/
    //    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    //    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    /* Mirror the original image */
    QImage* mirrorImage(const QImage* image);

signals:
    /* Signal: Hide this item in cover flow */
    void sig_rotateToHideStart();
    /* Signal: Show the movie info dialog with animation */
    void sig_showMovieInfoDialogStart(int index);

public slots:

private:
    /* Image and mirrored image for coverflow item */
    QImage* p_image;
    QImage* p_mirrorImage;
    /* Text displayed in coverflow item */
    QString p_text;
    /* Initial value of geometry */
    QRectF p_geometry;
    /* The index of item */
    int p_index;
};

#endif // CUMOCOVERFLOWITEM_H
