#include "abstractitemview.h"

AbstractItemView::AbstractItemView(QWidget *parent) : QAbstractItemView(parent)
{
    layouts = new QList<Layout *>();
    mainGrid = new QGridLayout();
    mainGrid->setContentsMargins(0,0,0,0);
    setLayout(mainGrid);
}

void AbstractItemView::addWidgetToLayout(int index, QWidget *widget)
{
    layouts->at(index)->layout->addWidget(widget);
}

void AbstractItemView::addWidgetToLayout(int index, QWidget *widget, int row, int col, Qt::Alignment alignment)
{
    layouts->at(index)->layout->addWidget(widget, row, col, alignment);
}

void AbstractItemView::addWidgetToLayout(int index, QWidget *widget, int row, int col, int rowSpan, int colSpan, Qt::Alignment alignment)
{
    layouts->at(index)->layout->addWidget(widget, row, col, rowSpan, colSpan, alignment);
}

void AbstractItemView::addLayout(QString layoutName)
{
    QLabel *headerSectionLabel = new QLabel(layoutName);
    headerSectionLabel->setFixedHeight(24);
    headerSectionLabel->setStyleSheet(QString("background-color: #6c6c6c;\n"
                                              "padding-left: 16px;\n"
                                              "padding-top: 5px;\n"
                                              "padding-bottom: 5px;\n"
                                              "font-weight: bold;\n"
                                              "border-bottom-right-radius: 0px;\n"
                                              "border-bottom-left-radius: 0px;\n"));

    QGridLayout *grid = new QGridLayout();
    grid->setContentsMargins(7,7,7,7);
    grid->setVerticalSpacing(7);

    QWidget *widget = new QWidget();
    widget->setLayout(grid);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widget);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->verticalScrollBar()->setCursor(Qt::PointingHandCursor);

    QGridLayout *headerLayout = new QGridLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->addWidget(headerSectionLabel, 0, 0);

    QGridLayout *wrapperLayout = new QGridLayout();
    wrapperLayout->setContentsMargins(0, 0, 0, 0);

    wrapperLayout->addLayout(headerLayout, 0, 0);
    wrapperLayout->addWidget(scrollArea, 1, 0);

    Layout *layout = new Layout;
    layout->layout = grid;
    layout->scrollArea = scrollArea;

    layouts->append(layout);

    if (layoutsCount() > 1)
        layouts->at(layoutsCount() - 2)->scrollArea->setStyleSheet(QString("border-radius: 0px;\n"));

    mainGrid->addLayout(wrapperLayout, layoutsCount() - 1, 0);
}

void AbstractItemView::addItemToLayout(int index, QLayoutItem *item, int row, int col)
{
    layouts->at(index)->layout->addItem(item, row, col);
}

void AbstractItemView::setMarginsForLayout(int index, QMargins margins)
{
    layouts->at(index)->layout->setContentsMargins(margins);
}

void AbstractItemView::setVSpacingForLayout(int index, int spacing)
{
    layouts->at(index)->layout->setVerticalSpacing(spacing);
}

void AbstractItemView::setFixedHeightForLayout(int index, int height)
{
    layouts->at(index)->scrollArea->setFixedHeight(height);
}

int AbstractItemView::layoutsCount()
{
    return layouts->count();
}
