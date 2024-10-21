#ifndef COMPORT_H
#define COMPORT_H


#include <QObject>
#include <QString>
#include <QSerialPort>
#include <QThread>

#include "serials.h"
#include "LoggingCategories.h"
#define NO_ANSWER_DELAY 10
#define ANSWER_DELAY 400


class ComPort: public QObject
{
    Q_OBJECT

public:
    ComPort(QSerialPort::BaudRate baudRate);
    ~ComPort();

    bool openPort(QString*);

    bool openPort(QSerialPort *port, QString* comPort,
                  QSerialPort::BaudRate baudRate);


    void closePort();
    // autoOpen(struct Peripherals* periph);
    void setPort(QSerialPort*);
    QSerialPort* getPort();
    bool isOpen();
public:
    QString lastAnswer;



public slots:
    void sendPackage(QByteArray, int);
    void sendPackageRead (QByteArray, int);

protected:
    bool opened;
    bool working;
    qint64 m_bytesWritten = 0;
    QSerialPort::BaudRate m_rate;
    QSerialPort* m_serial = nullptr;
    QString* m_port_name = nullptr;
};

#endif // COMPORT_H
