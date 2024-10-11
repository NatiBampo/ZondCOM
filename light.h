#ifndef LIGHT_H
#define LIGHT_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QSerialPort>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "serials.h"
#include "comport.h"
#include "LoggingCategories.h"

class Light : public ComPort
{
public:
    Light(QSerialPort*);
    ~Light();

    void lightController(QByteArray msg, struct WalkSettings* walk);
    void on(struct WalkSettings* walk);
    void off(struct WalkSettings* walk);

    bool parsePort(QString, struct Peripherals*) override;

};

#endif // LIGHT_H
