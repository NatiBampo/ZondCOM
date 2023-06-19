/********************************************************************************
** Form generated from reading UI file 'keithley.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEITHLEY_H
#define UI_KEITHLEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Keithley
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Keithley)
    {
        if (Keithley->objectName().isEmpty())
            Keithley->setObjectName("Keithley");
        Keithley->resize(400, 300);
        centralwidget = new QWidget(Keithley);
        centralwidget->setObjectName("centralwidget");
        Keithley->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Keithley);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 400, 22));
        Keithley->setMenuBar(menubar);
        statusbar = new QStatusBar(Keithley);
        statusbar->setObjectName("statusbar");
        Keithley->setStatusBar(statusbar);

        retranslateUi(Keithley);

        QMetaObject::connectSlotsByName(Keithley);
    } // setupUi

    void retranslateUi(QMainWindow *Keithley)
    {
        Keithley->setWindowTitle(QCoreApplication::translate("Keithley", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Keithley: public Ui_Keithley {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEITHLEY_H
