#ifndef KEITHLEY_H
#define KEITHLEY_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>


namespace Ui {
class Keithley;
}

class Keithley : public QMainWindow
{
    Q_OBJECT

public:
    Keithley(QWidget *parent = nullptr);
    ~Keithley();

private:
    Ui::Keithley *ui = nullptr;
    QSerialPort *m_serial = nullptr;
    QString port_name;
    QString lastAnswer;

    void writeData(const QByteArray&);


public slots:
    void openSerialPort(QString);
    void closeSerialPort();
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    void sendStatus(QString);
};

#endif // KEITHLEY_H
