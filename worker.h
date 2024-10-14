#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QThread>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <typeinfo>
#include <ctime>

#include "LoggingCategories.h"
#include "keithley.h"
#include "serials.h"
#include "connector.h"



class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(QMutex*, Connector*);
    ~Worker();
public:
    QMutex* mutex;
    QString dir = "С:\temp\1.csv";

    Connector* connector = nullptr;
public:
    void stopWalk(struct WalkSettings*);
    void checkPause(struct WalkSettings*);
    /**
     * @brief checkIndex проверяет, попадание индекса за пределы измеряемой зоны
     * @param DieParameters параметры пластины
     * @param Dots координаты мест контактирования зонда. gap диапазон разрыва
     */
    bool checkIndex(int, struct DieParameters*, struct Dots*);

    void timeSpent(int start);
signals:

    void sendProgressBarValueSignal();
    //oid sendProgressBarRangeSignal(int, int);
    void sendAddTableSignal();
    void sendBCoordsSignal(int, int);
    void sendEndWalkSignal();
    void sendEndOfWalkTime(QString);

public slots:
    /**
     * @brief calculate_dots проверяет, по ответу, что устройство выбрано правидьно
     * @param DieParameters параметры пластины
     * @param Dots координаты мест контактирования зонда
     * @param WalkSettings настройки обхода пластины
     */
    void calculateDots(struct DieParameters*, struct Dots*, struct WalkSettings*);
    void pauseWalk(struct WalkSettings*);
    //void goToDot(struct WalkSettings*, struct Dots*);

    void saveMeasure(struct WalkSettings* , struct Delays* ,
                     struct Dots* , struct DieParameters*, struct Currents* );

    /**
     * @brief autoWalk проверяет, по ответу, что устройство выбрано правидьно
     * @param Peripherals настройки подключения устройств
     * @param Dots координаты мест контактирования зонда
     * @param WalkSettings настройки обхода пластины
     */
    void autoWalk(struct WalkSettings* ,
                  struct Delays* ,
                  struct Dots* ,
                  struct DieParameters*,
                  struct Currents*);


    //вынести в отдельный виджет. заполнить таблицу
    void openCsvFile(QString, struct Currents*);
};

#endif // WORKER_H
