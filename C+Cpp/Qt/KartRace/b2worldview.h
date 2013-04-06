#ifndef B2WORLDVIEW_H
#define B2WORLDVIEW_H

#include <QtGui>
#include <Box2D/Box2D.h>

#include <b2kart.h>

class B2WorldView : public QGraphicsView
{
    Q_OBJECT
public:
    B2WorldView(QWidget *parent = 0);
    ~B2WorldView();

    void start();

protected:
    void timerEvent(QTimerEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    void createScene();
    void createB2World();
    void setupView();

    void createWorldItems();
    void resetKart();

private:
    int _timerId;   // timer ID
    bool _isLeftDown;
    bool _isRightDown;
    bool _isResetDown;

    b2World *_world;
    QGraphicsScene *_scene;
    B2Kart* _kart;
    QList<QGraphicsEllipseItem*> _circles;
    QList<b2Body*> _circleBodies;

};


#endif // B2WORLDVIEW_H
