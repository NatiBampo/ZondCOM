#include "colortableview.h"

ColorTableView::ColorTableView()
{

}

QVariant ColorTableView::data(const QModelIndex &index, int role) const{

}

void ColorTableView::colorData(const QModelIndex &index, double current){
    switch (index.column())
    {
    case 4: color = (current > - qPow(10, -5)) ? 0 : 9;
    case 5: color = (current < qPow(10, -12)) ? 1 : (current < 5 * qPow(10, -12)) ? 2 : (current < qPow(10, -11)) ? 3 : 9;
    case 6: color = (current < qPow(10, -11)) ? 1 : 9;
    case 7: color = (current < 1.07026 * qPow(10, -7)) ? 1 : 9;
    }
}
