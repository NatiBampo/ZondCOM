#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <worker.h>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QMutex>
#include <stats.h>
#include <QSettings>
#include <QShortcut>


#define ORGANIZATION_NAME "ZOO"
#define ORGANIZATION_DOMAIN "www.ZOO.ru"
#define APPLICATION_NAME "QSettings Program"

#define POINT_B_X "point_B_x"
#define POINT_B_Y "point_B_x"

#define ZERO_D "zero_d"
#define FC_D "fc_d"
#define DC10mV_D "dc10mV_d"
#define DC1V_D "dc1V_d"
#define LIGHT_D "light_d"
#define PLANAR_D "planar_d"
#define FC_V "fc_v"

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
    QList<int> delays;
    QList<bool> portResult = {false, false, false};
    QShortcut *keyUp;
    QShortcut *keyDown;
    QShortcut *keyNorth;
    QShortcut *keySouth;
    QShortcut *keyEast;
    QShortcut *keyWest;
    QShortcut *keyLight;
    int currentIndex = 0;
    int finalIndex = 0;
    void createWorkerThread();
    void createStatsThread();
    void addElement(int, int, double);
    int getUIIndex();
    void updateDelays();
    void syncSettings();
    void initializeShortKeys();
//    void showMessageBox(QString, QString);


signals:
    void scanningPlateSignal(double, double, double, double, double, double, double, double, double, bool, int, int, int, int);
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
    void setDelaySignal(QList<int>*);
    void getCurrentCoordsSignal();
    void measureFCSignal();

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
    void setCurrentCoords(int, int);
    void pauseButton_clicked(bool);
    void goToButton_clicked();
    void saveMeasureButton_clicked();
    void continueFromButton_clicked(bool);
    void orientationButton_clicked();
    void scanPushButton_clicked(bool checked);
    void autoPortButton_clicked();
    void measureBButton_clicked();
    void on_chartsButton_clicked();
    void measure2pushButton_clicked();
    void showMessageBox(QString, QString);

    void on_FCMeasureButton_clicked();
};
#endif // MAINWINDOW_H
