#include "comport.h"


ComPort::ComPort(QSerialPort *port)
{
        qDebug() << "ComPort 1";
    m_serial = port;
    qDebug() << "ComPort 2";

}

ComPort::~ComPort()
{
    closePort();
    delete m_serial;
    delete m_port_name;
}


void ComPort::setPort(QSerialPort *port)
{
    m_serial = port;
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
    if (opened) m_port_name = comPort;
    //emit openPortResultSignal(port, portName, comPort, res);
    return opened;
}

bool ComPort::openPort(QString* portName)
{
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

