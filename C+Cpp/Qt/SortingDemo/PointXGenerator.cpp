#include "PointXGenerator.h"

PointXGenerator::PointXGenerator(int length):_length(length)
{
}

QList<int> PointXGenerator::generate()
{
    QList<int> newXList;
    for(int i=1; i<=_length; i++)
        newXList.append(i);

    shuffle(newXList);
    return newXList;
}

void PointXGenerator::shuffle(QList<int> &pxl)
{
    int len = pxl.length();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0; i<len; i++)
    {
        int rd = qrand()%100;
        pxl.swap(rd, i);
    }
}
