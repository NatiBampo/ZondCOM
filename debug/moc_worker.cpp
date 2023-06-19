/****************************************************************************
** Meta object code from reading C++ file 'worker.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../worker.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
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
struct qt_meta_stringdata_Worker_t {
    uint offsetsAndSizes[70];
    char stringdata0[7];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[27];
    char stringdata4[27];
    char stringdata5[21];
    char stringdata6[19];
    char stringdata7[15];
    char stringdata8[18];
    char stringdata9[16];
    char stringdata10[15];
    char stringdata11[16];
    char stringdata12[14];
    char stringdata13[16];
    char stringdata14[16];
    char stringdata15[10];
    char stringdata16[11];
    char stringdata17[10];
    char stringdata18[12];
    char stringdata19[12];
    char stringdata20[14];
    char stringdata21[16];
    char stringdata22[16];
    char stringdata23[19];
    char stringdata24[29];
    char stringdata25[18];
    char stringdata26[21];
    char stringdata27[15];
    char stringdata28[18];
    char stringdata29[10];
    char stringdata30[9];
    char stringdata31[12];
    char stringdata32[14];
    char stringdata33[19];
    char stringdata34[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Worker_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
        QT_MOC_LITERAL(0, 6),  // "Worker"
        QT_MOC_LITERAL(7, 13),  // "sendLogSignal"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 26),  // "sendProgressBarValueSignal"
        QT_MOC_LITERAL(49, 26),  // "sendProgressBarRangeSignal"
        QT_MOC_LITERAL(76, 20),  // "openPortResultSignal"
        QT_MOC_LITERAL(97, 18),  // "sendAddTableSignal"
        QT_MOC_LITERAL(116, 14),  // "autoWalkSignal"
        QT_MOC_LITERAL(131, 17),  // "sendBCoordsSignal"
        QT_MOC_LITERAL(149, 15),  // "getKeithleyData"
        QT_MOC_LITERAL(165, 14),  // "sendMessageBox"
        QT_MOC_LITERAL(180, 15),  // "measureElement2"
        QT_MOC_LITERAL(196, 13),  // "scanningPlate"
        QT_MOC_LITERAL(210, 15),  // "tableController"
        QT_MOC_LITERAL(226, 15),  // "lightController"
        QT_MOC_LITERAL(242, 9),  // "openPorts"
        QT_MOC_LITERAL(252, 10),  // "closePorts"
        QT_MOC_LITERAL(263, 9),  // "pauseWalk"
        QT_MOC_LITERAL(273, 11),  // "goToElement"
        QT_MOC_LITERAL(285, 11),  // "saveMeasure"
        QT_MOC_LITERAL(297, 13),  // "autoOpenPorts"
        QT_MOC_LITERAL(311, 15),  // "getBCoordinates"
        QT_MOC_LITERAL(327, 15),  // "readData_planar"
        QT_MOC_LITERAL(343, 18),  // "handleError_planar"
        QT_MOC_LITERAL(362, 28),  // "QSerialPort::SerialPortError"
        QT_MOC_LITERAL(391, 17),  // "readData_keithley"
        QT_MOC_LITERAL(409, 20),  // "handleError_keithley"
        QT_MOC_LITERAL(430, 14),  // "readData_light"
        QT_MOC_LITERAL(445, 17),  // "handleError_light"
        QT_MOC_LITERAL(463, 9),  // "autoWalk2"
        QT_MOC_LITERAL(473, 8),  // "setDelay"
        QT_MOC_LITERAL(482, 11),  // "QList<int>*"
        QT_MOC_LITERAL(494, 13),  // "handleTimeout"
        QT_MOC_LITERAL(508, 18),  // "handleBytesWritten"
        QT_MOC_LITERAL(527, 5)   // "bytes"
    },
    "Worker",
    "sendLogSignal",
    "",
    "sendProgressBarValueSignal",
    "sendProgressBarRangeSignal",
    "openPortResultSignal",
    "sendAddTableSignal",
    "autoWalkSignal",
    "sendBCoordsSignal",
    "getKeithleyData",
    "sendMessageBox",
    "measureElement2",
    "scanningPlate",
    "tableController",
    "lightController",
    "openPorts",
    "closePorts",
    "pauseWalk",
    "goToElement",
    "saveMeasure",
    "autoOpenPorts",
    "getBCoordinates",
    "readData_planar",
    "handleError_planar",
    "QSerialPort::SerialPortError",
    "readData_keithley",
    "handleError_keithley",
    "readData_light",
    "handleError_light",
    "autoWalk2",
    "setDelay",
    "QList<int>*",
    "handleTimeout",
    "handleBytesWritten",
    "bytes"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Worker[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  194,    2, 0x06,    1 /* Public */,
       3,    1,  197,    2, 0x06,    3 /* Public */,
       4,    2,  200,    2, 0x06,    5 /* Public */,
       5,    3,  205,    2, 0x06,    8 /* Public */,
       6,    5,  212,    2, 0x06,   12 /* Public */,
       7,    2,  223,    2, 0x06,   18 /* Public */,
       8,    2,  228,    2, 0x06,   21 /* Public */,
       9,    0,  233,    2, 0x06,   24 /* Public */,
      10,    2,  234,    2, 0x06,   25 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    0,  239,    2, 0x0a,   28 /* Public */,
      12,   12,  240,    2, 0x0a,   29 /* Public */,
      13,    1,  265,    2, 0x0a,   42 /* Public */,
      14,    1,  268,    2, 0x0a,   44 /* Public */,
      15,    3,  271,    2, 0x0a,   46 /* Public */,
      16,    0,  278,    2, 0x0a,   50 /* Public */,
      17,    0,  279,    2, 0x0a,   51 /* Public */,
      18,    1,  280,    2, 0x0a,   52 /* Public */,
      19,    1,  283,    2, 0x0a,   54 /* Public */,
      20,    0,  286,    2, 0x0a,   56 /* Public */,
      21,    0,  287,    2, 0x0a,   57 /* Public */,
      22,    0,  288,    2, 0x0a,   58 /* Public */,
      23,    1,  289,    2, 0x0a,   59 /* Public */,
      25,    0,  292,    2, 0x0a,   61 /* Public */,
      26,    1,  293,    2, 0x0a,   62 /* Public */,
      27,    0,  296,    2, 0x0a,   64 /* Public */,
      28,    1,  297,    2, 0x0a,   65 /* Public */,
      29,    2,  300,    2, 0x0a,   67 /* Public */,
      30,    1,  305,    2, 0x0a,   70 /* Public */,
      32,    0,  308,    2, 0x0a,   72 /* Public */,
      33,    1,  309,    2, 0x0a,   73 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 31,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   34,

       0        // eod
};

