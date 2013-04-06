#ifndef B2KART_H
#define B2KART_H

#include <QtGui>
#include <Box2D/Box2D.h>
#include <math.h>

class B2Kart
{
public:
    B2Kart(b2World* world, QGraphicsScene* scene);
    ~B2Kart();

    void init();
    void adjust();

    qreal getX();
    qreal getY();

    b2Vec2 getLinearVelocity();

    void setKartMotor(int key);

private:
    void createKartGraphic();
    void createKartB2Frame();

private:
    b2World* _world;
    QGraphicsScene* _scene;

    // Create b2Bodys
    b2Body* _frameBody;
    b2Body* _frameWheel_1;
    b2Body* _frameWheel_2;
    b2Body* _frameAxle_1;
    b2Body* _frameAxle_2;

    // Moters for Wheels
    b2RevoluteJoint* _frameMotor_1;
    b2RevoluteJoint* _frameMotor_2;

    // Sprints for Wheels
    b2PrismaticJoint* _frameSpring_1;
    b2PrismaticJoint* _frameSpring_2;

    // Graphics of Kart
    QGraphicsRectItem* _kartBody;
    QGraphicsEllipseItem* _kartWheel_1;
    QGraphicsEllipseItem* _kartWheel_2;

    qreal _x;
    qreal _y;
};

#endif // B2KART_H
