#ifndef METER_H
#define METER_H

#include <QPair>
#include <QList>
#include <QDebug>
#include "serials.h"
#include "connector.h"
#include "keithley.h"
#include "keysight.h"


class Meter : public Connector
{
public:
    Meter(){}

    virtual int open_connection(const char*, int);
    virtual void close_connection();

    virtual int write_package(const char*, int);
    virtual const char* read_responce(const char*, int);
    virtual double read_double(const char*, int);

    virtual void zero_correction(int);
    virtual void set_05V(int, int);
    virtual void set_1V(int);
    virtual void set_10mV(int);

    virtual QList<double> single_measurement(struct Delays*);

    virtual double forward_current(struct Delays*);

    virtual dark_currents();
    bool status;
};

#endif // METER_H
