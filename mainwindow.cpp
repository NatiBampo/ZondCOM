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
    //connect(ui->measurePushButton, &QPushButton::clicked, this, &MainWindow::measurePushButton_on);
    connect(ui->lightPushButton, &QPushButton::clicked, this, &MainWindow::lightPushButton_on);

    connect(ui->goToButton, &QPushButton::clicked, this, &MainWindow::goToButton_clicked);
    connect(ui->continueFromButton, &QPushButton::clicked, this, &MainWindow::continueFromButton_clicked);
    connect(ui->saveMeasureButton, &QPushButton::clicked, this, &MainWindow::saveMeasureButton_clicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::pauseButton_clicked);
    connect(ui->orientationButton, &QPushButton::clicked, this, &MainWindow::orientationButton_clicked);
    connect(ui->autoPortButton, &QPushButton::clicked, this, &MainWindow::autoPortButton_clicked);
    connect(ui->measureBButton, &QPushButton::clicked, this, &MainWindow::measureBButton_clicked);
    connect(ui->measure2pushButton, &QPushButton::clicked, this, &MainWindow::measure2pushButton_clicked);
    connect(ui->FCMeasureButton, &QPushButton::clicked, this, &MainWindow::on_FCMeasureButton_clicked);
    createWorkerThread();

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->portComboBox->addItem(serialPortInfo.portName());
        ui->keithlyPortComboBox->addItem(serialPortInfo.portName());
        ui->lightPortComboBox->addItem(serialPortInfo.portName());
    }

    delays.append({400, 400, 800, 600, 400, 600, 1000});

    initializeShortKeys();

    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    int bx = (int) settings.value(POINT_B_X, 0).toInt();
    int by = (int) settings.value(POINT_B_Y, 0).toInt();
    ui->BXspinBox->setValue(bx);
    ui->BYspinBox->setValue(by);

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
    connect(this, &MainWindow::measureSignal, worker, &Worker::measureElement);
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
    connect(this, &MainWindow::autoWalkSignal, worker, &Worker::autoWalk);
    //connect(this, &MainWindow::pauseStatus, this, &Worker::pauseStatusSignal);
    connect(this, &MainWindow::getBCoordinatesSignal, worker, &Worker::getBCoordinates);
    connect(this, &MainWindow::getCurrentCoordsSignal, worker, &Worker::getCurrentCoords);
    connect(this, &MainWindow::setDelaySignal, worker, &Worker::setDelay);
    connect(this, &MainWindow::measureFCSignal, worker, &Worker::measureFC);

    connect(worker, &Worker::sendLogSignal, this, &MainWindow::writeLog);
    connect(worker, &Worker::sendProgressBarValueSignal, this, &MainWindow::setProgressBarValue);
    connect(worker, &Worker::sendProgressBarRangeSignal, this, &MainWindow::setProgressBarRange);
    connect(worker, &Worker::openPortResultSignal, this, &MainWindow::openPortResult);
    //сигнал для вывода последних измерений на форму
    connect(worker, &Worker::sendAddTableSignal, this, &MainWindow::addRowToTable);
    //сигнал паузы

    connect(worker, &Worker::sendBCoordsSignal, this, &MainWindow::setBCoords);
    connect(worker, &Worker::sendCurrentCoordsSignal, this, &MainWindow::setBCoords);
    connect(worker, &Worker::sendMessageBox, this, &MainWindow::showMessageBox);
}


void MainWindow::initializeShortKeys()
{
    // запустить по желанию измеряющего
    keyUp  = new QShortcut(this);
    keyUp -> setKey(Qt::Key_Q);
    connect(keyUp, SIGNAL(activated()), this, SLOT(tableUpPushButton_on()));

    keyDown = new QShortcut(this);
    keyDown -> setKey(Qt::Key_E);
    connect(keyDown, SIGNAL(activated()), this, SLOT(tableDownPushButton_on()));

    keyNorth = new QShortcut(this);
    keyNorth -> setKey(Qt::Key_W);//Qt::CTRL +
    connect(keyNorth, SIGNAL(activated()), this, SLOT(forwardPushButton_on()));

    keySouth = new QShortcut(this);
    keySouth -> setKey(Qt::Key_S);
    connect(keySouth, SIGNAL(activated()), this, SLOT(backwardPushButton_on()));

    keyWest = new QShortcut(this);
    keyWest -> setKey(Qt::Key_A);
    connect(keyWest, SIGNAL(activated()), this, SLOT(leftPushButton_on()));

    keyEast = new QShortcut(this);
    keyEast -> setKey(Qt::Key_D);
    connect(keyEast, SIGNAL(activated()), this, SLOT(rightPushButton_on()));

    keyLight = new QShortcut(this);
    keyLight -> setKey(Qt::Key_R);
    connect(keyLight, SIGNAL(activated()), this, SLOT(lightPushButton_on()));

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

        ui->measureBButton->setEnabled(false);
        ui->pauseButton->setEnabled(false);
        ui->scanPushButton->setEnabled(false);
        QMessageBox::information(this, "Сообщение", "COM порты закрыты");

        for (int i = 0; i < portResult.length(); i++)
        {
            portResult[i] = false;
        }
    }
}