Q_CONSTINIT const QMetaObject Worker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Worker.offsetsAndSizes,
    qt_meta_data_Worker,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Worker_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Worker, std::true_type>,
        // method 'sendLogSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>,
        // method 'sendProgressBarValueSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'sendProgressBarRangeSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'openPortResultSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'sendAddTableSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'autoWalkSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sendBCoordsSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'getKeithleyData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendMessageBox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'measureElement2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'scanningPlate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
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
        // method 'tableController'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>,
        // method 'lightController'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>,
        // method 'openPorts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'closePorts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pauseWalk'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goToElement'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'saveMeasure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'autoOpenPorts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getBCoordinates'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readData_planar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleError_planar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSerialPort::SerialPortError, std::false_type>,
        // method 'readData_keithley'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleError_keithley'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSerialPort::SerialPortError, std::false_type>,
        // method 'readData_light'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleError_light'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSerialPort::SerialPortError, std::false_type>,
        // method 'autoWalk2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setDelay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QList<int> *, std::false_type>,
        // method 'handleTimeout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleBytesWritten'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>
    >,
    nullptr
} };

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Worker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sendLogSignal((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 1: _t->sendProgressBarValueSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->sendProgressBarRangeSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 3: _t->openPortResultSignal((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        case 4: _t->sendAddTableSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5]))); break;
        case 5: _t->autoWalkSignal((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->sendBCoordsSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 7: _t->getKeithleyData(); break;
        case 8: _t->sendMessageBox((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 9: _t->measureElement2(); break;
        case 10: _t->scanningPlate((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[9])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[10])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[11])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[12]))); break;
        case 11: _t->tableController((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 12: _t->lightController((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 13: _t->openPorts((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 14: _t->closePorts(); break;
        case 15: _t->pauseWalk(); break;
        case 16: _t->goToElement((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->saveMeasure((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 18: _t->autoOpenPorts(); break;
        case 19: _t->getBCoordinates(); break;
        case 20: _t->readData_planar(); break;
        case 21: _t->handleError_planar((*reinterpret_cast< std::add_pointer_t<QSerialPort::SerialPortError>>(_a[1]))); break;
        case 22: _t->readData_keithley(); break;
        case 23: _t->handleError_keithley((*reinterpret_cast< std::add_pointer_t<QSerialPort::SerialPortError>>(_a[1]))); break;
        case 24: _t->readData_light(); break;
        case 25: _t->handleError_light((*reinterpret_cast< std::add_pointer_t<QSerialPort::SerialPortError>>(_a[1]))); break;
        case 26: _t->autoWalk2((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 27: _t->setDelay((*reinterpret_cast< std::add_pointer_t<QList<int>*>>(_a[1]))); break;
        case 28: _t->handleTimeout(); break;
        case 29: _t->handleBytesWritten((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Worker::*)(QByteArray );
            if (_t _q_method = &Worker::sendLogSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Worker::*)(int );
            if (_t _q_method = &Worker::sendProgressBarValueSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Worker::*)(int , int );
            if (_t _q_method = &Worker::sendProgressBarRangeSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Worker::*)(QString , QString , bool );
            if (_t _q_method = &Worker::openPortResultSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Worker::*)(int , double , double , double , double );
            if (_t _q_method = &Worker::sendAddTableSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Worker::*)(bool , QString );
            if (_t _q_method = &Worker::autoWalkSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Worker::*)(int , int );
            if (_t _q_method = &Worker::sendBCoordsSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Worker::*)();
            if (_t _q_method = &Worker::getKeithleyData; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Worker::*)(QString , QString );
            if (_t _q_method = &Worker::sendMessageBox; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void Worker::sendLogSignal(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Worker::sendProgressBarValueSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Worker::sendProgressBarRangeSignal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Worker::openPortResultSignal(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Worker::sendAddTableSignal(int _t1, double _t2, double _t3, double _t4, double _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Worker::autoWalkSignal(bool _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Worker::sendBCoordsSignal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Worker::getKeithleyData()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Worker::sendMessageBox(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
