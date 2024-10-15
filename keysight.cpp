#include "keysight.h"

Keysight::Keysight(QSerialPort* serial) : Meter(serial)
{
    qDebug() << "Keysight1";

}

bool Keysight::openConnection(struct Peripherals* p)//const char* ip_address
{
    ViChar resource_string[] = "TCPIP::192.168.0.9::INSTR";
    ViAccessMode access_mode = VI_NULL;
    ViUInt32 timeout_ms      = 400;//5000
    char full_address[32];
    //if(strlen(p->ip))
    //{
        snprintf(full_address, 32, "%s%d.%d.%d.%d%s", "TCPIP::",
                 p->ip[0], p->ip[1], p->ip[2], p->ip[3], "::INSTR"); //"%s%s%s"
        qDebug() << full_address;
        memmove(resource_string,  full_address, strlen(full_address));
    ///}
    // Communication buffer
    const ViUInt32 buffer_size_B = 1000;
    ViChar buffer[1000];
    ViUInt32 io_bytes;

    // Get VISA resource manager
    ViSession resource_manager;
    ViStatus  status;
    status = viOpenDefaultRM(&resource_manager);

    if (status < VI_SUCCESS) {
        qDebug() << "Could not open VISA resource manager";
        return false;
    }

    // Connect to instrument
    ViSession instrument;
    status = viOpen(resource_manager, resource_string,
                    access_mode, timeout_ms, &instrument);
    if (status < VI_SUCCESS) {
        qDebug() << "Error connecting to instrument";
        viStatusDesc(resource_manager, status, buffer);
        qDebug() <<  buffer;
        return false;
    }

    // Set timeout on instrument io
    viSetAttribute(instrument, VI_ATTR_TMO_VALUE, timeout_ms);

    // Set term char
    // viSetAttribute(instrument, VI_ATTR_TERMCHAR_EN, '\n');

    // Write *IDN? (id string?)
    ViBuf scpi_command = (ViBuf) "*IDN?";
    status = viWrite(instrument, scpi_command,
                     (ViUInt32)strlen( (const char*) scpi_command),
                     &io_bytes);
    if (status < VI_SUCCESS) {
        qDebug() << "Error writing to instrument";
        viStatusDesc(resource_manager, status, buffer);
        qDebug() << buffer;
        return false;
    }

    // Read response from instrument
    // Response (identification string) should
    // look something like this
    // (depending on model):
    // "Rohde-Schwarz,ZNBT8-8Port,1318700624100104,2.70"
    status = viRead(instrument, (ViBuf) buffer, buffer_size_B, &io_bytes);
    if (status < VI_SUCCESS) {
        qDebug() << "Error reading from instrument";
        viStatusDesc(resource_manager, status, buffer);
        qDebug() <<  buffer;
        return false;
    }


    pair = new QPair<ViSession, ViSession>();
    pair->first = resource_manager;
    pair->second = instrument;

    status = true;
    qDebug() << "success!!!";
    return status;
}


void Keysight::closeConnection()
{
    qDebug() << "Keysight::closeConnection()";
    if (!pair->first)
        return;
    viClose(pair->first);
    viClose(pair->second);

    //status = false;

}

int Keysight::writePackage(const char* command, int l = 0)
{
    // Communication buffer
    //const ViUInt32 buffer_size_B = 1000;
    ViChar buffer[1000];
    ViUInt32 io_bytes;

    ViBuf scpi_command = (ViBuf) command;
    ViStatus status = viWrite(pair->second, scpi_command,
                              (ViUInt32)strlen( (const char*) scpi_command),
                              &io_bytes);
    if (status < VI_SUCCESS) {
        qDebug() << "Error writing to instrument";
        viStatusDesc(pair->first, status, buffer);
        qDebug() <<  buffer;
        return 0;
    }
    qDebug() << "writePackage success" << command;
    return 1;
}


QString* Keysight::readResponce(const char* cmd, int l = 0)
{
    //const char* command = ":SENS:FUNC CURR\n:MEAS:CURR?";
    if (!writePackage(cmd, l))
        return nullptr;
    // Communication buffer
    const ViUInt32 buffer_size_B = 1000;
    ViChar buffer[1000];
    ViUInt32 io_bytes;

    ViStatus status = viRead(pair->second, (ViBuf) buffer, buffer_size_B, &io_bytes);
    if (status < VI_SUCCESS)
    {
        qDebug() << "Error reading from instrument";
        viStatusDesc(pair->first, status, buffer);
        qDebug() <<  buffer;
        return 0;
    }
    // Response is not null-terminated.
    // Add '\0' at end.
    if (io_bytes < buffer_size_B)
    {
        buffer[io_bytes] = '\0';
    }
    else
    {
        buffer[buffer_size_B] = '\0';
    }
    qDebug() << "read_responce success";
    // return response

    QString res = QString((const char*) buffer);
    return &res;
}


