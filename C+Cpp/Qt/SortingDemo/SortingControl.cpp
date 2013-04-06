#include "SortingControl.h"

SortingControl::SortingControl():_status(STOP)
{
    init();    // Initial view, scene, methoed, and UI
}

void SortingControl::init()
{
    _sortScene = new QGraphicsScene(200, -900, 450, 1000);
    _sortMethods = new SortingMethods(new PointXGenerator(100));
    _sortView = new SortingView(_sortScene, _sortMethods);

    _sortView->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Sorting Demo"));
    _sortView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    _sortView->setCacheMode(QGraphicsView::CacheBackground);
    _sortView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    _startB = new QPushButton();
    _startB->setText("Start Demo");

    _newB = new QPushButton();
    _newB->setText("New Sort");

    _resetB = new QPushButton();
    _resetB->setText("Reset");

    _selectC = new QComboBox();
    _selectC->addItem("Bubble Sort", SortingMethods::BUBBLESORT);
    _selectC->addItem("Insert Sort", SortingMethods::INSERTSORT);

    _rateS = new QSpinBox();
    _rateS->setRange(10, 400);
    _rateS->setSingleStep(50);
    _rateS->setValue(200);          // Init value

    _rateL = new QLabel("ms");
    _rateL->setBuddy(_rateS);

    _textBr = new SortingTextView(_sortMethods);
    _textBr->setMinimumHeight(80);

    QObject::connect(_startB, SIGNAL(clicked()), this, SLOT(startPressed()));
    QObject::connect(_newB, SIGNAL(clicked()), this, SLOT(newPressed()));
    QObject::connect(_selectC, SIGNAL(activated(int)), this, SLOT(changeSortMethod()));
    QObject::connect(_rateS, SIGNAL(valueChanged(int)), this, SLOT(changeDuration(int)));
    QObject::connect(_resetB, SIGNAL(clicked()), this, SLOT(resetPressed()));

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(_sortView, 0, 1);
    mainLayout->setRowMinimumHeight(1, 10);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(_startB);
    buttonLayout->addWidget(_resetB);
    buttonLayout->addWidget(_newB);
    buttonLayout->addWidget(_selectC);
    buttonLayout->addWidget(_rateS);
    buttonLayout->addWidget(_rateL);
    QVBoxLayout* bottomLayout = new QVBoxLayout();
    bottomLayout->addWidget(_textBr);
    bottomLayout->addLayout(buttonLayout);
    mainLayout->addLayout(bottomLayout, 1, 1, -1, -1, Qt::AlignCenter);

    this->setLayout(mainLayout);
}

void SortingControl::startPressed()
{
    switch(_status)
    {
        // TODO: Using State Machine!
    case START:
        _sortMethods->setPause(true);
        _selectC->setEnabled(false);
        _rateS->setEnabled(false);
        _startB->setText("Start Demo");
        _status = STOP;
        break;
    case STOP:
        _sortMethods->setPause(false);
        _selectC->setEnabled(false);
        _rateS->setEnabled(false);
        _startB->setText("Pause");
        _status = START;
        break;
    default:
        break;
    }
    if(!_sortMethods->isSorted())
        _sortMethods->startSort();
}

void SortingControl::newPressed()
{
    if(_status == STOP || _sortMethods->isSorted())
    {
        // TODO: Using State Machine!
        _selectC->setEnabled(true);
        _rateS->setEnabled(true);
        _startB->setText("Start Demo");
        _sortMethods->newSort();
        _sortView->resetCounter();
        _status = STOP;
    }
}

void SortingControl::resetPressed()
{
    if(_status == STOP || _sortMethods->isSorted())
    {
        // TODO: Using State Machine!
        _selectC->setEnabled(true);
        _rateS->setEnabled(true);
        _startB->setText("Start Demo");
        _sortMethods->reset();
        _sortView->resetCounter();
        _status = STOP;
    }
}

void SortingControl::changeSortMethod()
{
    _sortMethods->setSortType(SortingMethods::SORTTYPE(_selectC->itemData(_selectC->currentIndex(), Qt::UserRole).toInt()));
}

void SortingControl::changeDuration(int duration)
{
    _sortView->changeDuration(duration);
}
