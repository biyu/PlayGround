#include "CuMoBackend.h"

/* Webpage url for now-showing movies */
QString CuMoBackend::MOVIES_AVAILABLE_NOW = "http://www.finnkino.fi/eng/movies/now_showing";
QString CuMoBackend::MOVIES_TODAY = "https://www.finnkino.fi/eng/websales";

CuMoBackend::CuMoBackend(QObject* parent)
    : QObject(parent)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    /* Create web page parser */
    p_page = new QWebPage(this);
    /* Load html file for parsing */
    p_frame = p_page->mainFrame();
    /* Create network manager */
    p_networkManager = new QNetworkConfigurationManager(this);
}


bool CuMoBackend::checkNetwork()
{
    return p_networkManager->isOnline();
}


void CuMoBackend::fetchMovieInfoPage()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    p_frame->load(QUrl(MOVIES_AVAILABLE_NOW));
}

void CuMoBackend::slt_parseWebPage()
{
    /* Reset backend first */
    if(!p_movieInfoList.isEmpty())
        this->resetBackend();

    /* Parse movie information from web page */
    this->slt_parseMovieInfo();
    /* Parse schedule information from web page */
    this->slt_parseScheduleInfo();
    emit sig_parseFinished(p_movieInfoList);
}

void CuMoBackend::slt_parseMovieInfo(/*bool ok*/)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    qDebug() << "Page Loading Finished!";

    /* Start parsing movie informations by using jscript */
    QString parseMovieImage = "div[class*=eventImageDiv] img";
    /* Get all image elements in web page */
    QWebElementCollection movieImages = p_frame->findAllElements(parseMovieImage);
    /* Render images outof web page */
    foreach (QWebElement imageElement, movieImages)
    {
        /* Put all image into movie infos */
        QImage* image = new QImage(imageElement.geometry().size(), QImage::Format_RGB32);
        QPainter p;
        p.begin(image);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setRenderHint(QPainter::TextAntialiasing, true);
        p.setRenderHint(QPainter::SmoothPixmapTransform, true);
        imageElement.render(&p);
        p.end();
        /* Create movie info */
        CuMoMovieInfo* movieInfo = new CuMoMovieInfo();
        movieInfo->movieImage = image;
        p_movieInfoList << movieInfo;
    }
    /* Get movie names */
    QString parseMovieName = "span[class*=result_h]";
    QWebElementCollection movieNames = p_frame->findAllElements(parseMovieName);
    /* Put movie names into movie informations */
    for (int i=0; i<movieNames.count(); i++)
    {
        p_movieInfoList.at(i)->movieName = movieNames.at(i).toPlainText().toUpper();
    }
    /* Get movie description */
    QString parseMovieDescription = "div[style*='margin-top: 8px; margin-bottom: 8px; color: #333333;']";
    QWebElementCollection movieDescriptions = p_frame->findAllElements(parseMovieDescription);
    /* Put movie descriptions into movie informations */
    for (int i=0; i<movieNames.count(); i++)
    {
        p_movieInfoList.at(i)->movieDescription = movieDescriptions.at(i).toPlainText();
    }
    /* Get age limitation image */
    QString parseAgeLimit = "img[class*=agelimitBadge]";
    QWebElementCollection movieAgeLimit = p_frame->findAllElements(parseAgeLimit);
    for(int i=0; i<movieAgeLimit.count(); i++)
    {
        QWebElement ageLimitElement = movieAgeLimit.at(i);
        /* Put all image into movie infos */
        QImage* image = new QImage(ageLimitElement.geometry().size(), QImage::Format_RGB32);
        QPainter p;
        p.begin(image);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setRenderHint(QPainter::TextAntialiasing, true);
        p.setRenderHint(QPainter::SmoothPixmapTransform, true);
        ageLimitElement.render(&p);
        p.end();
        /* Create movie info */
        p_movieInfoList.at(i)->movieAgeLimit = image;
    }

    qDebug() << "image count: " << movieImages.count();
    qDebug() << "name count: " << movieNames.count();
    qDebug() << "description count: " << movieDescriptions.count();
    qDebug() << "age limit count: " << movieAgeLimit.count();
}

