#ifndef JBLOCKERMESSAGEVIEWBOX_H
#define JBLOCKERMESSAGEVIEWBOX_H

#include <QtGui>
#include <QtCore>
#include "JBlockerCore.h"

class JBlockerMessageViewBox : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    JBlockerMessageViewBox(QWidget* parent=0, Qt::WindowFlags f=0);

private:
    /* Setup components of widget */
    void setupUI();
    /* Setup signal and slot connection */
    void setupConnection();

public slots:
    /* Show message on this widget */
    void slt_showMessage(QMessage msg, QMessage::TypeFlags msgType);
    /* Clear message box */
    void slt_clear();

private:
    /* Text browser for displaying text message body */
    QTextBrowser* p_textBrowser;
    /* Exit button */
    QPushButton* p_exitButton;
};

#endif // JBLOCKERMESSAGEVIEWBOX_H
