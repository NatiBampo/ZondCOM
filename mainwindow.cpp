#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QThread>
#include <QFileDialog>

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
    //
    connect(ui->goToButton, &QPushButton::clicked, this, &MainWindow::goToButton_clicked);
    connect(ui->continueFromButton, &QPushButton::clicked, this, &MainWindow::continueFromButton_clicked);
    connect(ui->saveMeasureButton, &QPushButton::clicked, this, &MainWindow::saveMeasureButton_clicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::pauseButton_clicked);
    connect(ui->orientationButton, &QPushButton::clicked, this, &MainWindow::orientationButton_clicked);


    createWorkerThread();

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->portComboBox->addItem(serialPortInfo.portName());
        ui->keithlyPortComboBox->addItem(serialPortInfo.portName());
        ui->lightPortComboBox->addItem(serialPortInfo.portName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    emit closePortsSignal();
    workerThread.quit();
    workerThread.terminate();
}

void MainWindow::createWorkerThread() {
    worker = new Worker();
    worker->moveToThread(&workerThread);
    workerThread.start();

    connect(this, &MainWindow::scanningPlateSignal, worker, &Worker::scanningPlate);
    connect(this, &MainWindow::measureSignal, worker, &Worker::measureElement);
    connect(this, &MainWindow::openPortsSignal, worker, &Worker::openPorts);
    connect(this, &MainWindow::tableControllerSignal, worker, &Worker::tableController);
    connect(this, &MainWindow::lightControllerSignal, worker, &Worker::lightController);
    connect(this, &MainWindow::closePortsSignal, worker, &Worker::closePorts);
    //остановка цикла обхода
    connect(this, &MainWindow::sendPauseCommandSignal, worker, &Worker::pauseWalk);
    //продолжение обхода
    connect(this, &MainWindow::sendContinueWalkSignal, worker, &Worker::continueWalk);
    //переход на элемент в строке
    connect(this, &MainWindow::goToElementSignal, worker, &Worker::goToElement);
    //сохрание элемента в строке
    connect(this, &MainWindow::saveMeasureSignal, worker, &Worker::saveMeasure);
    //начать обход
    connect(this, &MainWindow::autoWalkSignal, worker, &Worker::autoWalk);

    connect(worker, &Worker::sendLogSignal, this, &MainWindow::writeLog);
    connect(worker, &Worker::sendProgressBarValueSignal, this, &MainWindow::setProgressBarValue);
    connect(worker, &Worker::sendProgressBarRangeSignal, this, &MainWindow::setProgressBarRange);
    connect(worker, &Worker::openPortResultSignal, this, &MainWindow::openPortResult);
    //сигнал для вывода последних измерений на форму
    connect(worker, &Worker::sendAddTableSignal, this, &MainWindow::addRowToTable);
}

void MainWindow::openPortPushButton_on() {
    if (ui->openPortPushButton->text() == "Открыть") {
        emit openPortsSignal(ui->portComboBox->currentText(), ui->keithlyPortComboBox->currentText(), ui->lightPortComboBox->currentText());
        ui->openPortPushButton->setText("Закрыть");
    } else {
        emit closePortsSignal();
        ui->openPortPushButton->setText("Открыть");
    }
}

void MainWindow::openPortResult(QString portName, bool result) {
    if (!result) {
        QMessageBox::warning(this, "Ошибка", "Не удалось подключиться к порту " + portName);
    } else {
        QMessageBox::information(this, "Сообщение", "Выбранный порт: " + portName);
    }
}

void MainWindow::statePushButton_on() {
    //emit sendPackageSignal(serialPortA5, "State\r\n", 1000);
    emit tableControllerSignal("State\r\n");
}

void MainWindow::coordsPushButton_on() {
    QByteArray x = ui->xLineEdit->text().toUtf8();
    QByteArray y = ui->yLineEdit->text().toUtf8();
    //emit sendPackageSignal(serialPortA5, "Set " + x + " " + y + '\r' + '\n', 1000);
    emit tableControllerSignal("Set " + x + " " + y + '\r' + '\n');
}

void MainWindow::tableUpPushButton_on() {
    //emit sendPackageSignal(serialPortA5, "Table UP\r\n", 1000);
    emit tableControllerSignal("Table UP\r\n");
}

