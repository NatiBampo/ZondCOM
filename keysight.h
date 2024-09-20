#ifndef KEYSIGHT_H
#define KEYSIGHT_H

#include <QThread>

#include "visa/visa.h"
#include "meter.h"

class Keysight_handler : public Meter
{
public:
    Keysight_handler();
    int open_connection(const char*) override;

    void close_connection()  override;

    int write_package(const char*) override;
    const char* read_responce(const char*) override;
    double read_double(const char*);


    void zero_correction(int) override;
    void set_05V(int, int) override;
    void set_1V(int) override;
    void set_10mV(int) override;

    QList<double> single_measurement(struct Delays*) override;
    double forward_current(struct Delays*) override;

private:
    QPair<ViSession, ViSession> *pair = nullptr;
};

#endif // KEYSIGHT_H
