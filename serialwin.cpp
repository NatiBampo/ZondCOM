#include "serialwin.h"
#include <windows.h>
#include <iostream>
#include <ctime>

SerialWin::SerialWin()
{
    HANDLE hSerial;

    hSerial = CreateFileA(
        "\\\\.\\COM9",
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
            std::cout << "serial port does not exist.\n";
        }
        std::cout << "some other error occurred.\n";
    }

    DCB dcbSerialParams;
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        std::cout << "getting state error\n";
    }
    dcbSerialParams.BaudRate = CBR_57600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        std::cout << "error setting serial port state\n";
    }

    COMMTIMEOUTS SerialTimeouts;
    SerialTimeouts.ReadIntervalTimeout = 10;
    SerialTimeouts.ReadTotalTimeoutConstant = 1;
    SerialTimeouts.ReadTotalTimeoutMultiplier = 1;
    SerialTimeouts.WriteTotalTimeoutConstant = 10;
    SerialTimeouts.WriteTotalTimeoutMultiplier = 1;
    if (!SetCommTimeouts(hSerial, &SerialTimeouts)) { std::cout << "timeout error"; }

}
void ReadCOM(const int size, const int deley)
{
    Sleep(deley);
    DWORD iSize = 0;
    char * sReceivedChar = new char[size];
    BOOL ret = ReadFile(hSerial, sReceivedChar, size, &iSize, 0);
    if (iSize > 0)
        std::cout << sReceivedChar << std::endl;
    delete[] sReceivedChar;
}

int WriteCOM(const char *data)
{
    DWORD dwSize = strlen(data) + 1;
    DWORD dwBytesWritten;
    BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);
    return dwBytesWritten;
}

void CloseCOM()
{
    CloseHandle(hSerial);
}
//        int start = clock();

//        WriteCOM("*RST\n");
//        WriteCOM("SYST:ZCH ON\n");
//        WriteCOM("CURR:RANG 2e-9\n");
//        Sleep(400);
//        WriteCOM("INIT\n");
//        Sleep(400);
//        WriteCOM("SYST:ZCOR:STAT OFF\n");
//        Sleep(400);
//        WriteCOM("SYST:ZCOR:ACQ\n");
//        WriteCOM("SYST:ZCH OFF\n");
//        WriteCOM("SYST:ZCOR ON\n");

//        WriteCOM("CURR:RANG 2e-3\n");
//        WriteCOM("SOUR:VOLT:RANG 1\n");
//        WriteCOM("SOUR:VOLT 6e-1\n");
//        WriteCOM("SOUR:VOLT:ILIM 1e-3\n");
//        WriteCOM("SOUR:VOLT:STAT ON\n");
//        Sleep(300);

//        WriteCOM("READ?\n");
//        ReadCOM(43, 400);

//        WriteCOM("CURR:RANG 2e-10\n");
//        WriteCOM("SOUR:VOLT:STAT OFF\n");
//        WriteCOM("SOUR:VOLT -1e-2\n");
//        WriteCOM("SOUR:VOLT:STAT ON\n");

//        Sleep(800);

//        WriteCOM("READ?\n");
//        ReadCOM(43, 400);

//        WriteCOM("SOUR:VOLT:STAT OFF\n");
//        WriteCOM("SOUR:VOLT -1\n");
//        WriteCOM("SOUR:VOLT:STAT ON\n");
//        Sleep(600);

//        WriteCOM("READ?\n");
//        ReadCOM(43, 400);

//        WriteCOM("CURR:RANG 2e-10\n");
//        WriteCOM("SOUR:VOLT:STAT OFF\n");
//        WriteCOM("SOUR:VOLT -1e-2\n");
//        WriteCOM("SOUR:VOLT:STAT ON\n");

//        WriteCOM("CURR:RANG 2e-6\n");
//        Sleep(200);

//        WriteCOM("READ?\n");
//        ReadCOM(43, 400);

//        WriteCOM("*RST\n");

//        int finish = clock();

//        std::cout << finish - start;




// ConsoleApplication2.cpp : Defines the entry point for the console application.
//



