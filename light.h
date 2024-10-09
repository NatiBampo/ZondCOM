#ifndef LIGHT_H
#define LIGHT_H

#include "connector.h"
#include "comport.h"

class Light : public ComPort
{
public:
    Light();
    ~Light();
    void lightController(QByteArray msg);
    void on();
    void off();

    bool parsePort(QString* , struct Peripherals*) override;
private:

    QString lastAnswer;
};

#endif // LIGHT_H
