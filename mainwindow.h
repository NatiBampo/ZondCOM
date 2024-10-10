#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include <QStandardItemModel>
#include <QMutex>
#include <QSettings>
#include <QShortcut>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QThread>
#include <QFileDialog>
#include <QtCharts>
#include <QDebug>
#include <QFile>
#include <QRect>
#include <QPainter>

#include "stats.h"
#include "worker.h"
#include "tabcanvas.h"
#include "serials.h"
#include "LoggingCategories.h"

#define ORGANIZATION_NAME "Orion"
#define ORGANIZATION_DOMAIN "AlfaCentarius"
#define APPLICATION_NAME "QSettings Program"

#define POINT_B_X "point_B_x"
#define POINT_B_Y "point_B_y"

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
    Worker *worker;

private:
    Ui::MainWindow *ui;
    Stats *stats;
    QStandardItemModel *model = nullptr;
    QThread workerThread;
    QThread statsThread;
    QMutex mutex;
    QString dir_name;
    //QList<int> delays;
    //QList<bool> portResult = {false, false, false};
    bool orientation = false;
    bool busy = false;
    void checkBusy();
    bool portsReady();
    bool readyCheck();
    bool adm = false;
    QShortcut *keyUp;
    QShortcut *keyDown;
    QShortcut *keyNorth;
    QShortcut *keySouth;
    QShortcut *keyEast;
    QShortcut *keyWest;
    QShortcut *keyLight;

    struct Peripherals* periph = nullptr;
    struct WalkSettings* walk = nullptr;
    struct Dots* dots = nullptr;
    struct Delays* delays = nullptr;
    struct DieParameters* die = nullptr;
    struct Currents* currs = nullptr;

    int gapIndex;

    void createWorkerThread();
    void createStatsThread();
    void addElement(int, int, double);
    int getUIIndex();
    void updateDelays();
    void syncSettings();
    void initializeShortKeys();
    void activateShortKeys();
    void deactivateShortKeys();
    void initializeModel();
    void writeCSV();
    void drawCanvas();
    void planarSender(QString);
    void initializeSettings();
    void initConnects();
    void updateDelays();


signals:
    void calculateDotsSignal(struct DieParameters*,
                        struct Dots*,
                        struct WalkSettings*);
    void measureSignal(struct WalkSettings* ,
                       struct Delays* ,
                       struct Currents* ,
                       struct Dots* );
    void tableControllerSignal(QByteArray, struct WalkSettings* );
    void lightControllerSignal(QByteArray, struct WalkSettings* );
    void openPortsSignal(QString, QString, QString);
    void closePortsSignal();
    void goToElementSignal(int, struct WalkSettings* );
    void sendPauseCommandSignal();
    void saveMeasureSignal(struct WalkSettings* , struct Delays* ,
                           struct Dots* , struct Currents* );
    void autoWalkSignal(struct WalkSettings* ,
                        struct Peripherals* ,
                        struct Dots* ,
                        struct DieParameters* );
    void autoOpenPortsSignal(struct Peripherals*);
    void showChartsSignal(QString);
    void getCurrentCoordsSignal(int, bool);
    void measureFCSignal(struct WalkSettings* ,
                         struct Delays* ,
                         struct Currents*,
                         struct Dots*);
    void openCsvFileSignal(QString);
    void copyUpSlot(int, QString);



public slots:
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

    void savePushButton_clicked();
    void on_loadFilePushButton_clicked();
    void stopPushButton_clicked();
    void on_toAPushButton_clicked();
    void on_toBPushButton_clicked();
    void on_FCMeasureButton_clicked();
    void on_hotKeysCheckBox_stateChanged(int arg1);

    void writeLog(QByteArray);
    void setProgressBarValue(int);
    void setProgressBarRange(int, int);
    void openPortResult();
    void addRowToTable();
    void setBCoords(int, int);
    void setCurrentCoords(int, int);

    void showMessageBox(QString, QString);
    void sendEndWalk();
    void setEndOfWalkTime(QString);

private slots:
    void on_planarCMDButton_clicked();
    void on_resetPortsPushButton_clicked();
    void on_stop2pushButton_clicked();
    void on_admCheckBox_stateChanged(int arg1);
    void on_schemePushButton_clicked();
};
#endif // MAINWINDOW_H
