#ifndef COMPORT_H
#define COMPORT_H

#include <QString>
#include <QSerialPort>
#define NO_ANSWER_DELAY 10
#define ANSWER_DELAY 400


class ComPort
{
public:
    ComPort(QSerialPort*);

    bool openPort(QSerialPort*, QString);

    virtual bool openPort(QString) override;

    bool openPort(QSerialPort *port, QString* comPort,
                  QString* portName,
                  QSerialPort::BaudRate baudRate);

    void closePort();

    void sendPackage(QByteArray, int);

    void sendPackageRead (QByteArray, int);

    void autoOpen(struct Peripherals* periph);

    void setPort(QSerialPort*);

    QString lastAnswer;


protected:
    QSerialPort::BaudRate m_rate;
    QSerialPort* m_serial = nullptr;
    QString* m_port_name = nullptr;
};

#endif // COMPORT_H
