#ifndef CUMOBUTTON_H
#define CUMOBUTTON_H

#include <QtGui>
#include <QtCore>
#include "CuMoWidget.h"

class CuMoButton : public CuMoWidget
{
    Q_OBJECT

public:
    enum ButtonType {
        /* SCHEDULE, LOGIN */
        GENERIC,
        /* EXIT */
        EXIT,
        /* OK, CANCEL */
        CONTROL
    };

    CuMoButton(ButtonType buttonType, QString buttonLabel, QGraphicsProxyWidget* parent=0);
    ~CuMoButton();

    void configGeometry(const QRect & rect);
    QString getLabel();
    void setLabel(QString);
    QPushButton const *getButton();

signals:
    void pressed();
    void released();

public slots:
    // void test();

protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
    QRect _rect;
    QString _buttonLabel;
    ButtonType _buttonType;
    QPushButton *_pushButton;
};

#endif // CUMOBUTTON_H
