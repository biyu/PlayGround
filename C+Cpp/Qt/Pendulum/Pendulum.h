#ifndef PENDULUM_H
#define PENDULUM_H

#include <QtGui>
#include "PendulumBall.h"

class Pendulum : public QGraphicsView
{
    Q_OBJECT
    enum {
        BODYNUM = 6
    };
public:
    Pendulum(QWidget *parent = 0);
    ~Pendulum();
    void start();

protected:
    void timerEvent(QTimerEvent *event);

private:
    void createScene();
    void createB2World();
    void createB2PendulumBalls();
    void createB2PendulumJoints();

    void createB2PendulumLines();
    void updatePudulumLines();

private:
    int _timerId;
    b2World *_world;
    PendulumBall* _ballItem[BODYNUM];
    QPointF _jointVertex[BODYNUM];
    QGraphicsLineItem* _lines[BODYNUM];
};

#endif // PENDULUM_H
