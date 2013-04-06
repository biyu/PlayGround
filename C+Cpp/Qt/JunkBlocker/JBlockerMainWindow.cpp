#include "JBlockerMainWindow.h"

JBlockerMainWindow::JBlockerMainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), p_tabW(0), p_inboxW(0), p_junkListW(0), p_messageCore(0), p_messageBox(0), p_progressBar(0),
    p_refresh(0), p_addToBlackList(0), p_switchAccount(0)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    /* Initialization */
    initUI();
    initCore();
    initConnections();
    QTimer::singleShot(1000, this, SLOT(slt_loadingStart()));
}

void JBlockerMainWindow::initUI()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    /* Setup geometry of Main Window */
    this->setFixedSize(800, 480);
    /* Setup status bar by using QProgressBar */
    p_progressBar = new QProgressBar();
    p_progressBar->setMinimum(0);
    p_progressBar->setMaximum(100);

    /* Create menu actions */
    p_addToBlackList = new QAction("ToBlackList", this);
    p_refresh = new QAction(tr("Refresh"), this);
    p_switchAccount = new QAction(tr("SwitchAccount"), this);
    /* Add actions to menu bar */
    QMenu* optionMenu = this->menuBar()->addMenu(tr("Options"));
    optionMenu->addAction(p_refresh);
    optionMenu->addAction(p_addToBlackList);
    optionMenu->addAction(p_switchAccount);

    /* Create Container Central Widget and Tab Widgets */
    p_tabW = new QTabWidget();
    /* Inbox widget */
    p_inboxW = new QTreeWidget();
    /* Configure inbox widget */
    /* Set number of displayed columns */
    p_inboxW->setColumnCount(2);
    /* Set the column's resize mode to "Stretch" */
    p_inboxW->header()->setResizeMode(0, QHeaderView::Stretch);
    /* Set header names */
    QStringList headerList;
    headerList << "Sender" << "Info";
    p_inboxW->setHeaderLabels(headerList);
    /* Set minimum width of header to half width of main window */
    p_inboxW->header()->setDefaultSectionSize(400);
    /* Add inbox widget to central tab widget */
    p_tabW->addTab(p_inboxW, tr("INBOX"));
    /* Black list widget */
    p_junkListW = new QListWidget();
    /* Add black list widget to central tab widget */
    p_tabW->addTab(p_junkListW, tr("JUNKS"));

    /* Insert central tab widget into main window */
    this->setCentralWidget(p_tabW);
    p_tabW->show();

    p_messageBox = new JBlockerMessageViewBox(this, Qt::Dialog);
    p_messageBox->hide();
}

void JBlockerMainWindow::initCore()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    p_messageCore = new JBlockerCore();
}

void JBlockerMainWindow::initConnections()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    QObject::connect(p_inboxW, SIGNAL(itemClicked(QTreeWidgetItem*,int))
                     , this, SLOT(slt_showInboxMessageByService(QTreeWidgetItem*,int)));
    QObject::connect(this, SIGNAL(sig_showMessageBox(QMessage, QMessage::TypeFlags))
                     , p_messageBox, SLOT(slt_showMessage(QMessage, QMessage::TypeFlags)));
    // QObject::connect(p_messageCore, SIGNAL(sig_updateInboxMsgOnce(QString,bool)), this, SLOT(slt_updateInboxMessages(QString,bool)));
    QObject::connect(this, SIGNAL(sig_startParsing()), p_messageCore, SLOT(slt_parseMessageToUniform()));
    QObject::connect(p_messageCore, SIGNAL(sig_loadingFinished()), this, SLOT(slt_loadingFinished()));
    QObject::connect(p_messageCore, SIGNAL(sig_updateProgressBar(int)), p_progressBar, SLOT(setValue(int)));
    QObject::connect(p_switchAccount, SIGNAL(triggered()), this, SLOT(slt_switchAccount()));
}

void JBlockerMainWindow::slt_loadingStart()
{
    this->statusBar()->showMessage(tr("LOADING MESSAGES ..."));
    // QMessageBox::information(this, QString(), QString("PROGRAM NEED TO LOAD MESSAGES"), QMessageBox::Ok);
    /* Create dialog */
    QDialog dialog;
    dialog.setWindowTitle(tr("Account Selection"));
    QHBoxLayout* layout = new QHBoxLayout();
    /* Label for dialog */
    QLabel* dialogLabel = new QLabel(tr("Select An Account:"));
    layout->addWidget(dialogLabel, 0, Qt::AlignHCenter);
    /* Combo box for selecting account */
    QComboBox* accountComboBox = new QComboBox();
    accountComboBox->setFixedWidth(280);
    /* Get account name list from message core */
    accountComboBox->addItems(p_messageCore->getAccountNameList());
    layout->addWidget(accountComboBox, 0, Qt::AlignHCenter);
    /* Button for dialog */
    QPushButton* dialogButton = new QPushButton(tr("Confirm"));
    layout->addWidget(dialogButton, 0, Qt::AlignHCenter);
    dialog.setLayout(layout);
    QObject::connect(dialogButton, SIGNAL(clicked()), &dialog, SLOT(accept()));
    dialog.exec();
    if(dialog.result())
    {
        /* Set selected account id */
        p_messageCore->setSelectedAccountId(accountComboBox->currentIndex());
    }

    this->statusBar()->addPermanentWidget(p_progressBar, 0);
    p_progressBar->setValue(0);
    p_progressBar->show();
    /* Core runs */
    p_messageCore->run();
}

