 #ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QSerialPort>
#include <QFile>
#include <QSqlQuery>
#include <QMutex>


#define ANSWER_DELAY 1000
#define NO_ANSWER_DELAY 10

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(QMutex*);
    ~Worker();

    void stopWalk();
    void setIndex(int);
private:
    QSerialPort *serialPortA5;
    QSerialPort *serialPortKeithly;
    QSerialPort *serialPortLight;
    QByteArray lastAnswer;
    QMutex* mutex;

    QList<double> DotsX;
    QList<double> DotsY;
    QString dir = "С:\temp\1.csv";

    volatile bool pause = false;
    bool overwrite = false;
    int currentIndex = 0;
    int pauseIndex = 0;
    int lastIndex = 0;
    double ForwardCurrent = 0.0;
    double DarkCurrent10mV = 0.0;
    double DarkCurrent1V = 0.0;
    double LightCurrent = 0.0;
    bool openPort(QSerialPort *, QString, QSerialPort::BaudRate);
    void MeasureDie(QSerialPort *, QSerialPort *);
    void KeithlyZeroCorrection(QSerialPort *);
    void Keithly05VSet(QSerialPort *);
    double KeithlyGet(QSerialPort *);
    void Keithly10mVSet(QSerialPort *);
    void Keithly1VSet(QSerialPort *);
    void LightOn();
    void LightOff();
    void copyUpToIndex(int);
    bool checkPlanarCOM(QSerialPort *serialPort, QByteArray package, int delay);

signals:
    void sendPackageSignal(QSerialPort * , QByteArray, int);
    void sendLogSignal(QByteArray);
    void sendProgressBarValueSignal(int);
    void sendProgressBarRangeSignal(int, int);
    void openPortResultSignal(QString, bool);
    void sendAddTableSignal(int, double, double, double, double);
    void autoWalkSignal(bool, QString);

public slots:
    void measureElement();
    void sendPackage(QSerialPort * , QByteArray, int);
    void scanningPlate(double, double, double, double, double, double, double, double, double, double, bool);
    void tableController(QByteArray);
    void lightController(QByteArray);
    void openPorts();
    void closePorts();
    void pauseWalk();
    //void continueWalk();
    void goToElement(int);
    void saveMeasure(int);
    void autoWalk(bool, QString);
};

#endif // WORKER_H
