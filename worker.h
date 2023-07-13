 #ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QSerialPort>
#include <QFile>
#include <QSqlQuery>
#include <QMutex>
#include <keithley.h>
#include <QTimer>
#include <QTextStream>


#define ANSWER_DELAY 400
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
    QByteArray keithleyResponce;
    QByteArray lightResponce;
    QByteArray planarResponce;

    QByteArray m_writeData;
    qint64 m_bytesWritten = 0;

    QTimer m_timer;
    QMutex* mutex;

    QList<int> gap;
    QList<double> DotsX;
    QList<double> DotsY;
    QString dir = "С:\temp\1.csv";

    volatile bool pause = false;
    bool overwrite = false;
    bool three_columns = false;
    int currentIndex = 0;
    int pauseIndex = 0;
    int lastIndex = 0;
    int upLeft_offset = 0;
    int upRight_offset = 0;
    int downLeft_offset = 0;
    int downRight_offset = 0;

    int zeroDelay = 400;
    int FCdelay = 300;
    int DC10mVDelay = 800;
    int DC1VDelay = 600;
    int lightDelay = 400;
    int planarDelay = 1000;
    double FCVoltage = 0.6;

    //counter for measuareDie
    int counter = 0;

    double localCurrent = 0.0;
    double ForwardCurrent = 0.0;
    double DarkCurrent10mV = 0.0;
    double DarkCurrent1V = 0.0;
    double LightCurrent = 0.0;

    bool openPort(QSerialPort*, QString, QSerialPort::BaudRate);
    void copyUpToIndex(int);
    bool checkPlanarCOM();
    bool checkKeithlyCOM();
    bool checkLightCOM();
    bool checkIndex(int);

    void MeasureDie(QSerialPort *, QSerialPort *);
    void KeithlyZeroCorrection(QSerialPort *);
    void Keithly05VSet(QSerialPort *);
    double KeithlyGet(QSerialPort *);
    void Keithly10mVSet(QSerialPort *);
    void Keithly1VSet(QSerialPort *);
    void LightOn();
    void LightOff();

    void closePort(QSerialPort*);
    //void sendPackage(QSerialPort*, QByteArray, int);

signals:

    void sendLogSignal(QByteArray);
    void sendProgressBarValueSignal(int);
    void sendProgressBarRangeSignal(int, int);
    void openPortResultSignal(QString, QString, bool);
    void sendAddTableSignal(int, double, double, double, double);
    void autoWalkSignal(bool, QString);
    void sendBCoordsSignal(int, int);
    void getKeithleyData();
    void sendMessageBox(QString, QString);
    void sendCurrentCoordsSignal(int, int);
    void sendPackageSignal(QSerialPort*, QByteArray, int);

public slots:
    void measureElement2();
    void scanningPlate(double, double, double, double, double, double, double, bool, int, int, int, int);
    void tableController(QByteArray);
    void lightController(QByteArray);
    void openPorts(QString, QString, QString);
    void closePorts();
    void pauseWalk();
    void goToElement(int);
    void saveMeasure(int);
    void autoOpenPorts();
    void getBCoordinates();
    void getCurrentCoords();

    void autoWalk(bool, QString);
    void setDelay(QList<int> *);
    void sendPackage(QSerialPort*, QByteArray, int);
};

#endif // WORKER_H
