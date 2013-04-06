#ifndef CUMOCOMMON_H
#define CUMOCOMMON_H

#include <QtCore>

class CuMoMovieInfo
{
public:
    QImage* movieImage;
    QString movieName;
    QString movieDescription;
    QImage* movieAgeLimit;
};

class CuMoScheduleInfo
{
public:
    /* Item list of combobox */
    QStringList areas;
    QStringList dates;
    QStringList beginTimes;
    QStringList genres;
    /* Current index */
    int areas_index;
    int dates_index;
    int beginTimes_index;
    int genres_index;
};

class CuMoScheduleChoices
{
public:
    int selectArea;
    int selectDate;
    int selectBeginTime;
    int selectGenre;
};

#endif // CUMOCOMMON_H
