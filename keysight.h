#ifndef KEYSIGHT_H
#define KEYSIGHT_H


#include "visatype.h"
#include <QThread>
#include <QDebug>
#include <QString>
//#include "serials.h"
#include "exchangeables.h"

class Keysight
{
public:

    Keysight(){}
    ~Keysight(){}


    bool openConnection();//Peripherals *p);
    void closeConnection();
    int writePackage(const char *, int);
    QString *readResponce(const char *, int );
    double readDouble();//const char *command, int l = 0);
    void zeroCorrection(int delay);
    void set05V(int , int);
    void set10V(int , int, int);
    void set1V(int, int, int);
    void set10mV(int, int);


    double lightCurrent(VoltDelay *);
    double forwardCurrent(VoltDelay *);
    void darkCurrents(VoltDelay *);

public:
    double dark10mV;
    double dark1V;
    double forward05V;
    void sourceOff();
private:
    QPair<ViSession, ViSession> *pair = nullptr;
};
#endif // KEYSIGHT_H
