/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[104];
    char stringdata0[11];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[22];
    char stringdata5[22];
    char stringdata6[16];
    char stringdata7[17];
    char stringdata8[18];
    char stringdata9[23];
    char stringdata10[18];
    char stringdata11[15];
    char stringdata12[20];
    char stringdata13[17];
    char stringdata14[15];
    char stringdata15[12];
    char stringdata16[23];
    char stringdata17[16];
    char stringdata18[22];
    char stringdata19[20];
    char stringdata20[21];
    char stringdata21[23];
    char stringdata22[21];
    char stringdata23[22];
    char stringdata24[18];
    char stringdata25[19];
    char stringdata26[19];
    char stringdata27[21];
    char stringdata28[19];
    char stringdata29[9];
    char stringdata30[20];
    char stringdata31[20];
    char stringdata32[15];
    char stringdata33[14];
    char stringdata34[11];
    char stringdata35[17];
    char stringdata36[20];
    char stringdata37[19];
    char stringdata38[26];
    char stringdata39[27];
    char stringdata40[26];
    char stringdata41[23];
    char stringdata42[8];
    char stringdata43[23];
    char stringdata44[23];
    char stringdata45[24];
    char stringdata46[27];
    char stringdata47[15];
    char stringdata48[12];
    char stringdata49[27];
    char stringdata50[32];
    char stringdata51[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 19),  // "scanningPlateSignal"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 13),  // "measureSignal"
        QT_MOC_LITERAL(46, 21),  // "tableControllerSignal"
        QT_MOC_LITERAL(68, 21),  // "lightControllerSignal"
        QT_MOC_LITERAL(90, 15),  // "openPortsSignal"
        QT_MOC_LITERAL(106, 16),  // "closePortsSignal"
        QT_MOC_LITERAL(123, 17),  // "goToElementSignal"
        QT_MOC_LITERAL(141, 22),  // "sendPauseCommandSignal"
        QT_MOC_LITERAL(164, 17),  // "saveMeasureSignal"
        QT_MOC_LITERAL(182, 14),  // "autoWalkSignal"
        QT_MOC_LITERAL(197, 19),  // "autoOpenPortsSignal"
        QT_MOC_LITERAL(217, 16),  // "showChartsSignal"
        QT_MOC_LITERAL(234, 14),  // "setDelaySignal"
        QT_MOC_LITERAL(249, 11),  // "QList<int>*"
        QT_MOC_LITERAL(261, 22),  // "getCurrentCoordsSignal"
        QT_MOC_LITERAL(284, 15),  // "measureFCSignal"
        QT_MOC_LITERAL(300, 21),  // "openPortPushButton_on"
        QT_MOC_LITERAL(322, 19),  // "coordsPushButton_on"
        QT_MOC_LITERAL(342, 20),  // "tableUpPushButton_on"
        QT_MOC_LITERAL(363, 22),  // "tableDownPushButton_on"
        QT_MOC_LITERAL(386, 20),  // "forwardPushButton_on"
        QT_MOC_LITERAL(407, 21),  // "backwardPushButton_on"
        QT_MOC_LITERAL(429, 17),  // "leftPushButton_on"
        QT_MOC_LITERAL(447, 18),  // "rightPushButton_on"
        QT_MOC_LITERAL(466, 18),  // "statePushButton_on"
        QT_MOC_LITERAL(485, 20),  // "measurePushButton_on"
        QT_MOC_LITERAL(506, 18),  // "lightPushButton_on"
        QT_MOC_LITERAL(525, 8),  // "writeLog"
        QT_MOC_LITERAL(534, 19),  // "setProgressBarValue"
        QT_MOC_LITERAL(554, 19),  // "setProgressBarRange"
        QT_MOC_LITERAL(574, 14),  // "openPortResult"
        QT_MOC_LITERAL(589, 13),  // "addRowToTable"
        QT_MOC_LITERAL(603, 10),  // "setBCoords"
        QT_MOC_LITERAL(614, 16),  // "setCurrentCoords"
        QT_MOC_LITERAL(631, 19),  // "pauseButton_clicked"
        QT_MOC_LITERAL(651, 18),  // "goToButton_clicked"
        QT_MOC_LITERAL(670, 25),  // "saveMeasureButton_clicked"
        QT_MOC_LITERAL(696, 26),  // "continueFromButton_clicked"
        QT_MOC_LITERAL(723, 25),  // "orientationButton_clicked"
        QT_MOC_LITERAL(749, 22),  // "scanPushButton_clicked"
        QT_MOC_LITERAL(772, 7),  // "checked"
        QT_MOC_LITERAL(780, 22),  // "autoPortButton_clicked"
        QT_MOC_LITERAL(803, 22),  // "measureBButton_clicked"
        QT_MOC_LITERAL(826, 23),  // "on_chartsButton_clicked"
        QT_MOC_LITERAL(850, 26),  // "measure2pushButton_clicked"
        QT_MOC_LITERAL(877, 14),  // "showMessageBox"
        QT_MOC_LITERAL(892, 11),  // "sendEndWalk"
        QT_MOC_LITERAL(904, 26),  // "on_FCMeasureButton_clicked"
        QT_MOC_LITERAL(931, 31),  // "on_hotKeysCheckBox_stateChanged"
        QT_MOC_LITERAL(963, 4)   // "arg1"
    },
    "MainWindow",
    "scanningPlateSignal",
    "",
    "measureSignal",
    "tableControllerSignal",
    "lightControllerSignal",
    "openPortsSignal",
    "closePortsSignal",
    "goToElementSignal",
    "sendPauseCommandSignal",
    "saveMeasureSignal",
    "autoWalkSignal",
    "autoOpenPortsSignal",
    "showChartsSignal",
    "setDelaySignal",
    "QList<int>*",
    "getCurrentCoordsSignal",
    "measureFCSignal",
    "openPortPushButton_on",
    "coordsPushButton_on",
    "tableUpPushButton_on",
    "tableDownPushButton_on",
    "forwardPushButton_on",
    "backwardPushButton_on",
    "leftPushButton_on",
    "rightPushButton_on",
    "statePushButton_on",
    "measurePushButton_on",
    "lightPushButton_on",
    "writeLog",
    "setProgressBarValue",
    "setProgressBarRange",
    "openPortResult",
    "addRowToTable",
    "setBCoords",
    "setCurrentCoords",
    "pauseButton_clicked",
    "goToButton_clicked",
    "saveMeasureButton_clicked",
    "continueFromButton_clicked",
    "orientationButton_clicked",
    "scanPushButton_clicked",
    "checked",
    "autoPortButton_clicked",
    "measureBButton_clicked",
    "on_chartsButton_clicked",
    "measure2pushButton_clicked",
    "showMessageBox",
    "sendEndWalk",
    "on_FCMeasureButton_clicked",
    "on_hotKeysCheckBox_stateChanged",
    "arg1"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      47,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,   18,  296,    2, 0x06,    1 /* Public */,
       3,    0,  333,    2, 0x06,   20 /* Public */,
       4,    1,  334,    2, 0x06,   21 /* Public */,
       5,    1,  337,    2, 0x06,   23 /* Public */,
       6,    3,  340,    2, 0x06,   25 /* Public */,
       7,    0,  347,    2, 0x06,   29 /* Public */,
       8,    1,  348,    2, 0x06,   30 /* Public */,
       9,    0,  351,    2, 0x06,   32 /* Public */,
      10,    1,  352,    2, 0x06,   33 /* Public */,
      11,    3,  355,    2, 0x06,   35 /* Public */,
      12,    0,  362,    2, 0x06,   39 /* Public */,
      13,    1,  363,    2, 0x06,   40 /* Public */,
      14,    1,  366,    2, 0x06,   42 /* Public */,
      16,    1,  369,    2, 0x06,   44 /* Public */,
      17,    0,  372,    2, 0x06,   46 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      18,    0,  373,    2, 0x0a,   47 /* Public */,
      19,    0,  374,    2, 0x0a,   48 /* Public */,
      20,    0,  375,    2, 0x0a,   49 /* Public */,
      21,    0,  376,    2, 0x0a,   50 /* Public */,
      22,    0,  377,    2, 0x0a,   51 /* Public */,
      23,    0,  378,    2, 0x0a,   52 /* Public */,
      24,    0,  379,    2, 0x0a,   53 /* Public */,
      25,    0,  380,    2, 0x0a,   54 /* Public */,
      26,    0,  381,    2, 0x0a,   55 /* Public */,
      27,    0,  382,    2, 0x0a,   56 /* Public */,
      28,    0,  383,    2, 0x0a,   57 /* Public */,
      29,    1,  384,    2, 0x0a,   58 /* Public */,
      30,    1,  387,    2, 0x0a,   60 /* Public */,
      31,    2,  390,    2, 0x0a,   62 /* Public */,
      32,    3,  395,    2, 0x0a,   65 /* Public */,
      33,    6,  402,    2, 0x0a,   69 /* Public */,
      34,    2,  415,    2, 0x0a,   76 /* Public */,
      35,    2,  420,    2, 0x0a,   79 /* Public */,
      36,    1,  425,    2, 0x0a,   82 /* Public */,
      37,    0,  428,    2, 0x0a,   84 /* Public */,
      38,    0,  429,    2, 0x0a,   85 /* Public */,
      39,    1,  430,    2, 0x0a,   86 /* Public */,
      40,    0,  433,    2, 0x0a,   88 /* Public */,
      41,    1,  434,    2, 0x0a,   89 /* Public */,
      43,    0,  437,    2, 0x0a,   91 /* Public */,
      44,    0,  438,    2, 0x0a,   92 /* Public */,
      45,    0,  439,    2, 0x0a,   93 /* Public */,
      46,    0,  440,    2, 0x0a,   94 /* Public */,
      47,    2,  441,    2, 0x0a,   95 /* Public */,
      48,    0,  446,    2, 0x0a,   98 /* Public */,
      49,    0,  447,    2, 0x0a,   99 /* Public */,
      50,    1,  448,    2, 0x08,  100 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Bool, QMetaType::Bool,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::Int,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   51,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'scanningPlateSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'measureSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'tableControllerSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>,
        // method 'lightControllerSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>,
        // method 'openPortsSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'closePortsSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goToElementSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'sendPauseCommandSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveMeasureSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'autoWalkSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'autoOpenPortsSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showChartsSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setDelaySignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QList<int> *, std::false_type>,
        // method 'getCurrentCoordsSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'measureFCSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openPortPushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'coordsPushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'tableUpPushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'tableDownPushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'forwardPushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'backwardPushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'leftPushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rightPushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'statePushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'measurePushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lightPushButton_on'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'writeLog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>,
        // method 'setProgressBarValue'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setProgressBarRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'openPortResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'addRowToTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setBCoords'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setCurrentCoords'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'pauseButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'goToButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveMeasureButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'continueFromButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'orientationButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'scanPushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'autoPortButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'measureBButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_chartsButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'measure2pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showMessageBox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sendEndWalk'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_FCMeasureButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_hotKeysCheckBox_stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->scanningPlateSignal((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[9])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[10])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[11])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[12])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[13])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[14])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[15])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[16])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[17])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[18]))); break;
        case 1: _t->measureSignal(); break;
        case 2: _t->tableControllerSignal((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 3: _t->lightControllerSignal((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 4: _t->openPortsSignal((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 5: _t->closePortsSignal(); break;
        case 6: _t->goToElementSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->sendPauseCommandSignal(); break;
        case 8: _t->saveMeasureSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->autoWalkSignal((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 10: _t->autoOpenPortsSignal(); break;
        case 11: _t->showChartsSignal((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->setDelaySignal((*reinterpret_cast< std::add_pointer_t<QList<int>*>>(_a[1]))); break;
        case 13: _t->getCurrentCoordsSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->measureFCSignal(); break;
        case 15: _t->openPortPushButton_on(); break;
        case 16: _t->coordsPushButton_on(); break;
        case 17: _t->tableUpPushButton_on(); break;
        case 18: _t->tableDownPushButton_on(); break;
        case 19: _t->forwardPushButton_on(); break;
        case 20: _t->backwardPushButton_on(); break;
        case 21: _t->leftPushButton_on(); break;
        case 22: _t->rightPushButton_on(); break;
        case 23: _t->statePushButton_on(); break;
        case 24: _t->measurePushButton_on(); break;
        case 25: _t->lightPushButton_on(); break;
        case 26: _t->writeLog((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 27: _t->setProgressBarValue((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 28: _t->setProgressBarRange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 29: _t->openPortResult((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        case 30: _t->addRowToTable((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6]))); break;
        case 31: _t->setBCoords((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 32: _t->setCurrentCoords((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 33: _t->pauseButton_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 34: _t->goToButton_clicked(); break;
        case 35: _t->saveMeasureButton_clicked(); break;
        case 36: _t->continueFromButton_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 37: _t->orientationButton_clicked(); break;
        case 38: _t->scanPushButton_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 39: _t->autoPortButton_clicked(); break;
        case 40: _t->measureBButton_clicked(); break;
        case 41: _t->on_chartsButton_clicked(); break;
        case 42: _t->measure2pushButton_clicked(); break;
        case 43: _t->showMessageBox((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 44: _t->sendEndWalk(); break;
        case 45: _t->on_FCMeasureButton_clicked(); break;
        case 46: _t->on_hotKeysCheckBox_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(double , double , double , double , double , double , double , double , double , bool , int , int , int , int , int , int , bool , bool );
            if (_t _q_method = &MainWindow::scanningPlateSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::measureSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QByteArray );
            if (_t _q_method = &MainWindow::tableControllerSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QByteArray );
            if (_t _q_method = &MainWindow::lightControllerSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString , QString , QString );
            if (_t _q_method = &MainWindow::openPortsSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::closePortsSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (_t _q_method = &MainWindow::goToElementSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::sendPauseCommandSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (_t _q_method = &MainWindow::saveMeasureSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(bool , QString , int );
            if (_t _q_method = &MainWindow::autoWalkSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::autoOpenPortsSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (_t _q_method = &MainWindow::showChartsSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QList<int> * );
            if (_t _q_method = &MainWindow::setDelaySignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (_t _q_method = &MainWindow::getCurrentCoordsSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::measureFCSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 47)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 47;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 47)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 47;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::scanningPlateSignal(double _t1, double _t2, double _t3, double _t4, double _t5, double _t6, double _t7, double _t8, double _t9, bool _t10, int _t11, int _t12, int _t13, int _t14, int _t15, int _t16, bool _t17, bool _t18)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t8))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t9))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t10))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t11))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t12))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t13))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t14))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t15))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t16))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t17))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t18))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::measureSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::tableControllerSignal(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::lightControllerSignal(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::openPortsSignal(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::closePortsSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::goToElementSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::sendPauseCommandSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void MainWindow::saveMeasureSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::autoWalkSignal(bool _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainWindow::autoOpenPortsSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void MainWindow::showChartsSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MainWindow::setDelaySignal(QList<int> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::getCurrentCoordsSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void MainWindow::measureFCSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
