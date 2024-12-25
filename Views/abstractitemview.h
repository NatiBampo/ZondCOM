#ifndef ABSTRACTITEMVIEW_H
#define ABSTRACTITEMVIEW_H

#include <QAbstractItemView>
#include <QLabel>
#include <QGridLayout>
#include <QScrollBar>
#include <QScrollArea>

struct Layout
{
    QGridLayout *layout = Q_NULLPTR;
    QScrollArea *scrollArea = Q_NULLPTR;
};
class AbstractItemView : QAbstractItemView
{
public:
    AbstractItemView(QWidget *parent = Q_NULLPTR);
    virtual ~AbstractItemView() {};

private:
    QGridLayout *mainGrid = Q_NULLPTR;

private:
    QList<Layout*> *layouts = Q_NULLPTR;

public:
    int layoutsCount();
public:
    void addWidgetToLayout(int index, QWidget *widget);
    void addWidgetToLayout(int index, QWidget *widget, int row, int col, int rowSpan, int colSpan, Qt::Alignment alignment = Qt::AlignCenter);
    void addWidgetToLayout(int index, QWidget *widget, int row, int col, Qt::Alignment alignment = Qt::AlignCenter);


public:
    void addLayout(QString layoutName);

public:
    void addItemToLayout(int index, QLayoutItem *item, int row, int col);

public:
    void setFixedHeightForLayout(int index, int height);
    void setMarginsForLayout(int index, QMargins margins);
    void setVSpacingForLayout(int index, int spacing);

public:
    QRect visualRect(const QModelIndex &)const { return QRect(); };
    void scrollTo(const QModelIndex &, ScrollHint) { };

    // Возвращает значение индекса QModelIndex, в котором находится мышь
    QModelIndex indexAt(const QPoint &) const { return QModelIndex(); };

protected:
    QModelIndex moveCursor(QAbstractItemView::CursorAction, Qt::KeyboardModifiers) { return QModelIndex(); };
    int horizontalOffset() const { return 0; };
    int verticalOffset() const { return 0; };
    bool isIndexHidden(const QModelIndex &) const { return false; };

    // Используется для установки выбранного состояния текущей области для выбранной области
    void setSelection(const QRect &, QItemSelectionModel::SelectionFlags) { };
    QRegion visualRegionForSelection(const QItemSelection &) const { return QRegion(); };

};

#endif // ABSTRACTITEMVIEW_H