void JBlockerMainWindow::slt_loadingFinished()
{
    /* Show loading finished for 3 seconds long*/
    this->statusBar()->showMessage(tr("LOADING FINISHED"), 3000);
    QMessageBox::information(this, QString(), QString("LOADING FINISHED"), QMessageBox::Ok);
    this->statusBar()->removeWidget(p_progressBar);
    this->slt_showInboxMessages();
}

void JBlockerMainWindow::slt_showInboxMessages()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    p_inboxW->clear();

    /* Show messages classified based on sender's name */
    p_nameToMessageHash = p_messageCore->getNameInfoHash();
    /* Get name list */
    QList<QString> nameList = p_nameToMessageHash.keys();
    /* Get current account message type */
    QMessage::TypeFlags accountType = p_messageCore->getCurrentAccountType();
    /* Put classified infos into inbox tree widget */
    for(int i=0; i<nameList.count(); i++)
    {
        QString name = nameList.at(i);
        QStringList rootItemString;
        /* Set the root element for each sender */
        /* Check message type */
        rootItemString << (accountType == QMessage::Sms ? p_messageCore->getContactName(name) : name) << QString("%1 message").arg(p_messageCore->messageCount(name));
        QTreeWidgetItem* parentItem = new QTreeWidgetItem(rootItemString);
        parentItem->setData(0, MessageIdRole, name);
        p_inboxW->addTopLevelItem(parentItem);

        /* Set children items for each sender */
        QList<QMessage>* messageList = p_messageCore->getMessageList(name);
        for(int j=0; j<messageList->count(); j++)
        {
            QMessage msg = messageList->at(j);
            QStringList childItemString;
            QString subject = QString::fromUtf8(msg.subject().toAscii());
            childItemString << subject << msg.date().toLocalTime().toString(QString("hh:mm:ss dd.MM.yyyy"));
            QTreeWidgetItem* childItem = new QTreeWidgetItem(childItemString);
            /* Set messageID as the DATA of each children items */
            childItem->setData(0, MessageIdRole, msg.id().toString());
            /* Set the size hint of children */
            childItem->setSizeHint(0, p_inboxW->headerItem()->sizeHint(0));
            p_inboxW->topLevelItem(i)->addChild(childItem);
        }
    }
}

void JBlockerMainWindow::slt_showInboxMessageByService(QTreeWidgetItem* item, int column)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    QTreeWidgetItem* parentItem = item->parent();
    /* Check if clicked item is child item or parent item */
    if(parentItem && column == 0)
    {
        /* Get parent name */
        QString parentName = parentItem->data(0, MessageIdRole).toString();
        QList<QMessage>* msgList = p_messageCore->getMessageList(parentName);
        int index = parentItem->indexOfChild(item);
        QMessage msg = msgList->at(index);
        /* Show message content */
        emit sig_showMessageBox(msg, p_messageCore->getCurrentAccountType());
    }
}

void JBlockerMainWindow::slt_switchAccount()
{
    p_tabW->setCurrentWidget(p_inboxW);
    p_inboxW->clear();
    p_messageCore->reInitializes();
    this->slt_loadingStart();
}

//    /* Parse messages and create uniform information */
//    MessageInfo* info = new MessageInfo();
//    info->messageID = message.id();
//    info->folderID = message.parentFolderId();
//    info->sentDate = message.date();
//    info->receivedDate = message.receivedDate();
//    info->from = message.from().addressee();
//    info->size = message.size();
//    info->subject = message.subject();
//    info->textContent = message.textContent();

//    QVariant itemData = item->data(0, MessageIdRole);
//    if(!itemData.isNull())
//    {
//        QMessageId id(itemData.toString());

//        /* Show message by service */
//    }

//void JBlockerMainWindow::slt_updateInboxMessages(QString name, bool isNew)
//{
//    qDebug() << "+ " << __PRETTY_FUNCTION__;

//    if(isNew)
//    {
//        QStringList rootItemString;
//        /* Set the root element for each sender */
//        rootItemString << name << QString("%1 message").arg(p_messageCore->messageCount(name));
//        p_inboxW->addTopLevelItem(new QTreeWidgetItem(rootItemString));
//        /* Add name to name list if it is new */
//        p_topNameList << name;
//    }
//    else
//    {
//        p_inboxW->topLevelItem(p_topNameList.indexOf(name))->setText(1, QString("%1 message").arg(p_messageCore->messageCount(name)));
//    }

//    QList<QMessage>* messageList = p_messageCore->getMessageList(name);
//    if(!messageList->isEmpty())
//    {
//        // MessageInfo* msgInfo = messageInfoList->last();
//        QMessage msg = messageList->last();
//        QStringList childItemString;
//        childItemString << msg.subject() << msg.date().toLocalTime().toString(QString("hh:mm:ss dd.MM.yyyy"));
//        QTreeWidgetItem* childItem = new QTreeWidgetItem(childItemString);
//        /* Set messageID as the DATA of each children items */
//        childItem->setData(0, MessageIdRole, msg.id().toString());
//        childItem->setSizeHint(0, p_inboxW->headerItem()->sizeHint(0));
//        p_inboxW->topLevelItem(p_topNameList.indexOf(name))->addChild(childItem);
//    }
//    /* Force inbox widget repaint itself to show message changes */
//    // p_inboxW->repaint();
//}
