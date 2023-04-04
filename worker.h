 #ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QSerialPort>
#include <QFile>
#include <QSqlQuery>


#define ANSWER_DELAY 1000
#define NO_ANSWER_DELAY 10

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker();
    ~Worker();

    void stopWalk();
private:
    QSerialPort *serialPortA5;
    QSerialPort *serialPortKeithly;
    QSerialPort *serialPortLight;
    QByteArray lastAnswer;

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
    void openPort(QSerialPort *, QString, QSerialPort::BaudRate, QSerialPort::DataBits, QSerialPort::StopBits, QSerialPort::Parity, QSerialPort::FlowControl);
    void MeasureDie(QSerialPort *, QSerialPort *);
    void KeithlyZeroCorrection(QSerialPort *);
    void Keithly05VSet(QSerialPort *);
    double KeithlyGet(QSerialPort *);
    void Keithly10mVSet(QSerialPort *);
    void Keithly1VSet(QSerialPort *);
    void LightOn();
    void LightOff();
    void copyUpToIndex(int);

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
    void openPorts(QString, QString, QString);
    void closePorts();
    void pauseWalk();
    void continueWalk(int);
    void goToElement(int);
    void saveMeasure(int);
    void autoWalk(bool, QString);
};

#endif // WORKER_H
