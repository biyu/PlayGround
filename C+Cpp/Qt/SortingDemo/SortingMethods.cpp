#include "SortingMethods.h"

SortingMethods::SortingMethods(PointXGenerator *pg, QObject* parent)
    : QObject(parent), _pointGenerator(pg), _stype(BUBBLESORT), _isSorted(false), _pause(true)
{
    _pointXList = _pxlBackUp = _pointGenerator->generate();     // implicit sharing: copying a Qt container is about as fast as copying a single pointer
}

void SortingMethods::startSort()
{
    //resetSort();                  // If sorted, shuffle it
    if(!_isSorted && !_pause)
        selectAndSort();
}

void SortingMethods::selectAndSort()
{
    switch(_stype)
    {
    case BUBBLESORT:
        bubbleSort();                   // Switch sorting methods
        break;
    case INSERTSORT:
        insertSort();
        break;
    }
}

void SortingMethods::newSort()
{
    _pointGenerator->shuffle(_pointXList);
    _pxlBackUp = _pointXList;
    pointUpdate();
    _isSorted = false;
}

void SortingMethods::reset()
{
    _pointXList = _pxlBackUp;
    pointUpdate();
    _isSorted = false;
}

void SortingMethods::insertSort()
{
    static int _insertCount = 1;
    if(_insertCount < _pointXList.length())
    {
        bool swapped = false;
        bool needUpdate = false;

        int value = _pointXList.at(_insertCount);     // get value of i:th item
        int j = _insertCount - 1;

        while(j>=0 && !swapped)
        {
            if(_pointXList.at(j) > value)
            {
                _pointXList.swap(j+1, j);
                j--;
                needUpdate = true;
            }
            else
                swapped = true;
        }

        if(needUpdate)
            countUpdate();

        pointUpdate();
        _insertCount++;
    }
    else
    {
        _insertCount = 1;
        _isSorted = true;
        _pause = true;
    }
}

void SortingMethods::bubbleSort()
{
    bool swapped = true;

    for(int i=0; i<_pointXList.length()-1; i++)
    {
        if(_pointXList.at(i) > _pointXList.at(i+1))
        {
            _pointXList.swap(i, i+1);
            swapped = false;
        }
    }

    if(!swapped)
        countUpdate();

    pointUpdate();

    if(swapped)
    {
        _isSorted = true;
        _pause = true;
    }
}

void SortingMethods::pointUpdate()
{
    for(int i=0; i<_sortListners.length(); i++)
        _sortListners.at(i)->pointUpdate();
}

void SortingMethods::countUpdate()
{
    for(int i=0; i<_sortListners.length(); i++)
        _sortListners.at(i)->countInc();
}

void SortingMethods::setSortType(SORTTYPE st)
{
    _stype = st;
}

QList<int> SortingMethods::getPointXList()
{
    return _pointXList;
}

void SortingMethods::addListner(SortingListner* sl)
{
    _sortListners.append(sl);
}

bool SortingMethods::isSorted()
{
    return _isSorted;
}

void SortingMethods::setPause(bool pause)
{
    _pause = pause;
}
