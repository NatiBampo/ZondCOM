#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QThread>
#include <QFileDialog>
#include <QtCharts>


//using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(1);
    ui->progressBar->setValue(0);

    connect(ui->statePushButton, &QPushButton::clicked, this, &MainWindow::statePushButton_on);
    connect(ui->openPortPushButton, &QPushButton::clicked, this, &MainWindow::openPortPushButton_on);
    connect(ui->coordsPushButton, &QPushButton::clicked, this, &MainWindow::coordsPushButton_on);
    connect(ui->tableUpPushButton, &QPushButton::clicked, this, &MainWindow::tableUpPushButton_on);
    connect(ui->tableDownPushButton, &QPushButton::clicked, this, &MainWindow::tableDownPushButton_on);
    connect(ui->forwardPushButton, &QPushButton::clicked, this, &MainWindow::forwardPushButton_on);
    connect(ui->backwardPushButton, &QPushButton::clicked, this, &MainWindow::backwardPushButton_on);
    connect(ui->leftPushButton, &QPushButton::clicked, this, &MainWindow::leftPushButton_on);
    connect(ui->rightPushButton, &QPushButton::clicked, this, &MainWindow::rightPushButton_on);
    connect(ui->scanPushButton, &QPushButton::clicked, this, &MainWindow::scanPushButton_clicked);
    connect(ui->measurePushButton, &QPushButton::clicked, this, &MainWindow::measurePushButton_on);
    connect(ui->lightPushButton, &QPushButton::clicked, this, &MainWindow::lightPushButton_on);

    connect(ui->goToButton, &QPushButton::clicked, this, &MainWindow::goToButton_clicked);
    connect(ui->continueFromButton, &QPushButton::clicked, this, &MainWindow::continueFromButton_clicked);
    connect(ui->saveMeasureButton, &QPushButton::clicked, this, &MainWindow::saveMeasureButton_clicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::pauseButton_clicked);
    connect(ui->orientationButton, &QPushButton::clicked, this, &MainWindow::orientationButton_clicked);
    connect(ui->autoPortButton, &QPushButton::clicked, this, &MainWindow::autoPortButton_clicked);
    connect(ui->measureBButton, &QPushButton::clicked, this, &MainWindow::measureBButton_clicked);
    connect(ui->measure2pushButton, &QPushButton::clicked, this, &MainWindow::measure2pushButton_clicked);

    createWorkerThread();

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->portComboBox->addItem(serialPortInfo.portName());
        ui->keithlyPortComboBox->addItem(serialPortInfo.portName());
        ui->lightPortComboBox->addItem(serialPortInfo.portName());
    }

    delays.append({400, 400, 800, 600, 400});

    initializeShortKeys();

    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    int bx = (int) settings.value(POINT_B_X, 0).toInt();
    int by = (int) settings.value(POINT_B_Y, 0).toInt();

    //createStatsThread();
    //statsThread.quit();
    //statsThread.terminate();
}

MainWindow::~MainWindow()
{
    delete ui;
    emit closePortsSignal();
    workerThread.quit();
    workerThread.terminate();
}