void MainWindow::openPortResult(QString port, QString portName, bool result)
{
    if (!result) {
        QMessageBox::warning(this, "Ошибка", "Не удалось подключиться к порту " + port);
    } else {
        //QMessageBox::information(this, "Сообщение", "Выбранный порт: " + port + " для " + portName);
        if (!portName.compare("Planar"))
        {
            ui->portComboBox->setCurrentText(port);
            portResult[0] = true;
        }
        else if (!portName.compare("Keithley"))
        {
            ui->keithlyPortComboBox->setCurrentText(port);
            portResult[1] = true;
        }
        else if (!portName.compare("Light"))
        {
            ui->lightPortComboBox->setCurrentText(port);
            portResult[2] = true;
        }
    }
    bool res = true;
    for (int i = 0; i < portResult.length(); i++)
    {
        if (!portResult.at(i)) res = false;
    }
    //block some buttons in case COMports not open
    ui->measureBButton->setEnabled(res);
    ui->orientationButton->setEnabled(res);
    ui->measure2pushButton->setEnabled(res);
    ui->continueFromButton->setEnabled(res);
    ui->goToButton->setEnabled(res);
    if (res) QMessageBox::information(this, "Сообщение", "Выбранный порты:\n"
                                      + ui->portComboBox->currentText() + " для Планара\n"
                                      + ui->keithlyPortComboBox->currentText() + " для Кейтли\n"
                                      + ui->lightPortComboBox->currentText() + " для Диода\n");
}


void MainWindow::statePushButton_on()
{
    //emit sendPackageSignal(serialPortA5, "State\r\n", 1000);
    emit getCurrentCoordsSignal();
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
    emit tableControllerSignal("Move 100 0\r\n");
}


void MainWindow::measurePushButton_on()
{
    updateDelays();
    emit measureSignal();
}


void MainWindow::lightPushButton_on()
{
    if (ui->lightPushButton->text() == "Диод Вкл")
    {
        emit lightControllerSignal("1111\n");
        ui->lightPushButton->setText("Диод Выкл");
    } else {
        emit lightControllerSignal("0001\n");
        ui->lightPushButton->setText("Диод Вкл");
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
    //addElement(index, 7, index);//индекс

    //focusing on the last row
    QItemSelectionModel::SelectionFlags flags = QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows;
    QModelIndex i = ui->tableView->model()->index(index, 0);
    ui->tableView->selectionModel()->select(i, flags);

    ui->columnSpinBox->setValue(column + 1);
    ui->rowSpinBox->setValue(index % (rowCount * colCount) / colCount + 1);
    ui->elemSpinBox->setValue(index % (rowCount * colCount) % colCount + 1);
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

    if (checked)
    {
        ui->pauseButton->setEnabled(true);
        ui->scanPushButton->setText("Завершить обход");

        QFileDialog directory;
        dir_name = directory.getSaveFileName(this,"Choose directory and name");
        ui->addressLabel->setText(dir_name);
        updateDelays();
        emit autoWalkSignal(true, dir_name);
    }
    else {
        ui->pauseButton->setEnabled(false);
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
    double AX = (double)ui->AXspinBox->value();
    double AY = (double)ui->AYspinBox->value();
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
    model = new QStandardItemModel(numRows, 7, this);
    model->setHeaderData(0, Qt::Horizontal, "Столб");
    model->setHeaderData(1, Qt::Horizontal, "Ряд");
    model->setHeaderData(2, Qt::Horizontal, "Элем");
    model->setHeaderData(3, Qt::Horizontal, "FC");
    model->setHeaderData(4, Qt::Horizontal, "DC10mV");
    model->setHeaderData(5, Qt::Horizontal, "DC1V");
    model->setHeaderData(6, Qt::Horizontal, "PhotoCur");
    //model->setHeaderData(7, Qt::Horizontal, "№");
    ui->tableView->setModel(model);


    emit scanningPlateSignal(AX, AY, BX, BY, stepX, stepY, numberX, numberY, colSlide, all_three, upLeft, upRight, downLeft, downRight);
    updateDelays();
    ui->scanPushButton->setEnabled(true);
    ui->goToButton->setEnabled(true);
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

    ui->AXspinBox->setValue(0);
    ui->AYspinBox->setValue(0);
    syncSettings();
}


void MainWindow::setCurrentCoords(int x, int y)
{
    ui->xLineEdit->setText(QString::number(x));
    ui->yLineEdit->setText(QString::number(y));
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
    //emit showChartsSignal(dir_name);

    /*QFileDialog directory;
    QString stats_dir = directory.getSaveFileName(this,"Выберите данные для построенния графика");
    stats->showCharts(stats_dir);*/

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
    delays[5] = ui->voltageSpinBox->value();
    delays[6] = ui->planarSpinBox->value();

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



void MainWindow::on_FCMeasureButton_clicked()
{
    updateDelays();
    emit measureFCSignal();
}

