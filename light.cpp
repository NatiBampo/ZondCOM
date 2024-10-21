#include "light.h"


Light::Light(struct Peripherals* periph)
{
    m_serial = new ComPort(QSerialPort::Baud9600);
    periph->light = m_serial->getPort();
    qDebug() << "light";
    connect(this, &Light::sendPackageSignal, m_serial, &ComPort::sendPackage);
    connect(this, &Light::sendPackageReadSignal, m_serial, &ComPort::sendPackageRead);
    qDebug() << "light connected sending";
}



bool Light::openPort(QSerialPort *port, QString* comPort,
                 QSerialPort::BaudRate baudRate)
{
    return m_serial->openPort(port, comPort,baudRate);
}

bool Light::openPort(QString *comPort)
{
    return m_serial->openPort(comPort);
}


void Light::setPort(QSerialPort* port)
{
    m_serial->setPort(port);
}

void Light::closePort()
{
    m_serial->closePort();
}

bool Light::parsePort(QString com_name, struct Peripherals* periph)
{
    if (working) return true;
    if (!m_serial->isOpen()) openPort(&com_name);
    for (int i = 0; i < 5; i++)
    {
        try
        {
            //openPort(&com_name);
            //on(nullptr);
            sendPackageReadSignal("1111\r\n", ANSWER_DELAY);

            //emit sendLogSignal(m_serial->lastAnswer);
            if (m_serial->lastAnswer.contains("C3B2A1") ||
                    m_serial->lastAnswer.contains("A1B2C3"))
            {
                working = true;
                //off(nullptr);
                sendPackageSignal("0001\r\n", NO_ANSWER_DELAY);

                periph->light_com = &com_name;
                periph->light_open = working;

                return working;
            }
            //off(nullptr);
            sendPackageSignal("0001\r\n", NO_ANSWER_DELAY);
        }
        catch (QSerialPort::SerialPortError error)
        {
        }
    }
    return false;
}


void Light::on(struct WalkSettings* walk)
{
    lightController("1111\r\n", walk);
}


void Light::off(struct WalkSettings* walk)
{
    lightController("0001\n", walk);
}


void Light::lightController(QByteArray msg,
                            struct WalkSettings* walk)
{
    if (walk->light_status && m_serial->isOpen())
    {
        sendPackageSignal(msg, NO_ANSWER_DELAY);
    }
    else
    {
        //emit sendMessageBox("warning", "Порт диода закрыт.\n Отправка комманды не работает");
        qWarning(logWarning()) << "Порт диода закрыт. Отправка комманды не работает.\r";
    }

}