void MainWindow::createWorkerThread()
{
    worker = new Worker(&mutex);
    worker->moveToThread(&workerThread);
    workerThread.start();

    connect(this, &MainWindow::scanningPlateSignal, worker, &Worker::scanningPlate);
    connect(this, &MainWindow::measureSignal, worker, &Worker::measureElement2);
    connect(this, &MainWindow::openPortsSignal, worker, &Worker::openPorts);
    connect(this, &MainWindow::autoOpenPortsSignal, worker, &Worker::autoOpenPorts);
    connect(this, &MainWindow::tableControllerSignal, worker, &Worker::tableController);
    connect(this, &MainWindow::lightControllerSignal, worker, &Worker::lightController);
    connect(this, &MainWindow::closePortsSignal, worker, &Worker::closePorts);
    //остановка цикла обхода
    connect(this, &MainWindow::sendPauseCommandSignal, worker, &Worker::pauseWalk);
    //продолжение обхода
    //connect(this, &MainWindow::sendContinueWalkSignal, worker, &Worker::continueWalk);
    //переход на элемент в строке
    connect(this, &MainWindow::goToElementSignal, worker, &Worker::goToElement);
    //сохрание элемента в строке
    connect(this, &MainWindow::saveMeasureSignal, worker, &Worker::saveMeasure);
    //начать обход
    connect(this, &MainWindow::autoWalkSignal, worker, &Worker::autoWalk2);
    //connect(this, &MainWindow::pauseStatus, this, &Worker::pauseStatusSignal);
    connect(this, &MainWindow::getBCoordinatesSignal, worker, &Worker::getBCoordinates);

    connect(this, &MainWindow::setDelaySignal, worker, &Worker::setDelay);

    connect(worker, &Worker::sendLogSignal, this, &MainWindow::writeLog);
    connect(worker, &Worker::sendProgressBarValueSignal, this, &MainWindow::setProgressBarValue);
    connect(worker, &Worker::sendProgressBarRangeSignal, this, &MainWindow::setProgressBarRange);
    connect(worker, &Worker::openPortResultSignal, this, &MainWindow::openPortResult);
    //сигнал для вывода последних измерений на форму
    connect(worker, &Worker::sendAddTableSignal, this, &MainWindow::addRowToTable);
    //сигнал паузы

    connect(worker, &Worker::sendBCoordsSignal, this, &MainWindow::setBCoords);
    connect(worker, &Worker::sendMessageBox, this, &MainWindow::showMessageBox);
}


void MainWindow::initializeShortKeys()
{
    keyUp = new QShortcut(this);
    keyUp -> setKey(Qt::Key_Up);//Qt::CTRL +
    connect(keyUp, SIGNAL(activated()), this, SLOT(forwardPushButton_on()));

    keyDown = new QShortcut(this);
    keyDown -> setKey(Qt::Key_Down);
    connect(keyDown, SIGNAL(activated()), this, SLOT(backwardPushButton_on()));

    keyLeft = new QShortcut(this);
    keyLeft -> setKey(Qt::Key_Left);
    connect(keyLeft, SIGNAL(activated()), this, SLOT(leftPushButton_on()));

    keyRight = new QShortcut(this);
    keyRight -> setKey(Qt::Key_Right);
    connect(keyRight, SIGNAL(activated()), this, SLOT(rightPushButton_on()));

}


void MainWindow::openPortPushButton_on()
{
    if (ui->openPortPushButton->text() == "Открыть") {
        emit openPortsSignal(ui->portComboBox->currentText(), ui->keithlyPortComboBox->currentText(), ui->lightPortComboBox->currentText());
        ui->openPortPushButton->setText("Закрыть");
    } else {
        emit closePortsSignal();
        ui->openPortPushButton->setText("Открыть");
        ui->portComboBox->setCurrentText("Планар");
        ui->keithlyPortComboBox->setCurrentText("Keithley");
        ui->lightPortComboBox->setCurrentText("Диод");
        QMessageBox::information(this, "Сообщение", "COM порты закрыты");
    }
}


void MainWindow::openPortResult(QString port, QString portName, bool result)
{
    if (!result) {
        QMessageBox::warning(this, "Ошибка", "Не удалось подключиться к порту " + port);
    } else {
        QMessageBox::information(this, "Сообщение", "Выбранный порт: " + port + " для " + portName);
        if (!portName.compare("Planar")) ui->portComboBox->setCurrentText(port);
        else if (!portName.compare("Keithley")) ui->keithlyPortComboBox->setCurrentText(port);
        else if (!portName.compare("Light")) ui->lightPortComboBox->setCurrentText(port);
    }
}


void MainWindow::statePushButton_on()
{
    //emit sendPackageSignal(serialPortA5, "State\r\n", 1000);
    emit tableControllerSignal("State\r\n");
}


void MainWindow::coordsPushButton_on()
{
    QByteArray x = ui->xLineEdit->text().toUtf8();
    QByteArray y = ui->yLineEdit->text().toUtf8();
    //emit sendPackageSignal(serialPortA5, "Set " + x + " " + y + '\r' + '\n', 1000);
    emit tableControllerSignal("Set " + x + " " + y + '\r' + '\n');
}


void MainWindow::tableUpPushButton_on()
{
    emit tableControllerSignal("Table UP\r\n");
}


void MainWindow::tableDownPushButton_on()
{
    emit tableControllerSignal("Table DN\r\n");
}


void MainWindow::forwardPushButton_on()
{
    emit tableControllerSignal("Move 0 100\r\n");
}


