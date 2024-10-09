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
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <typeinfo>
#include <ctime>
#include <QDebug>

#include "LoggingCategories.h"
#include "keithley.h"
#include "mainwindow.h"
#include "serials.h"
#include "connector.h"



class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(QMutex*);
    ~Worker();
public:

    QByteArray lastAnswer;
    qint64 m_bytesWritten = 0;

    QTimer m_timer;
    QMutex* mutex;
    QString dir = "С:\temp\1.csv";

    Connector* connector = nullptr;
public:
    void stopWalk();
    void checkPause();
    /**
     * @brief checkIndex проверяет, попадание индекса за пределы измеряемой зоны
     * //check if measure is of odd space
     * @param DieParameters параметры пластины
     * @param Dots координаты мест контактирования зонда. gap диапазон разрыва
     */
    bool checkIndex(int, struct DieParameters*, struct Dots*);

    void timeSpent(int start);
signals:

    void sendLogSignal(QByteArray);
    void sendProgressBarValueSignal(int);
    void sendProgressBarRangeSignal(int, int);
    void sendAddTableSignal();
    void sendBCoordsSignal(int, int);
    void sendMessageBox(QString, QString);
    void sendEndWalkSignal();
    void sendEndOfWalkTime(QString);

public slots:
    /**
     * @brief calculate_dots проверяет, по ответу, что устройство выбрано правидьно
     * @param DieParameters параметры пластины
     * @param Dots координаты мест контактирования зонда
     * @param WalkSettings настройки обхода пластины
     */
    void calculate_dots(struct DieParameters*, struct Dots*, struct WalkSettings*);
    void pauseWalk();
    //void goToDot(struct WalkSettings*, struct Dots*);
    void saveMeasure(struct WalkSettings*);

    /**
     * @brief autoWalk проверяет, по ответу, что устройство выбрано правидьно
     * @param Peripherals настройки подключения устройств
     * @param Dots координаты мест контактирования зонда
     * @param WalkSettings настройки обхода пластины
     */
    void autoWalk(struct WalkSettings*, struct Peripherals*, struct Dots*,
                  struct DieParameters*);


    //вынести в отдельный виджет. заполнить таблицу
    void openCsvFile(QString, struct Currents*);
};

#endif // WORKER_H
