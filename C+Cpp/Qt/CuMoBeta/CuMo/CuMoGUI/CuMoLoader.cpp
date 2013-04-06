#include "CuMoLoader.h"

CuMoLoader::CuMoLoader(QGraphicsProxyWidget* parent)
    : CuMoWidget(parent), p_startAnimation(0), p_endAnimation(0), p_rotateAnimation(0)
    , p_posAnimation(0), p_opacityAnimation(0)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    /* Background rect */
    p_background = new QGraphicsRectItem(QRect(0, 0, 800, 480), this);
    p_background->setBrush(Qt::black);
    p_background->setOpacity(0.0);
    /* Loader image */
    p_image = new CuMoLogo(QPixmap(":images/loader.png"), QRectF(0, 0, 70, 70), this);
    p_image->setZValue(1.0);
    p_image->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    /* Loading progress text */
    p_text = new QGraphicsTextItem(this);
    p_text->setZValue(1.0);
    p_text->setDefaultTextColor(QColor(243, 186, 36));
    p_text->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    p_text->setPlainText(QString("%1%").arg(0));
}

void CuMoLoader::setStartAnimation()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;


    /* Create the animations to the group */
    p_startAnimation = new QParallelAnimationGroup(this);

    /* Rotation */
    // p_rotateAnimationGroup = new QSequentialAnimationGroup();
    p_rotateAnimation = new QPropertyAnimation();
    p_rotateAnimation->setTargetObject(p_image);
    p_rotateAnimation->setPropertyName("rotationY");
    p_rotateAnimation->setStartValue(0.0);
    p_rotateAnimation->setEndValue(360.0);
    p_rotateAnimation->setDuration(2000);
    p_rotateAnimation->setEasingCurve(QEasingCurve::OutQuart);
    p_startAnimation->addAnimation(p_rotateAnimation);

    /* Position */
    p_posAnimation = new QPropertyAnimation();
    p_posAnimation->setTargetObject(p_image);
    p_posAnimation->setPropertyName("pos");
    p_posAnimation->setStartValue(QPointF(400-35, 481));
    p_posAnimation->setEndValue(QPointF(400-35, 300));
    p_posAnimation->setDuration(500);
    p_posAnimation->setEasingCurve(QEasingCurve::Linear);
    p_startAnimation->addAnimation(p_posAnimation);

    p_posAnimation = new QPropertyAnimation();
    p_posAnimation->setTargetObject(p_text);
    p_posAnimation->setPropertyName("pos");
    p_posAnimation->setStartValue(QPointF(400-25, 481+85));
    p_posAnimation->setEndValue(QPointF(400-25, 300+85));
    p_posAnimation->setDuration(500);
    p_posAnimation->setEasingCurve(QEasingCurve::Linear);
    p_startAnimation->addAnimation(p_posAnimation);

    /* Opacity */
    p_opacityAnimation = new QPropertyAnimation();
    p_opacityAnimation->setTargetObject(p_image);
    p_opacityAnimation->setPropertyName("opacity");
    p_opacityAnimation->setStartValue(0.0);
    p_opacityAnimation->setEndValue(1.0);
    p_opacityAnimation->setDuration(500);
    p_opacityAnimation->setEasingCurve(QEasingCurve::Linear);
    p_startAnimation->addAnimation(p_opacityAnimation);

    p_opacityAnimation = new QPropertyAnimation();
    p_opacityAnimation->setTargetObject(p_text);
    p_opacityAnimation->setPropertyName("opacity");
    p_opacityAnimation->setStartValue(0.0);
    p_opacityAnimation->setEndValue(1.0);
    p_opacityAnimation->setDuration(500);
    p_opacityAnimation->setEasingCurve(QEasingCurve::Linear);
    p_startAnimation->addAnimation(p_opacityAnimation);

}

void CuMoLoader::setEndAnimation()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    p_endAnimation = new QParallelAnimationGroup(this);

    /* Position */
    p_posAnimation = new QPropertyAnimation();
    p_posAnimation->setTargetObject(p_image);
    p_posAnimation->setPropertyName("pos");
    p_posAnimation->setStartValue(QPointF(400-35, 300));
    p_posAnimation->setEndValue(QPointF(400-35, 481));
    p_posAnimation->setDuration(500);
    p_posAnimation->setEasingCurve(QEasingCurve::Linear);
    p_endAnimation->addAnimation(p_posAnimation);

    p_posAnimation = new QPropertyAnimation();
    p_posAnimation->setTargetObject(p_text);
    p_posAnimation->setPropertyName("pos");
    p_posAnimation->setStartValue(QPointF(400-20, 300+85));
    p_posAnimation->setEndValue(QPointF(400-20, 481+85));
    p_posAnimation->setDuration(500);
    p_posAnimation->setEasingCurve(QEasingCurve::Linear);
    p_endAnimation->addAnimation(p_posAnimation);

    /* Opacity */
    p_opacityAnimation = new QPropertyAnimation();
    p_opacityAnimation->setTargetObject(p_image);
    p_opacityAnimation->setPropertyName("opacity");
    p_opacityAnimation->setStartValue(1.0);
    p_opacityAnimation->setEndValue(0.0);
    p_opacityAnimation->setDuration(500);
    p_opacityAnimation->setEasingCurve(QEasingCurve::Linear);
    p_endAnimation->addAnimation(p_opacityAnimation);

    p_opacityAnimation = new QPropertyAnimation();
    p_opacityAnimation->setTargetObject(p_text);
    p_opacityAnimation->setPropertyName("opacity");
    p_opacityAnimation->setStartValue(1.0);
    p_opacityAnimation->setEndValue(0.0);
    p_opacityAnimation->setDuration(500);
    p_opacityAnimation->setEasingCurve(QEasingCurve::Linear);
    p_endAnimation->addAnimation(p_opacityAnimation);

}

void CuMoLoader::slt_startAnimation()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    p_background->setOpacity(0.5);
    this->setStartAnimation();
    p_startAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void CuMoLoader::slt_endAnimation()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    this->setEndAnimation();
    // connect(p_endAnimation, SIGNAL(finished()), p_startAnimation, SLOT(stop()));
    // connect(p_endAnimation, SIGNAL(finished()),this, SIGNAL(sig_loadFinished()));
    p_endAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    p_background->setOpacity(0.0);
}

void CuMoLoader::slt_setLoadingProgress(int value)
{
    p_text->setPlainText(QString("%1%").arg(value));
}
