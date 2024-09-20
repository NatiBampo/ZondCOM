#include "keysight.h"

Keysight_handler::Keysight_handler() : Meter()
{
}

int Keysight_handler::open_connection(const char* ip_address)
{
    // Connection info
    ViChar resource_string[] = "TCPIP::192.168.0.9::INSTR";
    ViAccessMode access_mode = VI_NULL;
    ViUInt32 timeout_ms      = 400;//5000
    char full_address[32];
    if(strlen(ip_address))
    {
        snprintf(full_address, 32, "%s%s%s", "TCPIP::",
                 ip_address, "::INSTR");
        qDebug() << full_address;
        memmove(resource_string,  full_address, strlen(full_address));
    }
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
        return 0;
    }

    // Connect to instrument
    ViSession instrument;
    status = viOpen(resource_manager, resource_string,
                    access_mode, timeout_ms, &instrument);
    if (status < VI_SUCCESS) {
        qDebug() << "Error connecting to instrument";
        viStatusDesc(resource_manager, status, buffer);
        qDebug() <<  buffer;
        return 0;
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
        return 0;
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
        return 0;
    }


    pair = new QPair<ViSession, ViSession>();
    pair->first = resource_manager;
    pair->second = instrument;

    status = true;
    qDebug() << "success!!!";
    return 1;
}


void Keysight_handler::close_connection()
{
    if (!pair->first)
        return;
    viClose(pair->first);
    viClose(pair->second);

    status = false;

}

int Keysight_handler::write_package(const char* command)
{
    // Communication buffer
    //const ViUInt32 buffer_size_B = 1000;
    ViChar buffer[1000];
    ViUInt32 io_bytes;

    ViBuf scpi_command = (ViBuf) command;
    ViStatus status = viWrite(pair->second, scpi_command, (ViUInt32)strlen( (const char*) scpi_command), &io_bytes);
    if (status < VI_SUCCESS) {
        qDebug() << "Error writing to instrument";
        viStatusDesc(pair->first, status, buffer);
        qDebug() <<  buffer;
        return 0;
    }
    qDebug() << "write_package success" << command;
    return 1;
}


const char* Keysight_handler::read_responce(const char* command)
{

    if (!write_package(command))
        return "";
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
    return (const char*) buffer;
}


double Keysight_handler::read_double(const char* command)
{

    if (!write_package(command))
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

     qDebug() << "read double ensd";
    return d1;
}


void Keysight_handler::zero_correction(int delay)
{
    qDebug() << "zero begin";
    write_package("*RST\n");
    write_package( ":SYST:ZCH ON\n");
    write_package( ":CURR:RANG 2e-9\n");
    qDebug() << "delay start " << delay;
    QThread::msleep(delay);//400
    qDebug() << "delay end " << delay;

    write_package( ":INIT\n");
    QThread::msleep(delay);
    write_package( ":SYST:ZCOR:STAT OFF\n");
    QThread::msleep(delay);
    write_package( ":SYST:ZCOR:ACQ\n");
    write_package( ":SYST:ZCH OFF\n");
    write_package( ":SYST:ZCOR ON\n");
    qDebug() << "zero end";

}

void Keysight_handler::set_05V(int volt, int delay)
{
    qDebug() << "set_05V begin";

    delay = delay? delay : 6;
    write_package( ":CURR:RANG 2e-3\n");
    write_package( ":SOUR:VOLT:RANG 1\n");
    char full_address[32];
    snprintf(full_address, 32, ":SOUR:VOLT %d-1\n", volt);
    write_package((const char*) full_address);
    write_package( ":SOUR:VOLT:ILIM 1e-3\n");
    write_package( ":SOUR:VOLT:STAT ON\n");
    QThread::msleep(delay);//600);
    qDebug() << "set_05V end";
}


void Keysight_handler::set_1V(int delay)
{
    qDebug() << "set_1V begin";
    write_package("SOUR:VOLT:STAT OFF\n");
    write_package("SOUR:VOLT -1\n");
    write_package("SOUR:VOLT:STAT ON\n");
    QThread::msleep(delay);
    write_package("CURR:RANG 2e-10\n");
    qDebug() << "set_1V end";
}

void Keysight_handler::set_10mV(int delay)
{
    qDebug() << "set_10mV begin";
    write_package("SOUR:VOLT:STAT OFF\n");
    write_package("SOUR:VOLT -1e-2\n");
    write_package("SOUR:VOLT:STAT ON\n");
    write_package("CURR:RANG 2e-10\n");
    QThread::msleep(delay);
    qDebug() << "set_10mV end";
}


QList<double> Keysight_handler::single_measurement(struct Delays* settings)
{
    QList<double> res;

    qDebug() << "1settings->dc_10mV" << settings->dc_10mV;
    qDebug() << "settings->dc_1V" << settings->dc_1V;
    qDebug() << "settings->fc" << settings->fc;
    qDebug() << "settings->light" << settings->light;
    qDebug() << "settings->fc_volt" << settings->fc_volt;


    zero_correction(settings->zero);
    set_10mV(settings->dc_10mV);
    //get dark current
    res.append(read_double(":SENS:FUNC CURR\n:MEAS:CURR?"));

    set_1V(settings->dc_1V);
    res.append(read_double(":SENS:FUNC CURR\n:MEAS:CURR?"));

    //get forward current
    set_05V(settings->fc, settings->fc_volt);
    res.append(read_double(":SENS:FUNC CURR\n:MEAS:CURR?"));
    qDebug() << "light begin";
    set_10mV(settings->light);
    //get light current
    res.append(read_double(":SENS:FUNC CURR\n:MEAS:CURR?"));
    return res;
}


double Keysight_handler::forward_current(struct Delays* settings)
{
    zero_correction(settings->zero);
    set_05V(settings->fc_volt, settings->fc);
    const char* resp = read_responce(":SENS:FUNC CURR\n:MEAS:CURR?");

    char* pEnd;
    double d1;
    d1 = strtod (resp, &pEnd);
    return d1;
}
