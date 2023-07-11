#include "serialwin.h"
#include <windows.h>
#include <iostream>
#include <ctime>

HANDLE hSerial;

SerialWin::SerialWin()
{

}

//port_type 0 Keithley, 1 Zond, 2 light
int SerialWin::initCOM(const char* port, int baud)
{

//    char* port = "\\\\.\\9"; // + portNumber;
    hSerial = CreateFileA(
        port,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);


    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            //std::cout << "serial port does not exist.\n";
            return 0;
        }
        //std::cout << "some other error occurred.\n";
        return -1;
    }

    DCB dcbSerialParams;
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        //std::cout << "getting state error\n";
        return -2;
    }

//    dcbSerialParams.BaudRate = CBR_57600;
    dcbSerialParams.BaudRate = baud;

    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        //std::cout << "error setting serial port state\n";
        return -3;
    }

    COMMTIMEOUTS SerialTimeouts;
    SerialTimeouts.ReadIntervalTimeout = 10;
    SerialTimeouts.ReadTotalTimeoutConstant = 1;
    SerialTimeouts.ReadTotalTimeoutMultiplier = 1;
    SerialTimeouts.WriteTotalTimeoutConstant = 10;
    SerialTimeouts.WriteTotalTimeoutMultiplier = 1;
    if (!SetCommTimeouts(hSerial, &SerialTimeouts))
    {
       // std::cout << "timeout error";
        return -4;
    }

    opened = true;

    return 1;
}


char* SerialWin::readCOM(const int size, const int delay)
{
    Sleep(delay);
    DWORD iSize = 0;
    char * sReceivedChar = new char[size];
    BOOL ret = ReadFile(hSerial, sReceivedChar, size, &iSize, 0);
    if (iSize > 0)
        //std::cout << sReceivedChar << std::endl;
    return sReceivedChar;
}


void SerialWin::writeCOM(const char *data)
{
    DWORD dwSize = strlen(data) + 1;
    DWORD dwBytesWritten;
    BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);
    //return dwBytesWritten;
}


void SerialWin::closeCOM()
{
    CloseHandle(hSerial);
    opened = false;
}


bool SerialWin::isOpen()
{
    if (isWin) return opened;
    return serialPort->isOpen();
}


bool SerialWin::openQtPort(QSerialPort *port, QString portName, QSerialPort::BaudRate baudRate)
{
    port->setPortName(portName);
    port->setBaudRate(baudRate);
    port->setDataBits(QSerialPort::DataBits::Data8);
    port->setStopBits(QSerialPort::StopBits::OneStop);
    port->setParity(QSerialPort::Parity::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);

    //emit openPortResultSignal(portName, port->open(QSerialPort::ReadWrite));
    return port->open(QSerialPort::ReadWrite);
}


bool SerialWin::closeQtPort()
{
    if (serialPort->isOpen()) serialPort->close();
}

void SerialWin::sendPackage(QByteArray package, int delay)
{
    answer = "";
    serialPort->write(package);
    serialPort->flush();
    //emit sendLogSignal(package.remove(package.indexOf("\\"), package.length() - package.indexOf("\\")));
    while (serialPort->waitForReadyRead(delay)) answer.append(serialPort->readAll());
    //if (lastAnswer != "") emit sendLogSignal(lastAnswer.remove(lastAnswer.indexOf("\\"), lastAnswer.length() - lastAnswer.indexOf("\\")));
}
