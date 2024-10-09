#ifndef KEITHLEY_H
#define KEITHLEY_H

#include <QWidget>
#include <QMessageBox>
#include <QThread>
#include "meter.h"

class Keithley : public Meter, public ComPort
{
    Q_OBJECT

public:
    Keithley(QSerialPort *);
    ~Keithley();

    void zeroCorrection(int) override;
    void set05V(int, int) override;
    void set10mV(int) override;
    void set1V(int) override;

    double readDouble() override;
    QString readResponce();

};

#endif // KEITHLEY_H
