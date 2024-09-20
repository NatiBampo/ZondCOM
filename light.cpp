#include "light.h"


Light::Light(){}


Light::~Light()
{
    serialPortLight->close();
    delete serialPortLight;
}


bool Light::parsePort(QSerialPort *port, QString* com_name)
{
    for (int i = 0; i < 5; i++)
    {
        try
        {
            on();
            if (serial->waitForReadyRead(1000))
                lastAnswer.append(serial->readAll());
            //emit sendLogSignal(lastAnswer);
            if (lastAnswer.contains("C3B2A1") ||
                    lastAnswer.contains("A1B2C3"))
            {
                off();
                serialPortLight = port;
                port_name = *com_name;
                return true;
            }
            off();
        }
        catch (QSerialPort::SerialPortError error)
        {
            qDebug() << error;
        }
    }
    return false;
}

void Light::on()
{
    lightController("1111\r\n");
}

void Light::off()
{
    lightController("0001\n");
}

void Light::lightController(QByteArray msg)
{
    if (serialPort->isOpen())
    {
        emit sendPackageSignal(serialPortLight, msg, NO_ANSWER_DELAY);
    }
    else
    {
        emit sendMessageBox("warning", "Порт диода закрыт.\n Отправка комманды не работает");
        qWarning(logWarning()) << "Порт диода закрыт. Отправка комманды не работает.\r\n";
    }

}
