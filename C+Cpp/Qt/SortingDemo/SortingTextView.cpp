#include "SortingTextView.h"

SortingTextView::SortingTextView(SortingMethods *sm) :QTextBrowser(), _sortMethods(sm)
{
    init();
}

void SortingTextView::init()
{
    _sortMethods->addListner(this);
    updateText(generateText());
}

void SortingTextView::pointUpdate()
{
    updateText(generateText());
}

void SortingTextView::updateText(QString str)
{
    this->clear();
    this->setPlainText(str);
}

QString SortingTextView::generateText()
{
    QString str;
    QString num;

    QList<int> xl = _sortMethods->getPointXList();

    for(int i=0; i<xl.length(); i++)
    {
        num.setNum(xl.at(i));
        str.append(num+" ");
    }
    return str;
}

void SortingTextView::countInc()
{
}
