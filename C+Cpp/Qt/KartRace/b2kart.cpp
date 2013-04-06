#include "b2kart.h"

static const float32 PI = 3.14;

B2Kart::B2Kart(b2World* world, QGraphicsScene* scene)
    : _world(world), _scene(scene), _frameBody(0), _frameWheel_1(0), _frameWheel_2(0), _frameAxle_1(0), _frameAxle_2(0)
    , _frameMotor_1(0), _frameMotor_2(0), _frameSpring_1(0), _frameSpring_2(0), _kartBody(0), _kartWheel_1(0), _kartWheel_2(0)
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    init();

}

B2Kart::~B2Kart()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    //delete b2World bodies
    _world->DestroyBody(_frameBody);
    _world->DestroyBody(_frameWheel_1);
    _world->DestroyBody(_frameWheel_2);

    // remove graphics items from scene
    _scene->removeItem(_kartBody);
    _scene->removeItem(_kartWheel_1);
    _scene->removeItem(_kartWheel_2);

    // free memory
    delete _kartBody;
    delete _kartWheel_1;
    delete _kartWheel_2;
}

void B2Kart::init()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    createKartGraphic();
    createKartB2Frame();
}


void B2Kart::createKartGraphic()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    // create kart's body
    _kartBody = new QGraphicsRectItem();
    _kartBody->setRect(-1.5, -0.3, 3, 0.6);
    _kartBody->setPos(0, -3.5);
    _kartBody->setBrush(Qt::gray);
    _kartBody->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    _scene->addItem(_kartBody);

    // create kart's forward wheel
    _kartWheel_1 = new QGraphicsEllipseItem();
    _kartWheel_1->setRect(-0.7, -0.7, 1.4, 1.4);
    _kartWheel_1->setPos(_kartBody->x()-(1+0.6*cos(PI/3.0))- 0.3*cos(PI/3.0)
                         , _kartBody->y()+(0.3+0.6*sin(PI/3.0))+0.3*sin(PI/3.0));

    QConicalGradient gradient(0, 0, 60);
    _kartWheel_1->setBrush(gradient);
    _kartWheel_1->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    _scene->addItem(_kartWheel_1);

    //    // create kart's backward wheel
    _kartWheel_2 = new QGraphicsEllipseItem();
    _kartWheel_2->setRect(-0.7, -0.7, 1.4, 1.4);
    _kartWheel_2->setPos(_kartBody->x()+(1+0.6*cos(PI/3.0))+ 0.3*cos(PI/3.0)
                         , _kartBody->y()+(0.3-0.6*sin(-PI/3.0))+0.3*sin(PI/3.0));

    _kartWheel_2->setBrush(gradient);
    _kartWheel_2->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    _scene->addItem(_kartWheel_2);
}

void B2Kart::createKartB2Frame()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    // Setup kart body's frame
    b2BodyDef frameBodyDef;
    frameBodyDef.type = b2_dynamicBody;
    frameBodyDef.position.Set(_kartBody->x(), -_kartBody->y());

    b2PolygonShape frameBodyShape;
    frameBodyShape.SetAsBox(_kartBody->rect().width()/2.0, _kartBody->rect().height()/2.0, b2Vec2(0, 0), 0);

    b2FixtureDef frameBodyFixture;
    frameBodyFixture.shape = &frameBodyShape;
    frameBodyFixture.density = 2.0f;
    frameBodyFixture.friction = 0.5f;
    frameBodyFixture.restitution = 0.2f;
    frameBodyFixture.filter.groupIndex = -1;

    _frameBody = _world->CreateBody(&frameBodyDef);
    _frameBody->CreateFixture(&frameBodyFixture);                   // create main shape

    frameBodyShape.SetAsBox(_kartBody->rect().width()/4.0-0.35, _kartBody->rect().height()/4.0
                            ,b2Vec2(-(_kartBody->rect().width()/2.0-0.5), -_kartBody->rect().height()/2.0), PI/3.0);
    _frameBody->CreateFixture(&frameBodyFixture);                   // create left foot

    frameBodyShape.SetAsBox(_kartBody->rect().width()/4.0-0.35, _kartBody->rect().height()/4.0
                            , b2Vec2(_kartBody->rect().width()/2.0-0.5, -_kartBody->rect().height()/2.0), -PI/3.0);
    _frameBody->CreateFixture(&frameBodyFixture);                   // create right foot

    // Setup kart axles's body

    frameBodyFixture.density = 1.0f;

    _frameAxle_1 = _world->CreateBody(&frameBodyDef);

    frameBodyShape.SetAsBox(_kartBody->rect().width()/4.0-0.35, _kartBody->rect().height()/4.0-0.05
                            , b2Vec2(-(_kartBody->rect().width()/2.0-0.5)-0.6*cos(PI/3.0), -_kartBody->rect().height()/2.0-0.6*sin(PI/3.0))
                            , PI/3.0);
    _frameAxle_1->CreateFixture(&frameBodyFixture);                 // create left axle

    b2PrismaticJointDef pJointDef;
    pJointDef.Initialize(_frameBody, _frameAxle_1, _frameAxle_1->GetWorldCenter(), b2Vec2(cos(PI/3.0), sin(PI/3.0)));
    pJointDef.lowerTranslation = -0.3f;
    pJointDef.upperTranslation = 0.5f;
    pJointDef.enableLimit = true;
    pJointDef.enableMotor = true;

    _frameSpring_1 = (b2PrismaticJoint*) _world->CreateJoint(&pJointDef);

    _frameAxle_2 = _world->CreateBody(&frameBodyDef);

    frameBodyShape.SetAsBox(_kartBody->rect().width()/4.0-0.35, _kartBody->rect().height()/4.0-0.05
                            , b2Vec2((_kartBody->rect().width()/2.0-0.5)+0.6*cos(-PI/3.0), -_kartBody->rect().height()/2.0-0.6*sin(PI/3.0))
                            , -PI/3.0);
    _frameAxle_2->CreateFixture(&frameBodyFixture);                 // create right axle

    pJointDef.Initialize(_frameBody, _frameAxle_2, _frameAxle_2->GetWorldCenter(), b2Vec2(-cos(PI/3.0), sin(PI/3.0)));
    _frameSpring_2 = (b2PrismaticJoint*) _world->CreateJoint(&pJointDef);

    // Setup kart wheel's frame
    b2BodyDef frameWheelDef;
    frameWheelDef.type = b2_dynamicBody;
    frameWheelDef.position.Set(_kartWheel_1->x(), -_kartWheel_1->y());
    frameWheelDef.allowSleep = false;

    b2CircleShape frameWheelShape;
    frameWheelShape.m_radius = _kartWheel_1->rect().width()/2.0;

    b2FixtureDef frameWheelFixture;
    frameWheelFixture.shape = &frameWheelShape;
    frameWheelFixture.density = 1.0f;
    frameWheelFixture.friction = 5.0f;
    frameWheelFixture.restitution = 0.2f;
    frameWheelFixture.filter.groupIndex = -1;

    _frameWheel_1 = _world->CreateBody(&frameWheelDef);         // create wheel 1
    _frameWheel_1->CreateFixture(&frameWheelFixture);

    frameWheelDef.position.Set(_kartWheel_2->x(), -_kartWheel_2->y());
    _frameWheel_2 = _world->CreateBody(&frameWheelDef);         // create wheel 2
    _frameWheel_2->CreateFixture(&frameWheelFixture);

    // create revolute joint
    b2RevoluteJointDef rJointDef;
    rJointDef.enableMotor = true;

    rJointDef.Initialize(_frameWheel_1, _frameAxle_1, _frameWheel_1->GetWorldCenter());
    _frameMotor_1 = (b2RevoluteJoint*) _world->CreateJoint(&rJointDef);

    rJointDef.Initialize(_frameWheel_2, _frameAxle_2,  _frameWheel_2->GetWorldCenter());
    _frameMotor_2 = (b2RevoluteJoint*) _world->CreateJoint(&rJointDef);
}

