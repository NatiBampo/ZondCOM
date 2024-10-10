#ifndef METER_H
#define METER_H

#include <QPair>
#include <QList>
#include <QDebug>
#include <QString>

#include "serials.h"

class Meter
{
public:
    Meter(){}
    ~Meter() {}

    virtual bool openConnection(struct Peripherals*) = 0; //{return false;}
    virtual void closeConnection() = 0; //{}
    virtual void zeroCorrection(int) = 0; //{}
    virtual void set05V(int, int) = 0; //{}
    virtual void set1V(int) = 0; //{}
    virtual void set10mV(int) = 0; //{}
    virtual double forwardCurrent(struct Delays*) = 0; //{return 0.0;}
    virtual void darkCurrents(struct WalkSettings* walk,
                              struct Delays* delays,
                              struct Currents* curr) = 0; //{}
    virtual void lightCurrent(struct WalkSettings* ,
                                struct Delays* ,
                                struct Currents* ) = 0;

    virtual int writePackage(const char*, int) = 0;
    virtual QString* readResponce(const char*, int) = 0;
    virtual double readDouble(const char*, int) = 0;

};

#endif // METER_H
