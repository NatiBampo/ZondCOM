#ifndef KEYSIGHT_H
#define KEYSIGHT_H


#include <QString>


class Keysight{
public:

    Keysight(){}
    ~Keysight(){}


    bool openConnection(Peripherals *p);
    void closeConnection();
    int writePackage(const char *command, int l = 0);
    QString *readResponce(const char *cmd, int l = 0);
    double readDouble(const char *command, int l = 0);
    void zeroCorrection(int delay);
    void set05V(int volt = 600, int delay = 600);
    void set1V(int delay);
    void set10mV(int delay);
    void darkCurrents(WalkSettings *walk, Delays *delays, Currents *curr);
    void lightCurrent(WalkSettings *walk, Delays *delays, Currents *curr);
    double forwardCurrent(Delays *delays);
};
#endif // KEYSIGHT_H
