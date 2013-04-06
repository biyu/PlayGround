#ifndef JBLOCKERMAINWINDOW_H
#define JBLOCKERMAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include "JBlockerCore.h"
#include "JBlockerMessageViewBox.h"

class JBlockerMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    JBlockerMainWindow(QWidget* parent=0, Qt::WindowFlags flags = Qt::Window);

protected:

private:
    /* Initialize UI part */
    void initUI();
    /* Initialize message core */
    void initCore();
    /* Initialize signal and slot connections */
    void initConnections();

signals:
    /* SIGNAL: Show inbox messages in inbox tab*/
    void sig_showInboxMessages();
    /* SIGNAL: Show message detail in message box */
    void sig_showMessageBox(QMessage msg, QMessage::TypeFlags msgType);
    /* SIGNAL Parsing */
    void sig_startParsing();

public slots:
    /* SLOT: Show inbox messages */
    void slt_showInboxMessages();
    /* SLOT: Show message of inbox with message service */
    void slt_showInboxMessageByService(QTreeWidgetItem* item, int column);
    /* SLOT: Update inbox messages once  */
    //    void slt_updateInboxMessages(QString name, bool isNew);
    /* Show loading message box */
    void slt_loadingStart();
    /* SLOT: Loading finished */
    void slt_loadingFinished();
    /* SLOT: Switch account */
    void slt_switchAccount();

private:
    static const int MessageIdRole = Qt::UserRole + 1;

private:

    QTabWidget* p_tabW;
    /* Inbox widget */
    QTreeWidget* p_inboxW;
    QListWidget* p_junkListW;
    /* Message core */
    JBlockerCore* p_messageCore;
    QHash<QString, QList<QMessage>* > p_nameToMessageHash;
    /* Message box */
    JBlockerMessageViewBox* p_messageBox;
    /* Name list of top level item */
    QList<QString> p_topNameList;
    /* Process bar */
    QProgressBar* p_progressBar;
    /* Actions */
    QAction* p_refresh;
    QAction* p_addToBlackList;
    QAction* p_switchAccount;
};

#endif // JBLOCKERMAINWINDOW_H
