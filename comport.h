#ifndef COMPORT_H
#define COMPORT_H

#include <QString>
#include <QSerialPort>

#include "LoggingCategories.h"
#define NO_ANSWER_DELAY 10
#define ANSWER_DELAY 400


class ComPort
{
public:
    ComPort(QSerialPort*);
    ~ComPort();

    bool openPort(QString*);

    bool openPort(QSerialPort *port, QString* comPort,
                  QSerialPort::BaudRate baudRate);

    virtual bool parsePort(QString, struct Peripherals*) = 0;

    void closePort();
    void sendPackage(QByteArray, int);
    void sendPackageRead (QByteArray, int);
    // autoOpen(struct Peripherals* periph);
    void setPort(QSerialPort*);

    QString lastAnswer;


protected:
    bool opened;
    bool working;
    qint64 m_bytesWritten = 0;
    QSerialPort::BaudRate *m_rate = nullptr;
    QSerialPort* m_serial = nullptr;
    QString* m_port_name = nullptr;
};

#endif // COMPORT_H
