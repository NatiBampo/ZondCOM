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
    delete planar;
    delete light;
    delete meter;
}

void Connector::openPorts(struct Peripherals* periph)
{
    closePorts();
    if (planar->openPort(periph->planar, periph->planar_com,
                          QSerialPort::Baud115200))
        planar->setPort(periph->planar);

    if (light->openPort(periph-light, periph->light_com,
                          QSerialPort::Baud9600))
        light->setPort(periph->light);

    if (periph->lan)
    {
        delete meter;
        meter = new Keysight(periph);
    }
    //костыль
    else //if (light->openPort(periph->keithley, periph->keithley_com, QSerialPort::Baud57600))
    {
        //meter->setPort(periph->keithley);
        openConnection(p);
    }
    else
    {
        qDebug() << "you're moron";
    }

    emit portsReady();
}


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
    emit openPortResultSignal();
}


void Connector::closePorts()
{
    meter->closeConnection();
    planar->closePort();
    light->closePort();
}


bool Connector::allPortsOpen(struct WalkSettings* walk)
{
    return (walk->planar_status
            && walk->keithley_status
            && walk->light_status);
}


void Connector::measureDot(struct WalkSettings* walk,
                           struct Delays* delays,
                           struct Currents* currs,
                           struct Dots* dots)
{
    if (allPortsOpen(walk) || walk->keithley_status)
    {
        int start = clock();
        //planar->goToDot(walk, dots);
        meter->zeroCorrection(delays->zero);
        //emit sendPackageSignalRead(periph->serialPortA5, "Table UP\r\n", 200);
        if (walk->planar_status) planar->up(walk);

        meter->darkCurrents(walk, delays, currs);
        //lightController("1111\n", walk->light_status);
        light->on(walk);

        meter->lightCurrent(walk, delays, currs);

        emit sendLogSignal((QString::number(currs->currentIndex) + ", "
                            + QString::number(currs->forward05V, 'E', 4) + ", "
                            + QString::number(currs->dark10mV, 'E', 4) + ", "
                            + QString::number(currs->dark1V, 'E', 4) + ", "
                            + QString::number(currs->light10mV, 'E', 4)).toUtf8());

        //lightController("0001\n", walk->light_status);
        light->off(walk);
        if (walk->planar_status) planar->down(walk);
            //emit sendPackageSignalRead(periph->planar, "Table DN\r\n", 200);

        int end = clock();
        int t = (end - start);

        emit sendMessageBox("Последнее измерение: ",
                            "FC: " + QString::number(currs->forward05V, 'E', 4)
                            + ", \nDC10mV: " + QString::number(currs->dark10mV, 'E', 4)
                            + ", \nDC1V: " + QString::number(currs->dark1V, 'E', 4)
                            + ", \nLC10mV: " + QString::number(currs->light10mV, 'E', 4)
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
    if (walk->keithley_status)
    {
        //planar->goToDot(walk, dots);
        meter->zeroCorrection(delays->zero);
        //emit sendPackageSignalRead(periph->serialPortA5, "Table UP\r\n", 200);
        if (walk->planar_status)
            table->up(walk);
        if (walk->keithley_status)
            meter->darkCurrents(walk, delays, currs);
        //lightController("1111\n", walk->light_status);
        light->on(walk);

        meter->lightCurrent(walk, delays, currs);

        emit sendLogSignal((QString::number(currs->currentIndex) + ", "
                            + QString::number(currs->forward05V, 'E', 4) + ", "
                            + QString::number(currs->dark10mV, 'E', 4) + ", "
                            + QString::number(currs->dark1V, 'E', 4) + ", "
                            + QString::number(currs->LightCurrent, 'E', 4)).toUtf8());

        //lightController("0001\n", walk->light_status);
        light->off(walk);
        if (walk->planar_status) planar->down(walk);
            //emit sendPackageSignalRead(periph->planar, "Table DN\r\n", 200);
        emit sendMessageBox("Прямой ток измерение: ", "Voltage : "
                            + QByteArray::number(((double)delays->fc_volt) / 1000) + " V : "
                            + QString::number(currs->forward05V, 'E', 4));

    }
    else
    {
        emit sendMessageBox("warning", "Один из портов закрыт.\n Измерение не возможно.");
    }
}
