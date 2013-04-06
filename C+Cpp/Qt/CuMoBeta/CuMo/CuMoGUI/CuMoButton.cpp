#include "CuMoButton.h"

/*! \brief CuMoButton constructor.
 *  \param buttonType
 *  \param buttonLabel String to be written on the button.
 */
CuMoButton::CuMoButton(ButtonType buttonType, QString buttonLabel, QGraphicsProxyWidget* parent)
    : CuMoWidget(parent)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    _pushButton = new QPushButton();
    _buttonType = buttonType;
    _buttonLabel = buttonLabel;
    this->setWidget(_pushButton);
    /* No need to use mouseClickEvent */
    // QObject::connect(_pushButton, SIGNAL(clicked()), this, SLOT(test()));
}

/*! \brief CuMoButton destructor. */
CuMoButton::~CuMoButton()
{

}

//void CuMoButton::test()
//{
//    qDebug() << "Clicked Event";
//}

/*! \brief overload paint */
void CuMoButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    bool down = option->state & QStyle::State_Sunken;
    if(down)
    {
        painter->translate(3, 3);
    }

    QRect paintRect(0, 0, _rect.width(), _rect.height());

    //    QFont font;
    //    font.setFamily("Nokia Sans");
    //    font.setStyle(QFont::StyleNormal);
    //    font.setStyleStrategy(QFont::PreferAntialias);
    //    font.setWeight(QFont::Bold);
    //    font.setPixelSize(16);

    QFont font;
    font.setFamily("Helvetica");
    font.setStyle(QFont::StyleNormal);
    font.setStyleStrategy(QFont::PreferAntialias);
    font.setWeight(QFont::Bold);

    switch (_buttonType){
    case GENERIC:
        painter->setBrush(Qt::black);
        painter->setOpacity(0.7);
        painter->drawRoundRect(paintRect, 20, 50);
        /* set color to Finnkino yellow */
        painter->setPen(QColor(243, 186, 36));
        font.setPixelSize(18);
        painter->setFont(font);
        painter->drawText(paintRect, Qt::AlignCenter, _buttonLabel);
        break;
    case EXIT:
        painter->setBrush(Qt::black);
        painter->setOpacity(0.7);
        painter->drawEllipse(paintRect);
        /* set color to Finnkino yellow */
        painter->setPen(QColor(243, 186, 36));
        font.setPixelSize(35);
        painter->setFont(font);
        painter->drawText(paintRect, Qt::AlignCenter, _buttonLabel);
        break;
    case CONTROL:
        break;
    }
}

/*!
 *  \brief set geometry of button.
 *  \param buttonLabel String to be written on the button.
 */
void CuMoButton::configGeometry (const QRect & rect)
{
    _rect = rect;
    this->setGeometry(_rect);
    // _pushButton->setGeometry(_rect);
}

/*!
 * \brief This function returns point of _pushButton
 */
QPushButton const * CuMoButton::getButton()
{
    return _pushButton;
}

/*!
 * \brief This function changes a button's label.
 * \param label The button's label.
 */
void CuMoButton::setLabel(QString label)
{
    this->_buttonLabel = label;
}

QString CuMoButton::getLabel()
{
    return this->_buttonLabel;
}

/*!
 * \brief Overridden.
 */
void CuMoButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    emit pressed();
    CuMoWidget::mousePressEvent(event);
}

/*!
 * \brief Overridden.
 */
void CuMoButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    emit released();
    CuMoWidget::mouseReleaseEvent(event);
}
