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
#include <QtWidgets/QCheckBox>
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
#include <QtWidgets/QSpacerItem>
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
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_26;
    QLabel *label_25;
    QLabel *label_24;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *portComboBox;
    QComboBox *keithlyPortComboBox;
    QComboBox *lightPortComboBox;
    QPushButton *autoPortButton;
    QPushButton *openPortPushButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *addressHeaderLabel;
    QLabel *addressLabel;
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
    QDoubleSpinBox *stepRowSpinBox;
    QLabel *label_12;
    QSpinBox *numYspinBox;
    QLabel *label_15;
    QLabel *label_9;
    QDoubleSpinBox *stepXspinBox;
    QLabel *label_11;
    QLabel *label_7;
    QSpinBox *upRightSpinBox;
    QLabel *label_22;
    QSpinBox *BYspinBox;
    QPushButton *orientationButton;
    QSpinBox *BXspinBox;
    QLabel *label_21;
    QSpinBox *numXspinBox;
    QLabel *label_14;
    QSpinBox *downRightSpinBox;
    QLabel *label_13;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_5;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_9;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *goToButton;
    QPushButton *measurePushButton;
    QPushButton *saveMeasureButton;
    QPushButton *continueFromButton;
    QVBoxLayout *verticalLayout_4;
    QSpinBox *columnSpinBox;
    QSpinBox *rowSpinBox;
    QSpinBox *elemSpinBox;
    QSpinBox *upLeftSpinBox;
    QDoubleSpinBox *stepYspinBox;
    QLabel *label_10;
    QPushButton *measureBButton;
    QLabel *label_23;
    QSpinBox *downLeftSpinBox;
    QProgressBar *progressBar;
    QLabel *label_27;
    QPushButton *pauseButton;
    QLabel *label_28;
    QLabel *label_8;
    QPushButton *scanPushButton;
    QLabel *label_4;
    QDoubleSpinBox *stepColSpinBox;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 692);
        MainWindow->setMaximumSize(QSize(1200, 1000));
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
        tableView->setDragDropOverwriteMode(false);
        tableView->horizontalHeader()->setCascadingSectionResizes(true);
        tableView->horizontalHeader()->setMinimumSectionSize(33);
        tableView->horizontalHeader()->setDefaultSectionSize(60);
        tableView->verticalHeader()->setMinimumSectionSize(24);
        tableView->verticalHeader()->setDefaultSectionSize(27);

        gridLayout_10->addWidget(tableView, 3, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_10, 0, 2, 6, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_3->setContentsMargins(-1, -1, -1, 11);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(42, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_26 = new QLabel(centralwidget);
        label_26->setObjectName("label_26");

        horizontalLayout_2->addWidget(label_26);

        label_25 = new QLabel(centralwidget);
        label_25->setObjectName("label_25");

        horizontalLayout_2->addWidget(label_25);

        label_24 = new QLabel(centralwidget);
        label_24->setObjectName("label_24");

        horizontalLayout_2->addWidget(label_24);

        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_2);

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

        autoPortButton = new QPushButton(centralwidget);
        autoPortButton->setObjectName("autoPortButton");

        horizontalLayout->addWidget(autoPortButton);

        openPortPushButton = new QPushButton(centralwidget);
        openPortPushButton->setObjectName("openPortPushButton");

        horizontalLayout->addWidget(openPortPushButton);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        addressHeaderLabel = new QLabel(centralwidget);
        addressHeaderLabel->setObjectName("addressHeaderLabel");
        addressHeaderLabel->setMaximumSize(QSize(100, 30));
        addressHeaderLabel->setAutoFillBackground(true);

        horizontalLayout_3->addWidget(addressHeaderLabel);

        addressLabel = new QLabel(centralwidget);
        addressLabel->setObjectName("addressLabel");
        addressLabel->setMaximumSize(QSize(650, 40));
        addressLabel->setAutoFillBackground(true);
        addressLabel->setLineWidth(2);
        addressLabel->setMidLineWidth(1);
        addressLabel->setTextFormat(Qt::RichText);
        addressLabel->setWordWrap(true);

        horizontalLayout_3->addWidget(addressLabel);


        verticalLayout_3->addLayout(horizontalLayout_3);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout_3);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMaximumSize(QSize(600, 16777215));
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
        stepRowSpinBox = new QDoubleSpinBox(tab_2);
        stepRowSpinBox->setObjectName("stepRowSpinBox");
        stepRowSpinBox->setValue(2.810000000000000);

        gridLayout_6->addWidget(stepRowSpinBox, 3, 6, 1, 1);

        label_12 = new QLabel(tab_2);
        label_12->setObjectName("label_12");
        label_12->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_12, 0, 5, 1, 1);

        numYspinBox = new QSpinBox(tab_2);
        numYspinBox->setObjectName("numYspinBox");
        numYspinBox->setMaximum(100);
        numYspinBox->setValue(30);

        gridLayout_6->addWidget(numYspinBox, 2, 6, 1, 1);

        label_15 = new QLabel(tab_2);
        label_15->setObjectName("label_15");
        label_15->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_15, 2, 5, 1, 1);

        label_9 = new QLabel(tab_2);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(10, 10));
        label_9->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_9, 2, 1, 1, 1);

        stepXspinBox = new QDoubleSpinBox(tab_2);
        stepXspinBox->setObjectName("stepXspinBox");
        stepXspinBox->setDecimals(3);
        stepXspinBox->setValue(1.550000000000000);

        gridLayout_6->addWidget(stepXspinBox, 1, 2, 1, 1);

        label_11 = new QLabel(tab_2);
        label_11->setObjectName("label_11");

        gridLayout_6->addWidget(label_11, 2, 0, 1, 1);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName("label_7");

        gridLayout_6->addWidget(label_7, 4, 5, 1, 1);

        upRightSpinBox = new QSpinBox(tab_2);
        upRightSpinBox->setObjectName("upRightSpinBox");
        upRightSpinBox->setSingleStep(0);
        upRightSpinBox->setValue(4);

        gridLayout_6->addWidget(upRightSpinBox, 4, 6, 1, 1);

        label_22 = new QLabel(tab_2);
        label_22->setObjectName("label_22");
        label_22->setMinimumSize(QSize(10, 10));
        label_22->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_22, 3, 1, 1, 1);

        BYspinBox = new QSpinBox(tab_2);
        BYspinBox->setObjectName("BYspinBox");
        sizePolicy.setHeightForWidth(BYspinBox->sizePolicy().hasHeightForWidth());
        BYspinBox->setSizePolicy(sizePolicy);
        BYspinBox->setMinimum(0);
        BYspinBox->setMaximum(400000);

        gridLayout_6->addWidget(BYspinBox, 0, 6, 1, 1);

        orientationButton = new QPushButton(tab_2);
        orientationButton->setObjectName("orientationButton");
        orientationButton->setEnabled(true);
        orientationButton->setFlat(false);

        gridLayout_6->addWidget(orientationButton, 6, 2, 1, 1);

        BXspinBox = new QSpinBox(tab_2);
        BXspinBox->setObjectName("BXspinBox");
        sizePolicy.setHeightForWidth(BXspinBox->sizePolicy().hasHeightForWidth());
        BXspinBox->setSizePolicy(sizePolicy);
        BXspinBox->setMinimum(0);
        BXspinBox->setMaximum(400000);

        gridLayout_6->addWidget(BXspinBox, 0, 2, 1, 1);

        label_21 = new QLabel(tab_2);
        label_21->setObjectName("label_21");

        gridLayout_6->addWidget(label_21, 3, 0, 1, 1);

        numXspinBox = new QSpinBox(tab_2);
        numXspinBox->setObjectName("numXspinBox");
        numXspinBox->setMaximum(100);
        numXspinBox->setValue(15);

        gridLayout_6->addWidget(numXspinBox, 2, 2, 1, 1);

        label_14 = new QLabel(tab_2);
        label_14->setObjectName("label_14");
        label_14->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_14, 1, 5, 1, 1);

        downRightSpinBox = new QSpinBox(tab_2);
        downRightSpinBox->setObjectName("downRightSpinBox");
        downRightSpinBox->setValue(4);

        gridLayout_6->addWidget(downRightSpinBox, 5, 6, 1, 1);

        label_13 = new QLabel(tab_2);
        label_13->setObjectName("label_13");

        gridLayout_6->addWidget(label_13, 5, 0, 1, 1);

        label_5 = new QLabel(tab_2);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(10, 10));
        label_5->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_5, 0, 1, 1, 1);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName("label_6");

        gridLayout_6->addWidget(label_6, 4, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setMinimumSize(QSize(650, 200));
        groupBox_5->setMaximumSize(QSize(700, 16777215));
        gridLayoutWidget = new QWidget(groupBox_5);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 20, 551, 201));
        gridLayout_9 = new QGridLayout(gridLayoutWidget);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalSpacer_3 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_3);

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

        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_2);


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
        continueFromButton->setCheckable(true);

        verticalLayout_2->addWidget(continueFromButton);


        gridLayout_9->addLayout(verticalLayout_2, 0, 2, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        columnSpinBox = new QSpinBox(gridLayoutWidget);
        columnSpinBox->setObjectName("columnSpinBox");
        columnSpinBox->setMinimum(1);
        columnSpinBox->setMaximum(3);

        verticalLayout_4->addWidget(columnSpinBox);

        rowSpinBox = new QSpinBox(gridLayoutWidget);
        rowSpinBox->setObjectName("rowSpinBox");
        rowSpinBox->setMinimum(1);
        rowSpinBox->setMaximum(30);

        verticalLayout_4->addWidget(rowSpinBox);

        elemSpinBox = new QSpinBox(gridLayoutWidget);
        elemSpinBox->setObjectName("elemSpinBox");
        elemSpinBox->setMinimum(1);
        elemSpinBox->setMaximum(16);

        verticalLayout_4->addWidget(elemSpinBox);


        gridLayout_9->addLayout(verticalLayout_4, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox_5);


        gridLayout_6->addLayout(verticalLayout, 11, 0, 1, 7);

        upLeftSpinBox = new QSpinBox(tab_2);
        upLeftSpinBox->setObjectName("upLeftSpinBox");
        upLeftSpinBox->setValue(4);

        gridLayout_6->addWidget(upLeftSpinBox, 4, 2, 1, 1);

        stepYspinBox = new QDoubleSpinBox(tab_2);
        stepYspinBox->setObjectName("stepYspinBox");
        stepYspinBox->setDecimals(3);
        stepYspinBox->setValue(2.805000000000000);

        gridLayout_6->addWidget(stepYspinBox, 1, 6, 1, 1);

        label_10 = new QLabel(tab_2);
        label_10->setObjectName("label_10");

        gridLayout_6->addWidget(label_10, 1, 0, 1, 1);

        measureBButton = new QPushButton(tab_2);
        measureBButton->setObjectName("measureBButton");

        gridLayout_6->addWidget(measureBButton, 0, 0, 1, 1);

        label_23 = new QLabel(tab_2);
        label_23->setObjectName("label_23");
        label_23->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_23, 3, 5, 1, 1);

        downLeftSpinBox = new QSpinBox(tab_2);
        downLeftSpinBox->setObjectName("downLeftSpinBox");
        downLeftSpinBox->setValue(4);

        gridLayout_6->addWidget(downLeftSpinBox, 5, 2, 1, 1);

        progressBar = new QProgressBar(tab_2);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(200, 30));
        progressBar->setValue(24);

        gridLayout_6->addWidget(progressBar, 7, 0, 1, 1);

        label_27 = new QLabel(tab_2);
        label_27->setObjectName("label_27");

        gridLayout_6->addWidget(label_27, 5, 1, 1, 1);

        pauseButton = new QPushButton(tab_2);
        pauseButton->setObjectName("pauseButton");
        pauseButton->setEnabled(true);
        pauseButton->setCheckable(true);
        pauseButton->setFlat(false);

        gridLayout_6->addWidget(pauseButton, 7, 6, 1, 1);

        label_28 = new QLabel(tab_2);
        label_28->setObjectName("label_28");

        gridLayout_6->addWidget(label_28, 5, 5, 1, 1);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(10, 10));
        label_8->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_8, 1, 1, 1, 1);

        scanPushButton = new QPushButton(tab_2);
        scanPushButton->setObjectName("scanPushButton");
        scanPushButton->setCheckable(true);

        gridLayout_6->addWidget(scanPushButton, 7, 2, 1, 1);

        label_4 = new QLabel(tab_2);
        label_4->setObjectName("label_4");

        gridLayout_6->addWidget(label_4, 4, 0, 1, 1);

        stepColSpinBox = new QDoubleSpinBox(tab_2);
        stepColSpinBox->setObjectName("stepColSpinBox");
        stepColSpinBox->setValue(26.059999999999999);

        gridLayout_6->addWidget(stepColSpinBox, 3, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 41, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_6->addItem(verticalSpacer, 9, 0, 1, 1);

        checkBox = new QCheckBox(tab_2);
        checkBox->setObjectName("checkBox");
        checkBox->setLayoutDirection(Qt::RightToLeft);

        gridLayout_6->addWidget(checkBox, 6, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        BXspinBox->raise();
        label_10->raise();
        pauseButton->raise();
        stepYspinBox->raise();
        numXspinBox->raise();
        label_9->raise();
        stepColSpinBox->raise();
        label_5->raise();
        BYspinBox->raise();
        numYspinBox->raise();
        label_11->raise();
        label_21->raise();
        label_22->raise();
        stepRowSpinBox->raise();
        stepXspinBox->raise();
        label_8->raise();
        label_23->raise();
        label_15->raise();
        label_14->raise();
        label_12->raise();
        orientationButton->raise();
        scanPushButton->raise();
        measureBButton->raise();
        progressBar->raise();
        upLeftSpinBox->raise();
        label_4->raise();
        upRightSpinBox->raise();
        label_6->raise();
        label_7->raise();
        downLeftSpinBox->raise();
        downRightSpinBox->raise();
        label_13->raise();
        label_27->raise();
        label_28->raise();
        checkBox->raise();

        formLayout->setWidget(1, QFormLayout::FieldRole, tabWidget);


        gridLayout_5->addLayout(formLayout, 0, 0, 6, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 22));
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
        label_26->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\320\275\320\260\321\200", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Keithley", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "\320\224\320\270\320\276\320\264", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202\321\213", nullptr));
        portComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\320\275\320\260\321\200", nullptr));
        keithlyPortComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Keithley", nullptr));
        lightPortComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\224\320\270\320\276\320\264", nullptr));
        autoPortButton->setText(QCoreApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276", nullptr));
        openPortPushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        addressHeaderLabel->setText(QCoreApplication::translate("MainWindow", "\320\220\320\264\321\200\320\265\321\201 \321\204\320\260\320\271\320\273\320\260: ", nullptr));
        addressLabel->setText(QCoreApplication::translate("MainWindow", "\320\241:\\temp\\1.csv", nullptr));
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
        label_12->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\210\320\260\320\263\320\276\320\262", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        orientationButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\200\320\270\320\265\320\275\321\202\320\260\321\206\320\270\321\217", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263 \320\274\321\203\320\273\321\214\321\202\320\270\320\277\320\273\320\270\320\272\320\260\321\206\320\270\320\270", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\236\321\201\321\202\321\203\320\277 \321\201\320\275\320\270\320\267\321\203", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\205\320\276\320\264 \320\275\320\260 \320\275\321\203\320\266\320\275\321\213\320\271 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\273\320\261\320\265\321\206", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\320\240\321\217\320\264", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        goToButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270", nullptr));
        measurePushButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", nullptr));
        saveMeasureButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", nullptr));
        continueFromButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\321\214 \320\276\320\261\321\205\320\276\320\264 \321\201 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\260", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263", nullptr));
        measureBButton->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213  \321\202.\320\222", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\203\320\267\320\260", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        scanPushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\201\321\202\321\203\320\277 \321\201\320\262\320\265\321\200\321\205\321\203", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\205\320\276\320\264 \320\277\320\276 3 \321\201\321\202\320\276\320\273\320\261\321\206\320\260\320\274", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
