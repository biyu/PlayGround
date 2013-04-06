#include "CuMoWidget.h"

// Constructor; Initialize here
CuMoWidget::CuMoWidget(QGraphicsProxyWidget* parent)
    : QGraphicsProxyWidget(parent), p_degree(0), p_scale(0), p_degreeForScale(0)
{
}

// Destructor
CuMoWidget::~CuMoWidget()
{

}

qreal CuMoWidget::rotationY() const
{
    return p_degree;
}

void CuMoWidget::setRotationY(qreal degree)
{
    qreal centerX = this->rect().width()/2;
    qreal centerY = this->rect().height()/2;
    QTransform transform;
    transform.translate(centerX, centerY);
    transform.rotate(degree, Qt::YAxis);
    transform.translate(-centerX, -centerY);
    this->setTransform(transform);
    p_degree = degree;
}

qreal CuMoWidget::scaleC() const
{
    return p_scale;
}

void CuMoWidget::setScaleC(qreal scale)
{
    qreal centerX = this->rect().width()/2;
    qreal centerY = this->rect().height()/2;
    QTransform transform;
    transform.translate(centerX, centerY);
    transform.scale(scale, scale);
    transform.translate(-centerX, -centerY);
    this->setTransform(transform);
    p_scale = scale;
}

qreal CuMoWidget::scaleCRotationY() const
{
    return p_degreeForScale;
}

void CuMoWidget::setScaleCRotationY(qreal degree)
{
    qreal centerX = this->rect().width()/2;
    qreal centerY = this->rect().height()/2;
    QTransform transform;
    transform.translate(centerX, centerY);
    transform.rotate(degree, Qt::YAxis);
    qreal scale = 1 - sin(degree/180*3.14) * 0.5;
    transform.scale(scale, scale);
    transform.translate(-centerX, -centerY);
    this->setTransform(transform);
    p_degreeForScale = degree;
}

void CuMoWidget::addPropertyAnimToGroup(QAnimationGroup* group,
                                        const QByteArray & name,
                                        int duration,
                                        const QVariant & startValue,
                                        const QVariant & endValue,
                                        const QEasingCurve & curve)
{
    /* Create property animation */
    QPropertyAnimation *animation = new QPropertyAnimation();
    /* Set target object for this animation */
    animation->setTargetObject(this);
    /* Set property name */
    animation->setPropertyName(name);
    /* Set start value */
    animation->setStartValue(startValue);
    /* Set end value */
    animation->setEndValue(endValue);
    /* Set animation duration */
    animation->setDuration(duration);
    /* Set easing curve */
    animation->setEasingCurve(curve);
    /* Add animation into group */
    group->addAnimation(animation);
}
