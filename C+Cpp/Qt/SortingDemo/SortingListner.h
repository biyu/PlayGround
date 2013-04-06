#ifndef SORTINGLISTNER_H
#define SORTINGLISTNER_H

#include <QList>

// Observer Pattern; TODO: Should be replaced by Signal and Slot
class SortingListner
{
public:
    virtual void pointUpdate() = 0;
    virtual void countInc() = 0;
};

#endif // SORTINGLISTNER_H
