#ifndef KEITHLEY_H
#define KEITHLEY_H

#include <QWidget>
#include <QMessageBox>
#include <QThread>
#include "meter.h"

class Keithley : public Meter
{
    Q_OBJECT

public:
    Keithley();
    ~Keithley();

    void zeroCorrection(int);
    void set_05V(int, int);
    void set_10mV(int);
    void set_1V(int);

    double read_double();
    QString read_responce();
private:
    QSerialPort *serial = nullptr;
    QString* port_name;
};

#endif // KEITHLEY_H
