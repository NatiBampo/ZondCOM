#include "comport.h"


ComPort::ComPort(QSerialPort::BaudRate rate)
{
    m_serial = new QSerialPort();
    m_rate = rate;
    qDebug() << "ComPort";

}

ComPort::~ComPort()
{
    //closePort();
    delete m_serial;
    delete m_port_name;
}


void ComPort::setPort(QSerialPort *port)
{
    m_serial = port;
}



QSerialPort* ComPort::getPort()
{
    return m_serial;
}

bool ComPort::openPort(QSerialPort *port, QString* comPort,
                       QSerialPort::BaudRate baudRate)
{
    port->setPortName(*comPort);
    port->setBaudRate(baudRate);
    port->setDataBits(QSerialPort::DataBits::Data8);
    port->setStopBits(QSerialPort::StopBits::OneStop);
    port->setParity(QSerialPort::Parity::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);

    opened = port->open(QSerialPort::ReadWrite);
    if (opened)
    {
        m_port_name = comPort;
        working = true;
    }
    //emit openPortResultSignal(port, portName, comPort, res);
    return opened;
}

bool ComPort::openPort(QString* portName)
{
    if (!m_serial){ qDebug() << "ComPort::openPort |serial does not exist"; return false;}

    m_serial->setPortName(*portName);
    m_serial->setBaudRate(m_rate);
    m_serial->setDataBits(QSerialPort::DataBits::Data8);
    m_serial->setStopBits(QSerialPort::StopBits::OneStop);
    m_serial->setParity(QSerialPort::Parity::NoParity);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    return m_serial->open(QSerialPort::ReadWrite);
}


void ComPort::closePort()
{
    if (m_serial != nullptr && m_serial->isOpen())
        m_serial->close();

}


bool ComPort::isOpen()
{
    return m_serial->isOpen();
}

void ComPort::sendPackage(QByteArray package, int delay)
{
    if (m_serial == nullptr)
    {
        qDebug() << "ComPort::sendPackage ";
        return ;
    }
    if (!m_serial->isOpen()) return;
    m_serial->write(package);
    m_serial->flush();
    m_serial->waitForBytesWritten(delay);//delay
}


void ComPort::sendPackageRead (QByteArray package, int delay)
{
    if (!m_serial->isOpen()) return;

    lastAnswer = "";
    m_serial->write(package);
    m_serial->flush();
    m_serial->waitForBytesWritten(delay);
    if (m_serial->waitForReadyRead(delay)) lastAnswer.append(m_serial->readAll());

}

