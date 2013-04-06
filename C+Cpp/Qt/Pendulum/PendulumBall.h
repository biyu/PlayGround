#ifndef PENDULUMBALL_H
#define PENDULUMBALL_H

#include <QtGui>
#include "Box2D/Box2D.h"

class PendulumBall : public QGraphicsEllipseItem
{
public:
    PendulumBall(b2World *world, QGraphicsItem *parent = 0);

    void setupBody();
    void adjust();

    b2Body* getBody();

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent (QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    b2World *_world;
    b2Body *_body;
    b2Body* _groundBody;
    b2MouseJoint *_mouseJoint;
};

#endif // PENDULUMBALL_H
