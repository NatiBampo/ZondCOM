/********************************************************************************
** Form generated from reading UI file 'stats.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATS_H
#define UI_STATS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Stats
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Stats)
    {
        if (Stats->objectName().isEmpty())
            Stats->setObjectName("Stats");
        Stats->resize(400, 400);
        Stats->setMaximumSize(QSize(20000, 20000));
        centralwidget = new QWidget(Stats);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(9, 9, 64, 18));
        label->setTextFormat(Qt::PlainText);
        label->setMargin(1);
        label->setIndent(1);
        Stats->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Stats);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 400, 22));
        Stats->setMenuBar(menubar);
        statusbar = new QStatusBar(Stats);
        statusbar->setObjectName("statusbar");
        Stats->setStatusBar(statusbar);

        retranslateUi(Stats);

        QMetaObject::connectSlotsByName(Stats);
    } // setupUi

    void retranslateUi(QMainWindow *Stats)
    {
        Stats->setWindowTitle(QCoreApplication::translate("Stats", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("Stats", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Stats: public Ui_Stats {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATS_H
