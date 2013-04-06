#include "Pendulum.h"

static const int32 B2_VELOCITYITERATIONS = 10;
static const int32 B2_POSITIONITERATIONS = 10;
static const float32 B2_TIMESTEP = 1.0f / 60.0f;
static const float32 PENDULUM_LENGTH = 60.0f;

Pendulum::Pendulum(QWidget *parent)
    : QGraphicsView(parent), _timerId(0)
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    createScene();
    createB2World();
    createB2PendulumBalls();
    createB2PendulumJoints();
    createB2PendulumLines();
}

Pendulum::~Pendulum()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;
    delete _world;
}

void Pendulum::createScene()
{
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setBackgroundBrush(Qt::white);
    scene->setSceneRect(-110, -150, 220, 160);

    this->setScene(scene);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setRenderHint(QPainter::Antialiasing);
    this->scale(4, 4);
}

void Pendulum::createB2World()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    _world = new b2World(/* gravity = */ b2Vec2(0.0f, -300.0f), /* doSleep = */ true);
}

void Pendulum::createB2PendulumBalls()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    for(int i=0; i<BODYNUM; i++) {
        _ballItem[i] = new PendulumBall(_world);
        _ballItem[i]->setRect(-5.0, -5.0, 10.0, 10.0);
        _ballItem[i]->setPos(i*11.5, -50.0);
        _ballItem[i]->setBrush(QColor(Qt::red));
        _ballItem[i]->setupBody();
        this->scene()->addItem(_ballItem[i]);
    }
}

void Pendulum::createB2PendulumJoints()
{
    for(int i=0; i<BODYNUM; i++) {
        float32 x = _ballItem[i]->x();
        float32 y = _ballItem[i]->y();

        b2BodyDef jointBodyDef;
        jointBodyDef.position.Set(x, -y + PENDULUM_LENGTH);
        jointBodyDef.type = b2_staticBody;
        b2Body* jointBody = _world->CreateBody(&jointBodyDef);

        b2RevoluteJointDef jointDef;
        jointDef.Initialize(_ballItem[i]->getBody(), jointBody, b2Vec2(x, -y + PENDULUM_LENGTH));

        jointDef.lowerAngle = -0.25f * b2_pi; // -45 degrees
        jointDef.upperAngle = 0.25f * b2_pi; // 45 degrees
        jointDef.enableLimit = false;

        _world->CreateJoint(&jointDef);

        _jointVertex[i].setX(x);
        _jointVertex[i].setY(y - PENDULUM_LENGTH);
    }
}

void Pendulum::createB2PendulumLines()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    for(int i=0; i<BODYNUM; i++) {
        _lines[i] =  this->scene()->addLine(_ballItem[i]->x(), _ballItem[i]->y()
                                            , _jointVertex[i].x(), _jointVertex[i].y());
    }
}

void Pendulum::updatePudulumLines()
{
    for(int i=0; i<BODYNUM; i++) {
        _lines[i]->setLine(_ballItem[i]->x(), _ballItem[i]->y()
                           , _jointVertex[i].x(), _jointVertex[i].y());
    }
}

void Pendulum::start()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    if (!_timerId) {
        _timerId = startTimer(1000 / 60.0);
    }
}

void Pendulum::timerEvent(QTimerEvent *event)
{
    //qDebug() << "~ " << __PRETTY_FUNCTION__;

    if (event->timerId() == _timerId) {
        _world->Step(B2_TIMESTEP, B2_VELOCITYITERATIONS, B2_POSITIONITERATIONS);
        for(int i=0; i<BODYNUM; i++) {
            _ballItem[i]->adjust();
            updatePudulumLines();
        }
    }
    QObject::timerEvent(event);
}