void MainWindow::tableDownPushButton_on() {
    //emit sendPackageSignal(serialPortA5, "Table DN\r\n", 1000);
    emit tableControllerSignal("Table DN\r\n");
}

void MainWindow::forwardPushButton_on() {
    //emit sendPackageSignal(serialPortA5, "Move 0 100\r\n", 1000);
    emit tableControllerSignal("Move 0 100\r\n");
}

void MainWindow::backwardPushButton_on() {
    //emit sendPackageSignal(serialPortA5, "Move 0 -100\r\n", 1000);
    emit tableControllerSignal("Move 0 -100\r\n");
}

void MainWindow::leftPushButton_on() {
    //emit sendPackageSignal(serialPortA5, "Move -100 0\r\n", 1000);
    emit tableControllerSignal("Move -100 0\r\n");
}

void MainWindow::rightPushButton_on() {
    //emit sendPackageSignal(serialPortA5, "Move 100 0\r\n", 1000);
    emit tableControllerSignal("Move 100 0\r\n");
}

void MainWindow::measurePushButton_on() {
    emit measureSignal();
}

void MainWindow::lightPushButton_on() {
    if (ui->lightPushButton->text() == "Включить") {
        emit lightControllerSignal("1101\n");
        ui->lightPushButton->setText("Выключить");
    } else {
        emit lightControllerSignal("0001\n");
        ui->lightPushButton->setText("Включить");
    }
}

//функция записи последних измерений в таблицу
void MainWindow::addRowToTable(int index, double FC, double DC10mV, double DC1V, double LC) {
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
void MainWindow::addElement(int row, int element, double value) {
    QModelIndex index;
    index = model->index(row, element);
    model->setData(index, value);
}
void MainWindow::writeLog(QByteArray log) {
    ui->logsListWidget->addItem(log);
}

void MainWindow::setProgressBarValue(int val) {
    ui->progressBar->setValue(val);
}

void MainWindow::setProgressBarRange(int minVal, int maxVal) {
    ui->progressBar->setMinimum(minVal);
    ui->progressBar->setMaximum(maxVal);
}


void MainWindow::pauseButton_clicked(bool checked)
{
    if (checked){
        ui->pauseButton->setText("Продолжить");
        //emit sendPauseCommandSignal();

    } else {
        ui->pauseButton->setText("Пауза");
        //worker->continueWalk(currentIndex);
        //emit sendContinueWalkSignal(0);
    }
    worker->pauseWalk();
}


int MainWindow::getIndex()
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
    emit goToElementSignal(getIndex());
}


void MainWindow::saveMeasureButton_clicked()
{
    emit saveMeasureSignal(getIndex());
}


void MainWindow::continueFromButton_clicked()
{
    ui->pauseButton->setText("Пауза");
    emit sendContinueWalkSignal(getIndex());
}

void MainWindow::scanPushButton_clicked(bool checked)
{
    if (checked) {
        ui->scanPushButton->setText("Завершить обход");

        QFileDialog directory;
        QString dir_name = directory.getSaveFileName(this,"Choose directory and name");

        emit autoWalkSignal(true, dir_name);
    }
    else {
        ui->scanPushButton->setText("Начать");
        ui->pauseButton->setChecked(false);
        ui->pauseButton->setText("Пауза");
        currentIndex = finalIndex;
        worker->stopWalk();
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
    double rowSlide = (double)ui->stepRowSpinBox->value();

    //создаем модель таблицы для отображения(впоследствие можно сократить до N рядов)
    model = new QStandardItemModel(numberX * numberY, 8, this);
    model->setHeaderData(0, Qt::Horizontal, "Столбец");
    model->setHeaderData(1, Qt::Horizontal, "Ряд");
    model->setHeaderData(2, Qt::Horizontal, "Элемент");
    model->setHeaderData(3, Qt::Horizontal, "FC");
    model->setHeaderData(4, Qt::Horizontal, "DC10mV");
    model->setHeaderData(5, Qt::Horizontal, "DC1V");
    model->setHeaderData(6, Qt::Horizontal, "PhotoC");
    model->setHeaderData(7, Qt::Horizontal, "№");
    ui->tableView->setModel(model);

    bool all_three = ui->checkBox->isChecked();
    emit scanningPlateSignal(AX, AY, BX, BY, stepX, stepY, numberX, numberY, colSlide, rowSlide, all_three);

}



