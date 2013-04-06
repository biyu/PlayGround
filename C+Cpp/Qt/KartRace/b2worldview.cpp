#include "b2worldview.h"

static const int32 B2_VELOCITYITERATIONS = 10;
static const int32 B2_POSITIONITERATIONS = 10;
static const float32 B2_TIMESTEP = 1.0f / 60.0f;

static const float32 PI = 3.14;

B2WorldView::B2WorldView(QWidget *parent)
    : QGraphicsView(parent), _timerId(0), _isLeftDown(false), _isRightDown(false)
    , _isResetDown(false), _world(0), _scene(0), _kart(0)
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    // init view, scene and b2world
    createScene();
    createB2World();
    setupView();
    createWorldItems();
    start();
}

B2WorldView::~B2WorldView()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    if(_world) {
        delete _world;
    }
}

void B2WorldView::createScene()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    _scene = new QGraphicsScene();
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    _scene->setBackgroundBrush(Qt::white);
    _scene->setSceneRect(-100, -50, 200, 52);

}

void B2WorldView::createB2World()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    _world = new b2World(b2Vec2(0.0f, -10.0f), true);

}

void B2WorldView::createWorldItems()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    if(_world && _scene) {

        // create world ground

        QGraphicsRectItem *groundItem = _scene->addRect(-100, -0.5, 200, 1);
        groundItem->setBrush(Qt::gray);
        groundItem->setPos(0, -0.5);

        // ground body define
        b2BodyDef groundBD;
        groundBD.type = b2_staticBody;
        groundBD.position.Set(0.0f, 0.5f);

        // ground shape define
        b2PolygonShape groundSD;
        groundSD.SetAsBox(100.0f, 0.5f, b2Vec2(0.0f, 0.0f), 0);

        // ground fixture define
        b2FixtureDef groundFD;
        groundFD.shape = &groundSD;
        groundFD.density = 0.1f;
        groundFD.friction = 5.0f;

        b2Body* groundBody = _world->CreateBody(&groundBD);
        groundBody->CreateFixture(&groundFD);

        groundItem = _scene->addRect(-1.0, -2.0, 2.0, 4.0);
        groundItem->setBrush(Qt::blue);
        groundItem->setPos(-100.0, -1.0);

        groundSD.SetAsBox(1.0f, 2.0f, b2Vec2(-100.0f, 0.5f), 0);
        groundBody->CreateFixture(&groundFD);

        groundItem = _scene->addRect(-1.0, -2.0, 2.0, 4.0);
        groundItem->setBrush(Qt::blue);
        groundItem->setPos(100.0, -0.5);

        groundSD.SetAsBox(1.0f, 2.0f, b2Vec2(100.0f, 1.0f), 0);
        groundBody->CreateFixture(&groundFD);

        groundItem = _scene->addRect(-3.0, -0.5, 6.0, 1.0);
        groundItem->setBrush(Qt::blue);
        groundItem->setPos(5, -2.0);
        groundItem->setRotation(-(PI / 4.0 * 360.0) / (2 * PI));

        groundSD.SetAsBox(3.0f, 0.5f, b2Vec2(5.0f, 1.5f), PI/4.0);
        groundBody->CreateFixture(&groundFD);

        groundItem = _scene->addRect(-3.0, -0.5, 6.0, 1.0);
        groundItem->setBrush(Qt::blue);
        groundItem->setPos(3.5, -1.5);
        groundItem->setRotation(-(PI / 8.0 * 360.0) / (2 * PI));

        groundSD.SetAsBox(3.0f, 0.5f, b2Vec2(3.5f, 1.0f), PI/8.0);
        groundBody->CreateFixture(&groundFD);

        groundItem = _scene->addRect(-3.0, -0.5, 6, 1.0);
        groundItem->setBrush(Qt::blue);
        groundItem->setPos(9, -2.0);
        groundItem->setRotation(-(-PI / 4.0 * 360.0) / (2 * PI));

        groundSD.SetAsBox(3.0f, 0.5f, b2Vec2(9.0f, 1.5f), -PI/4.0);
        groundBody->CreateFixture(&groundFD);

        groundItem = _scene->addRect(-3, -0.5, 6, 1.0);
        groundItem->setBrush(Qt::blue);
        groundItem->setPos(10.5, -1.5);
        groundItem->setRotation(-(-PI / 8.0 * 360.0) / (2 * PI));

        groundSD.SetAsBox(3.0f, 0.5f, b2Vec2(10.5f, 1.0f), -PI/8.0);
        groundBody->CreateFixture(&groundFD);

        // add random shit //

        b2CircleShape circleShape;

        b2FixtureDef circleFixture;
        circleFixture.shape = &circleShape;
        circleFixture.density = 0.01;
        circleFixture.friction = 0.1;
        circleFixture.restitution = 0.5;

        for (int i = 0; i < 30; i++) {

            qreal radius = qrand()%20*0.01+0.02;

            QGraphicsEllipseItem* circle = _scene->addEllipse(-radius, -radius, radius*2, radius*2);
            circle->setBrush(Qt::green);
            circle->setPos(qrand()%35+15.0, -1.5);

            _circles << circle;

            circleShape.m_radius = radius;

            b2BodyDef circleBD;
            circleBD.type = b2_dynamicBody;
            circleBD.position.Set(circle->pos().x(), -circle->pos().y());
            circleBD.allowSleep = true;
            circleBD.linearDamping = 0.1;
            circleBD.angularDamping = 0.1;

            b2Body* circleBody = _world->CreateBody(&circleBD);
            circleBody->CreateFixture(&circleFixture);

            _circleBodies << circleBody;
        }

        // create kart
        _kart = new B2Kart(_world, _scene);
    }
}

