#include "CuMoCoverFlowView.h"

CuMoCoverFlowView::CuMoCoverFlowView(QSize size, QWidget* parent)
    : QGraphicsView(parent), Flickable(), p_scene(0), p_size(size), p_offset(0), p_index(0)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    /* Setup parameters of coverflow */
    setupView();
    // createCoverFlowItems();
}

void CuMoCoverFlowView::setupView()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    /* Create and set scene for coverflow view */
    p_scene = new QGraphicsScene();
    p_scene->setSceneRect(QRect(0, 0, p_size.width(), p_size.height()));
    this->setScene(p_scene);

    /* Set background to Black */
    // this->setBackgroundBrush(Qt::black);
    /* Fix the size of view which can not be changed */
    this->setFixedSize(p_size);
    /* Disable the horizontal and vertical scroll bars */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    /* Disable frame style */
    this->setFrameStyle(0);
    /* Set cache mode */
    this->setCacheMode(QGraphicsView::CacheBackground);
    /* Set viewport update mode */
    // this->setViewportUpdateMode(FullViewportUpdate);
    /* Set render hint */
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    /* Set attribute: WA_OpaquePaintEvent */
    this->setAttribute(Qt::WA_OpaquePaintEvent, true);

    /* Flickable: Set the widget which accpet the mouse click event */
    this->setAcceptMouseClick(this->viewport());
    /* Default threshold is 10, set it to 0 and make it much more sensitive */
    // this->setThreshold(0);
}

void CuMoCoverFlowView::drawBackground(QPainter* painter, const QRectF& rect)
{
    Q_UNUSED(rect);
    /* Fill the exposed rect of scene to black */
    painter->fillRect(rect, Qt::black);
    /* Draw holes of film */
    int holeNum = 20;
    int holeWidth = this->width()/holeNum;
    painter->setBrush(QColor(14, 48, 21));
    for(int i=0; i<holeNum; i++)
    {
        /* Draw upper row */
        painter->drawRect(QRect(QPoint(i*holeWidth+10, 8), QSize(holeWidth-15, 15)));
        /* Draw lower row */
        painter->drawRect(QRect(QPoint(i*holeWidth+10, this->height()-8-15), QSize(holeWidth-15, 15)));
    }
}

QPoint CuMoCoverFlowView::scrollOffset() const
{
    /*
     * Flickable: Overwrite scrollOffset function;
     * Return the current scrolling offset
     */
    return QPoint(p_offset, 0);
}

void CuMoCoverFlowView::setScrollOffset(const QPoint &offset)
{
    int dx = offset.x();
    /* Check if the x offset changes or not */
    if (dx != p_offset)
    {
        /* Limit the x offset */
        p_offset = qBound(0, dx, (p_itemList.count()-1)*this->width()/3);
    }
}

