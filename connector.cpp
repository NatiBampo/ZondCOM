#include "connector.h"


Connector::Connector()
{
    serialPortPlanar = new QSerialPort();
    serialPortKeithly = new QSerialPort();
    serialPortLight = new QSerialPort();


}


Connector::~Connector()
{
    //closePorts();
    delete serialPortPlanar;
    delete serialPortKeithly;
    delete serialPortLight;
}

void Connector::openPorts(struct Peripherals* periph)
{
    closePorts();
    if (openPort(serialPortPlanar, periph->planar_com, periph->planar_name, QSerialPort::Baud115200))
        periph->planar = serialPortPlanar;

    if (openPort(periph->keithley, periph->keithley_com ,periph->keithley_name, QSerialPort::Baud57600))
        periph->keithley = serialPortKeithly;

    if (openPort(periph-light, periph->light_com ,periph->light_name, QSerialPort::Baud9600))
        periph->light = serialPortLight;
}

void Connector::openPorts2()
{
    closePorts();
    emit openPortResultSignal(periph->planar_com, "Planar",
                              openPort(periph->planar, periph->planar_com, QSerialPort::Baud115200));
    emit openPortResultSignal(periph->keithley,"Keithley",
                              openPort(periph->keithley, periph->keithley_com, QSerialPort::Baud57600));
    emit openPortResultSignal(periph->light, "Light",
                              openPort(periph->light, periph->light_com, QSerialPort::Baud9600));
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



void Connector::autoOpen()
{
    serialPortPlanar = new QSerialPort();
    serialPortKeithly = new QSerialPort();
    serialPortLight = new QSerialPort();
    QList<QString> list;
    foreach(const QSerialPortInfo &port,  QSerialPortInfo::availablePorts())
    {
        list.append(port.portName());
    };

    QHash<QSerialPort *, QString> map;
    bool tmp_flag;
    for (int i=0; i < list.length(); i++)
    {
        //сперва окрываем порт планара
        if (!map.contains(serialPortA5))
        {
            tmp_flag = openPort(serialPortA5, list[i], QSerialPort::Baud115200);

            if (tmp_flag && checkPlanarCOM())
            {
                map.insert(serialPortA5, list[i]);
                emit openPortResultSignal(list[i], "Planar", tmp_flag);
                continue;
            }
            if (serialPortA5->isOpen())serialPortA5->close();
        }

        //порт кейтли
        if (!map.contains(serialPortKeithly))
        {
            tmp_flag = openPort(serialPortKeithly, list[i], QSerialPort::Baud57600);
            if (tmp_flag && checkKeithlyCOM())
            {
                map.insert(serialPortKeithly, list[i]);
                emit openPortResultSignal(list[i], "Keithley", tmp_flag);
                continue;
            }
            if (serialPortKeithly->isOpen()) serialPortKeithly->close();
        }
        //порт ардуины/диода

        if (!map.contains(serialPortLight))
        {
            //qDebug() << i << " light condition";
            tmp_flag = openPort(serialPortLight, list[i], QSerialPort::Baud9600);
            if (tmp_flag && checkLightCOM())
            {
                map.insert(serialPortLight, list[i]);
                emit openPortResultSignal(list[i], "Light", tmp_flag);
            } else
            {
                if (serialPortLight->isOpen()) serialPortLight->close();
            }
        }
    }
}



void Connector::closePorts(struct Peripherals* periph)
{
    closePort(periph->keithley);
    closePort(periph->light);
    closePort(periph->planar);
}


void Connector::closePort(QSerialPort* port)
{
    if (port->isOpen())
        port->close();
}


bool Connector::allPortsOpen()
{
    return (serialPortPlanar->isOpen()
            && serialPortKeithly->isOpen()
            && serialPortLight->isOpen());
}


void Connector::sendPackage(QSerialPort *serialPort, QByteArray package, int delay)
{
    lastAnswer = "";
    serialPort->write(package);
    serialPort->flush();
    serialPort->waitForBytesWritten(400);
}

void Connector::sendPackageRead (QSerialPort *serialPort, QByteArray package, int delay)
{
    lastAnswer = "";
    serialPort->write(package);
    serialPort->flush();
    serialPort->waitForBytesWritten(400);
    if (serialPort->waitForReadyRead(400)) lastAnswer.append(serialPort->readAll());
}


void Connector::measureDot(struct WalkSettings* walk,
                           struct Delays* delays, struct Currents* curr)
{
    if (allPortsOpen() || walk->keithley_status)
    {
        meter->zeroCorrection();
        //emit sendPackageSignalRead(periph->serialPortA5, "Table UP\r\n", 200);
        if (walk->planar_status) table->up();
        meter->dark_currents(walk, delays, curr);
        //lightController("1111\n", walk->light_status);
        light->on(walk);

        meter->light_current(walk, delays, curr);

        emit sendLogSignal((QString::number(currentIndex) + ", "
                            + QString::number(curr->forward05V, 'E', 4) + ", "
                            + QString::number(curr->dark10mV, 'E', 4) + ", "
                            + QString::number(curr->dark1V, 'E', 4) + ", "
                            + QString::number(curr->LightCurrent, 'E', 4)).toUtf8());

        //lightController("0001\n", walk->light_status);
        light->off(walk);
        if (walk->planar_status) table_down();
            //emit sendPackageSignalRead(periph->planar, "Table DN\r\n", 200);

    }
    else
    {
        emit sendMessageBox("warning", "Один из портов закрыт.\n Измерение не возможно.");
    }
}
