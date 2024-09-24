#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include "serials.h"
#include "meter.h"

#define ANSWER_DELAY 400
#define NO_ANSWER_DELAY 10

class Connector
{
public:
    Connector();

    void openPorts(struct Ports*);
    void autoOpen();
    void closePorts();
    bool checkPlanar();
    bool checkKeithly();
    bool checkKeysight();
    bool checkLight();
    bool allPortsOpen();
    void sendPackage(QSerialPort *serialPort,
                     QByteArray package, int delay);
    void sendPackageRead(QSerialPort *serialPort,
                         QByteArray package, int delay);


    /**
     * @brief parsePort проверяет, по ответу, что устройство выбрано правидьно
     * @param
     */
    virtual bool parsePort(QSerialPort *port, QString* com_name){return false;}


    bool openPort(QSerialPort *port, QString portName,
                          QSerialPort::BaudRate baudRate);
    void closePort(QSerialPort* port);

private:
    struct Peripherals* peripherals = nullptr;

    QSerialPort* serialPortPlanar = nullptr;
    QSerialPort* serialPortKeithly = nullptr;
    QSerialPort* serialPortLight = nullptr;

    QString lastAnswer;
};

#endif // CONNECTOR_H
