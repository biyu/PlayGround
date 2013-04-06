#include "CuMoAppManager.h"

CuMoAppManager::CuMoAppManager()
    : p_mainWindow(0),p_view(0), p_scene(0), p_coverFlow(0)
    , p_scheduleButton(0), p_loginButton(0), p_exitButton(0), p_backend(0)
    , p_loader(0)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    createMainWindow();
    createBackend();
    createConnections();
}

CuMoAppManager::~CuMoAppManager()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
}

void CuMoAppManager::load()
{
    QTimer::singleShot(0, this, SLOT(slt_startLoading()));
}

void CuMoAppManager::createMainWindow()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    p_mainWindow = new QMainWindow();

    p_scene = new QGraphicsScene(0,0,800,480);
    p_view = new QGraphicsView(p_scene);

    p_view->setFixedSize(800, 480);
    p_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    p_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    p_view->setFrameStyle(0);
    p_view->showFullScreen();
    p_view->setBackgroundBrush(QColor(14, 48, 21));

    p_coverFlow = new CuMoCoverFlowView(QSize(800, 320));
    QGraphicsProxyWidget* coverFlow = p_scene->addWidget(p_coverFlow);
    coverFlow->setPos(0, 80);

    p_scheduleButton = new CuMoButton(CuMoButton::GENERIC, QString("SCHEDULE"));
    p_scheduleButton->configGeometry(QRect(10, 420, 120, 50));
    p_scene->addItem(p_scheduleButton);

    p_loginButton = new CuMoButton(CuMoButton::GENERIC, QString("LOGIN"));
    p_loginButton->configGeometry(QRect(670, 420, 120, 50));
    p_scene->addItem(p_loginButton);

    p_exitButton = new CuMoButton(CuMoButton::EXIT, QString("x"));
    p_exitButton->configGeometry(QRect(720, 15, 50, 50));
    p_scene->addItem(p_exitButton);

    /* Create loader, but not show it at once */
    p_loader = new CuMoLoader();

    p_mainWindow->setFixedSize(800, 480);
    p_mainWindow->showFullScreen();
    p_mainWindow->setCentralWidget(p_view);
    p_mainWindow->show();
}

void CuMoAppManager::createBackend()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    /* Create web backend */
    p_backend = new CuMoBackend(this);
}

void CuMoAppManager::createConnections()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    /* Connect signal and slot to show dialog */
    /* Show movie information dialog when coverflow item is clicked */
    QObject::connect(p_coverFlow, SIGNAL(sig_showInfoDialogInMainView()), this, SLOT(slt_showMovieInfoDialog()));
    /* Create coverflow items based on movie informations */
    QObject::connect(p_backend, SIGNAL(sig_parseFinished(QList<CuMoMovieInfo*>)), p_coverFlow, SLOT(slt_createCoverFlowItems(QList<CuMoMovieInfo*>)));
    /* Start loader animation when web page loading */
    QObject::connect(p_backend->getWebPage()->mainFrame(), SIGNAL(loadStarted()), p_loader, SLOT(slt_startAnimation()));
    /* Process information when web page loading finished */
    QObject::connect(p_backend->getWebPage()->mainFrame(), SIGNAL(loadFinished(bool)), this, SLOT(slt_finishLoading()));
    /* Exit application when exit button pressed */
    QObject::connect(p_exitButton, SIGNAL(released()), qApp, SLOT(quit()));
    /* Update loading process of loader */
    QObject::connect(p_backend->getWebPage(), SIGNAL(loadProgress(int)), p_loader, SLOT(slt_setLoadingProgress(int)));
    /* Show scheduling dialog */
    QObject::connect(p_scheduleButton, SIGNAL(released()), this, SLOT(slt_showMovieScheduleDialog()));
    // QObject::connect(this, SIGNAL(sig_quit()), qApp, SLOT(quit()));
    // QObject::connect(p_loader, SIGNAL(sig_loadFinished()), p_backend, SLOT(slt_parseMovieInfo()));
}

void CuMoAppManager::slt_showMovieInfoDialog()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    int index = p_coverFlow->getCentralIndex();
    /* Show movie information dialog */
    CuMoDialog *movieInfoDialog = new CuMoDialog(CuMoDialog::MOVIEINFO);
    movieInfoDialog->setMovieInfo(p_backend->getMovieInfo(index));
    movieInfoDialog->setupAndShow();
    p_scene->addItem(movieInfoDialog);
    QObject::connect(movieInfoDialog, SIGNAL(sig_movieDialogClosed()),
                     p_coverFlow, SLOT(slt_rotateCentralToShow()));

    qDebug() << "Index: " << index;
}

void CuMoAppManager::slt_showMovieScheduleDialog()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    CuMoDialog* movieScheduleDialog = new CuMoDialog(CuMoDialog::SCHEDULE);
    movieScheduleDialog->setScheduleInfo(p_backend->getScheduleInfo());
    movieScheduleDialog->setupAndShow();
    p_scene->addItem(movieScheduleDialog);
    QObject::connect(movieScheduleDialog, SIGNAL(sig_scheduleDialogClosed(CuMoScheduleChoices)),
                     p_backend, SLOT(slt_scheduleChanged(CuMoScheduleChoices)));
}

void CuMoAppManager::slt_parseFinished(QList<CuMoMovieInfo*> infoList)
{
    Q_UNUSED(infoList);
}

void CuMoAppManager::slt_startLoading()
{
    QMessageBox::StandardButton reply;

    if(p_backend->checkNetwork())
    {
        reply = QMessageBox::question(p_mainWindow,
                                      QString(),
                                      tr("Load Movie Informations"),
                                      QMessageBox::Yes | QMessageBox::No,
                                      QMessageBox::Yes);
        if (reply == QMessageBox::No)
        {
            qApp->quit();
        }
        else
        {
            p_mainWindow->statusBar()->showMessage(tr("LOADING..."));
            /* Show loader */
            p_scene->addItem(p_loader);
            // p_loader->slt_startAnimation();
            p_backend->fetchMovieInfoPage();
            // p_backend->start();
        }
    }
    else
    {
        reply = QMessageBox::information(p_mainWindow,
                                         tr("Connection"),
                                         tr("Please Connect Network First"));
        qApp->quit();
    }
}

void CuMoAppManager::slt_finishLoading()
{
    p_backend->slt_parseWebPage();
    /* Show loading finished for 3 seconds long*/
    p_mainWindow->statusBar()->showMessage(tr("LOADING FINISHED"), 3000);
    p_loader->slt_endAnimation();
}
