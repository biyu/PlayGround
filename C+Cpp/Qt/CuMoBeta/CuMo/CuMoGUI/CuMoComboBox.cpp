#include "CuMoComboBox.h"

CuMoComboBox::CuMoComboBox(QGraphicsProxyWidget *parent)
    : CuMoWidget(parent), p_comboBox(0)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    p_comboBox = new QComboBox();
    this->setWidget(p_comboBox);
}

CuMoComboBox::~CuMoComboBox()
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
}

void CuMoComboBox::addNewItem(QString choice)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
}

void CuMoComboBox::addNewItems(const QStringList& items)
{
    p_comboBox->addItems(items);
}

void CuMoComboBox::configGeometry(const QRect& rect)
{
    qDebug() << "+ " << __PRETTY_FUNCTION__;
    p_comboBox->setGeometry(rect);
    this->setGeometry(rect);
}

void CuMoComboBox::setCurrentIndex(int index)
{
    p_comboBox->setCurrentIndex(index);
}

int CuMoComboBox::getCurrentIndex()
{
    return p_comboBox->currentIndex();
}
