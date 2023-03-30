#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <worker.h>
#include <QStandardItemModel>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Worker *worker;
    QStandardItemModel *model;
    QThread workerThread;
    int currentIndex = 0;
    int finalIndex = 0;
    void createWorkerThread();
    void addElement(int, int, double);

signals:
    void scanningPlateSignal(double, double, double, double, double, double, double, double, double, double, QString);
    void measureSignal();
    void tableControllerSignal(QByteArray);
    void lightControllerSignal(QByteArray);
    void openPortsSignal(QString, QString, QString);
    void closePortsSignal();
    void goToElementSignal(int);
    void sendPauseCommandSignal();
    void sendContinueWalkSignal(int);
    void saveMeasureSignal(int);

private slots:
    void openPortPushButton_on();
    void coordsPushButton_on();
    void tableUpPushButton_on();
    void tableDownPushButton_on();
    void forwardPushButton_on();
    void backwardPushButton_on();
    void leftPushButton_on();
    void rightPushButton_on();
    void statePushButton_on();
    void measurePushButton_on();
    void lightPushButton_on();

    void writeLog(QByteArray);
    void setProgressBarValue(int);
    void setProgressBarRange(int, int);
    void openPortResult(QString, bool);
    void addRowToTable(int, double, double, double, double);
    void pauseButton_clicked(bool);
    void goToButton_clicked();
    void saveMeasureButton_clicked();
    void continueFromButton_clicked();
    void orientationButton_clicked();
    void scanPushButton_clicked(bool checked);
};
#endif // MAINWINDOW_H
