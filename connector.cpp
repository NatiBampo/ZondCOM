#include "connector.h"


Connector::Connector(struct Peripherals* periph)
{

    planar = new Planar(periph);
    qDebug() << "Connector" << " planar";

    light = new Light(periph);
    qDebug() << "Connector" << " Light";

    //kith = new Keithley(periph->keithley);
    //qDebug() << "Connector" << " kith";
    //key = new Keysight(periph->keithley);
    //qDebug() << "Connector" << " key";
    //meter = periph->lan? static_cast<Meter*>(key) : static_cast<Meter*>(kith);
//    qDebug() << "Connector" << " Meter";
}


Connector::~Connector()
{
    delete planar;
    delete light;
    delete meter;
    delete kith;
    delete key;
}

void Connector::openPorts(struct Peripherals* periph)
{
    //closePorts();
    if (planar->openPort(periph->planar, periph->planar_com,
                          QSerialPort::Baud115200))
        planar->setPort(periph->planar);

    if (light->openPort(periph->light, periph->light_com,
                          QSerialPort::Baud9600))
        light->setPort(periph->light);

    if (meter!=nullptr) delete meter;
    if (!periph->lan)
    {
        if (kith == nullptr) kith = new Keithley(periph);
        meter = kith;
    }
    else
    {
        if (key == nullptr) key = new Keysight();

        meter = key;//
    }

    if (kith)
    {
        //connect(kith, &Keithley::sendPackageReadSignal,
        //kith->parent()->parent(), &ComPort::sendPackageRead);

    }

    qDebug() << "Connector::openPorts meter->openConnection(periph);";
    periph->meter = meter->openConnection(periph);

    qDebug() << "Connector::openPorts portsReadySignal";

    emit portsReadySignal();

}



void Connector::parsePorts(struct Peripherals* periph)
{

    if (meter) delete meter;
    qDebug() << " Connector::parsePorts 1";
    if (periph->lan)
    {
        if (key!=nullptr) key = new Keysight();
        meter = key;
        meter->openConnection(periph);
    }
    else
    {
        if (!kith) kith = new Keithley(periph);//
    }

    qDebug() << " Connector::parsePorts 2";

    foreach(const QSerialPortInfo &port,  QSerialPortInfo::availablePorts())
    {
        planar->parsePort(port.portName(), periph);
        light->parsePort(port.portName(), periph);

        if (!periph->lan)
            qDebug() << " Connector::parsePorts 3";
            kith->parsePort(port.portName(), periph);
    }

    if(kith) meter = kith;
    qDebug() << " Connector::parsePorts 4";
    emit portsReadySignal();
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
        //emit sendPackageSignalRead(periph->serialPortA5, "Table UP\r\n", 200);
        if (walk->planar_status) planar->up(walk);

        meter->zeroCorrection(delays->zero);

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

void Connector::measureFC(struct WalkSettings* walk,
                          struct Delays* delays,
                          struct Currents* currs,
                          struct Dots* dots)
{
    if (walk->keithley_status)
    {
        if (walk->planar_status)
        {
            planar->goToDot(walk, dots);
            planar->up(walk);
        }
        if (walk->keithley_status)
        {
            meter->zeroCorrection(delays->zero);
            currs->forward05V = meter->forwardCurrent(delays);


        }
        if (walk->planar_status)
            planar->down(walk);
        emit sendMessageBox("Прямой ток измерение: ", "Voltage : "
                            + QByteArray::number(((double)delays->fc_volt) / 1000) + " V : "
                            + QString::number(currs->forward05V, 'E', 4));

    }
    else
    {
        emit sendMessageBox("warning", "Один из портов закрыт.\n Измерение не возможно.");
    }
}
