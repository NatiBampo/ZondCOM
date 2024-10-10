#ifndef SERIALS_H
#define SERIALS_H

#include <QString>
#include <QMap>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <vector>

struct Delays
{
    int zero;
    int dc_10mV;
    int dc_1V;
    int fc;
    int light;
    int planar;
    int fc_volt;
};


struct DieParameters
{
   int  AX, AY, BX, BY;
   int stepX, stepY, numX, numY;
   int upLeft, upRight;
   int downLeft, downRight;
   int downCenter, upCenter;
   bool centerColumn, leftColumn, rightColumn;
   double colSlide;

};

struct Currents
{
    int currentIndex;
    double forward05V;
    double dark10mV;
    double dark1V;
    double light10mV;
    double borderFC = -qPow(10, -5);
    double borderLC = 5*qPow(10, -8);
};


struct Peripherals
{
    QSerialPort *planar = nullptr;
    QSerialPort *keithley = nullptr;
    QSerialPort *light = nullptr;

    QString* light_com = nullptr;
    QString* planar_com = nullptr;
    QString* keithley_com = nullptr;

    bool light_open;
    bool planar_open;
    bool keithley_open;

    bool meter;

    bool lan;
    int ip[4];
    int keysight_open;
};


struct Dots
{
    int gap[12]{};
    std::vector<int> *X;
    std::vector<int> *Y;

};

struct WalkSettings
{
    bool allNew;
    bool planar_status;
    bool keithley_status;
    bool light_status;
    bool badDie;

    int startIndex;
    int currentIndex;
    int lastIndex;
    bool paused;
    bool stopped;
    bool orientation;

    QString dir_cur;
};


#endif // SERIALS_H
