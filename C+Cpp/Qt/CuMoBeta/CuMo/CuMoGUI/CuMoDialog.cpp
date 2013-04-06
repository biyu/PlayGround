#include "CuMoDialog.h"

// #################################  CuMoDialogPicture  ####################################

CuMoDialogPicture::CuMoDialogPicture(QImage* image, QGraphicsProxyWidget* parent)
    : CuMoWidget(parent), p_image(image)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    this->setAttribute(Qt::WA_OpaquePaintEvent);
}

void CuMoDialogPicture::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(this->rect(), *p_image, p_image->rect());
}

// ################################  CuMoDialog  ##########################################

CuMoDialog::CuMoDialog(CuMoDialog::DialogType type, QGraphicsProxyWidget* parent)
    : CuMoWidget(parent), p_type(type), p_okButton(0), p_exitButton(0), p_infoPicture(0)
    , p_textArea(0), p_movieInfo(0), p_scheduleInfo(0), p_areaC(0), p_dateC(0), p_beginTimesC(0)
    , p_genresC(0), p_signalMapper(0)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    /* Block all event in dialog, no propagation */
    this->setAttribute(Qt::WA_WindowPropagation, true);
    this->setFlag(QGraphicsItem::ItemIsPanel, true);
    this->setPanelModality(QGraphicsItem::SceneModal);
}

CuMoDialog::~CuMoDialog()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    qDebug() << "Dialog deleted!";
}

