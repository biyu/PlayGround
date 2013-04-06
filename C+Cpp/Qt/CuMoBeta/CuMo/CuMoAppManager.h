#ifndef CUMOAPPMANAGER_H
#define CUMOAPPMANAGER_H

#include <QtCore>
#include <QtGui>

#include "CuMoGUI/CuMoCoverFlowView.h"
#include "CuMoGUI/CuMoLogo.h"
#include "CuMoGUI/CuMoButton.h"
#include "CuMoGUI/CuMoDialog.h"
#include "CuMoGUI/CuMoLoader.h"
#include "CuMoWebCore/CuMoBackend.h"
#include "CuMoCommon.h"

class CuMoAppManager : public QObject
{
    Q_OBJECT

public:
    /* Constructor */
    CuMoAppManager();
    /* Destructor */
    ~CuMoAppManager();
    /* Load application */
    void load();

private:
    /* Create main menu's UI */
    void createMainWindow();
    /* Create backend */
    void createBackend();
    /* Create connections */
    void createConnections();

signals:
    /* close the application */
    void sig_quit();

public slots:
    /* SLOT: Show movie info dialog */
    void slt_showMovieInfoDialog();
    /* SLOT: Show schedule dialog */
    void slt_showMovieScheduleDialog();
    /* SLOT: Web page parsing finished */
    void slt_parseFinished(QList<CuMoMovieInfo*> infoList);
    /* SLOT: Start loading web page */
    void slt_startLoading();
    /* SLOT: Finish loading web page */
    void slt_finishLoading();

private:
    /* Main window */
    QMainWindow* p_mainWindow;
    /* Central graphics view */
    QGraphicsView* p_view;
    /* Scene for graphics view */
    QGraphicsScene* p_scene;
    /* Coverflow */
    CuMoCoverFlowView* p_coverFlow;
    /* Schedule button */
    CuMoButton* p_scheduleButton;
    /* Login button */
    CuMoButton* p_loginButton;
    /* Exit button */
    CuMoButton* p_exitButton;
    /* Core backend */
    CuMoBackend* p_backend;
    /* Loader */
    CuMoLoader* p_loader;
};

#endif // CUMOAPPMANAGER_H
