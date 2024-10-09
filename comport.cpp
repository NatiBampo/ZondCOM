#include "comport.h"


ComPort::ComPort(QSerialPort *port)
{
    m_serial = port;
}

ComPort::~ComPort()
{
    closePort();
    delete m_rate;
    delete m_serial;
    delete m_port_name;
}

void ComPort::setPort(QSerialPort *port)
{
    m_serial = port;
}


bool ComPort::openPort(QSerialPort *port, QString* comPort,
                         QString* portName, QSerialPort::BaudRate baudRate)
{
    port->setPortName(*comPort);
    port->setBaudRate(baudRate);
    port->setDataBits(QSerialPort::DataBits::Data8);
    port->setStopBits(QSerialPort::StopBits::OneStop);
    port->setParity(QSerialPort::Parity::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);

    bool res = port->open(QSerialPort::ReadWrite);
    //emit openPortResultSignal(port, portName, comPort, res);
    return res;
}

bool ComPort::openPort(QString portName)
{
    m_serial->setPortName(portName);
    //m_serial->setBaudRate(baudRate);
    m_serial->setDataBits(QSerialPort::DataBits::Data8);
    m_serial->setStopBits(QSerialPort::StopBits::OneStop);
    m_serial->setParity(QSerialPort::Parity::NoParity);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    return port->open(QSerialPort::ReadWrite);
}


void ComPort::closePort()
{
    if (m_serial->isOpen())
        m_serial->close();
}


void ComPort::sendPackage(QByteArray package, int delay)
{
    m_serial->write(package);
    m_serial->flush();
    m_serial->waitForBytesWritten(delay);//delay
}


void ComPort::sendPackageRead (QByteArray package, int delay)
{
    lastAnswer = "";
    m_serial->write(package);
    m_serial->flush();
    m_serial->waitForBytesWritten(delay);
    if (m_serial->waitForReadyRead(delay)) lastAnswer.append(m_serial->readAll());
}


//актуализировать
/*void ComPort::autoOpen(struct Peripherals* periph)
{
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
*/


