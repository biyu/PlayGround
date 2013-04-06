#ifndef CUMOWIDGET_H
#define CUMOWIDGET_H

#include <QtCore>
#include <QtGui>

class CuMoWidget : public QGraphicsProxyWidget
{
    Q_OBJECT
    /* Property: Rotation degree around Y-axis */
    Q_PROPERTY(qreal rotationY READ rotationY WRITE setRotationY);
    /* Property: Scale item around Center point */
    Q_PROPERTY(qreal scaleC READ scaleC WRITE setScaleC);
    /* Property: Scale item with Rotation around Y-axis */
    Q_PROPERTY(qreal scaleCRotationY READ scaleCRotationY WRITE setScaleCRotationY);

public:

    CuMoWidget (QGraphicsProxyWidget* parent=0);

    ~CuMoWidget();

    /* Getter for property rotationY */
    qreal rotationY() const;
    /* Setter for property rotationY */
    void setRotationY(qreal degree);
    /* Getter for property scaleC */
    qreal scaleC() const;
    /* Setter for property scaleC */
    void setScaleC(qreal scale);
    /* Scale around center point and rotate around Y-axis */
    qreal scaleCRotationY() const;
    void setScaleCRotationY(qreal degree);

    /* Create property animations easily */
    void addPropertyAnimToGroup(QAnimationGroup* group,
                                const QByteArray & name,
                                int duration,
                                const QVariant & startValue,
                                const QVariant & endValue,
                                const QEasingCurve & curve);

protected:

    /* Degree for rotation around Y */
    qreal p_degree;
    qreal p_scale;
    qreal p_degreeForScale;
};
#endif // CUMOWIDGET_H
