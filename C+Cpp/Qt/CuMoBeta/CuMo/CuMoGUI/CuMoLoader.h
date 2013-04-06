#ifndef CUMOLOADER_H
#define CUMOLOADER_H

#include <QtGui>
#include <QtCore>
#include "CuMoWidget.h"
#include "CuMoLogo.h"

class CuMoLoader : public CuMoWidget
{
    Q_OBJECT

public:
    /* Constructor */
    CuMoLoader(QGraphicsProxyWidget* parent=0);

protected:

private:
    /* Set start animation */
    void setStartAnimation();
    /* Set end animation */
    void setEndAnimation();

signals:
    /* Loading finished */
    // void sig_loadFinished();

public slots:
    /* Start animation */
    void slt_startAnimation();
    /* End animation */
    void slt_endAnimation();
    /* Set loading progress */
    void slt_setLoadingProgress(int value);

private:
    /* Loader image */
    CuMoLogo* p_image;
    /* Loader text */
    QGraphicsTextItem* p_text;
    /* Background */
    QGraphicsRectItem* p_background;
    /* Start animation */
    QParallelAnimationGroup* p_startAnimation;
    /* End animation */
    QParallelAnimationGroup* p_endAnimation;
    /* Rotation animation */
    // QSequentialAnimationGroup* p_rotateAnimationGroup;
    QPropertyAnimation* p_rotateAnimation;
    /* Position animation */
    QPropertyAnimation* p_posAnimation;
    /* Opacity animation */
    QPropertyAnimation* p_opacityAnimation;
};

#endif // CUMOLOADER_H
