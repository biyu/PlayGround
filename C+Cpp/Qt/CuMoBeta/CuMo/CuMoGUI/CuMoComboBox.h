#ifndef CUMOCOMBOBOX_H
#define CUMOCOMBOBOX_H

#include "CuMoWidget.h"

class CuMoComboBox : public CuMoWidget
{
    Q_OBJECT

public:
    /* Constructor */
    CuMoComboBox(QGraphicsProxyWidget* parent=0);
    /* Destructor */
    ~CuMoComboBox();
    /* Add new action to combobox */
    void addNewItem(QString choice);
    /* Add items */
    void addNewItems(const QStringList& texts);
    /* Set geometry */
    void configGeometry(const QRect& rect);
    /* Get current index */
    int getCurrentIndex();
    /* Set current index */
    void setCurrentIndex(int index);

protected:

private:

private:
    /* QComboBox */
    QComboBox* p_comboBox;
};

#endif // CUMOCOMBOBOX_H