double Keysight::readDouble(const char* command, int l = 0)
{

    if (!writePackage(command, l))
        return 0.0;
    // Communication buffer
    const ViUInt32 buffer_size_B = 1000;
    ViChar buffer[1000];
    ViUInt32 io_bytes;

    ViStatus status = viRead(pair->second, (ViBuf) buffer, buffer_size_B, &io_bytes);
    if (status < VI_SUCCESS)
    {
        qDebug() << "Error reading from instrument";
        viStatusDesc(pair->first, status, buffer);
        qDebug() <<  buffer;
        return 0;
    }
    // Response is not null-terminated.
    // Add '\0' at end.
    if (io_bytes < buffer_size_B)
    {
        buffer[io_bytes] = '\0';
    }
    else
    {
        buffer[buffer_size_B] = '\0';
    }

    // return response
    char* pEnd;
    double d1;
    d1 = strtod ((char*)buffer, &pEnd);

    qDebug() << "read double end";
    return d1;
}


void Keysight::zeroCorrection(int delay)
{
    qDebug() << "zero begin";
    writePackage("*RST\n");
    writePackage( ":SYST:ZCH ON\n");
    writePackage( ":CURR:RANG 2e-9\n");
    qDebug() << "delay start " << delay;
    QThread::msleep(delay);//400
    qDebug() << "delay end " << delay;

    writePackage( ":INIT\n");
    QThread::msleep(delay);
    writePackage( ":SYST:ZCOR:STAT OFF\n");
    QThread::msleep(delay);
    writePackage( ":SYST:ZCOR:ACQ\n");
    writePackage( ":SYST:ZCH OFF\n");
    writePackage( ":SYST:ZCOR ON\n");
    qDebug() << "zero end";

}

void Keysight::set05V(int volt, int delay)
{
    qDebug() << "set_05V begin";

    delay = delay? delay : 6;
    writePackage( ":CURR:RANG 2e-3\n");
    writePackage( ":SOUR:VOLT:RANG 1\n");
    char full_address[32];
    snprintf(full_address, 32, ":SOUR:VOLT %d-1\n", volt);
    writePackage((const char*) full_address);
    writePackage( ":SOUR:VOLT:ILIM 1e-3\n");
    writePackage( ":SOUR:VOLT:STAT ON\n");
    QThread::msleep(delay);//600);
    qDebug() << "set_05V end";
}


void Keysight::set1V(int delay)
{
    qDebug() << "set_1V begin";
    writePackage("SOUR:VOLT:STAT OFF\n");
    writePackage("SOUR:VOLT -1\n");
    writePackage("SOUR:VOLT:STAT ON\n");
    QThread::msleep(delay);
    writePackage("CURR:RANG 2e-10\n");
    qDebug() << "set_1V end";
}

void Keysight::set10mV(int delay)
{
    qDebug() << "set_10mV begin";
    writePackage("SOUR:VOLT:STAT OFF\n");
    writePackage("SOUR:VOLT -1e-2\n");
    writePackage("SOUR:VOLT:STAT ON\n");
    writePackage("CURR:RANG 2e-10\n");
    QThread::msleep(delay);
    qDebug() << "set_10mV end";
}


void Keysight::darkCurrents(struct WalkSettings* walk,
                            struct Delays* delays,
                            struct Currents* curr)
{
    qDebug() << "settings->dc_10mV" << delays->dc_10mV;
    qDebug() << "settings->dc_1V" << delays->dc_1V;
    qDebug() << "settings->fc" << delays->fc;
    qDebug() << "settings->light" << delays->light;
    qDebug() << "settings->fc_volt" << delays->fc_volt;

    zeroCorrection(delays->zero);
    set10mV(delays->dc_10mV);
    //get dark current
    curr->dark10mV = readDouble(":SENS:FUNC CURR\n:MEAS:CURR?");

    set1V(delays->dc_1V);
    curr->dark1V = readDouble(":SENS:FUNC CURR\n:MEAS:CURR?");

    //get forward current
    set05V(delays->fc, delays->fc_volt);
    curr->forward05V = readDouble(":SENS:FUNC CURR\n:MEAS:CURR?");
}


void Keysight::lightCurrent(struct WalkSettings* walk,
                            struct Delays* delays,
                            struct Currents* curr)
{
    if (walk->keithley_status)
        return;
    qDebug() << "light begin";

    set10mV(delays->light);
    //get light current
    curr->light10mV = readDouble(":SENS:FUNC CURR\n:MEAS:CURR?");
}


double Keysight::forwardCurrent(struct Delays* delays)
{
    zeroCorrection(delays->zero);
    set05V(delays->fc_volt, delays->fc);
    return readDouble(":SENS:FUNC CURR\n:MEAS:CURR?", 1);
}


bool Keysight::parsePort(QString, struct Peripherals*)
{return false;}
