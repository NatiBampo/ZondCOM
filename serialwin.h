#ifndef SERIALWIN_H
#define SERIALWIN_H

#include <QThread>
#include <QSerialPort>


class SerialWin
{
public:
    SerialWin();
    int initCOM(const char*, int);
    void closeCOM();
    char* readCOM(const int, const int);
    void writeCOM(const char *d);
    bool isOpen();


private:
    bool opened = false;
    bool isWin = false;
    QSerialPort *serialPort;
    QString answer;
    bool openQtPort(QSerialPort *port, QString portName, QSerialPort::BaudRate baudRate);
    void sendPackage(QByteArray package, int delay);
    bool closeQtPort();
};

#endif // SERIALWIN_H
