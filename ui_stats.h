/********************************************************************************
** Form generated from reading UI file 'stats.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATS_H
#define UI_STATS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Stats
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Stats)
    {
        if (Stats->objectName().isEmpty())
            Stats->setObjectName("Stats");
        Stats->resize(800, 600);
        menubar = new QMenuBar(Stats);
        menubar->setObjectName("menubar");
        Stats->setMenuBar(menubar);
        centralwidget = new QWidget(Stats);
        centralwidget->setObjectName("centralwidget");
        Stats->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Stats);
        statusbar->setObjectName("statusbar");
        Stats->setStatusBar(statusbar);

        retranslateUi(Stats);

        QMetaObject::connectSlotsByName(Stats);
    } // setupUi

    void retranslateUi(QMainWindow *Stats)
    {
        Stats->setWindowTitle(QCoreApplication::translate("Stats", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Stats: public Ui_Stats {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATS_H
