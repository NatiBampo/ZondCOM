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
    QTableView *tableView;
    QLabel *label_16;
    QFormLayout *formLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QPushButton *backwardPushButton;
    QPushButton *rightPushButton;
    QPushButton *leftPushButton;
    QPushButton *forwardPushButton;
    QLabel *label_20;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_8;
    QSpinBox *DC1VSpinBox;
    QSpinBox *DC10spinBox;
    QSpinBox *zeroSpinBox;
    QSpinBox *FCSpinBox;
    QLabel *label_37;
    QLabel *label_31;
    QSpinBox *lightSpinBox;
    QDoubleSpinBox *voltageSpinBox;
    QLabel *label_32;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_33;
    QLabel *label_38;
    QSpinBox *planarSpinBox;
    QListWidget *logsListWidget;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QPushButton *lightPushButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *coordsPushButton;
    QLineEdit *yLineEdit;
    QLineEdit *xLineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *statePushButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *tableDownPushButton;
    QPushButton *tableUpPushButton;
    QGroupBox *groupBox_5;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QSpinBox *columnSpinBox;
    QSpinBox *rowSpinBox;
    QSpinBox *elemSpinBox;
    QLabel *label_36;
    QPushButton *goToButton;
    QPushButton *saveMeasureButton;
    QPushButton *continueFromButton;
    QPushButton *measure2pushButton;
    QWidget *tab_2;
    QGridLayout *gridLayout_6;
    QLabel *label_10;
    QLabel *label_21;
    QDoubleSpinBox *stepRowSpinBox;
    QLabel *label_15;
    QLabel *label_27;
    QLabel *label_23;
    QDoubleSpinBox *stepXspinBox;
    QLabel *label_9;
    QSpinBox *downLeftSpinBox;
    QSpinBox *numYspinBox;
    QSpinBox *upRightSpinBox;
    QDoubleSpinBox *stepColSpinBox;
    QLabel *label_22;
    QLabel *label_11;
    QDoubleSpinBox *stepYspinBox;
    QLabel *label_14;
    QPushButton *pauseButton;
    QLabel *label_12;
    QSpinBox *BXspinBox;
    QLabel *label_6;
    QLabel *label_5;
    QSpinBox *BYspinBox;
    QLabel *label_13;
    QProgressBar *progressBar;
    QPushButton *orientationButton;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_8;
    QCheckBox *checkBox;
    QLabel *label_7;
    QSpinBox *numXspinBox;
    QSpinBox *downRightSpinBox;
    QLabel *label_4;
    QPushButton *scanPushButton;
    QSpinBox *upLeftSpinBox;
    QLabel *label_28;
    QPushButton *chartsButton;
    QLabel *label_29;
    QSpinBox *AXspinBox;
    QSpinBox *AYspinBox;
    QLabel *label_30;
    QLabel *label_39;
    QLabel *label_40;
    QPushButton *measureBButton;
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
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 871);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(4000, 2000));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_10->setSizeConstraint(QLayout::SetDefaultConstraint);
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setMinimumSize(QSize(400, 200));
        tableView->setBaseSize(QSize(400, 200));
        tableView->setDragDropOverwriteMode(false);
        tableView->horizontalHeader()->setCascadingSectionResizes(true);
        tableView->horizontalHeader()->setMinimumSectionSize(33);
        tableView->horizontalHeader()->setDefaultSectionSize(60);
        tableView->verticalHeader()->setMinimumSectionSize(24);
        tableView->verticalHeader()->setDefaultSectionSize(27);

        gridLayout_10->addWidget(tableView, 2, 0, 1, 1);

        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");

        gridLayout_10->addWidget(label_16, 1, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_10, 0, 2, 6, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setSizeConstraint(QLayout::SetMaximumSize);
        formLayout->setVerticalSpacing(6);
        formLayout->setContentsMargins(0, 0, 0, -1);
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

        label_20 = new QLabel(tab);
        label_20->setObjectName("label_20");

        gridLayout_3->addWidget(label_20, 8, 0, 1, 1);

        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName("groupBox_6");
        gridLayout_8 = new QGridLayout(groupBox_6);
        gridLayout_8->setObjectName("gridLayout_8");
        DC1VSpinBox = new QSpinBox(groupBox_6);
        DC1VSpinBox->setObjectName("DC1VSpinBox");
        DC1VSpinBox->setMaximum(5000);
        DC1VSpinBox->setSingleStep(100);
        DC1VSpinBox->setValue(600);

        gridLayout_8->addWidget(DC1VSpinBox, 3, 1, 1, 1);

        DC10spinBox = new QSpinBox(groupBox_6);
        DC10spinBox->setObjectName("DC10spinBox");
        DC10spinBox->setMaximum(5000);
        DC10spinBox->setSingleStep(100);
        DC10spinBox->setValue(800);

        gridLayout_8->addWidget(DC10spinBox, 2, 1, 1, 1);

        zeroSpinBox = new QSpinBox(groupBox_6);
        zeroSpinBox->setObjectName("zeroSpinBox");
        zeroSpinBox->setMaximum(5000);
        zeroSpinBox->setSingleStep(100);
        zeroSpinBox->setValue(400);

        gridLayout_8->addWidget(zeroSpinBox, 0, 1, 1, 1);

        FCSpinBox = new QSpinBox(groupBox_6);
        FCSpinBox->setObjectName("FCSpinBox");
        FCSpinBox->setMaximum(5000);
        FCSpinBox->setSingleStep(100);
        FCSpinBox->setValue(300);

        gridLayout_8->addWidget(FCSpinBox, 1, 1, 1, 1);

        label_37 = new QLabel(groupBox_6);
        label_37->setObjectName("label_37");

        gridLayout_8->addWidget(label_37, 6, 0, 1, 1);

        label_31 = new QLabel(groupBox_6);
        label_31->setObjectName("label_31");

        gridLayout_8->addWidget(label_31, 0, 0, 1, 1);

        lightSpinBox = new QSpinBox(groupBox_6);
        lightSpinBox->setObjectName("lightSpinBox");
        lightSpinBox->setMaximum(5000);
        lightSpinBox->setSingleStep(100);
        lightSpinBox->setValue(400);

        gridLayout_8->addWidget(lightSpinBox, 4, 1, 1, 1);

        voltageSpinBox = new QDoubleSpinBox(groupBox_6);
        voltageSpinBox->setObjectName("voltageSpinBox");
        voltageSpinBox->setMaximum(3.000000000000000);
        voltageSpinBox->setSingleStep(0.050000000000000);
        voltageSpinBox->setValue(0.600000000000000);

        gridLayout_8->addWidget(voltageSpinBox, 6, 1, 1, 1);

        label_32 = new QLabel(groupBox_6);
        label_32->setObjectName("label_32");

        gridLayout_8->addWidget(label_32, 1, 0, 1, 1);

        label_34 = new QLabel(groupBox_6);
        label_34->setObjectName("label_34");

        gridLayout_8->addWidget(label_34, 3, 0, 1, 1);

        label_35 = new QLabel(groupBox_6);
        label_35->setObjectName("label_35");

        gridLayout_8->addWidget(label_35, 4, 0, 1, 1);

        label_33 = new QLabel(groupBox_6);
        label_33->setObjectName("label_33");

        gridLayout_8->addWidget(label_33, 2, 0, 1, 1);

        label_38 = new QLabel(groupBox_6);
        label_38->setObjectName("label_38");

        gridLayout_8->addWidget(label_38, 5, 0, 1, 1);

        planarSpinBox = new QSpinBox(groupBox_6);
        planarSpinBox->setObjectName("planarSpinBox");
        planarSpinBox->setMaximum(5000);
        planarSpinBox->setSingleStep(100);
        planarSpinBox->setValue(1000);

        gridLayout_8->addWidget(planarSpinBox, 5, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_6, 7, 0, 1, 1);

        logsListWidget = new QListWidget(tab);
        logsListWidget->setObjectName("logsListWidget");

        gridLayout_3->addWidget(logsListWidget, 9, 0, 1, 2);

        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setObjectName("gridLayout_7");
        lightPushButton = new QPushButton(groupBox_4);
        lightPushButton->setObjectName("lightPushButton");

        gridLayout_7->addWidget(lightPushButton, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_4, 3, 1, 1, 1);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        coordsPushButton = new QPushButton(groupBox);
        coordsPushButton->setObjectName("coordsPushButton");

        gridLayout->addWidget(coordsPushButton, 2, 0, 1, 2);

        yLineEdit = new QLineEdit(groupBox);
        yLineEdit->setObjectName("yLineEdit");

        gridLayout->addWidget(yLineEdit, 1, 1, 1, 1);

        xLineEdit = new QLineEdit(groupBox);
        xLineEdit->setObjectName("xLineEdit");

        gridLayout->addWidget(xLineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        statePushButton = new QPushButton(groupBox);
        statePushButton->setObjectName("statePushButton");

        gridLayout->addWidget(statePushButton, 3, 0, 1, 2);


        gridLayout_3->addWidget(groupBox, 6, 1, 1, 1);

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

        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setMinimumSize(QSize(650, 200));
        groupBox_5->setMaximumSize(QSize(700, 16777215));
        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(0, 20, 71, 60));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy1);
        label_17->setMinimumSize(QSize(40, 60));
        label_17->setLayoutDirection(Qt::LeftToRight);
        label_17->setMargin(6);
        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(0, 70, 81, 41));
        sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy1);
        label_18->setMinimumSize(QSize(40, 0));
        label_18->setLayoutDirection(Qt::LeftToRight);
        label_18->setMargin(6);
        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(230, -150, 177, 156));
        sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy1);
        label_19->setMinimumSize(QSize(40, 0));
        label_19->setLayoutDirection(Qt::LeftToRight);
        label_19->setMargin(6);
        columnSpinBox = new QSpinBox(groupBox_5);
        columnSpinBox->setObjectName("columnSpinBox");
        columnSpinBox->setGeometry(QRect(70, 40, 71, 20));
        columnSpinBox->setMinimumSize(QSize(20, 20));
        columnSpinBox->setMinimum(1);
        columnSpinBox->setMaximum(3);
        rowSpinBox = new QSpinBox(groupBox_5);
        rowSpinBox->setObjectName("rowSpinBox");
        rowSpinBox->setGeometry(QRect(70, 80, 71, 22));
        sizePolicy1.setHeightForWidth(rowSpinBox->sizePolicy().hasHeightForWidth());
        rowSpinBox->setSizePolicy(sizePolicy1);
        rowSpinBox->setMinimumSize(QSize(20, 20));
        rowSpinBox->setMinimum(1);
        rowSpinBox->setMaximum(30);
        elemSpinBox = new QSpinBox(groupBox_5);
        elemSpinBox->setObjectName("elemSpinBox");
        elemSpinBox->setGeometry(QRect(70, 120, 71, 22));
        elemSpinBox->setMinimumSize(QSize(20, 20));
        elemSpinBox->setMinimum(1);
        elemSpinBox->setMaximum(16);
        label_36 = new QLabel(groupBox_5);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(10, 120, 49, 16));
        goToButton = new QPushButton(groupBox_5);
        goToButton->setObjectName("goToButton");
        goToButton->setGeometry(QRect(160, 40, 141, 24));
        saveMeasureButton = new QPushButton(groupBox_5);
        saveMeasureButton->setObjectName("saveMeasureButton");
        saveMeasureButton->setGeometry(QRect(160, 80, 141, 24));
        continueFromButton = new QPushButton(groupBox_5);
        continueFromButton->setObjectName("continueFromButton");
        continueFromButton->setGeometry(QRect(20, 160, 291, 24));
        continueFromButton->setCheckable(true);
        measure2pushButton = new QPushButton(groupBox_5);
        measure2pushButton->setObjectName("measure2pushButton");
        measure2pushButton->setGeometry(QRect(160, 120, 141, 24));

        gridLayout_3->addWidget(groupBox_5, 7, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout_6 = new QGridLayout(tab_2);
        gridLayout_6->setObjectName("gridLayout_6");
        label_10 = new QLabel(tab_2);
        label_10->setObjectName("label_10");

        gridLayout_6->addWidget(label_10, 2, 0, 1, 1);

        label_21 = new QLabel(tab_2);
        label_21->setObjectName("label_21");

        gridLayout_6->addWidget(label_21, 4, 0, 1, 1);

        stepRowSpinBox = new QDoubleSpinBox(tab_2);
        stepRowSpinBox->setObjectName("stepRowSpinBox");
        stepRowSpinBox->setValue(0.000000000000000);

        gridLayout_6->addWidget(stepRowSpinBox, 4, 7, 1, 1);

        label_15 = new QLabel(tab_2);
        label_15->setObjectName("label_15");
        label_15->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_15, 3, 6, 1, 1);

        label_27 = new QLabel(tab_2);
        label_27->setObjectName("label_27");

        gridLayout_6->addWidget(label_27, 6, 2, 1, 1);

        label_23 = new QLabel(tab_2);
        label_23->setObjectName("label_23");
        label_23->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_23, 4, 6, 1, 1);

        stepXspinBox = new QDoubleSpinBox(tab_2);
        stepXspinBox->setObjectName("stepXspinBox");
        stepXspinBox->setDecimals(3);
        stepXspinBox->setValue(1.550000000000000);

        gridLayout_6->addWidget(stepXspinBox, 2, 3, 1, 1);

        label_9 = new QLabel(tab_2);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(10, 10));
        label_9->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_9, 3, 2, 1, 1);

        downLeftSpinBox = new QSpinBox(tab_2);
        downLeftSpinBox->setObjectName("downLeftSpinBox");
        downLeftSpinBox->setValue(4);

        gridLayout_6->addWidget(downLeftSpinBox, 6, 3, 1, 1);

        numYspinBox = new QSpinBox(tab_2);
        numYspinBox->setObjectName("numYspinBox");
        numYspinBox->setMaximum(100);
        numYspinBox->setValue(30);

        gridLayout_6->addWidget(numYspinBox, 3, 7, 1, 1);

        upRightSpinBox = new QSpinBox(tab_2);
        upRightSpinBox->setObjectName("upRightSpinBox");
        upRightSpinBox->setSingleStep(0);
        upRightSpinBox->setValue(4);

        gridLayout_6->addWidget(upRightSpinBox, 5, 7, 1, 1);

        stepColSpinBox = new QDoubleSpinBox(tab_2);
        stepColSpinBox->setObjectName("stepColSpinBox");
        stepColSpinBox->setValue(26.059999999999999);

        gridLayout_6->addWidget(stepColSpinBox, 4, 3, 1, 1);

        label_22 = new QLabel(tab_2);
        label_22->setObjectName("label_22");
        label_22->setMinimumSize(QSize(10, 10));
        label_22->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_22, 4, 2, 1, 1);

        label_11 = new QLabel(tab_2);
        label_11->setObjectName("label_11");

        gridLayout_6->addWidget(label_11, 3, 0, 1, 1);

        stepYspinBox = new QDoubleSpinBox(tab_2);
        stepYspinBox->setObjectName("stepYspinBox");
        stepYspinBox->setDecimals(3);
        stepYspinBox->setValue(2.805000000000000);

        gridLayout_6->addWidget(stepYspinBox, 2, 7, 1, 1);

        label_14 = new QLabel(tab_2);
        label_14->setObjectName("label_14");
        label_14->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_14, 2, 6, 1, 1);

        pauseButton = new QPushButton(tab_2);
        pauseButton->setObjectName("pauseButton");
        pauseButton->setEnabled(true);
        pauseButton->setCheckable(true);
        pauseButton->setFlat(false);

        gridLayout_6->addWidget(pauseButton, 8, 7, 1, 1);

        label_12 = new QLabel(tab_2);
        label_12->setObjectName("label_12");
        label_12->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_12, 1, 6, 1, 1);

        BXspinBox = new QSpinBox(tab_2);
        BXspinBox->setObjectName("BXspinBox");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(BXspinBox->sizePolicy().hasHeightForWidth());
        BXspinBox->setSizePolicy(sizePolicy2);
        BXspinBox->setMinimum(0);
        BXspinBox->setMaximum(500000);

        gridLayout_6->addWidget(BXspinBox, 1, 3, 1, 1);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName("label_6");

        gridLayout_6->addWidget(label_6, 5, 2, 1, 1);

        label_5 = new QLabel(tab_2);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(10, 10));
        label_5->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_5, 1, 2, 1, 1);

        BYspinBox = new QSpinBox(tab_2);
        BYspinBox->setObjectName("BYspinBox");
        sizePolicy2.setHeightForWidth(BYspinBox->sizePolicy().hasHeightForWidth());
        BYspinBox->setSizePolicy(sizePolicy2);
        BYspinBox->setMinimum(0);
        BYspinBox->setMaximum(500000);

        gridLayout_6->addWidget(BYspinBox, 1, 7, 1, 1);

        label_13 = new QLabel(tab_2);
        label_13->setObjectName("label_13");

        gridLayout_6->addWidget(label_13, 6, 0, 1, 1);

        progressBar = new QProgressBar(tab_2);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(200, 30));
        progressBar->setValue(24);

        gridLayout_6->addWidget(progressBar, 8, 0, 1, 2);

        orientationButton = new QPushButton(tab_2);
        orientationButton->setObjectName("orientationButton");
        orientationButton->setEnabled(true);
        orientationButton->setFlat(false);

        gridLayout_6->addWidget(orientationButton, 7, 3, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 400, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);


        gridLayout_6->addLayout(verticalLayout, 12, 0, 1, 8);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(10, 10));
        label_8->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_8, 2, 2, 1, 1);

        checkBox = new QCheckBox(tab_2);
        checkBox->setObjectName("checkBox");
        checkBox->setLayoutDirection(Qt::LeftToRight);

        gridLayout_6->addWidget(checkBox, 7, 0, 1, 2);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName("label_7");

        gridLayout_6->addWidget(label_7, 5, 6, 1, 1);

        numXspinBox = new QSpinBox(tab_2);
        numXspinBox->setObjectName("numXspinBox");
        numXspinBox->setMaximum(100);
        numXspinBox->setValue(15);

        gridLayout_6->addWidget(numXspinBox, 3, 3, 1, 1);

        downRightSpinBox = new QSpinBox(tab_2);
        downRightSpinBox->setObjectName("downRightSpinBox");
        downRightSpinBox->setValue(4);

        gridLayout_6->addWidget(downRightSpinBox, 6, 7, 1, 1);

        label_4 = new QLabel(tab_2);
        label_4->setObjectName("label_4");

        gridLayout_6->addWidget(label_4, 5, 0, 1, 1);

        scanPushButton = new QPushButton(tab_2);
        scanPushButton->setObjectName("scanPushButton");
        scanPushButton->setCheckable(true);

        gridLayout_6->addWidget(scanPushButton, 8, 3, 1, 1);

        upLeftSpinBox = new QSpinBox(tab_2);
        upLeftSpinBox->setObjectName("upLeftSpinBox");
        upLeftSpinBox->setValue(4);

        gridLayout_6->addWidget(upLeftSpinBox, 5, 3, 1, 1);

        label_28 = new QLabel(tab_2);
        label_28->setObjectName("label_28");

        gridLayout_6->addWidget(label_28, 6, 6, 1, 1);

        chartsButton = new QPushButton(tab_2);
        chartsButton->setObjectName("chartsButton");

        gridLayout_6->addWidget(chartsButton, 10, 3, 1, 1);

        label_29 = new QLabel(tab_2);
        label_29->setObjectName("label_29");
        sizePolicy1.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy1);

        gridLayout_6->addWidget(label_29, 0, 0, 1, 1);

        AXspinBox = new QSpinBox(tab_2);
        AXspinBox->setObjectName("AXspinBox");
        AXspinBox->setMaximum(500000);

        gridLayout_6->addWidget(AXspinBox, 0, 3, 1, 1);

        AYspinBox = new QSpinBox(tab_2);
        AYspinBox->setObjectName("AYspinBox");
        AYspinBox->setMaximum(500000);

        gridLayout_6->addWidget(AYspinBox, 0, 7, 1, 1);

        label_30 = new QLabel(tab_2);
        label_30->setObjectName("label_30");

        gridLayout_6->addWidget(label_30, 0, 2, 1, 1);

        label_39 = new QLabel(tab_2);
        label_39->setObjectName("label_39");

        gridLayout_6->addWidget(label_39, 0, 6, 1, 1);

        label_40 = new QLabel(tab_2);
        label_40->setObjectName("label_40");

        gridLayout_6->addWidget(label_40, 1, 0, 1, 1);

        measureBButton = new QPushButton(tab_2);
        measureBButton->setObjectName("measureBButton");

        gridLayout_6->addWidget(measureBButton, 7, 7, 1, 1);

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
        chartsButton->raise();
        label_29->raise();
        AXspinBox->raise();
        AYspinBox->raise();
        label_30->raise();
        label_39->raise();
        label_40->raise();
        measureBButton->raise();

        formLayout->setWidget(1, QFormLayout::FieldRole, tabWidget);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
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
        sizePolicy2.setHeightForWidth(portComboBox->sizePolicy().hasHeightForWidth());
        portComboBox->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(portComboBox);

        keithlyPortComboBox = new QComboBox(centralwidget);
        keithlyPortComboBox->setObjectName("keithlyPortComboBox");
        sizePolicy2.setHeightForWidth(keithlyPortComboBox->sizePolicy().hasHeightForWidth());
        keithlyPortComboBox->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(keithlyPortComboBox);

        lightPortComboBox = new QComboBox(centralwidget);
        lightPortComboBox->setObjectName("lightPortComboBox");
        sizePolicy2.setHeightForWidth(lightPortComboBox->sizePolicy().hasHeightForWidth());
        lightPortComboBox->setSizePolicy(sizePolicy2);

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

        tabWidget->setCurrentIndex(0);
        orientationButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\321\202\320\276\320\273\320\276\320\274", nullptr));
        backwardPushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        rightPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\277\321\200\320\260\320\262\320\276", nullptr));
        leftPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\273\320\265\320\262\320\276", nullptr));
        forwardPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\277\320\265\321\200\320\265\320\264", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "\320\226\321\203\321\200\320\275\320\260\320\273", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\265\321\200\320\266\320\272\320\270 \320\270 \320\275\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\320\265", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "Forward Voltage", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "zero", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "FC", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "DC1V", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "Light", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "DC10mV", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "Planar", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\236\321\201\320\262\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
        lightPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", nullptr));
        coordsPushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        statePushButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\273", nullptr));
        tableDownPushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        tableUpPushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\275\321\217\321\202\321\214", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\205\320\276\320\264 \320\275\320\260 \320\275\321\203\320\266\320\275\321\213\320\271 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\273\320\261\320\265\321\206", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\320\240\321\217\320\264", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        goToButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270", nullptr));
        saveMeasureButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", nullptr));
        continueFromButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\321\214 \320\276\320\261\321\205\320\276\320\264 \321\201 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\260", nullptr));
        measure2pushButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\320\240\321\203\321\207\320\275\320\276\320\271", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263 \320\274\321\203\320\273\321\214\321\202\320\270\320\277\320\273\320\270\320\272\320\260\321\206\320\270\320\270", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "L:", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\210\320\260\320\263\320\276\320\262", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\203\320\267\320\260", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "L:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\201\321\202\321\203\320\277 \321\201\320\275\320\270\320\267\321\203", nullptr));
        orientationButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\200\320\270\320\265\320\275\321\202\320\260\321\206\320\270\321\217", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\205\320\276\320\264 \320\277\320\276 \320\262\321\201\320\265\320\274 \321\201\321\202\320\276\320\273\320\261\321\206\320\260\320\274 ", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "R:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\201\321\202\321\203\320\277 \321\201\320\262\320\265\321\200\321\205\321\203", nullptr));
        scanPushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "R:", nullptr));
        chartsButton->setText(QCoreApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \321\202.\320\220", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \321\202.\320\222", nullptr));
        measureBButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\320\275\320\260\321\200", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Keithley", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "\320\224\320\270\320\276\320\264", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202\321\213", nullptr));
        portComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\235\320\265 \320\262\321\213\320\261\321\200\320\260\320\275", nullptr));
        keithlyPortComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\235\320\265 \320\262\321\213\320\261\321\200\320\260\320\275", nullptr));
        lightPortComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\235\320\265 \320\262\321\213\320\261\321\200\320\260\320\275", nullptr));
        autoPortButton->setText(QCoreApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276", nullptr));
        openPortPushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        addressHeaderLabel->setText(QCoreApplication::translate("MainWindow", "\320\220\320\264\321\200\320\265\321\201 \321\204\320\260\320\271\320\273\320\260: ", nullptr));
        addressLabel->setText(QCoreApplication::translate("MainWindow", "\320\241:\\temp\\1.csv", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
