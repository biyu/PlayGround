#include "PendulumBall.h"

PendulumBall::PendulumBall(b2World *world, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), _world(world), _body(0), _groundBody(0), _mouseJoint(0)
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;
    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

void PendulumBall::setupBody()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(x(), -y());
    _body = _world->CreateBody(&bd);

    b2CircleShape bodyShape;
    bodyShape.m_radius = this->rect().width()/2.0;

    b2FixtureDef fd;
    fd.shape = &bodyShape;
    fd.density = 1000.0f;
    fd.friction = 0.0f;
    fd.restitution = 1.0f;

    _body->CreateFixture(&fd);
}

void PendulumBall::adjust()
{
    //qDebug() << "~ " << __PRETTY_FUNCTION__;

    b2Vec2 position = _body->GetPosition();
    setPos(position.x, -position.y);
}

void PendulumBall::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "~ " << __PRETTY_FUNCTION__;

    b2BodyDef bodyDef;
    _groundBody = _world->CreateBody(&bodyDef);

    b2MouseJointDef md;
    md.bodyA = _groundBody;
    md.bodyB = _body;
    md.target = b2Vec2(event->scenePos().x(), -event->scenePos().y());
    md.maxForce = 100000.0f * _body->GetMass();

    _mouseJoint = (b2MouseJoint*)_world->CreateJoint(&md);
    _body->SetAwake(true);
}

void PendulumBall::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "~ " << __PRETTY_FUNCTION__;

    if (_mouseJoint)
    {
        _mouseJoint->SetTarget(b2Vec2(event->scenePos().x(), -event->scenePos().y()));
    }
}

void PendulumBall::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    //qDebug() << "~ " << __PRETTY_FUNCTION__;

    if (_mouseJoint)
    {
        _world->DestroyJoint(_mouseJoint);
        _mouseJoint = 0;
    }
}


b2Body* PendulumBall::getBody()
{
    return _body;
}
