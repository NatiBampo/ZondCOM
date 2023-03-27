/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_10;
    QLabel *label_16;
    QTableView *tableView;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *portComboBox;
    QComboBox *keithlyPortComboBox;
    QComboBox *lightPortComboBox;
    QPushButton *openPortPushButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QPushButton *backwardPushButton;
    QPushButton *rightPushButton;
    QPushButton *leftPushButton;
    QPushButton *forwardPushButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *yLineEdit;
    QPushButton *coordsPushButton;
    QLineEdit *xLineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QPushButton *lightPushButton;
    QPushButton *statePushButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *tableDownPushButton;
    QPushButton *tableUpPushButton;
    QLabel *label_20;
    QListWidget *logsListWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout_6;
    QSpinBox *AXspinBox;
    QLabel *label_10;
    QLabel *label_23;
    QPushButton *pauseButton;
    QPushButton *scanPushButton;
    QDoubleSpinBox *stepYspinBox;
    QSpinBox *numXspinBox;
    QLabel *label_9;
    QLabel *label_4;
    QDoubleSpinBox *stepColSpinBox;
    QProgressBar *progressBar;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *AYspinBox;
    QLabel *label_15;
    QSpinBox *BYspinBox;
    QSpinBox *numYspinBox;
    QLabel *label_11;
    QLabel *label_14;
    QLabel *label_21;
    QSpinBox *BXspinBox;
    QLabel *label_22;
    QPushButton *orientationButton;
    QDoubleSpinBox *stepRowSpinBox_2;
    QLabel *label_7;
    QDoubleSpinBox *stepXspinBox;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_8;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_5;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_9;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QVBoxLayout *verticalLayout_2;
    QPushButton *goToButton;
    QPushButton *measurePushButton;
    QPushButton *saveMeasureButton;
    QPushButton *continueFromButton;
    QVBoxLayout *verticalLayout_4;
    QSpinBox *columnSpinBox;
    QSpinBox *rowSpinBox;
    QSpinBox *elemSpinBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1195, 612);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_10->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");

        gridLayout_10->addWidget(label_16, 2, 0, 1, 1);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setMinimumSize(QSize(400, 200));
        tableView->setBaseSize(QSize(400, 200));
        tableView->horizontalHeader()->setCascadingSectionResizes(true);
        tableView->horizontalHeader()->setMinimumSectionSize(30);
        tableView->horizontalHeader()->setDefaultSectionSize(60);
        tableView->verticalHeader()->setMinimumSectionSize(24);
        tableView->verticalHeader()->setDefaultSectionSize(27);

        gridLayout_10->addWidget(tableView, 3, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_10, 0, 2, 6, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        portComboBox = new QComboBox(centralwidget);
        portComboBox->setObjectName("portComboBox");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(portComboBox->sizePolicy().hasHeightForWidth());
        portComboBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(portComboBox);

        keithlyPortComboBox = new QComboBox(centralwidget);
        keithlyPortComboBox->setObjectName("keithlyPortComboBox");
        sizePolicy.setHeightForWidth(keithlyPortComboBox->sizePolicy().hasHeightForWidth());
        keithlyPortComboBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(keithlyPortComboBox);

        lightPortComboBox = new QComboBox(centralwidget);
        lightPortComboBox->setObjectName("lightPortComboBox");
        sizePolicy.setHeightForWidth(lightPortComboBox->sizePolicy().hasHeightForWidth());
        lightPortComboBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lightPortComboBox);

        openPortPushButton = new QPushButton(centralwidget);
        openPortPushButton->setObjectName("openPortPushButton");

        horizontalLayout->addWidget(openPortPushButton);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName("gridLayout_4");
        backwardPushButton = new QPushButton(groupBox_3);
        backwardPushButton->setObjectName("backwardPushButton");

        gridLayout_4->addWidget(backwardPushButton, 2, 1, 1, 1);

        rightPushButton = new QPushButton(groupBox_3);
        rightPushButton->setObjectName("rightPushButton");

        gridLayout_4->addWidget(rightPushButton, 1, 2, 1, 1);

        leftPushButton = new QPushButton(groupBox_3);
        leftPushButton->setObjectName("leftPushButton");

        gridLayout_4->addWidget(leftPushButton, 1, 0, 1, 1);

        forwardPushButton = new QPushButton(groupBox_3);
        forwardPushButton->setObjectName("forwardPushButton");

        gridLayout_4->addWidget(forwardPushButton, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 6, 0, 1, 1);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        yLineEdit = new QLineEdit(groupBox);
        yLineEdit->setObjectName("yLineEdit");

        gridLayout->addWidget(yLineEdit, 1, 1, 1, 1);

        coordsPushButton = new QPushButton(groupBox);
        coordsPushButton->setObjectName("coordsPushButton");

        gridLayout->addWidget(coordsPushButton, 2, 0, 1, 2);

        xLineEdit = new QLineEdit(groupBox);
        xLineEdit->setObjectName("xLineEdit");

        gridLayout->addWidget(xLineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 6, 1, 1, 1);

        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setObjectName("gridLayout_7");
        lightPushButton = new QPushButton(groupBox_4);
        lightPushButton->setObjectName("lightPushButton");

        gridLayout_7->addWidget(lightPushButton, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_4, 3, 1, 1, 1);

        statePushButton = new QPushButton(tab);
        statePushButton->setObjectName("statePushButton");

        gridLayout_3->addWidget(statePushButton, 0, 0, 1, 2);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        tableDownPushButton = new QPushButton(groupBox_2);
        tableDownPushButton->setObjectName("tableDownPushButton");

        gridLayout_2->addWidget(tableDownPushButton, 1, 0, 1, 1);

        tableUpPushButton = new QPushButton(groupBox_2);
        tableUpPushButton->setObjectName("tableUpPushButton");

        gridLayout_2->addWidget(tableUpPushButton, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 3, 0, 1, 1);

        label_20 = new QLabel(tab);
        label_20->setObjectName("label_20");

        gridLayout_3->addWidget(label_20, 7, 0, 1, 1);

        logsListWidget = new QListWidget(tab);
        logsListWidget->setObjectName("logsListWidget");

        gridLayout_3->addWidget(logsListWidget, 8, 0, 1, 2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout_6 = new QGridLayout(tab_2);
        gridLayout_6->setObjectName("gridLayout_6");
        AXspinBox = new QSpinBox(tab_2);
        AXspinBox->setObjectName("AXspinBox");
        sizePolicy.setHeightForWidth(AXspinBox->sizePolicy().hasHeightForWidth());
        AXspinBox->setSizePolicy(sizePolicy);
        AXspinBox->setMinimum(0);
        AXspinBox->setMaximum(400000);

        gridLayout_6->addWidget(AXspinBox, 0, 2, 1, 1);

        label_10 = new QLabel(tab_2);
        label_10->setObjectName("label_10");

        gridLayout_6->addWidget(label_10, 2, 0, 1, 1);

        label_23 = new QLabel(tab_2);
        label_23->setObjectName("label_23");

        gridLayout_6->addWidget(label_23, 4, 3, 1, 1);

        pauseButton = new QPushButton(tab_2);
        pauseButton->setObjectName("pauseButton");
        pauseButton->setEnabled(true);
        pauseButton->setCheckable(true);
        pauseButton->setFlat(false);

        gridLayout_6->addWidget(pauseButton, 5, 4, 1, 1);

        scanPushButton = new QPushButton(tab_2);
        scanPushButton->setObjectName("scanPushButton");
        scanPushButton->setCheckable(true);

        gridLayout_6->addWidget(scanPushButton, 5, 3, 1, 1);

        stepYspinBox = new QDoubleSpinBox(tab_2);
        stepYspinBox->setObjectName("stepYspinBox");
        stepYspinBox->setDecimals(3);
        stepYspinBox->setValue(2.805000000000000);

        gridLayout_6->addWidget(stepYspinBox, 2, 4, 1, 1);

        numXspinBox = new QSpinBox(tab_2);
        numXspinBox->setObjectName("numXspinBox");
        numXspinBox->setMaximum(100);
        numXspinBox->setValue(15);

        gridLayout_6->addWidget(numXspinBox, 3, 2, 1, 1);

        label_9 = new QLabel(tab_2);
        label_9->setObjectName("label_9");

        gridLayout_6->addWidget(label_9, 3, 1, 1, 1);

        label_4 = new QLabel(tab_2);
        label_4->setObjectName("label_4");

        gridLayout_6->addWidget(label_4, 0, 0, 1, 1);

        stepColSpinBox = new QDoubleSpinBox(tab_2);
        stepColSpinBox->setObjectName("stepColSpinBox");
        stepColSpinBox->setValue(26.059999999999999);

        gridLayout_6->addWidget(stepColSpinBox, 4, 2, 1, 1);

        progressBar = new QProgressBar(tab_2);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(24);

        gridLayout_6->addWidget(progressBar, 5, 0, 1, 2);

        label_5 = new QLabel(tab_2);
        label_5->setObjectName("label_5");

        gridLayout_6->addWidget(label_5, 0, 1, 1, 1);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName("label_6");

        gridLayout_6->addWidget(label_6, 1, 0, 1, 1);

        AYspinBox = new QSpinBox(tab_2);
        AYspinBox->setObjectName("AYspinBox");
        sizePolicy.setHeightForWidth(AYspinBox->sizePolicy().hasHeightForWidth());
        AYspinBox->setSizePolicy(sizePolicy);
        AYspinBox->setMinimum(0);
        AYspinBox->setMaximum(400000);

        gridLayout_6->addWidget(AYspinBox, 0, 4, 1, 1);

        label_15 = new QLabel(tab_2);
        label_15->setObjectName("label_15");

        gridLayout_6->addWidget(label_15, 3, 3, 1, 1);

        BYspinBox = new QSpinBox(tab_2);
        BYspinBox->setObjectName("BYspinBox");
        BYspinBox->setMinimum(0);
        BYspinBox->setMaximum(400000);

        gridLayout_6->addWidget(BYspinBox, 1, 4, 1, 1);

        numYspinBox = new QSpinBox(tab_2);
        numYspinBox->setObjectName("numYspinBox");
        numYspinBox->setMaximum(100);
        numYspinBox->setValue(30);

        gridLayout_6->addWidget(numYspinBox, 3, 4, 1, 1);

        label_11 = new QLabel(tab_2);
        label_11->setObjectName("label_11");

        gridLayout_6->addWidget(label_11, 3, 0, 1, 1);

        label_14 = new QLabel(tab_2);
        label_14->setObjectName("label_14");

        gridLayout_6->addWidget(label_14, 2, 3, 1, 1);

        label_21 = new QLabel(tab_2);
        label_21->setObjectName("label_21");

        gridLayout_6->addWidget(label_21, 4, 0, 1, 1);

        BXspinBox = new QSpinBox(tab_2);
        BXspinBox->setObjectName("BXspinBox");
        BXspinBox->setMinimum(0);
        BXspinBox->setMaximum(400000);

        gridLayout_6->addWidget(BXspinBox, 1, 2, 1, 1);

        label_22 = new QLabel(tab_2);
        label_22->setObjectName("label_22");

        gridLayout_6->addWidget(label_22, 4, 1, 1, 1);

        orientationButton = new QPushButton(tab_2);
        orientationButton->setObjectName("orientationButton");
        orientationButton->setEnabled(false);
        orientationButton->setFlat(false);

        gridLayout_6->addWidget(orientationButton, 5, 2, 1, 1);

        stepRowSpinBox_2 = new QDoubleSpinBox(tab_2);
        stepRowSpinBox_2->setObjectName("stepRowSpinBox_2");
        stepRowSpinBox_2->setValue(2.810000000000000);

        gridLayout_6->addWidget(stepRowSpinBox_2, 4, 4, 1, 1);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName("label_7");

        gridLayout_6->addWidget(label_7, 1, 1, 1, 1);

        stepXspinBox = new QDoubleSpinBox(tab_2);
        stepXspinBox->setObjectName("stepXspinBox");
        stepXspinBox->setDecimals(3);
        stepXspinBox->setValue(1.550000000000000);

        gridLayout_6->addWidget(stepXspinBox, 2, 2, 1, 1);

        label_12 = new QLabel(tab_2);
        label_12->setObjectName("label_12");

        gridLayout_6->addWidget(label_12, 0, 3, 1, 1);

        label_13 = new QLabel(tab_2);
        label_13->setObjectName("label_13");

        gridLayout_6->addWidget(label_13, 1, 3, 1, 1);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName("label_8");

        gridLayout_6->addWidget(label_8, 2, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName("groupBox_5");
        gridLayoutWidget = new QWidget(groupBox_5);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 20, 551, 201));
        gridLayout_9 = new QGridLayout(gridLayoutWidget);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_17 = new QLabel(gridLayoutWidget);
        label_17->setObjectName("label_17");
        label_17->setLayoutDirection(Qt::LeftToRight);
        label_17->setMargin(6);

        verticalLayout_5->addWidget(label_17);

        label_18 = new QLabel(gridLayoutWidget);
        label_18->setObjectName("label_18");
        label_18->setLayoutDirection(Qt::LeftToRight);
        label_18->setMargin(6);

        verticalLayout_5->addWidget(label_18);

        label_19 = new QLabel(gridLayoutWidget);
        label_19->setObjectName("label_19");
        label_19->setLayoutDirection(Qt::LeftToRight);
        label_19->setMargin(6);

        verticalLayout_5->addWidget(label_19);


        gridLayout_9->addLayout(verticalLayout_5, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        goToButton = new QPushButton(gridLayoutWidget);
        goToButton->setObjectName("goToButton");

        verticalLayout_2->addWidget(goToButton);

        measurePushButton = new QPushButton(gridLayoutWidget);
        measurePushButton->setObjectName("measurePushButton");

        verticalLayout_2->addWidget(measurePushButton);

        saveMeasureButton = new QPushButton(gridLayoutWidget);
        saveMeasureButton->setObjectName("saveMeasureButton");

        verticalLayout_2->addWidget(saveMeasureButton);

        continueFromButton = new QPushButton(gridLayoutWidget);
        continueFromButton->setObjectName("continueFromButton");

        verticalLayout_2->addWidget(continueFromButton);


        gridLayout_9->addLayout(verticalLayout_2, 0, 2, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        columnSpinBox = new QSpinBox(gridLayoutWidget);
        columnSpinBox->setObjectName("columnSpinBox");

        verticalLayout_4->addWidget(columnSpinBox);

        rowSpinBox = new QSpinBox(gridLayoutWidget);
        rowSpinBox->setObjectName("rowSpinBox");

        verticalLayout_4->addWidget(rowSpinBox);

        elemSpinBox = new QSpinBox(gridLayoutWidget);
        elemSpinBox->setObjectName("elemSpinBox");

        verticalLayout_4->addWidget(elemSpinBox);


        gridLayout_9->addLayout(verticalLayout_4, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox_5);


        gridLayout_6->addLayout(verticalLayout, 7, 0, 1, 5);

        tabWidget->addTab(tab_2, QString());

        formLayout->setWidget(1, QFormLayout::FieldRole, tabWidget);


        gridLayout_5->addLayout(formLayout, 0, 0, 5, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1195, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        orientationButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\273\320\265\320\264\320\275\320\270\320\265 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202\321\213", nullptr));
        portComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\320\275\320\260\321\200", nullptr));
        keithlyPortComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Keithley", nullptr));
        lightPortComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\224\320\270\320\276\320\264", nullptr));
        openPortPushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\321\202\320\276\320\273\320\276\320\274", nullptr));
        backwardPushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        rightPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\277\321\200\320\260\320\262\320\276", nullptr));
        leftPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\273\320\265\320\262\320\276", nullptr));
        forwardPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\277\320\265\321\200\320\265\320\264", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", nullptr));
        coordsPushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\236\321\201\320\262\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
        lightPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
        statePushButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\273", nullptr));
        tableDownPushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        tableUpPushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\275\321\217\321\202\321\214", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "\320\226\321\203\321\200\320\275\320\260\320\273", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\320\240\321\203\321\207\320\275\320\276\320\271", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\203\320\267\320\260", nullptr));
        scanPushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\320\276", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\320\265\321\206", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\210\320\260\320\263\320\276\320\262", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263 \320\274\321\203\320\273\321\214\321\202\320\270\320\277\320\273\320\270\320\272\320\260\321\206\320\270\320\270", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        orientationButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\200\320\270\320\265\320\275\321\202\320\260\321\206\320\270\321\217 \320\277\320\273\320\260\321\201\321\202\320\270\320\275\321\213", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\205\320\276\320\264 \320\275\320\260 \320\275\321\203\320\266\320\275\321\213\320\271 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\273\320\261\320\265\321\206", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\320\240\321\217\320\264", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        goToButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270", nullptr));
        measurePushButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", nullptr));
        saveMeasureButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", nullptr));
        continueFromButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\321\214 \320\276\320\261\321\205\320\276\320\264 \321\201 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
