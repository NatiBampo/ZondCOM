#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QSerialPort>
#include <QSerialPortInfo>

#include "serials.h"
#include "meter.h"
#include "comport.h"
#include "planar.h"
#include "light.h"
#include "keithley.h"
#include "keysight.h"

#define ANSWER_DELAY 400
#define NO_ANSWER_DELAY 10

class Connector
{
public:
    Connector(struct Peripherals*);
    ~Connector();

public slots:
    void openPorts(struct Peripherals* periph);

    void closePorts();

    bool allPortsOpen(struct WalkSettings* walk);

    bool openPort(QSerialPort *port, QString portName,
                          QSerialPort::BaudRate baudRate);
    bool openPort(QSerialPort *port, QString* comPort,
                  QString* portName, QSerialPort::BaudRate baudRate);

    void parsePorts(struct Peripherals*);

    void measureDot(struct WalkSettings* , struct Delays* , struct Currents*, struct Dots*);

    void measureFC(struct WalkSettings* , struct Delays* , struct Currents*, struct Dots*);

    void sendLog(QByteArray msg);

    void sendMessageBox(QString, QString);

    void sendProgessRange(int, int);

public:
    Meter* meter = nullptr;
    Planar* planar = nullptr;
    Light* light = nullptr;
    Keithley* kith = nullptr;
signals:
    void portsReadySignal();
    void sendLogSignal(QByteArray msg);
    void sendMessageBoxSignal(QString, QString);
};

#endif // CONNECTOR_H