void CuMoCoverFlowView::mousePressEvent(QMouseEvent *event) {
    Flickable::handleMousePress(event);
    if (event->isAccepted())
        return;

    qDebug() << "+ " << __PRETTY_FUNCTION__;

    /* Check clicked item */
    foreach(CuMoCoverFlowItem* item, p_itemList)
    {
        bool yes = item->contains(item->mapFromScene(event->posF()));
        if(yes && p_index != item->getIndex())
        {
            int p_index = item->getIndex();
            animateItemsTo(p_index);
            /* Set offset to current point */
            this->setNewOffset(p_index*this->width()/3);
            event->accept();
            return;
        }
        if(yes && p_index == item->getIndex())
        {
            this->slt_rotateCentralToHide();
            event->accept();
            return;
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void CuMoCoverFlowView::mouseMoveEvent(QMouseEvent *event) {
    Flickable::handleMouseMove(event);
    // qDebug() << "+ " << __PRETTY_FUNCTION__;
    dragItems(p_offset);
}

void CuMoCoverFlowView::mouseReleaseEvent(QMouseEvent *event) {
    /* Filckable handles the event first */
    Flickable::handleMouseRelease(event);
    if(event->isAccepted() && !this->isSteady() && !this->isStop())
    {
        /* Auto moving to the nearest index when mouse released */
        int p_index = qRound(qreal(p_offset)/qreal(this->width()/3.0));
        /* Animate coverflow items to INDEX:th */
        this->animateItemsTo(p_index);
        this->setNewOffset(p_index*this->width()/3);
        return;
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
        return;
    }
}

void CuMoCoverFlowView::slt_createCoverFlowItems(QList<CuMoMovieInfo*> infoList)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    /* Reset coverflow first */
    if(!p_itemList.isEmpty())
        this->resetView();

    QParallelAnimationGroup* animationGroup = new QParallelAnimationGroup();
    // QPropertyAnimation* animation;

    for(int i=0; i<infoList.count(); i++)
    {
        QRectF itemGeo(this->width()/2-this->width()/8+i*this->width()/3, this->height()/2-this->height()*4/5/2
                       , this->width()/4, this->height()*4/5);
        CuMoCoverFlowItem* item = new CuMoCoverFlowItem(infoList.at(i)->movieImage, infoList.at(i)->movieName, itemGeo, i);
        /* Only light on the central item */
        if (i==0)
            item->addPropertyAnimToGroup(animationGroup, "opacity", 1000, 0, 1, QEasingCurve::OutQuart);
        else if (i==1)
            item->addPropertyAnimToGroup(animationGroup, "opacity", 1000, 0, 0.3, QEasingCurve::OutQuart);
        else
            item->setOpacity(0.3);

        p_scene->addItem(item);
        p_itemList.append(item);
    }

    qDebug() << p_itemList.count();

    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void CuMoCoverFlowView::resetView()
{
    /* Reset cover flow */
    p_index=0;
    this->setNewOffset(0);
    foreach(CuMoCoverFlowItem* item, p_itemList)
    {
        p_scene->removeItem(item);
        delete item;
    }
    p_itemList.clear();
}

void CuMoCoverFlowView::animateItemsTo(int index)
{
    p_index = index;

    QParallelAnimationGroup* animationGroup = new QParallelAnimationGroup();

    for(int i=0; i<p_itemList.count(); i++) {
        CuMoCoverFlowItem* item = p_itemList.at(i);

        item->addPropertyAnimToGroup(animationGroup, "pos",
                                     500,
                                     item->pos(),
                                     QPointF(item->getInitGeometry().x()-index*this->width()/3, item->y()),
                                     QEasingCurve::OutQuart);
        if(i==p_index)
            item->addPropertyAnimToGroup(animationGroup, "opacity", 500, item->opacity(), 1.0, QEasingCurve::OutQuart);
        else
            item->addPropertyAnimToGroup(animationGroup, "opacity", 500, item->opacity(), 0.3, QEasingCurve::OutQuart);
    }
    animationGroup->start();
}

void CuMoCoverFlowView::dragItems(int offset)
{
    for(int i=0; i<p_itemList.count(); i++)
    {
        CuMoCoverFlowItem* item = p_itemList.at(i);
        item->setPos(QPointF(item->getInitGeometry().x()-offset, item->getInitGeometry().y()));
    }
}

void CuMoCoverFlowView::setNewOffset(int offset)
{
    /* Set offset to current point */
    this->setInnerOffset(QPoint(offset, 0));
    p_offset = offset;
}

QSize& CuMoCoverFlowView::getSize()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    /* Return the size of coverflow */
    return p_size;
}

int CuMoCoverFlowView::getCentralIndex()
{
    return p_index;
}

void CuMoCoverFlowView::slt_rotateCentralToHide()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    CuMoCoverFlowItem* centralItem = p_itemList.at(p_index);

    QParallelAnimationGroup* animationGroup = new QParallelAnimationGroup();
    /* Start animation to hide coverflow item */
    centralItem->addPropertyAnimToGroup(animationGroup, "rotationY", 500, 0, 90, QEasingCurve::OutQuart);
    centralItem->addPropertyAnimToGroup(animationGroup, "opacity", 500, 1, 0, QEasingCurve::OutQuart);
    QObject::connect(animationGroup, SIGNAL(finished()), this, SIGNAL(sig_showInfoDialogInMainView()));
    animationGroup->start();
}

void CuMoCoverFlowView::slt_rotateCentralToShow()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    CuMoCoverFlowItem* centralItem = p_itemList.at(p_index);

    QParallelAnimationGroup* animationGroup = new QParallelAnimationGroup();
    /* Start animation to hide coverflow item */
    centralItem->addPropertyAnimToGroup(animationGroup, "rotationY", 500, 90, 0, QEasingCurve::OutQuart);
    centralItem->addPropertyAnimToGroup(animationGroup, "opacity", 500, 0, 1, QEasingCurve::OutQuart);
    animationGroup->start();
}
