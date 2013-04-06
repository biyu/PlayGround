#ifndef FLICKABLE_H
#define FLICKABLE_H

class QMouseEvent;
class QPoint;
class QWidget;

class FlickableTicker;
class FlickablePrivate;

class Flickable
{
public:

    Flickable();
    virtual ~Flickable();

    void setThreshold(int threshold);
    int threshold() const;

    void setAcceptMouseClick(QWidget *target);

    void handleMousePress(QMouseEvent *event);
    void handleMouseMove(QMouseEvent *event);
    void handleMouseRelease(QMouseEvent *event);

    /* Set the offset mannually */
    void setInnerOffset(QPoint offset);
    bool isSteady();
    bool isStop();

protected:
    virtual QPoint scrollOffset() const = 0;
    virtual void setScrollOffset(const QPoint &offset) = 0;

private:
    void tick();

private:
    FlickablePrivate *d;
    friend class FlickableTicker;
};

#endif // FLICKABLE_H