void MainWindow::backwardPushButton_on()
{
    emit tableControllerSignal("Move 0 -100\r\n");
}


void MainWindow::leftPushButton_on()
{
    emit tableControllerSignal("Move -100 0\r\n");
}


void MainWindow::rightPushButton_on()
{
    qDebug() << clock();
    updateDelays();
    syncSettings();
    emit tableControllerSignal("Move 100 0\r\n");
}


void MainWindow::measurePushButton_on()
{
    updateDelays();
    emit measureSignal();
}


void MainWindow::lightPushButton_on()
{
    if (ui->lightPushButton->text() == "Включить") {
        emit lightControllerSignal("1111\n");
        ui->lightPushButton->setText("Выключить");
    } else {
        emit lightControllerSignal("0001\n");
        ui->lightPushButton->setText("Включить");
    }
}


//функция записи последних измерений в таблицу
void MainWindow::addRowToTable(int index, double FC, double DC10mV, double DC1V, double LC)
{
    currentIndex = index;
    int rowCount = ui->numYspinBox->value();
    int colCount = ui->numXspinBox->value() + 1;
    int column = index / (rowCount * colCount);
    addElement(index, 0, column + 1);//колонка
    addElement(index, 1, index % (rowCount * colCount) / colCount + 1);//ряд
    addElement(index, 2, index % (rowCount * colCount) % colCount + 1);//элемент
    addElement(index, 3, FC);//прямой ток
    addElement(index, 4, DC10mV);//темновой ток при 10мВ
    addElement(index, 5, DC1V);//темновой ток при 1В
    addElement(index, 6, LC);//фототок
    addElement(index, 7, index);//индекс
}


//записываем ячейку таблицы на форму
void MainWindow::addElement(int row, int element, double value)
{
    QModelIndex index;
    index = model->index(row, element);
    model->setData(index, value);
}


void MainWindow::writeLog(QByteArray log)
{
    ui->logsListWidget->addItem(log);
}


void MainWindow::setProgressBarValue(int val)
{
    ui->progressBar->setValue(val);
}


void MainWindow::setProgressBarRange(int minVal, int maxVal)
{
    ui->progressBar->setMinimum(minVal);
    ui->progressBar->setMaximum(maxVal);
    finalIndex = maxVal;
}


void MainWindow::pauseButton_clicked(bool checked)
{
    if (checked)
    {
        ui->pauseButton->setText("Продолжить");
    } else
    {
        updateDelays();
        ui->pauseButton->setText("Пауза");
    }
    mutex.lock();
    //в перспективе добавить вспомогателный поток или выходить из цикла обхода пластины вместо ожидания даже при паузе
    worker->pauseWalk();
    mutex.unlock();
}


int MainWindow::getUIIndex()
{
    int row = ui->rowSpinBox->value();
    int element = ui->elemSpinBox->value();
    int col = ui->columnSpinBox->value();
    int numberX = ui->numXspinBox->value();
    int numberY = ui->numYspinBox->value();
    int index = (col - 1) * (numberX + 1) * numberY + (row - 1) * (numberX + 1) + element - 1;
    return index;
}


void MainWindow::goToButton_clicked()
{
    emit goToElementSignal(getUIIndex());
}


void MainWindow::saveMeasureButton_clicked()
{
    if (!ui->scanPushButton->isChecked()) {
        updateDelays();
        emit saveMeasureSignal(getUIIndex());
    }
}


void MainWindow::continueFromButton_clicked(bool checked)
{
    if(!ui->scanPushButton->isChecked()){
        if (checked){
            ui->pauseButton->setText("Пауза");
            ui->continueFromButton->setText("Завершить обход");
            mutex.lock();
            worker->stopWalk();
            mutex.unlock();
            emit autoWalkSignal(false, dir_name);
        }
        else {
            ui->continueFromButton->setText("Продолжить обход с элемента");
        }
    }
    else {
        ui->continueFromButton->setChecked(false);
        ui->continueFromButton->setText("Продолжить обход с элемента");
    }

}


