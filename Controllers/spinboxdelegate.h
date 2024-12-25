#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QObject>
#include <QPainter>
#include <QSpinBox>
#include <QModelIndex>
#include <QStyledItemDelegate>

class SpinBoxDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    SpinBoxDelegate(QObject *parent = Q_NULLPTR) : QStyledItemDelegate(parent) {};
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;


    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;


    void setValue(QWidget *editor, int value);
    void setMaximum(QWidget *editor, int value);
    void setMinimum(QWidget *editor, int value);
    void setHexValues(QWidget *editor);
    void setDecValues(QWidget *editor);
    void setButtonSymbols(QWidget *editor, QAbstractSpinBox::ButtonSymbols symbol);
    void setAligment(QWidget *editor, Qt::Alignment aligment);
    //void setRightLeftStyle(QWidget *editor);
    void setStyleSheet(QWidget *editor, QString style);

private:
    void updateEditorValues(QSpinBox *spinbox, const QModelIndex &index) const;
    void updateEditorVisibility(QSpinBox *spinbox, const QModelIndex &index) const;


private slots:
    void commitEditor();
};

#endif // SPINBOXDELEGATE_H
