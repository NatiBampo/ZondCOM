#ifndef KEYSIGHT_H
#define KEYSIGHT_H


#include <QThread>
#include <QDebug>
#include <QString>
#include "serials.h"
#include "visa/visa.h"

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
    void set05V(int , int );
    void set1V(int delay);
    void set10mV(int delay);


    double lightCurrent(int );
    double forwardCurrent(int , int );
    void darkCurrents(int , int , int , int );

public:
    double dark10mV;
    double dark1V;
    double forward05V;
private:
    QPair<ViSession, ViSession> *pair = nullptr;
};
#endif // KEYSIGHT_H
