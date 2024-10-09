#include "connector.h"


Connector::Connector(struct Peripherals* periph)
{
    periph->planar = new QSerialPort();
    periph->keithley = new QSerialPort();
    periph->light = new QSerialPort();

    planar = new Planar(periph->planar);
    light = new Light(periph->light);
    meter = new Keithley(periph->keithley);
}


Connector::~Connector()
{
    delete periph->planar;
    delete periph->keithley;
    delete periph->light;
}

void Connector::openPorts(struct Peripherals* periph)
{
    closePorts();
    if (openPort(periph->planar, periph->planar_com, periph->planar_name, QSerialPort::Baud115200))
        planar->setPort(periph->planar);

    if (openPort(periph-light, periph->light_com ,periph->light_name, QSerialPort::Baud9600))
        light->setPort(periph->light);

    if (periph->lan)
    {
        delete meter;
        meter = new Keysight(periph);
    }
    else if (openPort(periph->keithley, periph->keithley_com,
                 periph->keithley_name, QSerialPort::Baud57600))
    {
        meter->setPort(periph->keithley);
    }
    else
    {
        qDebug() << "you're moron";
    }

    emit portsReady();
}


void Connector::openPorts2(struct Peripherals* periph)
{
    closePorts();
    emit openPortResultSignal(periph->planar_com, "Planar",
                              openPort(periph->planar, periph->planar_com, QSerialPort::Baud115200));
    emit openPortResultSignal(periph->keithley,"Keithley",
                              openPort(periph->keithley, periph->keithley_com, QSerialPort::Baud57600));
    emit openPortResultSignal(periph->light, "Light",
                              openPort(periph->light, periph->light_com, QSerialPort::Baud9600));
}


bool Connector::openPort(QSerialPort *port, QString portName,
                      QSerialPort::BaudRate baudRate)
{
    port->setPortName(portName);
    port->setBaudRate(baudRate);
    port->setDataBits(QSerialPort::DataBits::Data8);
    port->setStopBits(QSerialPort::StopBits::OneStop);
    port->setParity(QSerialPort::Parity::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);

    return port->open(QSerialPort::ReadWrite);
}


bool Connector::openPort(QSerialPort *port, QString* comPort,
                         QString* portName, QSerialPort::BaudRate baudRate)
{
    port->setPortName(*comPort);
    port->setBaudRate(baudRate);
    port->setDataBits(QSerialPort::DataBits::Data8);
    port->setStopBits(QSerialPort::StopBits::OneStop);
    port->setParity(QSerialPort::Parity::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);

    bool res = port->open(QSerialPort::ReadWrite);
    emit openPortResultSignal(port, portName, comPort, res);
    return res;
}

//актуализировать
void Connector::parsePorts(struct Peripherals* periph)
{
    if (periph->lan ) meter = new Keysight(periph);
    else meter = new Keithley(periph);

    foreach(const QSerialPortInfo &port,  QSerialPortInfo::availablePorts())
    {
        planar->parsePort(port.portName(), periph);
        meter->parsePort(port.portName(), periph);
        light->parsePort(port.portName(), periph);
    }
}


void Connector::closePorts(struct Peripherals* periph)
{
    if (periph->lan)
        meter->closeConnection();
    else
        meter->closePort();
    planar->closePort();
    light->closePort();
}


bool Connector::allPortsOpen()
{
    return (serialPortPlanar->isOpen()            
            && serialPortLight->isOpen()
            && meter->isOpen());
}


void Connector::measureDot(struct WalkSettings* walk,
                           struct Delays* delays,
                           struct Currents* currs,
                           struct Dots* dots)
{
    if (allPortsOpen() || walk->keithley_status)
    {
        int start = clock();
        //planar->goToDot(walk, dots);
        meter->zeroCorrection();
        //emit sendPackageSignalRead(periph->serialPortA5, "Table UP\r\n", 200);
        if (walk->planar_status) table->up();

        meter->darkCurrents(walk, delays, currs);
        //lightController("1111\n", walk->light_status);
        light->on(walk);

        meter->lightCurrent(walk, delays, currs);

        emit sendLogSignal((QString::number(currs->currentIndex) + ", "
                            + QString::number(curr->forward05V, 'E', 4) + ", "
                            + QString::number(curr->dark10mV, 'E', 4) + ", "
                            + QString::number(curr->dark1V, 'E', 4) + ", "
                            + QString::number(curr->LightCurrent, 'E', 4)).toUtf8());

        //lightController("0001\n", walk->light_status);
        light->off(walk);
        if (walk->planar_status) planar->down();
            //emit sendPackageSignalRead(periph->planar, "Table DN\r\n", 200);

        int end = clock();
        int t = (end - start);

        emit sendMessageBox("Последнее измерение: ",
                            "FC: " + QString::number(curr->forward05V, 'E', 4)
                            + ", \nDC10mV: " + QString::number(curr->dark10mV, 'E', 4)
                            + ", \nDC1V: " + QString::number(curr->dark1V, 'E', 4)
                            + ", \nLC10mV: " + QString::number(curr->light10mV, 'E', 4)
                            + "\n\nВремя: " + QString::number(t / CLOCKS_PER_SEC) + "сек");
    }
    else
    {
        emit sendMessageBox("warning", "Один из портов закрыт.\n Измерение не возможно.");
    }
}


void Connector::measureFC(struct WalkSettings* walk,
                          struct Delays* delays,
                          struct Currents* currs,
                          struct Dots* dots)
{
    if (allPortsOpen() || walk->keithley_status)
    {
        //planar->goToDot(walk, dots);
        meter->zeroCorrection();
        //emit sendPackageSignalRead(periph->serialPortA5, "Table UP\r\n", 200);
        if (walk->planar_status)
            table->up();
        if (walk->keithley_status)
            meter->darkCurrents(walk, delays, currs);
        //lightController("1111\n", walk->light_status);
        light->on(walk);

        meter->lightCurrent(walk, delays, currs);

        emit sendLogSignal((QString::number(currs->currentIndex) + ", "
                            + QString::number(curr->forward05V, 'E', 4) + ", "
                            + QString::number(curr->dark10mV, 'E', 4) + ", "
                            + QString::number(curr->dark1V, 'E', 4) + ", "
                            + QString::number(curr->LightCurrent, 'E', 4)).toUtf8());

        //lightController("0001\n", walk->light_status);
        light->off(walk);
        if (walk->planar_status) planar->down();
            //emit sendPackageSignalRead(periph->planar, "Table DN\r\n", 200);
        emit sendMessageBox("Прямой ток измерение: ", "Voltage : "
                            + QByteArray::number(((double)FCVoltage) / 1000) + " V : "
                            + QString::number(ForwardCurrent, 'E', 4));

    }
    else
    {
        emit sendMessageBox("warning", "Один из портов закрыт.\n Измерение не возможно.");
    }
}