void CuMoDialog::setupAndShow()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    /* Setup dialog components based on the type of dialog */
    switch(p_type)
    {
    case CuMoDialog::MOVIEINFO:
        {
            /* Setup geometry for movie info dialog */
            this->configGeometry(QRect(800*0.5-800*0.8/2, 480*0.5-480*0.8/2, 800*0.8, 480*0.8));
            /* Setup components */

            if(!p_movieInfo)
                return;

            p_infoPicture = new CuMoDialogPicture(p_movieInfo->movieImage, this);
            p_infoPicture->setGeometry(QRectF(80, 35, p_rect.width()/2-160, p_rect.height()/2));
            p_infoPicture->setOpacity(0);

            p_ageLimitPicture = new CuMoDialogPicture(p_movieInfo->movieAgeLimit, this);
            p_ageLimitPicture->setGeometry(QRectF(145, p_rect.height()/2+50, 30, 30));
            p_ageLimitPicture->setOpacity(0);

            /* Text info of movie */
            QTextBrowser* textArea = new QTextBrowser();
            p_textArea = new CuMoWidget(this);
            p_textArea->setWidget(textArea);
            p_textArea->setGeometry(QRectF(p_rect.width()/2, 35, p_rect.width()/2-35, p_rect.height()- 80));
            p_textArea->setOpacity(0);

            if(!p_movieInfo->movieDescription.isEmpty())
                textArea->setPlainText(p_movieInfo->movieDescription);
            else
                textArea->setPlainText(tr("No Description"));

            textArea->setTextColor(Qt::white);
            QPalette p(Qt::white, Qt::black);
            textArea->setPalette(p);

            /* Ok button to exit this dialog */
            p_okButton = new CuMoButton(CuMoButton::GENERIC, QString("OK"), this);
            p_okButton->configGeometry(QRect(p_rect.width()/2-60/2, p_rect.height()-30-10, 60, 30));
            QObject::connect(p_okButton, SIGNAL(released()), this, SLOT(slt_animateToHide()));
            /* Create signal mapper */
            p_signalMapper = new QSignalMapper(this);
            /* Setup signal mapper for buttons */
            QObject::connect(p_okButton, SIGNAL(released()), p_signalMapper, SLOT(map()));
            p_signalMapper->setMapping(p_okButton, p_okButton->getLabel());
            QObject::connect(p_signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(slt_animateToHide(const QString &)));
            break;
        }
    case CuMoDialog::SCHEDULE:
        {
            /* Setup geometry for movie info dialog */
            this->configGeometry(QRect(800*0.5-800*0.8/2, 480*0.5-480*0.8/2, 800*0.8, 480*0.8));
            /* Create comboboxes */
            p_areaC = new CuMoComboBox(this);
            p_dateC = new CuMoComboBox(this);
            p_beginTimesC = new CuMoComboBox(this);
            p_genresC = new CuMoComboBox(this);
            /* Setup geometry for comboboxes */
            int widthC = p_rect.width()/2;
            int heightC = p_rect.height()/5;
            p_areaC->configGeometry(QRect(widthC/2, 15, widthC, heightC));
            p_dateC->configGeometry(QRect(p_areaC->pos().x(), p_areaC->pos().y()+heightC+15, widthC, heightC));
            p_beginTimesC->configGeometry(QRect(p_areaC->pos().x(), p_dateC->pos().y()+heightC+15, widthC, heightC));
            p_genresC->configGeometry(QRect(p_areaC->pos().x(), p_beginTimesC->pos().y()+heightC+15, widthC, heightC));
            /* Setup combobox items */
            p_areaC->addNewItems(p_scheduleInfo->areas);
            p_dateC->addNewItems(p_scheduleInfo->dates);
            p_beginTimesC->addNewItems(p_scheduleInfo->beginTimes);
            p_genresC->addNewItems(p_scheduleInfo->genres);
            /* Setup current item of combobox */
            p_areaC->setCurrentIndex(p_scheduleInfo->areas_index);
            p_dateC->setCurrentIndex(p_scheduleInfo->dates_index);
            p_beginTimesC->setCurrentIndex(p_scheduleInfo->beginTimes_index);
            p_genresC->setCurrentIndex(p_scheduleInfo->genres_index);
            /* Hide comboxes */
            p_areaC->setOpacity(0);
            p_dateC->setOpacity(0);
            p_beginTimesC->setOpacity(0);
            p_genresC->setOpacity(0);

            /* Ok button to confirm schedule choises */
            p_okButton = new CuMoButton(CuMoButton::GENERIC, QString("OK"), this);
            p_okButton->configGeometry(QRect(p_rect.width()*3/4+60/2+30, p_rect.height()-30-30-40, 80, 30));
            // QObject::connect(p_okButton, SIGNAL(released()), this, SLOT(slt_animateToHide()));
            /* Exit button to close schedule dialog */
            p_exitButton = new CuMoButton(CuMoButton::GENERIC, QString("CANCEL"), this);
            p_exitButton->configGeometry(QRect(p_rect.width()*3/4+60/2+30, p_rect.height()-30-30, 80, 30));
            /* Create signal mapper */
            p_signalMapper = new QSignalMapper(this);
            /* Setup signal mapper for buttons */
            QObject::connect(p_okButton, SIGNAL(released()), p_signalMapper, SLOT(map()));
            QObject::connect(p_exitButton, SIGNAL(released()), p_signalMapper, SLOT(map()));
            p_signalMapper->setMapping(p_okButton, p_okButton->getLabel());
            p_signalMapper->setMapping(p_exitButton, p_exitButton->getLabel());
            QObject::connect(p_signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(slt_animateToHide(const QString &)));
            break;
        }
    default:
        break;
    }
    /* Hide dialog first */
    this->hide();
    /* Show dialog */
    QTimer::singleShot(0, this, SLOT(slt_animateToShow()));
}

void CuMoDialog::paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setBrush(Qt::black);
    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.5);
    painter->drawRoundRect(QRect(0, 0, p_rect.width(), p_rect.height()), 20, 50);
    painter->restore();
}

void CuMoDialog::configGeometry(QRect rect)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    p_rect = rect;
    this->setGeometry(p_rect);
}

