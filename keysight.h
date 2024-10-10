#ifndef KEYSIGHT_H
#define KEYSIGHT_H

#include <QThread>

#include "visa/visa.h"
#include "meter.h"

class Keysight : public Meter
{
public:
    Keysight();
    //const char*
    bool openConnection(struct Peripherals*);
    void closeConnection()  override;
    int writePackage(const char*, int) override;
    double readDouble(const char*, int) override;
    QString* readResponce(const char*, int) override;

    bool parsePort(QSerialPort *port,
                   QString* com_name);

    void zeroCorrection(int) override;
    void set05V(int, int) override;
    void set10mV(int) override;
    void set1V(int) override;

    void darkCurrents(struct WalkSettings* walk,
                      struct Delays* delays,
                      struct Currents* curr) override;
    void lightCurrent(struct WalkSettings* walk,
                      struct Delays* delays,
                      struct Currents* curr) override;

    double forwardCurrent(struct Delays*) override;



private:
    QPair<ViSession, ViSession> *pair = nullptr;
};

#endif // KEYSIGHT_H
