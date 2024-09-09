#ifndef COLORTABLEVIEW_H
#define COLORTABLEVIEW_H
#include <QItemDelegate>


class ColorTableView : QItemDelegate
{
Q_OBJECT
public:
    ColorTableView(QWidget *parent = 0) : QItemDelegate(parent) {}
};

#endif // COLORTABLEVIEW_H
