#include "keithley.h"


Keithley::Keithley(QSerialPort* serial) : Meter(serial)
{
    qDebug() << "Keithley 1";
    m_rate =  QSerialPort::Baud57600;
    qDebug() << "Keithley 2";
}

Keithley::~Keithley()
{}


bool Keithley::openConnection(struct Peripherals* p)
{
    bool res = ComPort::openPort(p->keithley_com);
    p->meter = res;
    return res;
}

void Keithley::closeConnection()
{
    qDebug() << "Keithley::closeConnection()";
    return ComPort::closePort();
}

int Keithley::writePackage(const char * cmd, int l = 0)
{
    sendPackage(QByteArray(cmd), NO_ANSWER_DELAY);
}


bool Keithley::parsePort(QString com_name, struct Peripherals* periph)
{
    if (periph->meter)
        return true;
    try
    {
        if (!ComPort::openPort(&com_name))
            return false;
        lastAnswer = *readResponce("READ?\n", 1);
        if (lastAnswer.contains(QRegularExpression(R"(\d+A,)")))
        {
            periph->meter = true;
            return true;//\d+.\d+[+-]\d+A,
        }
    }
    catch (const char* error){}
    return false;
}


void Keithley::zeroCorrection(int delay)
{
    sendPackage("*RST\n", NO_ANSWER_DELAY);
    sendPackage("SYST:ZCH ON\n", NO_ANSWER_DELAY);
    sendPackage("CURR:RANG 2e-9\n", NO_ANSWER_DELAY);
    QThread::msleep(delay);//400
    sendPackage("INIT\n", NO_ANSWER_DELAY);
    QThread::msleep(delay);
    sendPackage("SYST:ZCOR:STAT OFF\n", NO_ANSWER_DELAY);
    QThread::msleep(delay);
    sendPackage("SYST:ZCOR:ACQ\n", NO_ANSWER_DELAY);
    sendPackage("SYST:ZCH OFF\n", NO_ANSWER_DELAY);
    sendPackage("SYST:ZCOR ON\n", NO_ANSWER_DELAY);
}


void Keithley::set05V(int FCVoltage, int delay)
{
    sendPackage("CURR:RANG 2e-3\n", NO_ANSWER_DELAY);
    sendPackage("SOUR:VOLT:RANG 1\n", NO_ANSWER_DELAY);
    QByteArray tmp = QByteArray::number(((double)FCVoltage) / 1000);
    sendPackage("SOUR:VOLT " + tmp + '\n', NO_ANSWER_DELAY);
    sendPackage("SOUR:VOLT:ILIM 1e-3\n", NO_ANSWER_DELAY);
    sendPackage("SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
    QThread::msleep(delay);
}


void Keithley::set10mV(int delay)
{
   sendPackage("SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
   sendPackage("SOUR:VOLT -1e-2\n", NO_ANSWER_DELAY);
   sendPackage("SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
   QThread::msleep(delay);
    sendPackage("CURR:RANG 2e-10\n", NO_ANSWER_DELAY);
}

void Keithley::set1V(int delay)
{
    sendPackage("SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
    sendPackage("SOUR:VOLT -1\n", NO_ANSWER_DELAY);
    sendPackage("SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
    QThread::msleep(delay);
}

double Keithley::readDouble(const char * cmd, int l = 0)
{
    sendPackageRead( "READ?\n", ANSWER_DELAY);
    QByteArray byteArray = lastAnswer.toUtf8();
    byteArray = byteArray.remove(byteArray.indexOf("A"),
                                 byteArray.length() - byteArray.indexOf("A"));
    return byteArray.toDouble();
}


QString* Keithley::readResponce(const char * cmd, int l = 0)
{
    sendPackage("READ?\n", ANSWER_DELAY);
    return &lastAnswer;
}

void Keithley::darkCurrents(struct WalkSettings* walk,
                             struct Delays* delays,
                             struct Currents* curr)
{
    if (!walk->keithley_status)
        return;

    QThread::msleep(200);//800
    set10mV(delays->dc_10mV);
    QThread::msleep(delays->dc_10mV);//800
    curr->dark10mV = readDouble("READ?\n", 1);
    set1V(delays->dc_1V);
    curr->dark1V = readDouble("READ?\n", 1);
    set05V(delays->fc_volt, delays->fc);
    curr->forward05V = readDouble("READ?\n",1);
}

void Keithley::lightCurrent(struct WalkSettings* walk,
                             struct Delays* delays,
                             struct Currents* curr)
{
    set10mV(delays->light);
    sendPackage("CURR:RANG 2e-6\n", NO_ANSWER_DELAY);
    QThread::msleep(delays->light);//200
    curr->light10mV = readDouble("READ?\n",1);
}


double Keithley::forwardCurrent(struct Delays* delays)
{
    zeroCorrection(delays->zero);
    set05V(delays->fc_volt, delays->fc);
    return readDouble("READ?\n", 1);
}
