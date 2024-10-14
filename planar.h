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

class Planar : public ComPort
{
    Q_OBJECT

public:
    Planar(QSerialPort*);
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
    bool parsePort(QString , struct Peripherals* ) override;

    void tableController(QByteArray , struct WalkSettings*);
    void goToDot(struct WalkSettings* , struct Dots* );
    void down(struct WalkSettings* );
    void up(struct WalkSettings* );

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
private:
    int errorCount;
};

#endif // PLANAR_H
