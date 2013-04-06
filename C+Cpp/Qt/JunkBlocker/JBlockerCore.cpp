#include "JBlockerCore.h"

void showMessagesInMap(QHash<QString, QList<QMessage>* > msgToNameInfoHash)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    foreach(QString name, msgToNameInfoHash.keys())
    {
        qDebug() << name << " sent " << msgToNameInfoHash.value(name)->count() << "messages";
    }
}

JBlockerCore::JBlockerCore(QObject *parent)
    :QObject(parent), p_messageManager(0), p_service(0), p_contactManager(0)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    initMessageCore();
}

void JBlockerCore::run()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    slt_parseMessageToUniform();
}

void JBlockerCore::initMessageCore()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    /* Create message manager */
    p_messageManager = new QMessageManager();
    /* Search all available accounts */
    p_accountIdList = p_messageManager->queryAccounts();
    /* Create contact manager for sms messages*/
    //    QStringList availableManagers = QContactManager::availableManagers();
    QMap<QString, QString> params;
    QString managerUri = QContactManager::buildUri(QString("maemo5"), params);
    p_contactManager = QContactManager::fromUri(managerUri);
    if (p_contactManager->error()) {
        qDebug() << QString("Failed to open store!\n(error code %1)").arg(p_contactManager->error());
        return;
    }
    /* Create message service */
    p_service = new QMessageService();
}

void JBlockerCore::slt_parseMessageToUniform()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    /* Create account filters */
    QMessageFilter accountFilter = QMessageFilter::byParentAccountId(p_accountId);
    /* Create folder filter */
    QMessageFilter inboxFilter = QMessageFilter::byStandardFolder(QMessage::InboxFolder);
    /* Get message Id list */
    QMessageIdList idList = p_messageManager->queryMessages(accountFilter & inboxFilter);

    /* Parse all information and classify in ONE loop */
    int count = idList.count();
    for(int i=0; i<count; i++)
    {
        QMessageId id = idList.at(i);
        QMessage message = p_messageManager->message(id);

        /* Get the name of sender */
        QString fromWho = message.from().addressee();
        /* Debug use */
        qDebug() << "Sender: " << fromWho;

        bool yes = p_msgToNameInfoHash.contains(fromWho);
        /* Check if this key has already been added in the map */
        if(!yes)
        {
            qDebug() << "Sender (" << fromWho << ")" << "is a NEW name!";
            /* Create new message info list for this sender */
            QList<QMessage>* messageList = new QList<QMessage>();
            /* Insert message into list */
            *messageList << message;
            /* Create name - messageList hash */
            p_msgToNameInfoHash.insert(fromWho, messageList);
        }
        /* If sender's name is already in map */
        else
        {
            /* Add message to existed list */
            *(p_msgToNameInfoHash.value(fromWho)) << message;
        }
        emit sig_updateProgressBar(i*100/count);
    }
    /* Debug use */
    showMessagesInMap(p_msgToNameInfoHash);
    /* Show loading finished */
    emit sig_loadingFinished();
}

QHash<QString, QList<QMessage>* > JBlockerCore::getNameInfoHash() const
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    return p_msgToNameInfoHash;
}

int JBlockerCore::messageCount(QString name)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    return p_msgToNameInfoHash.value(name)->count();
}
int JBlockerCore::senderCount()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    return p_msgToNameInfoHash.count();
}

QList<QMessage>* JBlockerCore::getMessageList(QString name)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    return p_msgToNameInfoHash.value(name);
}

QString JBlockerCore::getContactName(QString number)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    QContactFilter numberFilter = QContactPhoneNumber::match(number);
    QList<QContact> contactList = p_contactManager->contacts(numberFilter);
    if(!contactList.empty())
    {
        return contactList.at(0).displayLabel();
    }
    else
    {
        return number;
    }
}

QStringList JBlockerCore::getAccountNameList()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    QStringList accountNameList;
    for(int i=0; i<p_accountIdList.count(); i++)
    {
        QMessageAccount account(p_accountIdList.at(i));
        accountNameList << account.name();
    }

    qDebug() << accountNameList;
    return accountNameList;
}

void JBlockerCore::setSelectedAccountId(int index)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    p_accountId = p_accountIdList.at(index);
    qDebug() << "Selected Account ID: " << p_accountId.toString();
}

QMessage::TypeFlags JBlockerCore::getCurrentAccountType()
{
    QMessageAccount account(p_accountId);
    return account.messageTypes();
}

void JBlockerCore::reInitializes()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    foreach(QList<QMessage>* list, p_msgToNameInfoHash.values())
    {
        delete list;
    }
    p_msgToNameInfoHash.clear();
}

void JBlockerCore::showMessage(QMessageId id)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    if(id.isValid())
    {
        p_service->show(id);
    }
}