void B2WorldView::setupView()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    if(_scene) {
        this->setScene(_scene);
        this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        this->setRenderHint(QPainter::Antialiasing);
        this->centerOn(0, 0);
        this->scale(40, 40);
    }
}

void B2WorldView::resetKart()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    if(_kart) {
        delete _kart;
        _kart = new B2Kart(_world, _scene);
    }
    _isResetDown = false;
}

void B2WorldView::start()
{
    qDebug() << "~ " << __PRETTY_FUNCTION__;

    if (!_timerId) {
        _timerId = startTimer(1000 / 60.0);
    }
}

void B2WorldView::timerEvent(QTimerEvent *event)
{
    // qDebug() << "~ " << __PRETTY_FUNCTION__;

    if (event->timerId() == _timerId) {

        if (_world && _kart) {
            // update b2World step
            _world->Step(B2_TIMESTEP, B2_VELOCITYITERATIONS, B2_POSITIONITERATIONS);

            // update kart's motors
            _kart->setKartMotor(_isLeftDown ? Qt::Key_Left : _isRightDown ? Qt::Key_Right : -1);

            // update pos of items here
            _kart->adjust();

            this->centerOn(_kart->getX()+_kart->getLinearVelocity().x*0.2, _kart->getY()-_kart->getLinearVelocity().y*0.2);

            // udpate circle shits

            for(int i=0; i<_circles.length(); i++) {
                b2Vec2 pos = _circleBodies.at(i)->GetPosition();
                _circles.at(i)->setPos(pos.x, -pos.y);
            }
        }

        if (_isResetDown) {
            resetKart();
        }
    }
    QObject::timerEvent(event);
}

void B2WorldView::keyPressEvent(QKeyEvent* event)
{
    // qDebug() << "~ " << __PRETTY_FUNCTION__;

    switch(event->key())
    {
    case Qt::Key_Left:
        _isLeftDown = true;
        break;
    case Qt::Key_Right:
        _isRightDown = true;
        break;
    case Qt::Key_Space:
        // TODO: Jump The Kart
        break;
    case Qt::Key_R:
        // Reset The Kart
        _isResetDown = true;
        break;
    default:
        break;
    }
}

void B2WorldView::keyReleaseEvent(QKeyEvent* event)
{
    // qDebug() << "~ " << __PRETTY_FUNCTION__;

    switch(event->key())
    {
    case Qt::Key_Left:
        _isLeftDown = false;
        break;
    case Qt::Key_Right:
        _isRightDown = false;
        break;
    default:
        break;
    }

}
