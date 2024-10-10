#ifndef LIGHT_H
#define LIGHT_H

#include <QByteArray>
#include <QString>
#include <QSerialPort>
#include "serials.h"
#include "comport.h"

class Light : public ComPort
{
public:
    Light(QSerialPort*);
    ~Light();

    void lightController(QByteArray msg, struct WalkSettings* walk);
    void on(struct WalkSettings* walk);
    void off(struct WalkSettings* walk);

    bool parsePort(QString*, struct Peripherals*) override;
};

#endif // LIGHT_H