void CuMoBackend::slt_parseScheduleInfo(/*bool ok*/)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    /* Create schedule information */
    p_scheduleInfo = new CuMoScheduleInfo();
    /* Parse areas */
    QString parseAreas = "select[name=area] option";
    QWebElementCollection areas = p_frame->findAllElements(parseAreas);
    for(int i=0; i<areas.count(); i++)
    {
        p_scheduleInfo->areas << areas.at(i).toPlainText();
    }
    /* Set current area index */
    p_scheduleInfo->areas_index = document().findFirst("select[name=area]").evaluateJavaScript("this.selectedIndex").toInt();

    /* Parse dates */
    QString parseDates = "select[name=dt] option";
    QWebElementCollection dates = p_frame->findAllElements(parseDates);
    for(int i=0; i<dates.count(); i++)
    {
        p_scheduleInfo->dates << dates.at(i).toPlainText();
    }
    /* Set current date index */
    p_scheduleInfo->dates_index = document().findFirst("select[name=dt]").evaluateJavaScript("this.selectedIndex").toInt();

    /* Parse being times */
    // QString parseBeginTimes = "select[name=tm] option[value]";
    QString parseBeginTimes = "select[name=tm] option";
    QWebElementCollection beginTimes = p_frame->findAllElements(parseBeginTimes);
    for(int i=0; i<beginTimes.count(); i++)
    {
        p_scheduleInfo->beginTimes << beginTimes.at(i).toPlainText();
    }
    /* Set current begin-time index */
    p_scheduleInfo->beginTimes_index = document().findFirst("select[name=tm]").evaluateJavaScript("this.selectedIndex").toInt();

    /* Parse genres */
    QString parsegenres = "select[name=genre] option";
    QWebElementCollection genres = p_frame->findAllElements(parsegenres);
    for(int i=0; i<genres.count(); i++)
    {
        p_scheduleInfo->genres << genres.at(i).toPlainText();
    }
    /* Set current genres index */
    p_scheduleInfo->genres_index = document().findFirst("select[name=genre]").evaluateJavaScript("this.selectedIndex").toInt();

    qDebug() << "areas: " << p_scheduleInfo->areas.count();
    qDebug() << "dates: " << p_scheduleInfo->dates.count();
    qDebug() << "begin times: " << p_scheduleInfo->beginTimes.count();
    qDebug() << "genres: " << p_scheduleInfo->genres.count();
    qDebug() << "area_index" << p_scheduleInfo->areas_index;
    qDebug() << "date_index" << p_scheduleInfo->dates_index;
    qDebug() << "beginTime_index" << p_scheduleInfo->beginTimes_index;
    qDebug() << "genres_index" << p_scheduleInfo->genres_index;
}

void CuMoBackend::slt_scheduleChanged(CuMoScheduleChoices choises)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    int areaIndex = choises.selectArea;
    int dateIndex = choises.selectDate;
    int beginTimeIndex = choises.selectBeginTime;
    int genreIndex = choises.selectGenre;

    /* check if reloading needed */
    if(areaIndex == p_scheduleInfo->areas_index && dateIndex == p_scheduleInfo->dates_index
       && beginTimeIndex == p_scheduleInfo->beginTimes_index && genreIndex == p_scheduleInfo->genres_index)
        return;

    document().findFirst("select[name=area]").evaluateJavaScript(QString("this.selectedIndex=%1").arg(areaIndex));
    document().findFirst("select[name=dt]").evaluateJavaScript(QString("this.selectedIndex=%1").arg(dateIndex));
    document().findFirst("select[name=tm]").evaluateJavaScript(QString("this.selectedIndex=%1").arg(beginTimeIndex));
    document().findFirst("select[name=genre]").evaluateJavaScript(QString("this.selectedIndex=%1").arg(genreIndex));
    document().findFirst("form[onclick]").evaluateJavaScript("this.submit()");
}

void CuMoBackend::resetBackend()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    /* Clear movie information list */
    p_movieInfoList.clear();
    /* Delete schedule information list */
    delete p_scheduleInfo;
}

QWebElement CuMoBackend::document()
{
    return p_page->mainFrame()->documentElement();
}

QWebPage* CuMoBackend::getWebPage()
{
    return p_page;
}

CuMoMovieInfo* CuMoBackend::getMovieInfo(int index)
{
    return p_movieInfoList.at(index);
}

CuMoScheduleInfo* CuMoBackend::getScheduleInfo()
{
    return p_scheduleInfo;
}
