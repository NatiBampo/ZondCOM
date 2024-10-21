#ifndef PLANAR_H
#define PLANAR_H

#include <QObject>
#include <QThread>
#include <QSerialPort>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "LoggingCategories.h"
#include "comport.h"
#include "serials.h"

class Planar : public QObject
{
    Q_OBJECT

public:
    Planar(struct Peripherals* periph);
    ~Planar();
    /**
     * @brief endLine проверяет, выход из строя планара через задержу
     * @param
     */
    void endLine(struct WalkSettings*);

    /**
     * @brief parsePort проверяет, по ответу, что устройство выбрано правидьно
     * @param
     */
    bool parsePort(QString , struct Peripherals* );

    void tableController(QByteArray , struct WalkSettings*);
    void goToDot(struct WalkSettings* , struct Dots* );
    void down(struct WalkSettings* );
    void up(struct WalkSettings* );
    bool openPort(QSerialPort *port, QString* comPort,
                     QSerialPort::BaudRate baudRate);
    bool openPort(QString* comPort);
    void setPort(QSerialPort* port);
    void closePort();

public:
    bool working;


public slots:
    /**
     * @brief currentCoords проверяет, по ответу, что устройство выбрано правидьно
     * @param int param -1 sends current : -2 sends  point B : 0 checks current with calculated
     */
    void currentCoords(int, struct WalkSettings* , struct Dots*);

 signals:
    void sendMessageBoxSignal(QString, QString);
    void sendLogSignal(QByteArray msg);
    void sendCurrentCoordsSignal(int , int, int);

signals:
    void sendPackageSignal(QByteArray, int);
    void sendPackageReadSignal(QByteArray , int );



private:
    int errorCount;
    ComPort *m_serial =  nullptr;
};

#endif // PLANAR_H
