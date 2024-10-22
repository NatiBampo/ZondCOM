#include "keysight.h"


bool Keysight::openConnection()//struct Peripherals* p)//const char* ip_address
{
    ViChar resource_string[] = "TCPIP::192.168.0.9::INSTR";
    ViAccessMode access_mode = VI_NULL;
    ViUInt32 timeout_ms      = 400;//5000
    char full_address[32];
    //if(strlen(p->ip))
    //{
        /*snprintf(full_address, 32, "%s%d.%d.%d.%d%s", "TCPIP::",
                 p->ip[0], p->ip[1], p->ip[2], p->ip[3], "::INSTR"); //"%s%s%s"
        memmove(resource_string,  full_address, strlen(full_address));*/
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
        qDebug() << "Keysight::openConnection viOpenDefaultRM fail";

        return false;
    }

    // Connect to instrument
    ViSession instrument;
    status = viOpen(resource_manager, resource_string,
                    access_mode, timeout_ms, &instrument);
    if (status < VI_SUCCESS) {
        viStatusDesc(resource_manager, status, buffer);
        qDebug() << "Keysight::openConnection viOpen fail";
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
        viStatusDesc(resource_manager, status, buffer);
        qDebug() << "Keysight::openConnection viWrite fail";
        return false;
    }

    // Read response from instrument
    // Response (identification string) should
    // look something like this
    // (depending on model):
    // "Rohde-Schwarz,ZNBT8-8Port,1318700624100104,2.70"
    status = viRead(instrument, (ViBuf) buffer, buffer_size_B, &io_bytes);
    if (status < VI_SUCCESS) {
        viStatusDesc(resource_manager, status, buffer);
        qDebug() << "Keysight::openConnection viRead fail";

        return false;
    }


    pair = new QPair<ViSession, ViSession>();
    pair->first = resource_manager;
    pair->second = instrument;


    qDebug() << "Keysight::openConnection ";
    return true;
}


void Keysight::closeConnection()
{
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
        viStatusDesc(pair->first, status, buffer);
        qDebug() << "Keysight::writePackage fail";
        return 0;
    }
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
        qDebug() << "Keysight::readResponce fail";
        viStatusDesc(pair->first, status, buffer);
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

    QString res = QString((const char*) buffer);
    return &res;
}


double Keysight::readDouble()//const char* command, int l = 0)
{

    if (!writePackage(":SENS:FUNC CURR\n:MEAS:CURR?", 0))
        return 0.0;
    // Communication buffer
    const ViUInt32 buffer_size_B = 1000;
    ViChar buffer[1000];
    ViUInt32 io_bytes;

    ViStatus status = viRead(pair->second, (ViBuf) buffer, buffer_size_B, &io_bytes);
    if (status < VI_SUCCESS)
    {
        qDebug() << "Keysight::readDouble fail";
        viStatusDesc(pair->first, status, buffer);
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

    return d1;
}


void Keysight::zeroCorrection(int delay)
{
    writePackage("*RST\n");
    writePackage( ":SYST:ZCH ON\n");
    writePackage( ":CURR:RANG 2e-9\n");
    QThread::msleep(delay);//400

    writePackage( ":INIT\n");
    QThread::msleep(delay);
    writePackage( ":SYST:ZCOR:STAT OFF\n");
    QThread::msleep(delay);
    writePackage( ":SYST:ZCOR:ACQ\n");
    writePackage( ":SYST:ZCH OFF\n");
    writePackage( ":SYST:ZCOR ON\n");

}

void Keysight::set05V(int volt = 600, int delay = 600 )
{

    writePackage( ":CURR:RANG 2e-3\n");
    writePackage( ":SOUR:VOLT:RANG 1\n");
    char full_address[32];
    snprintf(full_address, 32, ":SOUR:VOLT %de-1\n", volt/100);
    qDebug() << "Keysight::set_05V cmd:" << full_address;
    writePackage((const char*) full_address);
    writePackage( ":SOUR:VOLT:ILIM 1e-3\n");
    writePackage( ":SOUR:VOLT:STAT ON\n");
    QThread::msleep(delay);//600);
}


void Keysight::set1V(int delay)
{
    writePackage("SOUR:VOLT:STAT OFF\n");
    writePackage("SOUR:VOLT -1\n");
    writePackage("SOUR:VOLT:STAT ON\n");
    QThread::msleep(delay);
    writePackage("CURR:RANG 2e-10\n");
}

void Keysight::set10mV(int delay = 400)
{
    writePackage("SOUR:VOLT:STAT OFF\n");
    writePackage("SOUR:VOLT -1e-2\n");
    writePackage("SOUR:VOLT:STAT ON\n");
    QThread::msleep(delay);
    writePackage("CURR:RANG 2e-10\n");
}


void Keysight::darkCurrents(int dc10, int dc1, int dc05, int dc05volt)
//struct WalkSettings* walk, struct Delays* delays, struct Currents* curr)
{

    //zeroCorrection(delays->zero);
    set10mV(dc10);
    //get dark current
    dark10mV = readDouble();

    set1V(dc1);
    dark1V = readDouble();

    //get forward current
    set05V(dc05volt, dc05);
    forward05V = readDouble();
}


double Keysight::lightCurrent(int lightDelay)
{

    set10mV(400);
    QThread::msleep(lightDelay);
    //get light current
    return readDouble();
}


double Keysight::forwardCurrent(int dc05, int dc05volt)
{

//    zeroCorrection(delays->zero);
    set05V(dc05volt, dc05);
    return readDouble();
}


