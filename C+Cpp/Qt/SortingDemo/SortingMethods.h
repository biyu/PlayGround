#ifndef SORTINGMETHODS_H
#define SORTINGMETHODS_H

#include "PointXGenerator.h"
#include "SortingListner.h"

#include <QtCore>
#include <QtGlobal>
#include <QObject>
#include <QtDebug>
#include <iostream>

class PointXGenerator;

class SortingMethods : public QObject
{
    Q_OBJECT
public:
    enum SORTTYPE {
        BUBBLESORT,
        INSERTSORT
    };

    SortingMethods(PointXGenerator* pg, QObject* parent=0);

    QList<int> getPointXList();             // Getter
    void addListner(SortingListner* sl);    // Add listner; call pointUpdate()
    void setSortType(SORTTYPE st);
    bool isSorted();
    void setPause(bool pause);

public slots:
    void startSort();
    void newSort();
    void reset();

private:
    void bubbleSort();                      // Implement sorting algorithms here
    void insertSort();

    // Refactor method into small pieces
    void selectAndSort();
    void pointUpdate();
    void countUpdate();

private:
    PointXGenerator* _pointGenerator;
    QList<int> _pointXList;
    QList<int> _pxlBackUp;
    QList<SortingListner*> _sortListners;
    SORTTYPE _stype;

    bool _isSorted;
    bool _pause;
};

#endif // SORTINGMETHODS_H
