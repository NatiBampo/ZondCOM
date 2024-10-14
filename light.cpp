#include "light.h"


Light::Light(QSerialPort *port) : ComPort(port)
{
    m_rate = QSerialPort::Baud9600;
}


bool Light::parsePort(QString com_name, struct Peripherals* periph)
{
    if (working) return true;
    for (int i = 0; i < 5; i++)
    {
        try
        {
            openPort(&com_name);
            //on(nullptr);
            sendPackageRead("1111\r\n", ANSWER_DELAY);

            //emit sendLogSignal(lastAnswer);
            if (lastAnswer.contains("C3B2A1") ||
                    lastAnswer.contains("A1B2C3"))
            {
                working = true;
                //off(nullptr);
                sendPackage("0001\r\n", NO_ANSWER_DELAY);

                periph->light_com = &com_name;
                periph->light_open = working;

                return working;
            }
            //off(nullptr);
            sendPackage("0001\r\n", NO_ANSWER_DELAY);
        }
        catch (QSerialPort::SerialPortError error)
        {
            qDebug() << error;
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
    if (m_serial->isOpen() && walk->keithley_status)
    {
        sendPackage(msg, NO_ANSWER_DELAY);
    }
    else
    {
        //emit sendMessageBox("warning", "Порт диода закрыт.\n Отправка комманды не работает");
        qWarning(logWarning()) << "Порт диода закрыт. Отправка комманды не работает.\r\n";
    }

}
