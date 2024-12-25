#include "delayview.h"

DelayView::DelayView(QObject*):
    AbstractItemView()
{
    addLayout("Команды");

    for (int i = 0; i < 6; ++i)
    {
        SpinBoxDelegate *spinBoxDelegate = new SpinBoxDelegate();
        QSpinBox *spinBox = static_cast<QSpinBox*>(spinBoxDelegate->createEditor(this, QStyleOptionViewItem(), QModelIndex()));
        spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxDelegate->setMinimum(spinBox, 0x00);
        spinBoxDelegate->setMaximum(spinBox, 0xff);
        spinBoxDelegate->setHexValues(spinBox);
        spinBoxDelegate->setStyleSheet(spinBox, QString("QSpinBox {\n"
                                                        "background: #4f4f4f;\n"
                                                        "border-radius: 5px;\n"
                                                        "border: 1px solid #141414;\n"
                                                        "padding-top: 2px;\n"
                                                        "padding-bottom: 2px;\n"
                                                        "}\n"
                                                        "QSpinBox:hover {\n"
                                                        "border: 1px solid #6b6b6b;\n"
                                                        "}\n"
                                                        "QSpinBox:disabled {\n"
                                                        "background: rgba(10, 10, 10, 0.59);\n"
                                                        "color: rgba(217, 217, 217, 0.66);\n"
                                                        "border: 1px solid rgb(57, 57, 57);\n"
                                                        "}"));
        setDefault(spinBoxDelegate, spinBox, i);
        connect(spinBox, &QSpinBox::valueChanged, this, [i, spinBox, spinBoxDelegate, this]()
        {
            spinBoxDelegate->setModelData(spinBox, this->model(), this->model()->index(i, 0));
        });
        addWidgetToLayout(0, spinBox, 0, i, Qt::AlignVCenter);
    }

    /*PushButtonDelegate *pushButtonDelegate = new PushButtonDelegate();
    QPushButton *sendButton = static_cast<QPushButton*>(pushButtonDelegate->createEditor(this, QStyleOptionViewItem(), QModelIndex()));
    sendButton->setFixedHeight(static_cast<int>(UiFreeCommand::SendButtonHeight));
    sendButton->setText("Отправить");
    connect(sendButton, &QPushButton::clicked, this, [sendButton, pushButtonDelegate, this]()
    {
        pushButtonDelegate->setModelData(sendButton, this->model(), this->model()->index(-1, 0));
    });

    addWidgetToLayout(0, sendButton, 1, 0, 1, 6, Qt::AlignVCenter);
    */
    setFixedHeight(110);
}


DelayView::~DelayView()
{
    delete widget;
}

void DelayView::setDefault(SpinBoxDelegate *spinBoxDelegate, QSpinBox *spinBox, int index)
{
    switch (index) {
    case 0:
        spinBoxDelegate->setValue(spinBox, 0x5);
        break;
    case 1:
        spinBoxDelegate->setValue(spinBox, 0x5c);
        break;
    case 2:
        spinBoxDelegate->setValue(spinBox, 0x0);
        break;
    case 3:
        spinBoxDelegate->setValue(spinBox, 0x0);
        break;
    case 4:
        spinBoxDelegate->setValue(spinBox, 0xe);
        break;
    case 5:
        spinBoxDelegate->setValue(spinBox, 0x80);
    }
}