qreal B2Kart::getX()
{
    return _x;
}

qreal B2Kart::getY()
{
    return _y;
}

b2Vec2 B2Kart::getLinearVelocity()
{
    return b2Vec2(_frameBody->GetLinearVelocity().x, -_frameBody->GetLinearVelocity().y);
}

void B2Kart::setKartMotor(int key)
{
    _frameMotor_1->SetMotorSpeed(35*PI * (key == Qt::Key_Left ? -1 : key == Qt::Key_Right ? 1 : 0));
    _frameMotor_1->SetMaxMotorTorque(key == Qt::Key_Left || key == Qt::Key_Right ? 17 : 0.5);

    _frameMotor_2->SetMotorSpeed(35*PI * (key == Qt::Key_Left ? -1 : key == Qt::Key_Right ? 1 : 0));
    _frameMotor_2->SetMaxMotorTorque(key == Qt::Key_Left || key == Qt::Key_Right ? 12 : 0.5);

    _frameBody->ApplyTorque(50*(key == Qt::Key_Left ? 1: key == Qt::Key_Right ? -1 : 0));
}

void B2Kart::adjust()
{
    //qDebug() << "~ " << __PRETTY_FUNCTION__;

    // update body

    b2Vec2 kartBodyPos = _frameBody->GetPosition();
    _kartBody->setPos(kartBodyPos.x, -kartBodyPos.y);

    float32 kartBodyAngle = _frameBody->GetAngle();
    _kartBody->setRotation(-(kartBodyAngle * 360.0) / (2 * PI));

    // update kart x and y

    _x = kartBodyPos.x;
    _y = -kartBodyPos.y;

    // update forward wheel

    b2Vec2 kartWheel_1_Pos = _frameWheel_1->GetPosition();
    _kartWheel_1->setPos(kartWheel_1_Pos.x, -kartWheel_1_Pos.y);

    float32 kartWheel_1_Angle = _frameWheel_1->GetAngle();
    _kartWheel_1->setRotation(-(kartWheel_1_Angle * 360.0) / (2 * PI));

    // update backward wheel

    b2Vec2 kartWheel_2_Pos = _frameWheel_2->GetPosition();
    _kartWheel_2->setPos(kartWheel_2_Pos.x, -kartWheel_2_Pos.y);

    float32 kartWheel_2_Angle = _frameWheel_2->GetAngle();
    _kartWheel_2->setRotation(-(kartWheel_2_Angle * 360.0) / (2 * PI));

    // update springs

    _frameSpring_1->SetMaxMotorForce(30+abs(800*pow(_frameSpring_1->GetJointTranslation(), 2)));
    _frameSpring_1->SetMotorSpeed((_frameSpring_1->GetMotorSpeed() - 10*_frameSpring_1->GetJointTranslation())*0.4);

    _frameSpring_2->SetMaxMotorForce(30+abs(800*pow(_frameSpring_2->GetJointTranslation(), 2)));
    _frameSpring_2->SetMotorSpeed((_frameSpring_2->GetMotorSpeed() - 10*_frameSpring_2->GetJointTranslation())*0.4);

}
