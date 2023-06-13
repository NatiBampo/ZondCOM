#ifndef SERIALWIN_H
#define SERIALWIN_H

#include <QThread>


class SerialWin
{
public:
    SerialWin();
    int initCOM(const char*, int);
    void closeCOM();
    char* readCOM(const int, const int);
    void writeCOM(const char *d);
    bool isOpen();

private:
    bool opened = false;
};

#endif // SERIALWIN_H
