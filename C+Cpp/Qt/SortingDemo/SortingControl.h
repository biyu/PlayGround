#ifndef SORTINGCONTROL_H
#define SORTINGCONTROL_H

#include "SortingMethods.h"
#include "SortingItem.h"
#include "SortingView.h"
#include "SortingTextView.h"

#include <QtGui>
#include <QtCore>

class SortingControl : public QWidget
{
    Q_OBJECT
public:
    enum SORTSTATUS {
        START,
        STOP
    };

    SortingControl();

private:
    void init();
    void createSortingItems();

private slots:
    void startPressed();
    void newPressed();
    void changeSortMethod();
    void changeDuration(int duration);
    void resetPressed();

private:
    /*GUI*/
    SortingView* _sortView;
    QPushButton* _startB;       /*Start Button*/
    QPushButton* _newB;         /*New Button*/
    QPushButton* _resetB;       /*Reset Button*/
    QComboBox* _selectC;        /*Select Combo*/
    QSpinBox* _rateS;           /*Rate SpinBox*/
    QLabel* _rateL;             /*Rate Label*/
    SortingTextView* _textBr;      /*Text browser*/

    /*Core*/
    SortingMethods* _sortMethods;
    QGraphicsScene* _sortScene;
    SORTSTATUS _status;

};

#endif // SORTINGCONTROL_H
