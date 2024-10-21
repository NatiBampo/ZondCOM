#ifndef LIGHT_H
#define LIGHT_H


#include <QObject>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QSerialPort>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "serials.h"
#include "comport.h"
#include "LoggingCategories.h"

class Light : public QObject
{
    Q_OBJECT

public:
    Light(struct Peripherals*);
    ~Light(){}

    void lightController(QByteArray msg, struct WalkSettings* walk);
    void on(struct WalkSettings* walk);
    void off(struct WalkSettings* walk);

    bool parsePort(QString, struct Peripherals*) ;
    bool openPort(QSerialPort *port, QString* comPort,
                     QSerialPort::BaudRate baudRate);
    bool openPort(QString* comPort);
    void setPort(QSerialPort* port);
    void closePort();
public:
    bool working;
private:
    ComPort *m_serial = nullptr;

signals:
    void sendPackageSignal(QByteArray, int);
    void sendPackageReadSignal(QByteArray , int );
};

#endif // LIGHT_H
