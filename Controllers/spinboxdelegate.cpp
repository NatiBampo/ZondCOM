#include "spinboxdelegate.h"

QWidget* SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
                      const QModelIndex &index) const
{
    QSpinBox *spinbox = new QSpinBox(parent);
    //ControllerStyle *style  = new ControllerStyle();
    //spinbox->setStyle(style);
    spinbox->setAlignment(Qt::AlignCenter);
    spinbox->setCursor(Qt::PointingHandCursor);
    if (index.model())
    {
        updateEditorValues(spinbox, index);
        connect(spinbox, &QSpinBox::valueChanged, this, &SpinBoxDelegate::commitEditor);
    }
    return spinbox;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor);
    updateEditorValues(spinbox, index);
    updateEditorVisibility(spinbox, index);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor);
    int value = spinbox->value();
    if (model->data(index).toInt() != value)
        model->setData(index, value);
}


void SpinBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const
{
    QString labelText = "";
    bool isActive = index.model()->index(index.row(), 2).data().toBool();
    //ParametersType type = qvariant_cast<ParametersType>(index.model()->index(-1, -1).data());
    bool type = index.model()->index(-1, -1).data().toBool();

    if (type)
    {
        if (isActive) return;
        labelText = "Выкл";
    }
    if (!type)
    {
        if (!isActive) return;
        labelText = "Авто";
    }

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawText(option.rect, Qt::AlignCenter, labelText);

    painter->restore();
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor);
    updateEditorVisibility(spinbox, index);
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}


void SpinBoxDelegate::setValue(QWidget *editor, int value)
{
    if (QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor))
        spinbox->setValue(value);
}

void SpinBoxDelegate::setMaximum(QWidget *editor, int value)
{
    if (QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor))
        spinbox->setMaximum(value);
}

void SpinBoxDelegate::setMinimum(QWidget *editor, int value)
{
    if (QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor))
        spinbox->setMinimum(value);
}

void SpinBoxDelegate::setHexValues(QWidget *editor)
{
    if (QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor))
    {
        spinbox->setPrefix("0x");
        spinbox->setDisplayIntegerBase(16);
    }
}

void SpinBoxDelegate::setDecValues(QWidget *editor)
{
    if (QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor))
    {
        spinbox->setPrefix("");
        spinbox->setDisplayIntegerBase(10);
    }
}

void SpinBoxDelegate::setButtonSymbols(QWidget *editor,
                                       QAbstractSpinBox::ButtonSymbols symbol)
{
    if (QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor))
        spinbox->setButtonSymbols(symbol);
}

void SpinBoxDelegate::setAligment(QWidget *editor, Qt::Alignment aligment)
{
    if (QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor))
        spinbox->setAlignment(aligment);
}

void SpinBoxDelegate::setStyleSheet(QWidget *editor, QString style)
{
    if (QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor))
        spinbox->setStyleSheet(style);
}

void SpinBoxDelegate::updateEditorValues(QSpinBox *spinbox, const QModelIndex &index) const
{
    if (index.isValid())
    {
        int min = index.model()->index(index.row(), 3).data().toInt();
        int max = index.model()->index(index.row(), 4).data().toInt();
        int value = index.data().toInt();
        spinbox->setMinimum(min);
        spinbox->setMaximum(max);
        spinbox->setValue(value);
    }
}

void SpinBoxDelegate::updateEditorVisibility(QSpinBox *spinbox, const QModelIndex &index) const
{
    bool isActive = index.model()->index(index.row(), 2).data().toBool();
    //ParametersType type = qvariant_cast<ParametersType>(index.model()->index(-1, -1).data());
    bool type = index.model()->index(-1, -1).data().toBool();
    if (type) isActive = !isActive;
    spinbox->setVisible(!isActive);
}

void SpinBoxDelegate::commitEditor()
{
    QSpinBox *spinbox = qobject_cast<QSpinBox *>(sender());
    emit commitData(spinbox);
}
