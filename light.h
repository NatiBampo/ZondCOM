#ifndef LIGHT_H
#define LIGHT_H

#include "connector.h"


class Light : public Connector
{
public:
    Light();
    ~Light();
    void lightController(QByteArray msg);
    void on();
    void off();

    bool parsePort(QSerialPort *port, QString* com_name) override;
private:
    QSerialPort *serial = nullptr;
    QString* port_name;
    QString lastAnswer;
};

#endif // LIGHT_H
