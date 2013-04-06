#ifndef CUMOBACKEND_H
#define CUMOBACKEND_H

#include <QtGui>
#include <QtCore>
#include <QtWebKit>
#include <QtNetwork>
#include "CuMoCommon.h"

class CuMoBackend : public QObject
{
    Q_OBJECT

public:
    /* Constructor */
    CuMoBackend(QObject* parent = 0);
    /* Fetch movie information */
    void fetchMovieInfoPage();
    /* Get QWebPage ptr */
    QWebPage* getWebPage();
    /* Get movie information by index */
    CuMoMovieInfo* getMovieInfo(int index);
    /* Get schedule information */
    CuMoScheduleInfo* getScheduleInfo();
    /* Check network connections */
    bool checkNetwork();

protected:
    /* Overwrite run function of QThread */
    // void run();

private:
    /* Get document element in HTML file */
    QWebElement document();
    /* resetBackend */
    void resetBackend();

signals:
    /* Web page parsing finished */
    void sig_parseFinished(QList<CuMoMovieInfo*> infoList);

public slots:
    /* SLOT: Parse all information from web page */
    void slt_parseWebPage();
    /* SLOT: Parse movie information */
    void slt_parseMovieInfo(/*bool ok*/);
    /* SLOT: Parse schedule information */
    void slt_parseScheduleInfo(/*bool ok*/);
    /* TEMP SLOT: Change index of select box and refresh web page contents */
    void slt_scheduleChanged(CuMoScheduleChoices choises);

private:
    /* Web page for html parsing */
    QWebPage* p_page;
    /* Main frame of web page */
    QWebFrame* p_frame;
    /* List of movie infos */
    QList<CuMoMovieInfo*> p_movieInfoList;
    /* Schedule information */
    CuMoScheduleInfo* p_scheduleInfo;
    /* Network configuration manager */
    QNetworkConfigurationManager* p_networkManager;

private:
    static QString MOVIES_AVAILABLE_NOW;
    static QString MOVIES_TODAY;
};

#endif // CUMOBACKEND_H
