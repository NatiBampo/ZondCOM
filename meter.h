#ifndef METER_H
#define METER_H

#include <QPair>
#include <QList>
#include <QDebug>
#include <QString>

#include "serials.h"
#include "connector.h"
#include "keithley.h"
#include "keysight.h"


class Meter
{
public:
    virtual Meter() {}
    virtual ~Meter() {}
    virtual bool openConnection(struct Peripherals*) = 0;
    virtual void closeConnection() = 0;
    virtual void zeroCorrection(int) = 0;
    virtual void set05V(int, int) = 0;
    virtual void set1V(int) = 0;
    virtual void set10mV(int) = 0;
    virtual double forwardCurrent(struct Delays*) = 0;
    virtual void darkCurrents(struct Delays* ,
                              struct Currents*) = 0;
    virtual double lightCurrent(struct Delays*,
                                struct Currents*) = 0;

    virtual int writePackage(const char*, int) = 0;
    virtual QString* readResponce(const char*, int) = 0;
    virtual double readDouble(const char*, int) = 0;

};

#endif // METER_H
