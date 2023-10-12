#include "colortableview.h"

ColorTableView::ColorTableView()
{}

ColorTableView::ColorTableView(int rows, int columns, QObject *parent) : QStandardItemModel( rows,  columns, parent){}

QVariant ColorTableView::data(const QModelIndex &index, int role) const
{
    if (role==Qt::BackgroundRole)
    {
        switch(color)
        {
        case 1:
            return QVariant(QColor(Qt::darkGreen));
        case 2:
            return QVariant(QColor(Qt::green));
        case 3:
            return QVariant(QColor(Qt::blue));
        case 0:
            return QVariant(QColor(Qt::red));
        default://only to disable warning
            return QVariant(QColor(Qt::white));
        }
    }
}



void ColorTableView::colorData(const QModelIndex &index, double current){
    switch (index.column())
    {
    case 4: color = (current > - qPow(10, -5)) ? 1 : 9;
    case 5: color = (current < qPow(10, -12)) ? 1 : (current < 5 * qPow(10, -12)) ? 2 : (current < qPow(10, -11)) ? 3 : 9;
    case 6: color = (current < qPow(10, -11)) ? 1 : 9;
    case 7: color = (current < 1.07026 * qPow(10, -7)) ? 1 : 9;
    }
}
