#ifndef DELAYVIEW_H
#define DELAYVIEW_H

#include <QAbstractItemView>
#include <Views/abstractitemview.h>
#include "Controllers/spinboxdelegate.h"

class DelayView: public AbstractItemView
{
    Q_OBJECT
public:
    DelayView(QObject* parent = Q_NULLPTR);
    ~DelayView();

private:
    QWidget *widget;

private:
    void setDefault(SpinBoxDelegate *spinBoxDelegate, QSpinBox *spinBox, int index);
};

#endif // DELAYVIEW_H
