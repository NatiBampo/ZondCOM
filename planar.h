#ifndef PLANAR_H
#define PLANAR_H

#include "connector.h"

class Planar
{
public:
    Planar();

    bool openPort(QString) override;
    /**
     * @brief endLine проверяет, выход из строя планара через задержу
     * @param
     */
    void endLine();


    /**
     * @brief parsePort проверяет, по ответу, что устройство выбрано правидьно
     * @param
     */
    bool parsePort(QString* com_name);

    void tableController(QByteArray , struct WalkSettings*);
    void goToDot(struct WalkSettings* walk, struct Dots* dots);
    void down();
    void up();

 public slots:
    void currentCoords(int, bool);

private:
    bool working;
};

#endif // PLANAR_H
