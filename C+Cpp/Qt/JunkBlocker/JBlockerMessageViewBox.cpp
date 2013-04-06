#include "JBlockerMessageViewBox.h"

JBlockerMessageViewBox::JBlockerMessageViewBox(QWidget* parent, Qt::WindowFlags f)
    : QWidget(parent, f),p_textBrowser(0), p_exitButton(0)
{
    setupUI();
    setupConnection();
}

void JBlockerMessageViewBox::setupUI()
{
    /* Text browser for display message body */
    p_textBrowser = new QTextBrowser(this);
    /* OK button to exit message box */
    p_exitButton = new QPushButton(QString("OK"), this);
    /* Setup layout */
    QVBoxLayout* mainLayout = new QVBoxLayout();
    /* Add components onto layout */
    mainLayout->addWidget(p_textBrowser);

    /* Layout for bottom buttons */
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->insertSpacing(0, 220);
    bottomLayout->addWidget(p_exitButton);
    bottomLayout->insertSpacing(-1, 220);
    mainLayout->addLayout(bottomLayout);

    /* Add layout to message box */
    this->setLayout(mainLayout);
    /* Set geometry of message box */
    this->setGeometry(QRect(0, 0, 800, 480));
}

void JBlockerMessageViewBox::setupConnection()
{
    QObject::connect(p_exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

void JBlockerMessageViewBox::slt_showMessage(QMessage msg, QMessage::TypeFlags msgType)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;

    /* Clear message box if needed */
    this->slt_clear();
    /* Template of the format to show message on message box */
    static const QString htmlTemplate("\
                                      <html>\
                                      <head>\
                                      </head>\
                                      <body>\
                                      <table border=\"0\" cellspacing=\"0\">\
                                                                      <tr><td><b>From: </b></td><td>%1</td></tr>\
                                                                      <tr><td><b>Subject: </b></td><td>%2</td></tr>\
                                                                      <tr><td><b>Date: </b></td><td>%3</td></tr>\
                                                                      </table>\
                                                                      <hr>%4\
                                                                      <\body>\
                                                                      </html>\
                                                                      ");

    /* BUG(Nokia Qt SDK): need to convert original text content into ascii and then convert back to utf-8 */
    QString subject;
    QString textContent;
    /* Check message type */
    switch(msgType)
    {
    case QMessage::Sms:
        subject = QString::fromUtf8(msg.subject().toAscii());
        textContent = QString::fromUtf8(msg.textContent().toAscii());
        break;
    case QMessage::Email:
        subject = msg.subject();
        textContent = msg.textContent();
        break;
    default:
        qDebug() << "Not available message type";
        return;
    }

    /* Show message in HTML format on message box */
    p_textBrowser->setHtml(htmlTemplate\
                           .arg(msg.from().addressee())\
                           .arg(subject)\
                           .arg(msg.date().toLocalTime().toString(QString("hh:mm:ss dd.MM.yyyy")))\
                           .arg(textContent));
    this->show();
}

void JBlockerMessageViewBox::slt_clear()
{
    p_textBrowser->clear();
}
