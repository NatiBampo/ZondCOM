// SerialWin.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <iostream>

HANDLE hSerial;

void ReadCOM()
{
    DWORD iSize;
    char sReceivedChar;
    while (true)
    {
        BOOL ret = ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
        if (iSize > 0)   // если что-то принято, выводим
            std::cout << sReceivedChar;
    }
}

void WriteCom(const char data[]) 
{
    DWORD dwSize = sizeof(data);   // размер этой строки
    DWORD dwBytesWritten;    // тут будет количество собственно переданных байт

    BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);
    std::cout << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. " << std::endl;
}

int main()
{
    hSerial = CreateFileA("\\\\.\\COM7", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            std::cout << "serial port does not exist.\n";
        }
        std::cout << "some other error occurred.\n";
    }

    DCB dcbSerialParams = { 0 };
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

    WriteCom("*RST\n");
    WriteCom("SYST:ZCH ON\n");
    WriteCom( "CURR:RANG 2e-9\n");
    Sleep(400);//400
    WriteCom("INIT\n");
    Sleep(400);//400
    WriteCom("SYST:ZCOR:STAT OFF\n");
    Sleep(400);//400
    WriteCom("SYST:ZCOR:ACQ\n");
    WriteCom("SYST:ZCH OFF\n");
    WriteCom("SYST:ZCOR ON\n");


    //FC0.6V
    WriteCom("CURR:RANG 2e-3\n");
    WriteCom("SOUR:VOLT:RANG 1\n");
    WriteCom("SOUR:VOLT 0.6\n");
    WriteCom("SOUR:VOLT:ILIM 1e-3\n");
    WriteCom("SOUR:VOLT:STAT ON\n");
    Sleep(300);//400


    //dc10mV
    WriteCom("CURR:RANG 2e-10\n");
    WriteCom("SOUR:VOLT:STAT OFF\n");
    WriteCom("SOUR:VOLT -10e-3\n");
    WriteCom("SOUR:VOLT:STAT ON\n");
    Sleep(800);

    //dc1v
    WriteCom("SOUR:VOLT:STAT OFF\n");
    WriteCom("SOUR:VOLT -1\n");
    WriteCom("SOUR:VOLT:STAT ON\n");
    Sleep(600);

    //light
    WriteCom("CURR:RANG 2e-10\n");
    WriteCom("SOUR:VOLT:STAT OFF\n");
    WriteCom("SOUR:VOLT -10e-3\n");
    WriteCom("SOUR:VOLT:STAT ON\n");
    Sleep(400);


    //while (1)
    //{
    //    ReadCOM();
    //}

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
