#ifndef KEITHLEY_H
#define KEITHLEY_H

#include <QWidget>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QThread>
#include "meter.h"

class Keithley : public Meter
{
    Q_OBJECT

public:
    Keithley(QSerialPort *);
    ~Keithley();

    bool openConnection(struct Peripherals*) override;
    void closeConnection() override;
    int writePackage(const char*, int) override;
    double readDouble(const char*, int ) override;
    QString* readResponce(const char*, int) override;

    bool parsePort(QString, struct Peripherals*) override;

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
};

#endif // KEITHLEY_H
