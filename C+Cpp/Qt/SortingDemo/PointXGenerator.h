#ifndef POINTXGENERATOR_H
#define POINTXGENERATOR_H

#include <QtCore>

class PointXGenerator
{

public:
    PointXGenerator(int length);                //Can be extended later
    QList<int> generate();                      //Generate new shuffled point list
    void shuffle(QList<int>& pxl);              //Shuffle existing list

private:
    int _length;
};

#endif // POINTXGENERATOR_H
