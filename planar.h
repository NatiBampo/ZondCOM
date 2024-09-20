#ifndef PLANAR_H
#define PLANAR_H

#include "connector.h"

class Planar : public Connector
{
public:
    Planar();

    /**
     * @brief endLine проверяет, выход из строя планара через задержу
     * @param
     */
    void endLine();


    /**
     * @brief parsePort проверяет, по ответу, что устройство выбрано правидьно
     * @param
     */
    bool parsePort(QSerialPort *port, QString* com_name);

    void tableController(QByteArray package);
    void down();
    void up();
private:
    QSerialPort* serial = nullptr;
    QString* name = nullptr;
};

#endif // PLANAR_H
