#include "keithley.h"


Keithley::Keithley(){}

Keithley::~Keithley()
{
    delete serial;
}


bool Keithley::parsePort(Qserial *port, QString* com_name)
{
    try
    {

        QString* responce = read_responce();
        if (responce->contains(QRegularExpression(R"(\d+A,)")))
        {

            return true;//\d+.\d+[+-]\d+A,
        }
    }
    catch (const char* error){}
    return false;
}


void Keithley::zeroCorrection(int delay)
{
    sendPackage(serial, "*RST\n", NO_ANSWER_DELAY);
    sendPackage(serial, "SYST:ZCH ON\n", NO_ANSWER_DELAY);
    sendPackage(serial, "CURR:RANG 2e-9\n", NO_ANSWER_DELAY);
    QThread::msleep(delay);//400
    sendPackage(serial, "INIT\n", NO_ANSWER_DELAY);
    QThread::msleep(delay);
    sendPackage(serial, "SYST:ZCOR:STAT OFF\n", NO_ANSWER_DELAY);
    QThread::msleep(delay);
    sendPackage(serial, "SYST:ZCOR:ACQ\n", NO_ANSWER_DELAY);
    sendPackage(serial, "SYST:ZCH OFF\n", NO_ANSWER_DELAY);
    sendPackage(serial, "SYST:ZCOR ON\n", NO_ANSWER_DELAY);
}


void Keithley::set_05V(int FCVoltage, int delay)
{
    sendPackage(serial, "CURR:RANG 2e-3\n", NO_ANSWER_DELAY);
    sendPackage(serial, "SOUR:VOLT:RANG 1\n", NO_ANSWER_DELAY);
    QByteArray tmp = QByteArray::number(((double)FCVoltage) / 10);
    sendPackage(serial, "SOUR:VOLT " + tmp + '\n', NO_ANSWER_DELAY);
    sendPackage(serial, "SOUR:VOLT:ILIM 1e-3\n", NO_ANSWER_DELAY);
    sendPackage(serial, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
    QThread::msleep(FCdelay);
}


void Keithley::set_10mV(int delay)
{
   sendPackage(serial, "SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
   sendPackage(serial, "SOUR:VOLT -1e-2\n", NO_ANSWER_DELAY);
   sendPackage(serial, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
   QThread::msleep(delay);
    sendPackage(serial, "CURR:RANG 2e-10\n", NO_ANSWER_DELAY);
}

void Keithley::set_1V(int delay)
{
    emit sendPackageSignal(serial, "SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serial, "SOUR:VOLT -1\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serial, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
    QThread::msleep(delay);
}

double Keithley::read_double()
{
    emit sendPackageSignalRead(serial, "READ?\n", ANSWER_DELAY);
    QByteArray byteArray = lastAnswer;
    byteArray = byteArray.remove(byteArray.indexOf("A"),
                                 byteArray.length() - byteArray.indexOf("A"));
    return byteArray.toDouble();
}

QString* Keithley::read_responce()
{
    emit sendPackageSignal(serial, "READ?\n", ANSWER_DELAY);
    return &lastAnswer;
}

void Keithley::dark_currents(struct WalkSettings* walk,
                             struct Delays* delays,
                             struct Currents* curr)
{
    QThread::msleep(200);//800
    meter->darkCurrents(walk, delays, curr);
    set_10mV(delays->dc_10mV);
    QThread::msleep(delays->dc_10mV);//800
    curr->dark10mV = read_double();
    set_1V(delays->dc_1V);
    curr->dark1V = read_double();
    set_05V(delays->fc_volt, delays->fc);
    curr->forward05V = read_double();
}

void Keithley::light_current(struct WalkSettings* walk,
                             struct Delays* delays,
                             struct Currents* curr)
{
    set_10mV(delays->light);
    emit sendPackageSignal(periph->keithley, "CURR:RANG 2e-6\n", NO_ANSWER_DELAY);
    QThread::msleep(delays->light);//200
    curr->light10mV = read_double();
}