void CuMoDialog::slt_animateToShow()
{
    /* Show dialog by animation */
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    QSequentialAnimationGroup* animationGroupS = new QSequentialAnimationGroup();
    /* Animate rotation */
    this->addPropertyAnimToGroup(animationGroupS, "scaleCRotationY", 500, 90, 0, QEasingCurve::OutQuart);
    /* Show components */
    switch(p_type)
    {
    case CuMoDialog::MOVIEINFO:
        {
            QParallelAnimationGroup* animationGroupP = new QParallelAnimationGroup();
            p_infoPicture->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 0, 1, QEasingCurve::OutQuart);
            p_ageLimitPicture->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 0, 1, QEasingCurve::OutQuart);
            p_textArea->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 0, 1, QEasingCurve::OutQuart);
            animationGroupS->addAnimation(animationGroupP);
            break;
        }
    case CuMoDialog::SCHEDULE:
        {
            QParallelAnimationGroup* animationGroupP = new QParallelAnimationGroup();
            p_areaC->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 0, 1, QEasingCurve::OutQuart);
            p_dateC->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 0, 1, QEasingCurve::OutQuart);
            p_beginTimesC->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 0, 1, QEasingCurve::OutQuart);
            p_genresC->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 0, 1, QEasingCurve::OutQuart);
            animationGroupS->addAnimation(animationGroupP);
            break;
        }
    default:
        break;
    }
    /* Animation start */
    animationGroupS->start(QAbstractAnimation::DeleteWhenStopped);
    /* Show dialog */
    this->show();
}

void CuMoDialog::slt_animateToHide(const QString & name)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    QSequentialAnimationGroup* animationGroupS = new QSequentialAnimationGroup();
    /* Show components */
    switch(p_type)
    {
    case CuMoDialog::MOVIEINFO:
        {
            QParallelAnimationGroup* animationGroupP = new QParallelAnimationGroup();
            p_infoPicture->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 1, 0, QEasingCurve::OutQuart);
            p_ageLimitPicture->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 1, 0, QEasingCurve::OutQuart);
            p_textArea->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 1, 0, QEasingCurve::OutQuart);
            animationGroupS->addAnimation(animationGroupP);
            /* For movieinfo dialog */
            QObject::connect(animationGroupS, SIGNAL(finished()), this, SIGNAL(sig_movieDialogClosed()));
            QObject::connect(animationGroupS, SIGNAL(finished()), this, SLOT(deleteDialog()));
            break;
        }
    case CuMoDialog::SCHEDULE:
        {
            QParallelAnimationGroup* animationGroupP = new QParallelAnimationGroup();
            p_areaC->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 1, 0, QEasingCurve::OutQuart);
            p_dateC->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 1, 0, QEasingCurve::OutQuart);
            p_beginTimesC->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 1, 0, QEasingCurve::OutQuart);
            p_genresC->addPropertyAnimToGroup(animationGroupP, "opacity", 500, 1, 0, QEasingCurve::OutQuart);
            animationGroupS->addAnimation(animationGroupP);
            /* Check which button pressed */
            /* If OK pressed, then connecting signal */
            if(!name.compare("OK"))
                QObject::connect(animationGroupS, SIGNAL(finished()), this, SLOT(slt_scheduleDialogClosed()));
            /* If CANCEL pressed, then close dialog and destroy it */
            if(!name.compare("CANCEL"))
                QObject::connect(animationGroupS, SIGNAL(finished()), this, SLOT(deleteDialog()));
            break;
        }
    default:
        break;
    }
    this->addPropertyAnimToGroup(animationGroupS, "scaleCRotationY", 500, 0, 90, QEasingCurve::OutQuart);
    animationGroupS->start();

}

void CuMoDialog::slt_scheduleDialogClosed()
{
    /* Prepare choises */
    CuMoScheduleChoices choises;
    choises.selectArea = p_areaC->getCurrentIndex();
    choises.selectDate =  p_dateC->getCurrentIndex();
    choises.selectBeginTime = p_beginTimesC->getCurrentIndex();
    choises.selectGenre = p_genresC->getCurrentIndex();
    /* Send choises out */
    emit sig_scheduleDialogClosed(choises);
    /* Delete dialog */
    this->deleteDialog();
}

void CuMoDialog::setMovieInfo(CuMoMovieInfo* info)
{
    p_movieInfo = info;
}

void CuMoDialog::setScheduleInfo(CuMoScheduleInfo *info)
{
    p_scheduleInfo = info;
}

int CuMoDialog::deleteDialog()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    // p_eventLoop.exit(0);
    this->deleteLater();
    return 0;
}
