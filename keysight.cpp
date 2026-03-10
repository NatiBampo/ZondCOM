#include "keysight.h"


bool Keysight::openConnection()//struct Peripherals* p)//const char* ip_address
{
    ViChar resource_string[] = "TCPIP::192.168.0.9::INSTR";
    ViAccessMode access_mode = VI_NULL;
    ViUInt32 timeout_ms      = 5000;//5000
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


    QThread::msleep(300);


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

    //QThread::msleep(500);
    ViStatus status = viRead(pair->second, (ViBuf) buffer, buffer_size_B, &io_bytes);
    /*int k = 0;
    while (status < VI_SUCCESS || k < 5)
    {
        status = viRead(pair->second, (ViBuf) buffer, buffer_size_B, &io_bytes);
        ++k;
    }*/
    if (status < VI_SUCCESS)
    {
        qDebug() << "Keysight::readDouble fail after : ";// << k << "read attempts";
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
    writePackage(":INP:ZCOR ON\n");
    writePackage(":CURR:RANG 2e-3\n");

    QThread::msleep(delay);//400

    writePackage(":INIT\n");

    QThread::msleep(delay);

    writePackage(":INP:ZCOR:STAT OFF\n");

    QThread::msleep(delay);
    //writePackage( ":SYST:ZCOR:ACQ\n");
    //writePackage( ":SYST:ZCH OFF\n");

    writePackage(":INP:ZCOR ON\n");

}

void Keysight::set05V(int delay = 600, int mvolt = 600 )
{
    writePackage(":SOUR:VOLT:STAT ON\n");
    writePackage(":OUTP:STAT ON\n");
    writePackage(":INP:STAT ON");
    //writePackage(":CURR:RANG 2e-2\n");
    //writePackage(":SOUR:VOLT:RANG 1\n");
    char full_address[32];
    snprintf(full_address, 32, ":SOUR:VOLT -%de-1\n", mvolt/100);
    qDebug() << "Keysight::set_05V cmd:" << full_address;
    writePackage((const char*) full_address);
    //writePackage(":SOUR:VOLT:ILIM 1e-3\n");
    //writePackage(":SOUR:VOLT:STAT ON\n");
    //writePackage(":OUTP:STAT ON\n");
    //writePackage(":INP:STAT ON");
    QThread::msleep(delay);//600);
}
void Keysight::set10V(int delay = 600, int mvolt = 10000, int range = 10)
{ 
    writePackage(":SOUR:VOLT:STAT ON\n");
    writePackage(":OUTP:STAT ON\n");
    writePackage(":INP:STAT ON");
    char str[32];
    snprintf(str, 32, ":SOUR:VOLT %de-3\n", mvolt);
    qDebug() << "Keysight::set_10v cmd:" << str;
    writePackage((const char*) str);
}

void Keysight::set1V(int delay, int mvolt = 1000, int range = 10)
{
    //writePackage("SOUR:VOLT:STAT OFF\n");
    writePackage("*RST\n");
    writePackage(":OUTP:STAT OFF\n");
    writePackage(":INP:STAT OFF");
    if (mvolt == 1000){
        writePackage("SOUR:VOLT 1\n");}
    else {
        char str[32];
        snprintf(str, 32, ":SOUR:VOLT %de-3\n", mvolt);
        qDebug() << "Keysight::set_1v cmd:" << str;
        writePackage((const char*) str);

    }
    //writePackage("SOUR:VOLT:STAT ON\n");
    writePackage(":OUTP:STAT ON\n");
    writePackage(":INP:STAT ON");

    QThread::msleep(delay);
    if (mvolt == 1000){
        writePackage("CURR:RANG 1e-10\n");
    }
    else {
        char str[32];
        snprintf(str, 32, "CURR:RANG 1e-%d\n", range);
        qDebug() << "Keysight::curr_range cmd:" << str;
        writePackage((const char*) str);
    }
}

void Keysight::set10mV(int delay = 400, int mvolt = 10)
{
    //writePackage("SOUR:VOLT:STAT OFF\n");
    writePackage("*RST\n");

    writePackage(":OUTP:STAT OFF\n");
    writePackage(":INP:STAT OFF");
    if (mvolt==10) {
        writePackage("SOUR:VOLT 1e-2\n");
    }
    else{
        char str[32];
        snprintf(str, 32, ":SOUR:VOLT %de-3\n", mvolt);
        qDebug() << "Keysight::set_10mv cmd:" << str;
        writePackage((const char*) str);

    }
    //writePackage("SOUR:VOLT:STAT ON\n");
    writePackage(":OUTP:STAT ON\n");
    writePackage(":INP:STAT ON");
    QThread::msleep(delay);
    //writePackage("CURR:RANG 2e-10\n");
}

void Keysight::darkCurrents(int fcdelay, int dc1delay, int dc2delay, int fcvolt, int dc1volt, int dc2volt, int dc2range )
{

    forward05V = forwardCurrent(fcdelay, fcvolt);

    set10mV(dc1delay, dc1volt);
    //get dark current
    dark10mV = readDouble();


    set1V(dc2delay, dc2volt, dc2range);
    dark1V = readDouble();
}

double Keysight::lightCurrent(int delay, int mvolt)
{

    set10mV(delay, mvolt);
    QThread::msleep(delay);
    //get light current
    double res = readDouble();

    return res;

}


double Keysight::forwardCurrent(int delay, int mvolt)
{

    set05V(delay, mvolt);
    QThread::msleep(300);
    //sourceOff();
    double res = readDouble();
    if (res > (-1) * pow(10,-4))
    {
        set10V(delay, 10000);
        //QThread::msleep(300);
        set05V(delay, mvolt);
        //QThread::msleep(300);
        res = readDouble();

    }
    sourceOff();
    return res;
}


void Keysight::sourceOff()
{
    writePackage(":OUTP:STAT OFF\n");
    writePackage(":INP:STAT OFF\n");
}

