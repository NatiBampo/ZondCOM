#ifndef EXCHANGEABLES_H
#define EXCHANGEABLES_H

enum CoordsEnum{POINT_B= -2,
                POINT_CURRENT = -1};

typedef struct {
    int fcVolt;
    int dc1Volt; //prior DC10mV .also used for diod current set
    int dc2Volt;    //DC1V
    int lightVolt;

    int fcDelay;
    int zeroDelay;
    int dc1Delay;
    int dc2Delay;
    int lightDelay;
    int planarDelay;

    int rangedc1;
    int rangedc2;
} VoltDelay;

typedef struct  {
    bool allNew;
    bool planar;
    bool meter;//keithley;
    bool light;

    bool badDie;
    bool keysight;
    bool volt10;

    bool paused;
    bool stopped;
    bool orientation;

    int startIndex;
    int currentIndex;
    int lastIndex;

} RunStatus;

typedef struct  {
    bool centerColumn;
    bool leftColumn;
    bool rightColumn;


    int AX;
    int AY;
    int BX;
    int BY;

    int numX;
    int numY;

    int upLeft;
    int upRight;
    int upCenter;
    int downLeft;
    int downRight;
    int downCenter;

    double stepX;
    double stepY;
    double colSlide;
    double rowSlide;


} DieSettings;

#endif // EXCHANGEABLES_H
