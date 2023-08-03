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
    QLabel *label_20;
    QListWidget *logsListWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
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
    QPushButton *FCMeasureButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *yLineEdit;
    QLineEdit *xLineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *statePushButton;
    QPushButton *coordsPushButton;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_8;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_37;
    QLabel *label_34;
    QLabel *label_38;
    QSpinBox *voltageSpinBox;
    QSpinBox *FCSpinBox;
    QSpinBox *DC10spinBox;
    QSpinBox *DC1VSpinBox;
    QLabel *label_35;
    QLabel *label_31;
    QLabel *label_33;
    QSpinBox *planarSpinBox;
    QLabel *label_32;
    QSpinBox *lightSpinBox;
    QSpinBox *zeroSpinBox;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QPushButton *rightPushButton;
    QPushButton *forwardPushButton;
    QPushButton *tableUpPushButton;
    QPushButton *lightPushButton;
    QPushButton *tableDownPushButton;
    QPushButton *leftPushButton;
    QPushButton *backwardPushButton;
    QSpinBox *stepSpinBox;
    QCheckBox *hotKeysCheckBox;
    QCheckBox *checkBox;
    QWidget *tab_2;
    QGridLayout *gridLayout_6;
    QDoubleSpinBox *stepXspinBox;
    QLabel *label_41;
    QDoubleSpinBox *stepColSpinBox;
    QSpinBox *centerUpOffSpinBox;
    QLabel *label_13;
    QPushButton *orientationButton;
    QSpinBox *BXspinBox;
    QSpinBox *downCenterOffspinBox;
    QLabel *label_8;
    QDoubleSpinBox *stepRowSpinBox;
    QLabel *label_4;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *scanPushButton;
    QLabel *label_11;
    QLabel *label_6;
    QSpinBox *numYspinBox;
    QProgressBar *progressBar;
    QLabel *label_21;
    QLabel *label_39;
    QLabel *label_10;
    QSpinBox *AYspinBox;
    QLabel *label_7;
    QLabel *label_23;
    QPushButton *pauseButton;
    QPushButton *measureBButton;
    QSpinBox *BYspinBox;
    QLabel *label_28;
    QLabel *label_15;
    QDoubleSpinBox *stepYspinBox;
    QLabel *label_29;
    QLabel *label_22;
    QSpinBox *upRightSpinBox;
    QLabel *label_14;
    QSpinBox *numXspinBox;
    QLabel *label_12;
    QSpinBox *AXspinBox;
    QSpinBox *downRightSpinBox;
    QLabel *label_30;
    QLabel *label_42;
    QSpacerItem *verticalSpacer_3;
    QSpinBox *downLeftSpinBox;
    QLabel *label_5;
    QSpinBox *upLeftSpinBox;
    QLabel *label_27;
    QLabel *label_9;
    QPushButton *chartsButton;
    QSpacerItem *verticalSpacer_4;
    QCheckBox *leftCheckBox;
    QCheckBox *centerCheckBox;
    QCheckBox *rightCheckBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 1024);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1280, 1024));
        MainWindow->setMaximumSize(QSize(4000, 2000));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_10->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");

        gridLayout_10->addWidget(label_16, 1, 0, 1, 1);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);
        tableView->setMinimumSize(QSize(400, 200));
        tableView->setBaseSize(QSize(400, 200));
        tableView->setDragDropOverwriteMode(false);
        tableView->horizontalHeader()->setCascadingSectionResizes(true);
        tableView->horizontalHeader()->setMinimumSectionSize(40);
        tableView->horizontalHeader()->setDefaultSectionSize(75);
        tableView->verticalHeader()->setVisible(true);
        tableView->verticalHeader()->setMinimumSectionSize(24);
        tableView->verticalHeader()->setDefaultSectionSize(27);

        gridLayout_10->addWidget(tableView, 2, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_10, 0, 2, 6, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setSizeConstraint(QLayout::SetMaximumSize);
        formLayout->setVerticalSpacing(6);
        formLayout->setContentsMargins(0, 0, 0, -1);
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
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
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

        label_20 = new QLabel(centralwidget);
        label_20->setObjectName("label_20");

        formLayout->setWidget(2, QFormLayout::FieldRole, label_20);

        logsListWidget = new QListWidget(centralwidget);
        logsListWidget->setObjectName("logsListWidget");
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(logsListWidget->sizePolicy().hasHeightForWidth());
        logsListWidget->setSizePolicy(sizePolicy3);

        formLayout->setWidget(3, QFormLayout::FieldRole, logsListWidget);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 450));
        tabWidget->setMaximumSize(QSize(600, 16777215));
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName("groupBox_5");
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        groupBox_5->setMinimumSize(QSize(280, 200));
        groupBox_5->setMaximumSize(QSize(700, 16777215));
        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(0, 20, 71, 60));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);
        label_17->setMinimumSize(QSize(40, 60));
        label_17->setLayoutDirection(Qt::LeftToRight);
        label_17->setMargin(6);
        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(0, 70, 81, 41));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        label_18->setMinimumSize(QSize(40, 0));
        label_18->setLayoutDirection(Qt::LeftToRight);
        label_18->setMargin(6);
        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(230, -150, 177, 156));
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);
        label_19->setMinimumSize(QSize(40, 0));
        label_19->setLayoutDirection(Qt::LeftToRight);
        label_19->setMargin(6);
        columnSpinBox = new QSpinBox(groupBox_5);
        columnSpinBox->setObjectName("columnSpinBox");
        columnSpinBox->setGeometry(QRect(70, 40, 51, 22));
        sizePolicy.setHeightForWidth(columnSpinBox->sizePolicy().hasHeightForWidth());
        columnSpinBox->setSizePolicy(sizePolicy);
        columnSpinBox->setMinimumSize(QSize(20, 20));
        columnSpinBox->setMinimum(1);
        columnSpinBox->setMaximum(3);
        rowSpinBox = new QSpinBox(groupBox_5);
        rowSpinBox->setObjectName("rowSpinBox");
        rowSpinBox->setGeometry(QRect(70, 80, 51, 22));
        sizePolicy.setHeightForWidth(rowSpinBox->sizePolicy().hasHeightForWidth());
        rowSpinBox->setSizePolicy(sizePolicy);
        rowSpinBox->setMinimumSize(QSize(20, 20));
        rowSpinBox->setMinimum(1);
        rowSpinBox->setMaximum(30);
        elemSpinBox = new QSpinBox(groupBox_5);
        elemSpinBox->setObjectName("elemSpinBox");
        elemSpinBox->setGeometry(QRect(70, 120, 51, 22));
        elemSpinBox->setMinimumSize(QSize(20, 20));
        elemSpinBox->setMinimum(1);
        elemSpinBox->setMaximum(16);
        label_36 = new QLabel(groupBox_5);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(10, 120, 49, 16));
        goToButton = new QPushButton(groupBox_5);
        goToButton->setObjectName("goToButton");
        goToButton->setEnabled(false);
        goToButton->setGeometry(QRect(130, 40, 141, 24));
        saveMeasureButton = new QPushButton(groupBox_5);
        saveMeasureButton->setObjectName("saveMeasureButton");
        saveMeasureButton->setGeometry(QRect(130, 80, 141, 24));
        continueFromButton = new QPushButton(groupBox_5);
        continueFromButton->setObjectName("continueFromButton");
        continueFromButton->setEnabled(false);
        continueFromButton->setGeometry(QRect(60, 200, 191, 24));
        continueFromButton->setCheckable(true);
        measure2pushButton = new QPushButton(groupBox_5);
        measure2pushButton->setObjectName("measure2pushButton");
        measure2pushButton->setEnabled(false);
        measure2pushButton->setGeometry(QRect(130, 120, 141, 24));
        FCMeasureButton = new QPushButton(groupBox_5);
        FCMeasureButton->setObjectName("FCMeasureButton");
        FCMeasureButton->setGeometry(QRect(130, 160, 141, 24));

        gridLayout_3->addWidget(groupBox_5, 6, 1, 1, 1);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(28);
        sizePolicy4.setVerticalStretch(150);
        sizePolicy4.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy4);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
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

        gridLayout->addWidget(statePushButton, 3, 1, 1, 1);

        coordsPushButton = new QPushButton(groupBox);
        coordsPushButton->setObjectName("coordsPushButton");

        gridLayout->addWidget(coordsPushButton, 2, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 5, 1, 1, 1);

        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName("groupBox_6");
        gridLayout_8 = new QGridLayout(groupBox_6);
        gridLayout_8->setObjectName("gridLayout_8");
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_8->addItem(verticalSpacer_2, 6, 0, 1, 1);

        label_37 = new QLabel(groupBox_6);
        label_37->setObjectName("label_37");

        gridLayout_8->addWidget(label_37, 7, 0, 1, 1);

        label_34 = new QLabel(groupBox_6);
        label_34->setObjectName("label_34");

        gridLayout_8->addWidget(label_34, 3, 0, 1, 1);

        label_38 = new QLabel(groupBox_6);
        label_38->setObjectName("label_38");

        gridLayout_8->addWidget(label_38, 5, 0, 1, 1);

        voltageSpinBox = new QSpinBox(groupBox_6);
        voltageSpinBox->setObjectName("voltageSpinBox");
        voltageSpinBox->setMaximum(1500);
        voltageSpinBox->setSingleStep(50);
        voltageSpinBox->setValue(600);

        gridLayout_8->addWidget(voltageSpinBox, 7, 1, 1, 1);

        FCSpinBox = new QSpinBox(groupBox_6);
        FCSpinBox->setObjectName("FCSpinBox");
        FCSpinBox->setMaximum(5000);
        FCSpinBox->setSingleStep(100);
        FCSpinBox->setValue(300);

        gridLayout_8->addWidget(FCSpinBox, 1, 1, 1, 1);

        DC10spinBox = new QSpinBox(groupBox_6);
        DC10spinBox->setObjectName("DC10spinBox");
        DC10spinBox->setMaximum(5000);
        DC10spinBox->setSingleStep(100);
        DC10spinBox->setValue(500);

        gridLayout_8->addWidget(DC10spinBox, 2, 1, 1, 1);

        DC1VSpinBox = new QSpinBox(groupBox_6);
        DC1VSpinBox->setObjectName("DC1VSpinBox");
        DC1VSpinBox->setMaximum(5000);
        DC1VSpinBox->setSingleStep(100);
        DC1VSpinBox->setValue(500);

        gridLayout_8->addWidget(DC1VSpinBox, 3, 1, 1, 1);

        label_35 = new QLabel(groupBox_6);
        label_35->setObjectName("label_35");

        gridLayout_8->addWidget(label_35, 4, 0, 1, 1);

        label_31 = new QLabel(groupBox_6);
        label_31->setObjectName("label_31");

        gridLayout_8->addWidget(label_31, 0, 0, 1, 1);

        label_33 = new QLabel(groupBox_6);
        label_33->setObjectName("label_33");

        gridLayout_8->addWidget(label_33, 2, 0, 1, 1);

        planarSpinBox = new QSpinBox(groupBox_6);
        planarSpinBox->setObjectName("planarSpinBox");
        planarSpinBox->setMaximum(5000);
        planarSpinBox->setSingleStep(100);
        planarSpinBox->setValue(400);

        gridLayout_8->addWidget(planarSpinBox, 5, 1, 1, 1);

        label_32 = new QLabel(groupBox_6);
        label_32->setObjectName("label_32");

        gridLayout_8->addWidget(label_32, 1, 0, 1, 1);

        lightSpinBox = new QSpinBox(groupBox_6);
        lightSpinBox->setObjectName("lightSpinBox");
        lightSpinBox->setMaximum(5000);
        lightSpinBox->setSingleStep(100);
        lightSpinBox->setValue(400);

        gridLayout_8->addWidget(lightSpinBox, 4, 1, 1, 1);

        zeroSpinBox = new QSpinBox(groupBox_6);
        zeroSpinBox->setObjectName("zeroSpinBox");
        zeroSpinBox->setMaximum(5000);
        zeroSpinBox->setSingleStep(100);
        zeroSpinBox->setValue(300);

        gridLayout_8->addWidget(zeroSpinBox, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_6, 6, 0, 1, 1);

        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName("groupBox_3");
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(250, 150));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName("gridLayout_4");
        rightPushButton = new QPushButton(groupBox_3);
        rightPushButton->setObjectName("rightPushButton");

        gridLayout_4->addWidget(rightPushButton, 3, 2, 1, 1);

        forwardPushButton = new QPushButton(groupBox_3);
        forwardPushButton->setObjectName("forwardPushButton");

        gridLayout_4->addWidget(forwardPushButton, 2, 1, 1, 1);

        tableUpPushButton = new QPushButton(groupBox_3);
        tableUpPushButton->setObjectName("tableUpPushButton");

        gridLayout_4->addWidget(tableUpPushButton, 1, 0, 1, 1);

        lightPushButton = new QPushButton(groupBox_3);
        lightPushButton->setObjectName("lightPushButton");

        gridLayout_4->addWidget(lightPushButton, 1, 1, 1, 1);

        tableDownPushButton = new QPushButton(groupBox_3);
        tableDownPushButton->setObjectName("tableDownPushButton");

        gridLayout_4->addWidget(tableDownPushButton, 1, 2, 1, 1);

        leftPushButton = new QPushButton(groupBox_3);
        leftPushButton->setObjectName("leftPushButton");

        gridLayout_4->addWidget(leftPushButton, 3, 0, 1, 1);

        backwardPushButton = new QPushButton(groupBox_3);
        backwardPushButton->setObjectName("backwardPushButton");

        gridLayout_4->addWidget(backwardPushButton, 4, 1, 1, 1);

        stepSpinBox = new QSpinBox(groupBox_3);
        stepSpinBox->setObjectName("stepSpinBox");

        gridLayout_4->addWidget(stepSpinBox, 3, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 5, 0, 1, 1);

        hotKeysCheckBox = new QCheckBox(tab);
        hotKeysCheckBox->setObjectName("hotKeysCheckBox");
        hotKeysCheckBox->setMaximumSize(QSize(200, 50));

        gridLayout_3->addWidget(hotKeysCheckBox, 0, 0, 1, 1);

        checkBox = new QCheckBox(tab);
        checkBox->setObjectName("checkBox");
        checkBox->setEnabled(false);
        checkBox->setLayoutDirection(Qt::RightToLeft);
        checkBox->setIconSize(QSize(20, 20));

        gridLayout_3->addWidget(checkBox, 0, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout_6 = new QGridLayout(tab_2);
        gridLayout_6->setObjectName("gridLayout_6");
        stepXspinBox = new QDoubleSpinBox(tab_2);
        stepXspinBox->setObjectName("stepXspinBox");
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(stepXspinBox->sizePolicy().hasHeightForWidth());
        stepXspinBox->setSizePolicy(sizePolicy5);
        stepXspinBox->setMinimumSize(QSize(100, 0));
        stepXspinBox->setDecimals(3);
        stepXspinBox->setValue(1.550000000000000);

        gridLayout_6->addWidget(stepXspinBox, 2, 6, 1, 1);

        label_41 = new QLabel(tab_2);
        label_41->setObjectName("label_41");

        gridLayout_6->addWidget(label_41, 6, 3, 1, 1);

        stepColSpinBox = new QDoubleSpinBox(tab_2);
        stepColSpinBox->setObjectName("stepColSpinBox");
        sizePolicy5.setHeightForWidth(stepColSpinBox->sizePolicy().hasHeightForWidth());
        stepColSpinBox->setSizePolicy(sizePolicy5);
        stepColSpinBox->setMinimumSize(QSize(100, 0));
        stepColSpinBox->setValue(26.059999999999999);

        gridLayout_6->addWidget(stepColSpinBox, 4, 6, 1, 1);

        centerUpOffSpinBox = new QSpinBox(tab_2);
        centerUpOffSpinBox->setObjectName("centerUpOffSpinBox");
        sizePolicy5.setHeightForWidth(centerUpOffSpinBox->sizePolicy().hasHeightForWidth());
        centerUpOffSpinBox->setSizePolicy(sizePolicy5);
        centerUpOffSpinBox->setMinimumSize(QSize(100, 0));
        centerUpOffSpinBox->setMaximum(29);

        gridLayout_6->addWidget(centerUpOffSpinBox, 6, 6, 1, 1);

        label_13 = new QLabel(tab_2);
        label_13->setObjectName("label_13");

        gridLayout_6->addWidget(label_13, 7, 0, 1, 1);

        orientationButton = new QPushButton(tab_2);
        orientationButton->setObjectName("orientationButton");
        orientationButton->setEnabled(true);
        sizePolicy5.setHeightForWidth(orientationButton->sizePolicy().hasHeightForWidth());
        orientationButton->setSizePolicy(sizePolicy5);
        orientationButton->setMinimumSize(QSize(100, 0));
        orientationButton->setFlat(false);

        gridLayout_6->addWidget(orientationButton, 9, 6, 1, 1);

        BXspinBox = new QSpinBox(tab_2);
        BXspinBox->setObjectName("BXspinBox");
        sizePolicy5.setHeightForWidth(BXspinBox->sizePolicy().hasHeightForWidth());
        BXspinBox->setSizePolicy(sizePolicy5);
        BXspinBox->setMinimumSize(QSize(100, 0));
        BXspinBox->setMinimum(0);
        BXspinBox->setMaximum(500000);

        gridLayout_6->addWidget(BXspinBox, 1, 6, 1, 1);

        downCenterOffspinBox = new QSpinBox(tab_2);
        downCenterOffspinBox->setObjectName("downCenterOffspinBox");
        sizePolicy5.setHeightForWidth(downCenterOffspinBox->sizePolicy().hasHeightForWidth());
        downCenterOffspinBox->setSizePolicy(sizePolicy5);
        downCenterOffspinBox->setMinimumSize(QSize(100, 0));
        downCenterOffspinBox->setMaximum(29);

        gridLayout_6->addWidget(downCenterOffspinBox, 7, 6, 1, 1);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(20, 10));
        label_8->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_8, 2, 5, 1, 1);

        stepRowSpinBox = new QDoubleSpinBox(tab_2);
        stepRowSpinBox->setObjectName("stepRowSpinBox");
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(stepRowSpinBox->sizePolicy().hasHeightForWidth());
        stepRowSpinBox->setSizePolicy(sizePolicy6);
        stepRowSpinBox->setMinimumSize(QSize(100, 0));
        stepRowSpinBox->setValue(0.000000000000000);

        gridLayout_6->addWidget(stepRowSpinBox, 4, 9, 1, 1);

        label_4 = new QLabel(tab_2);
        label_4->setObjectName("label_4");

        gridLayout_6->addWidget(label_4, 6, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 300, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);


        gridLayout_6->addLayout(verticalLayout, 15, 0, 1, 10);

        scanPushButton = new QPushButton(tab_2);
        scanPushButton->setObjectName("scanPushButton");
        scanPushButton->setEnabled(false);
        sizePolicy5.setHeightForWidth(scanPushButton->sizePolicy().hasHeightForWidth());
        scanPushButton->setSizePolicy(sizePolicy5);
        scanPushButton->setMinimumSize(QSize(100, 0));
        scanPushButton->setCheckable(true);

        gridLayout_6->addWidget(scanPushButton, 11, 6, 1, 1);

        label_11 = new QLabel(tab_2);
        label_11->setObjectName("label_11");

        gridLayout_6->addWidget(label_11, 3, 0, 1, 3);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName("label_6");

        gridLayout_6->addWidget(label_6, 6, 5, 1, 1);

        numYspinBox = new QSpinBox(tab_2);
        numYspinBox->setObjectName("numYspinBox");
        sizePolicy6.setHeightForWidth(numYspinBox->sizePolicy().hasHeightForWidth());
        numYspinBox->setSizePolicy(sizePolicy6);
        numYspinBox->setMinimumSize(QSize(100, 0));
        numYspinBox->setMaximum(100);
        numYspinBox->setValue(30);

        gridLayout_6->addWidget(numYspinBox, 3, 9, 1, 1);

        progressBar = new QProgressBar(tab_2);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(200, 30));
        progressBar->setValue(24);

        gridLayout_6->addWidget(progressBar, 11, 0, 1, 5);

        label_21 = new QLabel(tab_2);
        label_21->setObjectName("label_21");

        gridLayout_6->addWidget(label_21, 4, 0, 1, 3);

        label_39 = new QLabel(tab_2);
        label_39->setObjectName("label_39");
        label_39->setMinimumSize(QSize(30, 0));

        gridLayout_6->addWidget(label_39, 0, 8, 1, 1);

        label_10 = new QLabel(tab_2);
        label_10->setObjectName("label_10");

        gridLayout_6->addWidget(label_10, 2, 0, 1, 1);

        AYspinBox = new QSpinBox(tab_2);
        AYspinBox->setObjectName("AYspinBox");
        sizePolicy6.setHeightForWidth(AYspinBox->sizePolicy().hasHeightForWidth());
        AYspinBox->setSizePolicy(sizePolicy6);
        AYspinBox->setMinimumSize(QSize(100, 0));
        AYspinBox->setMaximum(500000);

        gridLayout_6->addWidget(AYspinBox, 0, 9, 1, 1);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName("label_7");

        gridLayout_6->addWidget(label_7, 6, 8, 1, 1);

        label_23 = new QLabel(tab_2);
        label_23->setObjectName("label_23");
        label_23->setMinimumSize(QSize(30, 0));
        label_23->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_23, 4, 8, 1, 1);

        pauseButton = new QPushButton(tab_2);
        pauseButton->setObjectName("pauseButton");
        pauseButton->setEnabled(false);
        sizePolicy6.setHeightForWidth(pauseButton->sizePolicy().hasHeightForWidth());
        pauseButton->setSizePolicy(sizePolicy6);
        pauseButton->setMinimumSize(QSize(100, 0));
        pauseButton->setCheckable(true);
        pauseButton->setFlat(false);

        gridLayout_6->addWidget(pauseButton, 11, 9, 1, 1);

        measureBButton = new QPushButton(tab_2);
        measureBButton->setObjectName("measureBButton");
        measureBButton->setEnabled(false);
        measureBButton->setFlat(false);

        gridLayout_6->addWidget(measureBButton, 1, 0, 1, 1);

        BYspinBox = new QSpinBox(tab_2);
        BYspinBox->setObjectName("BYspinBox");
        sizePolicy6.setHeightForWidth(BYspinBox->sizePolicy().hasHeightForWidth());
        BYspinBox->setSizePolicy(sizePolicy6);
        BYspinBox->setMinimumSize(QSize(100, 0));
        BYspinBox->setMinimum(0);
        BYspinBox->setMaximum(500000);

        gridLayout_6->addWidget(BYspinBox, 1, 9, 1, 1);

        label_28 = new QLabel(tab_2);
        label_28->setObjectName("label_28");

        gridLayout_6->addWidget(label_28, 7, 8, 1, 1);

        label_15 = new QLabel(tab_2);
        label_15->setObjectName("label_15");
        label_15->setMinimumSize(QSize(30, 0));
        label_15->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_15, 3, 8, 1, 1);

        stepYspinBox = new QDoubleSpinBox(tab_2);
        stepYspinBox->setObjectName("stepYspinBox");
        sizePolicy6.setHeightForWidth(stepYspinBox->sizePolicy().hasHeightForWidth());
        stepYspinBox->setSizePolicy(sizePolicy6);
        stepYspinBox->setMinimumSize(QSize(100, 0));
        stepYspinBox->setDecimals(3);
        stepYspinBox->setValue(2.805000000000000);

        gridLayout_6->addWidget(stepYspinBox, 2, 9, 1, 1);

        label_29 = new QLabel(tab_2);
        label_29->setObjectName("label_29");
        sizePolicy.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(label_29, 0, 0, 1, 1);

        label_22 = new QLabel(tab_2);
        label_22->setObjectName("label_22");
        label_22->setMinimumSize(QSize(20, 10));
        label_22->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_22, 4, 5, 1, 1);

        upRightSpinBox = new QSpinBox(tab_2);
        upRightSpinBox->setObjectName("upRightSpinBox");
        sizePolicy6.setHeightForWidth(upRightSpinBox->sizePolicy().hasHeightForWidth());
        upRightSpinBox->setSizePolicy(sizePolicy6);
        upRightSpinBox->setMinimumSize(QSize(100, 0));
        upRightSpinBox->setMaximum(29);
        upRightSpinBox->setSingleStep(0);
        upRightSpinBox->setValue(4);

        gridLayout_6->addWidget(upRightSpinBox, 6, 9, 1, 1);

        label_14 = new QLabel(tab_2);
        label_14->setObjectName("label_14");
        label_14->setMinimumSize(QSize(30, 0));
        label_14->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_14, 2, 8, 1, 1);

        numXspinBox = new QSpinBox(tab_2);
        numXspinBox->setObjectName("numXspinBox");
        sizePolicy5.setHeightForWidth(numXspinBox->sizePolicy().hasHeightForWidth());
        numXspinBox->setSizePolicy(sizePolicy5);
        numXspinBox->setMinimumSize(QSize(100, 0));
        numXspinBox->setMaximum(100);
        numXspinBox->setValue(15);

        gridLayout_6->addWidget(numXspinBox, 3, 6, 1, 1);

        label_12 = new QLabel(tab_2);
        label_12->setObjectName("label_12");
        label_12->setMinimumSize(QSize(30, 0));
        label_12->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_12, 1, 8, 1, 1);

        AXspinBox = new QSpinBox(tab_2);
        AXspinBox->setObjectName("AXspinBox");
        sizePolicy5.setHeightForWidth(AXspinBox->sizePolicy().hasHeightForWidth());
        AXspinBox->setSizePolicy(sizePolicy5);
        AXspinBox->setMinimumSize(QSize(100, 0));
        AXspinBox->setMaximum(500000);

        gridLayout_6->addWidget(AXspinBox, 0, 6, 1, 1);

        downRightSpinBox = new QSpinBox(tab_2);
        downRightSpinBox->setObjectName("downRightSpinBox");
        sizePolicy6.setHeightForWidth(downRightSpinBox->sizePolicy().hasHeightForWidth());
        downRightSpinBox->setSizePolicy(sizePolicy6);
        downRightSpinBox->setMinimumSize(QSize(100, 0));
        downRightSpinBox->setMaximum(29);
        downRightSpinBox->setValue(4);

        gridLayout_6->addWidget(downRightSpinBox, 7, 9, 1, 1);

        label_30 = new QLabel(tab_2);
        label_30->setObjectName("label_30");
        label_30->setMinimumSize(QSize(20, 0));

        gridLayout_6->addWidget(label_30, 0, 5, 1, 1);

        label_42 = new QLabel(tab_2);
        label_42->setObjectName("label_42");

        gridLayout_6->addWidget(label_42, 7, 5, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_6->addItem(verticalSpacer_3, 8, 4, 1, 1);

        downLeftSpinBox = new QSpinBox(tab_2);
        downLeftSpinBox->setObjectName("downLeftSpinBox");
        downLeftSpinBox->setMinimumSize(QSize(100, 0));
        downLeftSpinBox->setMaximum(29);
        downLeftSpinBox->setValue(4);

        gridLayout_6->addWidget(downLeftSpinBox, 7, 4, 1, 1);

        label_5 = new QLabel(tab_2);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(20, 10));
        label_5->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_5, 1, 5, 1, 1);

        upLeftSpinBox = new QSpinBox(tab_2);
        upLeftSpinBox->setObjectName("upLeftSpinBox");
        upLeftSpinBox->setMinimumSize(QSize(100, 0));
        upLeftSpinBox->setMaximum(29);
        upLeftSpinBox->setValue(4);

        gridLayout_6->addWidget(upLeftSpinBox, 6, 4, 1, 1);

        label_27 = new QLabel(tab_2);
        label_27->setObjectName("label_27");

        gridLayout_6->addWidget(label_27, 7, 3, 1, 1);

        label_9 = new QLabel(tab_2);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(20, 10));
        label_9->setMaximumSize(QSize(16, 16777215));

        gridLayout_6->addWidget(label_9, 3, 5, 1, 1);

        chartsButton = new QPushButton(tab_2);
        chartsButton->setObjectName("chartsButton");
        chartsButton->setEnabled(false);
        sizePolicy5.setHeightForWidth(chartsButton->sizePolicy().hasHeightForWidth());
        chartsButton->setSizePolicy(sizePolicy5);
        chartsButton->setMinimumSize(QSize(100, 0));

        gridLayout_6->addWidget(chartsButton, 12, 6, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_6->addItem(verticalSpacer_4, 10, 4, 1, 1);

        leftCheckBox = new QCheckBox(tab_2);
        leftCheckBox->setObjectName("leftCheckBox");
        leftCheckBox->setEnabled(true);
        leftCheckBox->setChecked(true);
        leftCheckBox->setTristate(false);

        gridLayout_6->addWidget(leftCheckBox, 5, 4, 1, 1);

        centerCheckBox = new QCheckBox(tab_2);
        centerCheckBox->setObjectName("centerCheckBox");
        centerCheckBox->setChecked(true);

        gridLayout_6->addWidget(centerCheckBox, 5, 6, 1, 1);

        rightCheckBox = new QCheckBox(tab_2);
        rightCheckBox->setObjectName("rightCheckBox");
        rightCheckBox->setChecked(true);

        gridLayout_6->addWidget(rightCheckBox, 5, 9, 1, 1);

        tabWidget->addTab(tab_2, QString());
        label_10->raise();
        pauseButton->raise();
        stepYspinBox->raise();
        BYspinBox->raise();
        numYspinBox->raise();
        label_11->raise();
        label_21->raise();
        stepRowSpinBox->raise();
        label_23->raise();
        label_15->raise();
        label_14->raise();
        label_12->raise();
        progressBar->raise();
        upRightSpinBox->raise();
        label_7->raise();
        downRightSpinBox->raise();
        label_13->raise();
        label_28->raise();
        label_29->raise();
        AYspinBox->raise();
        label_39->raise();
        label_4->raise();
        measureBButton->raise();
        centerUpOffSpinBox->raise();
        stepColSpinBox->raise();
        numXspinBox->raise();
        stepXspinBox->raise();
        BXspinBox->raise();
        AXspinBox->raise();
        label_30->raise();
        label_5->raise();
        label_8->raise();
        label_9->raise();
        label_22->raise();
        label_6->raise();
        downCenterOffspinBox->raise();
        label_42->raise();
        orientationButton->raise();
        scanPushButton->raise();
        chartsButton->raise();
        upLeftSpinBox->raise();
        downLeftSpinBox->raise();
        label_27->raise();
        label_41->raise();
        leftCheckBox->raise();
        centerCheckBox->raise();
        rightCheckBox->raise();

        formLayout->setWidget(1, QFormLayout::FieldRole, tabWidget);


        gridLayout_5->addLayout(formLayout, 0, 0, 6, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        orientationButton->setDefault(false);
        measureBButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", nullptr));
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
        label_20->setText(QCoreApplication::translate("MainWindow", "\320\226\321\203\321\200\320\275\320\260\320\273", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\205\320\276\320\264 \320\275\320\260 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\273\320\261\320\265\321\206", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\320\240\321\217\320\264", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        goToButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270", nullptr));
        saveMeasureButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", nullptr));
        continueFromButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\321\214 \320\276\320\261\321\205\320\276\320\264 \321\201 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\260", nullptr));
        measure2pushButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", nullptr));
        FCMeasureButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\321\200\320\270\321\202\321\214 FC", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        statePushButton->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\270\320\265 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", nullptr));
        coordsPushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\265\321\200\320\266\320\272\320\270 \320\270 \320\275\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\320\265", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "Forward Voltage", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "DC1V", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "Planar", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "Light", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "zero", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "DC10mV", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "FC", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\321\202\320\276\320\273\320\276\320\274", nullptr));
        rightPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\277\321\200\320\260\320\262\320\276", nullptr));
        forwardPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\277\320\265\321\200\320\265\320\264", nullptr));
        tableUpPushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\275\321\217\321\202\321\214", nullptr));
        lightPushButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\270\320\276\320\264 \320\222\320\272\320\273", nullptr));
        tableDownPushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        leftPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\273\320\265\320\262\320\276", nullptr));
        backwardPushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        hotKeysCheckBox->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\200\321\217\321\207\320\270\320\265 \320\272\320\273\320\260\320\262\320\270\321\210\320\270", nullptr));
        checkBox->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\320\240\321\203\321\207\320\275\320\276\320\271", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "L:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\201\321\202\321\203\320\277 \321\201\320\275\320\270\320\267\321\203", nullptr));
        orientationButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\200\320\270\320\265\320\275\321\202\320\260\321\206\320\270\321\217", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\201\321\202\321\203\320\277 \321\201\320\262\320\265\321\200\321\205\321\203", nullptr));
        scanPushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\210\320\260\320\263\320\276\320\262", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "C:", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263 \320\274\321\203\320\273\321\214\321\202\320\270\320\277\320\273\320\270\320\272\320\260\321\206\320\270\320\270", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "R:", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\203\320\267\320\260", nullptr));
#if QT_CONFIG(whatsthis)
        measureBButton->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\235\320\260\320\266\320\270\320\274\320\260\321\202\321\214 \321\202\320\276\320\273\321\214\320\272\320\276 \320\275\320\260\320\264 \321\202\320\276\321\207\320\272\320\276\320\271 \320\222</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        measureBButton->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \321\202.B", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "R:", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", " \320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \321\202.\320\220", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "C:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "L:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        chartsButton->setText(QCoreApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 DC10mV", nullptr));
        leftCheckBox->setText(QCoreApplication::translate("MainWindow", "\320\233\320\265\320\262\321\213\320\271", nullptr));
        centerCheckBox->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\321\213\320\271", nullptr));
        rightCheckBox->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\260\320\262\321\213\320\271", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
