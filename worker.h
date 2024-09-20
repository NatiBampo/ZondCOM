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
    void stopWalk();
    void setIndex(int);


private:

    QByteArray lastAnswer;
    qint64 m_bytesWritten = 0;

    QTimer m_timer;
    QMutex* mutex;
    QString dir = "С:\temp\1.csv";

    Connector* connecter = nullptr;

    volatile bool paused = false;
    volatile bool stopped = false;

    double FCBorder = -qPow(10, -5);
    double LightBorder = 5*qPow(10, -8);

    void checkPause();

    bool copyUpToIndex(int);
    bool checkIndex(int);

    void timeSpent(int start);
signals:

    void sendLogSignal(QByteArray);
    void sendProgressBarValueSignal(int);
    void sendProgressBarRangeSignal(int, int);
    void openPortResultSignal(QString, QString, bool);
    void sendAddTableSignal(int, double, double, double, double);
    void sendBCoordsSignal(int, int);
    void sendMessageBox(QString, QString);
    void sendCurrentCoordsSignal(int, int);
    void sendPackageSignal(QSerialPort*, QByteArray, int);
    void sendPackageSignalRead(QSerialPort*, QByteArray, int);
    void sendEndWalkSignal();
    void sendEndOfWalkTime(QString);

public slots:
    void measureElement(struct WalkSettings*, struct Currents*);
    void calculate_dots(struct DieParameters*, struct Dots*);
    void tableController(QByteArray, struct WalkSettings*);
    void lightController(QByteArray, struct WalkSettings*);
    void openPorts(QString, QString, QString);
    void closePorts();
    void pauseWalk();
    void goToDot(struct WalkSettings*);
    void saveMeasure(struct WalkSettings*);
    void autoOpenPorts();
    bool getCurrentCoords(int, bool);

    void autoWalk(struct DieParameters*, int);

    void sendPackageRead(QSerialPort*, QByteArray, int);
    void measureFC(bool, bool );
    void openCsvFile(QString dir);
};

#endif // WORKER_H
