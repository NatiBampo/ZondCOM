#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <worker.h>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QMutex>
#include <stats.h>

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
    Stats *stats;
    QStandardItemModel *model;
    QThread workerThread;
    QThread statsThread;
    QMutex mutex;
    QString dir_name;
    int currentIndex = 0;
    int finalIndex = 0;
    void createWorkerThread();
    void createStatsThread();
    void addElement(int, int, double);
    int getUIIndex();


signals:
    void scanningPlateSignal(double, double, double, double, double, double, double, double, bool, int, int, int, int);
    void measureSignal();
    void tableControllerSignal(QByteArray);
    void lightControllerSignal(QByteArray);
    void openPortsSignal(QString, QString, QString);
    void closePortsSignal();
    void goToElementSignal(int);
    void sendPauseCommandSignal();
    void saveMeasureSignal(int);
    void autoWalkSignal(bool, QString);
    void autoOpenPortsSignal();
    void getBCoordinatesSignal();
    void showChartsSignal(QString);

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
    void openPortResult(QString, QString, bool);
    void addRowToTable(int, double, double, double, double);
    void setBCoords(int, int);

    void pauseButton_clicked(bool);
    void goToButton_clicked();
    void saveMeasureButton_clicked();
    void continueFromButton_clicked(bool);
    void orientationButton_clicked();
    void scanPushButton_clicked(bool checked);
    void autoPortButton_clicked();
    void measureBButton_clicked();
    void on_chartsButton_clicked();
};
#endif // MAINWINDOW_H
