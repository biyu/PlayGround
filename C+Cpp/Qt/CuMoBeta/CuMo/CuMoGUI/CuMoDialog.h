#ifndef CUMODIALOG_H
#define CUMODIALOG_H

#include <QtGui>
#include <QtCore>
#include <QEventLoop>
#include "CuMoWidget.h"
#include "CuMoButton.h"
#include "CuMoComboBox.h"
#include "CuMoCommon.h"

class CuMoDialogPicture : public CuMoWidget
{
    Q_OBJECT

public:
    CuMoDialogPicture(QImage* image, QGraphicsProxyWidget* parent=0);

protected:
    /* Paint function */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget=0);

private:
    QImage* p_image;
};

class CuMoDialog : public CuMoWidget
{
    Q_OBJECT

public:
    /* Define dialog types */
    enum DialogType
    {
        GENERIC,
        MOVIEINFO,
        SCHEDULE
    };

    /* Constructor */
    CuMoDialog(CuMoDialog::DialogType type, QGraphicsProxyWidget* parent=0);
    /* Distructor */
    ~CuMoDialog();
    /* Set geometry for both outlook and inner widget */
    void configGeometry(QRect rect);
    /* Set movie information */
    void setMovieInfo(CuMoMovieInfo* info);
    /* Set schedule information */
    void setScheduleInfo(CuMoScheduleInfo* info);
    /* Setup dialog components based on dialog type and show dialog */
    void setupAndShow();

protected:
    /* Overwrite paint function */
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );

private:

signals:
    /* Signal: Show coverflow item again */
    void sig_movieDialogClosed();
    /* SIGNAL: schedule selected */
    void sig_scheduleDialogClosed(CuMoScheduleChoices choices);

public slots:
    /* Slot: Animate dialog to show itself */
    void slt_animateToShow();
    /* Slot: Animate dialog to hide itself */
    void slt_animateToHide(const QString & name);
    /* Slot: Delete dialog later */
    int deleteDialog();
    /* SLOT: Schedule dialog closed */
    void slt_scheduleDialogClosed();

private:
    /* Dialog type */
    CuMoDialog::DialogType p_type;
    /* Widget geometry */
    QRect p_rect;
    /* Ok button */
    CuMoButton* p_okButton;
    /* Exit button */
    CuMoButton* p_exitButton;
    /* Movie info picture */
    CuMoDialogPicture* p_infoPicture;
    /* Movie age limit picture */
    CuMoDialogPicture* p_ageLimitPicture;
    /* Movie introduction text */
    CuMoWidget* p_textArea;
    /* Movie information */
    CuMoMovieInfo* p_movieInfo;
    /* Schedule information */
    CuMoScheduleInfo* p_scheduleInfo;
    /* Scheduling comboboxs */
    CuMoComboBox* p_areaC;
    CuMoComboBox* p_dateC;
    CuMoComboBox* p_beginTimesC;
    CuMoComboBox* p_genresC;
    /* Signal Mapper */
    QSignalMapper* p_signalMapper;
    /* Event loop */
    // QEventLoop p_eventLoop;
};

#endif // CUMODIALOG_H
