#ifndef JBLOCKERCORE_H
#define JBLOCKERCORE_H

#include <QtCore>
#include <QtGui>

#include <QMessage>
#include <QMessageManager>
#include <QMessageService>
#include <QContactManager>
#include <QContactFilter>
#include <QContactDetailFilter>
#include <QContactPhoneNumber>

/* Using namespace of mobility sdk */
using namespace QtMobility;

class MessageInfo
{
public:
    /* Message ID */
    QMessageId messageID;
    /* Folder ID */
    QMessageFolderId folderID;
    /* Sent date */
    QDateTime sentDate;
    /* Received date */
    QDateTime receivedDate;
    /* Sender's address */
    QString from;
    /* Receiver's address */
    /* Message size, Unit? */
    int size;
    /* Subject of message */
    QString subject;
    /* Text content */
    QString textContent;
};

class JBlockerCore : public QObject
{
    Q_OBJECT

public:
    /* Basic constructor */
    JBlockerCore(QObject* parent=0);
    /* Constructor with view widget binded */
    // JBlockerCore(QTreeWidget* view, QObject* parent=0);

    /* Getter of name-info map */
    QHash<QString, QList<QMessage>* > getNameInfoHash() const;
    /* Count message number for specific sender */
    int messageCount(QString name);
    /* Count for sender number */
    int senderCount();
    /* Getter of message info list of specific sender */
    // QList<QMessage>* getMessageList(QString name);
    QList<QMessage>* getMessageList(QString name);
    /* Get the contact name of sender */
    QString getContactName(QString number);
    /* Run the core to fetch messages */
    void run();
    /* Get account name list */
    QStringList getAccountNameList();
    /* Set account type */
    void setSelectedAccountId(int index);
    /* Get current account's message type */
    QMessage::TypeFlags getCurrentAccountType();
    /* Reinitial message core */
    void reInitializes();
    /* Show Email message */
    void showMessage(QMessageId id);

protected:

private:
    /* Initial Qt Mobility Message module */
    void initMessageCore();

signals:
    /* Update Inbox messages once */
    void sig_updateInboxMsgOnce(QString name, bool isNew);
    /* SIGNAL: Show loading finished message */
    void sig_loadingFinished();
    /* SIGNAL: Update progress bar */
    void sig_updateProgressBar(int value);

public slots:
    /* Parse messages into uniform structure */
    void slt_parseMessageToUniform();

private:
    /* Manager for managing messages in mobile devices */
    QMessageManager* p_messageManager;
    /* Service for messages */
    QMessageService* p_service;
    /* Manager for contact information */
    QContactManager* p_contactManager;
    /* Hash: Name to message list */
    // QHash<QString, QList<QMessage>* > p_msgToNameInfoHash;
    QHash<QString, QList<QMessage>* > p_msgToNameInfoHash;
    /* Selected account id */
    QMessageAccountId p_accountId;
    /* Account id list */
    QMessageAccountIdList p_accountIdList;
};

#endif // JBLOCKERCORE_H
