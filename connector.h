#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include "serials.h"
#include "meter.h"
#include "planar.h"
#include "light.h"


#define ANSWER_DELAY 400
#define NO_ANSWER_DELAY 10

class Connector
{
public:
    Connector(struct Peripherals*);
    ~Connector();

public slots:
    void openPorts();
    void openPorts2();
    void autoOpen();
    void closePorts();
    bool allPortsOpen();

    /**
     * @brief parsePort проверяет, по ответу, что устройство выбрано правидьно
     * @param port
     */
    virtual bool parsePort(QSerialPort *port, QString* com_name){return false;}

    void measureDot(struct WalkSettings* , struct Delays* , struct Currents*, struct Dots*);

    void measureFC(struct WalkSettings* , struct Delays* , struct Currents*, struct Dots*);
private:

    Meter* meter = nullptr;
    Planar* planar = nullptr;
    Light* light = nullptr;
};

#endif // CONNECTOR_H
