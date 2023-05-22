#include "keithley.h"
#include "ui_keithley.h"

#include <QMessageBox>


Keithley::Keithley(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Keithley),
    m_serial(new QSerialPort(this))
{
    ui->setupUi(this);
    connect(m_serial, &QSerialPort::errorOccurred, this, &Keithley::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &Keithley::readData);
    //connect(m_serial, &Worker::writeData, this, &Keithley::writeData);
}

Keithley::~Keithley()
{
    delete ui;
}

void Keithley::openSerialPort(QString name)
{
    m_serial->setPortName(name);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::DataBits::Data8);
    m_serial->setParity(QSerialPort::Parity::NoParity);
    m_serial->setStopBits(QSerialPort::StopBits::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);


    if (m_serial->open(QIODevice::ReadWrite)) {
        //showStatusMessage
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
    }
}

void Keithley::closeSerialPort()
{
    if (m_serial->isOpen()) m_serial->close();
}

void Keithley::writeData(const QByteArray &data)
{
    m_serial->write(data);
}

void Keithley::readData()
{
    const QByteArray data = m_serial->readAll();
}

void Keithley::sendStatus(QString msg)
{
    qDebug() << msg;
}

void Keithley::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

//void Worker::MeasureDie(QSerialPort *serialPortA5, QSerialPort *serialPortKeithly) {
//    KeithlyZeroCorrection(serialPortKeithly);
//    emit sendPackageSignal(serialPortA5, "Table UP\r\n", ANSWER_DELAY);
//    Keithly05VSet(serialPortKeithly);
//    ForwardCurrent = KeithlyGet(serialPortKeithly);
//    Keithly10mVSet(serialPortKeithly);
//    QThread::msleep(800);
//    DarkCurrent10mV = KeithlyGet(serialPortKeithly);
//    Keithly1VSet(serialPortKeithly);
//    DarkCurrent1V = KeithlyGet(serialPortKeithly);
//    LightOn();
//    Keithly10mVSet(serialPortKeithly);
//    emit sendPackageSignal(serialPortKeithly, "CURR:RANG 2e-6\n", NO_ANSWER_DELAY);
//    QThread::msleep(200);
//    LightCurrent = KeithlyGet(serialPortKeithly);
//    emit sendPackageSignal(serialPortKeithly, "*RST\n", NO_ANSWER_DELAY);
//    emit sendLogSignal((QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
//                        QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4)).toUtf8());
//    LightOff();
//}

//void Worker::KeithlyZeroCorrection(QSerialPort *serialPort) {
//    emit sendPackageSignal(serialPort, "*RST\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SYST:ZCH ON\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "CURR:RANG 2e-9\n", NO_ANSWER_DELAY);
//    QThread::msleep(400);
//    emit sendPackageSignal(serialPort, "INIT\n", NO_ANSWER_DELAY);
//    QThread::msleep(400);
//    emit sendPackageSignal(serialPort, "SYST:ZCOR:STAT OFF\n", NO_ANSWER_DELAY);
//    QThread::msleep(400);
//    emit sendPackageSignal(serialPort, "SYST:ZCOR:ACQ\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SYST:ZCH OFF\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SYST:ZCOR ON\n", NO_ANSWER_DELAY);
//}

//void Worker::Keithly05VSet(QSerialPort *serialPort) {
//    emit sendPackageSignal(serialPort, "CURR:RANG 2e-3\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SOUR:VOLT:RANG 1\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SOUR:VOLT " + QByteArray::number(0.6) + '\n', NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SOUR:VOLT:ILIM 1e-3\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
//    QThread::msleep(300);
//}

//double Worker::KeithlyGet(QSerialPort *serialPort) {
//    emit sendPackageSignal(serialPort, "READ?\n", ANSWER_DELAY);
//    QByteArray byteArray = lastAnswer;
//    byteArray = byteArray.remove(byteArray.indexOf("A"), byteArray.length() - byteArray.indexOf("A"));
//    return byteArray.toDouble();
//}

//void Worker::Keithly10mVSet(QSerialPort *serialPort) {
//    emit sendPackageSignal(serialPort, "CURR:RANG 2e-10\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SOUR:VOLT -1e-2\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
//}

//void Worker::Keithly1VSet(QSerialPort *serialPort) {
//    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SOUR:VOLT -1\n", NO_ANSWER_DELAY);
//    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
//    QThread::msleep(600);
//}
