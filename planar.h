#ifndef PLANAR_H
#define PLANAR_H

#include <QSerialPort>


#include "comport.h"
#include "connector.h"

class Planar : public ComPort
{
public:
    Planar(QSerialPort*);
    ~Planar();
    /**
     * @brief endLine проверяет, выход из строя планара через задержу
     * @param
     */
    void endLine();

    /**
     * @brief parsePort проверяет, по ответу, что устройство выбрано правидьно
     * @param
     */
    bool parsePort(QString* com_name, struct Peripherals* periph) override;

    void tableController(QByteArray , struct WalkSettings*);
    void goToDot(struct WalkSettings* walk, struct Dots* dots);
    void down(struct WalkSettings* walk);
    void up(struct WalkSettings* walk);

 public slots:
    void currentCoords(struct WalkSettings* walk, struct Dots* dots);

private:
    bool working;
};

#endif // PLANAR_H
