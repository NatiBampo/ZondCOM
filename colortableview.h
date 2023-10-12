#ifndef COLORTABLEVIEW_H
#define COLORTABLEVIEW_H
#include <QStandardItemModel>


class ColorTableView : public QStandardItemModel
{
Q_OBJECT
public:
    ColorTableView();
    ColorTableView(int rows, int columns, QObject *parent = nullptr); //: QStandardItemModel( rows,  columns, parent);
    int color = 0;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void colorData(const QModelIndex &index, double current);
};

#endif // COLORTABLEVIEW_H