void MainWindow::scanPushButton_clicked(bool checked)
{
    if (checked) {
        ui->scanPushButton->setText("Завершить обход");

        QFileDialog directory;
        dir_name = directory.getSaveFileName(this,"Choose directory and name");
        ui->addressLabel->setText(dir_name);
        updateDelays();
        emit autoWalkSignal(true, dir_name);
    }
    else {
        ui->scanPushButton->setText("Начать");
        ui->pauseButton->setChecked(false);
        ui->pauseButton->setText("Пауза");
        currentIndex = finalIndex;
        mutex.lock();
        worker->stopWalk();
        mutex.unlock();
    }
}


void MainWindow::orientationButton_clicked()
{
    double BX = (double)ui->BXspinBox->value();
    double BY = (double)ui->BYspinBox->value();
    double stepX = (double)ui->stepXspinBox->value();
    double stepY = (double)ui->stepYspinBox->value();
    double numberX = (double)ui->numXspinBox->value();
    double numberY = (double)ui->numYspinBox->value();
    //сдвиг меж столбцов и рядов
    double colSlide = (double)ui->stepColSpinBox->value();
    //double rowSlide = (double)ui->stepRowSpinBox->value();
    bool all_three = ui->checkBox->isChecked();

    //die offset due to cirle border cut
    int upLeft = ui->upLeftSpinBox->value();
    int upRight = ui->upRightSpinBox->value();
    int downLeft = ui->downLeftSpinBox->value();
    int downRight = ui->downRightSpinBox->value();

    //создаем модель таблицы для отображения(впоследствие можно сократить до N рядов)
    int numRows = (numberX+1) * numberY;
    if (all_three) {
        numRows += numberX * (numberY*2 - upLeft - upRight - downLeft - downRight) ;
    }
    model = new QStandardItemModel(numRows, 8, this);
    model->setHeaderData(0, Qt::Horizontal, "Столбец");
    model->setHeaderData(1, Qt::Horizontal, "Ряд");
    model->setHeaderData(2, Qt::Horizontal, "Элемент");
    model->setHeaderData(3, Qt::Horizontal, "FC");
    model->setHeaderData(4, Qt::Horizontal, "DC10mV");
    model->setHeaderData(5, Qt::Horizontal, "DC1V");
    model->setHeaderData(6, Qt::Horizontal, "PhotoC");
    model->setHeaderData(7, Qt::Horizontal, "№");
    ui->tableView->setModel(model);


    emit scanningPlateSignal(BX, BY, stepX, stepY, numberX, numberY, colSlide, all_three, upLeft, upRight, downLeft, downRight);
    syncSettings();
}


void MainWindow::autoPortButton_clicked()
{
    emit autoOpenPortsSignal();
    ui->openPortPushButton->setText("Закрыть");
}


void MainWindow::measureBButton_clicked()
{
    emit getBCoordinatesSignal();
}


void MainWindow::setBCoords(int x, int y)
{
    ui->BXspinBox->setValue(x);
    ui->BYspinBox->setValue(y);
}


void  MainWindow::createStatsThread()
{
    stats = new Stats();
    stats->moveToThread(&statsThread);
    statsThread.start();
    connect(this, &MainWindow::showChartsSignal, stats, &Stats::showCharts);
}


void MainWindow::on_chartsButton_clicked()
{
    emit showChartsSignal(dir_name);
}


void MainWindow::showMessageBox(QString msg_type, QString msg)
{
    if (msg_type == "information"){
        QMessageBox::information(this, "Информация", msg);
    } else if (msg_type == "critical") {
        QMessageBox::critical(this, "Ошибка", msg);
    } else if (msg_type == "warning") {
        QMessageBox::warning(this, "Предупреждение", msg);
    } else {
        QMessageBox::information(this, msg_type, msg);
    }
}


void MainWindow::updateDelays()
{
    delays[0] = ui->zeroSpinBox->value();
    delays[1] = ui->FCSpinBox->value();
    delays[2] = ui->DC10spinBox->value();
    delays[3] = ui->DC1VSpinBox->value();
    delays[4] = ui->lightSpinBox->value();
    emit setDelaySignal(&delays);
}


void MainWindow::syncSettings()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    int BX = ui->BXspinBox->value();
    int BY = ui->BYspinBox->value();

    if(BX != 0 || BY != 0){
        settings.setValue(POINT_B_X, BX);
        settings.setValue(POINT_B_Y, BY);
    }
    settings.sync();
}


void MainWindow::measure2pushButton_clicked()
{
    updateDelays();
    emit measureSignal();
}
