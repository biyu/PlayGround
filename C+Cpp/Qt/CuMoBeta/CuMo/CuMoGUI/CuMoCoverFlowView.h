#ifndef CUMOCOVERFLOWVIEW_H
#define CUMOCOVERFLOWVIEW_H

#include <QtGui>
#include <QtCore>
#include "Flickable.h"
#include "CuMoCoverFlowItem.h"

class CuMoCoverFlowView : public QGraphicsView, public Flickable
{
    Q_OBJECT

public:

    CuMoCoverFlowView(QSize size, QWidget* parent=0);
    /* Getter of view size */
    QSize& getSize();
    /* Get central index */
    int getCentralIndex();

protected:
    /* Draw film-like background */
    void drawBackground(QPainter* painter, const QRectF& rect);
    /* Reimplement virtual function in Flickable */
    QPoint scrollOffset() const;
    void setScrollOffset(const QPoint &offset);

    /* Reimplement mouse events */
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    /* Setup coverflow view */
    void setupView();
    /* Reset coverflow */
    void resetView();

signals:
    /* Signal: show movie infor dialog in main view */
    void sig_showInfoDialogInMainView();

public slots:
    /* SLOT: Create coverflow items */
    void slt_createCoverFlowItems(QList<CuMoMovieInfo*> infoList);
    /* SLOT: Item animated */
    void animateItemsTo(int index);
    /* SLOT: Item dragged moving */
    void dragItems(int offset);
    /* SLOT: Set new offset */
    void setNewOffset(int offset);
    /* SLOT: Emit show movie info signal to main view */
    // void slt_showMovieInfoDialog(int index);
    /* SLOT: Turn the central item back to normal */
    // void slt_showCentralItemAgain();
    /* SLOT: Hide central item */
    void slt_rotateCentralToHide();
    /* SLOT: Show central item */
    void slt_rotateCentralToShow();

private:
    /* GraphicsScene */
    QGraphicsScene* p_scene;
    /* Size of coverflow view window and scene */
    QSize p_size;
    /* Scroll offset of coverflow */
    int p_offset;
    /* Current index of top item in coverflows */
    int p_index;
    /* List of coverflow items */
    QList<CuMoCoverFlowItem*> p_itemList;
};

#endif // CUMOCOVERFLOWVIEW_H
