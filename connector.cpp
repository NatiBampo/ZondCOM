#include "connector.h"


Connector::Connector(struct Peripherals* periph)
{
    qDebug() << "Connector 1";
    periph->planar = new QSerialPort();
    periph->keithley = new QSerialPort();
    periph->light = new QSerialPort();
    qDebug() << "Connector 2";
    planar = new Planar(periph->planar);
    qDebug() << "Connector 2.5";
    light = new Light(periph->light);
    qDebug() << "Connector 3";
    kith = new Keithley(periph->keithley);
    qDebug() << "Connector 4";
    Keysight* key = new Keysight(periph->keithley);
    meter = periph->lan? static_cast<Meter*>(key) : static_cast<Meter*>(kith);
}


Connector::~Connector()
{
    delete planar;
    delete light;
    delete meter;
}

void Connector::openPorts(struct Peripherals* periph)
{
    qDebug() << "openPorts 1";
    closePorts();
    if (planar->openPort(periph->planar, periph->planar_com,
                          QSerialPort::Baud115200))
        planar->setPort(periph->planar);
    qDebug() << "openPorts 2";

    if (light->openPort(periph->light, periph->light_com,
                          QSerialPort::Baud9600))
        light->setPort(periph->light);
    qDebug() << "openPorts 3";

    if (!periph->lan)
    {
        qDebug() << " chepuha " << periph->lan;
        meter = new Keithley(periph->keithley);
    }
    else
    {
        if(meter) delete meter;
        meter = new Keysight(periph->keithley);
    }
    qDebug() << "openPorts 4";
    periph->meter = meter->openConnection(periph);

    qDebug() << "openPorts 5";
    emit portsReadySignal();
}


void Connector::parsePorts(struct Peripherals* periph)
{
    if (meter) delete meter;
    if (periph->lan)
    {
        meter = new Keysight(periph->keithley);
        meter->openConnection(periph);
    }
    else
    {
        if (!kith)
            kith = new Keithley(periph->keithley);//
    }


    foreach(const QSerialPortInfo &port,  QSerialPortInfo::availablePorts())
    {
        planar->parsePort(port.portName(), periph);
        light->parsePort(port.portName(), periph);
        if (!periph->lan)
            kith->parsePort(port.portName(), periph);
    }
    if(kith) meter = kith;

    emit portsReadySignal();
}


void Connector::closePorts()
{
    qDebug() << "closePorts 1";
    meter->closeConnection();
        qDebug() << "closePorts 2";
    planar->closePort();
        qDebug() << "closePorts 3";
    light->closePort();
        qDebug() << "closePorts 4";
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


void Connector::sendLog(QByteArray msg)
{
    emit sendLogSignal(msg);
}

void Connector::sendMessageBox(QString msgtype, QString msg)
{
    emit sendMessageBoxSignal(msgtype, msg);
}

/*void Connector::sendProgessRange(int, int);

{
    emit sendProgressSignal(msgtype, msg);
}*/


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
            planar->up(walk);
        if (walk->keithley_status)
            meter->darkCurrents(walk, delays, currs);
        //lightController("1111\n", walk->light_status);
        light->on(walk);

        meter->lightCurrent(walk, delays, currs);

        sendLog((QString::number(currs->currentIndex) + ", "
                            + QString::number(currs->forward05V, 'E', 4) + ", "
                            + QString::number(currs->dark10mV, 'E', 4) + ", "
                            + QString::number(currs->dark1V, 'E', 4) + ", "
                            + QString::number(currs->light10mV, 'E', 4)).toUtf8());

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
