#include "mainwindow.h"
#include "ui_mainwindow.h"


//using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qInfo(logInfo()) << "Start MainWindow";
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(1);
    ui->progressBar->setValue(0);

    createWorkerThread();
    createStatsThread();
    /*
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->portComboBox->addItem(serialPortInfo.portName());
        ui->keithlyPortComboBox->addItem(serialPortInfo.portName());
        ui->lightPortComboBox->addItem(serialPortInfo.portName());
    }*/

    dir_name = "С:\temp\1.csv";

    //delays.append({300, 300, 500, 500, 400, 400, 600});
    delays = {300, 300, 500, 500, 400, 400, 600};

    initializeShortKeys();
    initializeSettings();
    initConnects();

    readyCheck();
    //statsThread.quit();
    //statsThread.terminate();

    tabCanvas *page = new tabCanvas(ui->tabWidget);

    ui->tabWidget->addTab(page,"Scheme");

    ui->tabWidget->setTabVisible(3, true);
    ui->tabWidget->setTabVisible(4, false);
    ui->chartsButton->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    emit closePortsSignal();
    qInfo(logInfo()) << "Финишь worker";
    workerThread.quit();
    workerThread.terminate();

    //statsThread.quit();
    //statsThread.terminate();
    qInfo(logInfo()) << "Finish MainWindow";
}


void MainWindow::initConnects()
{
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

    connect(ui->savePushButton, &QPushButton::clicked, this, &MainWindow::savePushButton_clicked);
    //connect(ui->loadFilePushButton, &QPushButton::clicked, this, &MainWindow::on_loadFilePushButton_clicked);
    connect(ui->stopPushButton, &QPushButton::clicked, this, &MainWindow::stopPushButton_clicked);

    //connect(ui->toAPushButton, &QPushButton::clicked, this, &MainWindow::on_toAPushButton_clicked);
    //connect(ui->toBPushButton, &QPushButton::clicked, this, &MainWindow::on_toBPushButton_clicked);
    //connect(ui->planarCMDButton, &QPushButton::clicked, this, &MainWindow::on_planarCMDButton_clicked);
    //connect(ui->schemePushButton, &QPushButton::clicked, this, &MainWindow::on_schemePushButton_clicked);

}


void MainWindow::initializeSettings()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    int bx = (int) settings.value(POINT_B_X, 0).toInt();
    int by = (int) settings.value(POINT_B_Y, 0).toInt();
    ui->BXspinBox->setValue(bx);
    ui->BYspinBox->setValue(by);

    int tmp = (int) settings.value(ZERO_D, 0).toInt();
    if (tmp !=  0) ui->zeroSpinBox->setValue(tmp);

    tmp = (int) settings.value(FC_D, 0).toInt();
    if (tmp !=  0) ui->FCSpinBox->setValue(tmp);

    tmp  = (int) settings.value(DC10mV_D, 0).toInt();
    if (tmp !=  0) ui->DC10spinBox->setValue(tmp);

    tmp = (int) settings.value(DC1V_D, 0).toInt();
    if (tmp != 0) ui->DC1VSpinBox->setValue(tmp);

    tmp = (int) settings.value(LIGHT_D, 0).toInt();
    if (tmp != 0) ui->lightSpinBox->setValue(tmp);

    tmp = (int) settings.value(PLANAR_D, 0).toInt();
    if (tmp != 0) ui->planarSpinBox->setValue(tmp);

    tmp = (int) settings.value(FC_V, 0).toInt();
    if (tmp != 0) ui->voltageSpinBox->setValue(tmp);
}


void MainWindow::createWorkerThread()
{
    qInfo(logInfo()) << "Старт Worker";
    periph = new Peripherals();
    worker = new Worker(&mutex, periph);
    worker->moveToThread(&workerThread);
    workerThread.start();

    connect(this, &MainWindow::scanningPlateSignal, worker, &Worker::calculate_dots);
    connect(this, &MainWindow::measureSignal, worker->connector, &Connector::measureElement);
    connect(this, &MainWindow::openPortsSignal, worker->connector, &Connector::openPorts);
    connect(this, &MainWindow::autoOpenPortsSignal, worker->connector, &Connector::autoOpenPorts);
    connect(this, &MainWindow::tableControllerSignal,
            worker->connector->planar, &Worker::tableController);
    connect(this, &MainWindow::lightControllerSignal,
            worker->connector->light, &Worker::lightController);
    connect(this, &MainWindow::closePortsSignal, worker->connector, &Connector::closePorts);
    connect(this, &MainWindow::sendPauseCommandSignal, worker, &Worker::pauseWalk);
    connect(this, &MainWindow::goToElementSignal, worker->connector->planar, &Planar::goToDot);
    connect(this, &MainWindow::saveMeasureSignal, worker, &Worker::saveMeasure);
    connect(this, &MainWindow::autoWalkSignal, worker, &Worker::autoWalk);
    connect(this, &MainWindow::getCurrentCoordsSignal,
            worker->connector->planar, &Worker::getCurrentCoords);
    //connect(this, &MainWindow::setDelaySignal, worker, &Worker::setDelay);
    connect(this, &MainWindow::measureFCSignal, worker->connector, &Connector::measureFC);
    connect(this, &MainWindow::openCsvFileSignal, worker, &Worker::openCsvFile);

    connect(worker, &Worker::sendLogSignal, this, &MainWindow::writeLog);
    connect(worker, &Worker::sendProgressBarValueSignal, this, &MainWindow::setProgressBarValue);
    connect(worker, &Worker::sendProgressBarRangeSignal, this, &MainWindow::setProgressBarRange);
    //connect(worker, &Worker::openPortResultSignal, this, &MainWindow::openPortResult);
    //сигнал для вывода последних измерений на форму
    connect(worker, &Worker::sendAddTableSignal, this, &MainWindow::addRowToTable);
    //сигнал паузы

    connect(worker->connector->planar, &Planar::sendBCoordsSignal,
            this, &MainWindow::setBCoords);
    connect(worker->connector->planar, &Planar::sendCurrentCoordsSignal,
            this, &MainWindow::setCurrentCoords);
    connect(worker, &Worker::sendMessageBox, this, &MainWindow::showMessageBox);
    connect(worker, &Worker::sendEndWalkSignal, this, &MainWindow::sendEndWalk);
    connect(worker, &Worker::sendEndOfWalkTime, this, &MainWindow::setEndOfWalkTime);
}


void MainWindow::initializeShortKeys()
{
    // запустить по желанию измеряющего
    keyUp  = new QShortcut(this);
    keyUp -> setKey(Qt::Key_R);

    keyDown = new QShortcut(this);
    keyDown -> setKey(Qt::Key_F);

    keyNorth = new QShortcut(this);
    keyNorth -> setKey(Qt::Key_W);//Qt::CTRL +

    keySouth = new QShortcut(this);
    keySouth -> setKey(Qt::Key_S);

    keyWest = new QShortcut(this);
    keyWest -> setKey(Qt::Key_A);

    keyEast = new QShortcut(this);
    keyEast -> setKey(Qt::Key_D);

    keyLight = new QShortcut(this);
    keyLight -> setKey(Qt::Key_T);
}


void MainWindow::activateShortKeys()
{
    connect(keyUp, SIGNAL(activated()), this, SLOT(tableUpPushButton_on()));
    connect(keyDown, SIGNAL(activated()), this, SLOT(tableDownPushButton_on()));
    connect(keyNorth, SIGNAL(activated()), this, SLOT(forwardPushButton_on()));
    connect(keySouth, SIGNAL(activated()), this, SLOT(backwardPushButton_on()));
    connect(keyWest, SIGNAL(activated()), this, SLOT(leftPushButton_on()));
    connect(keyEast, SIGNAL(activated()), this, SLOT(rightPushButton_on()));
    connect(keyLight, SIGNAL(activated()), this, SLOT(lightPushButton_on()));
}


void MainWindow::deactivateShortKeys()
{
    disconnect(keyUp, SIGNAL(activated()), this, SLOT(tableUpPushButton_on()));
    disconnect(keyDown, SIGNAL(activated()), this, SLOT(tableDownPushButton_on()));
    disconnect(keyNorth, SIGNAL(activated()), this, SLOT(forwardPushButton_on()));
    disconnect(keySouth, SIGNAL(activated()), this, SLOT(backwardPushButton_on()));
    disconnect(keyWest, SIGNAL(activated()), this, SLOT(leftPushButton_on()));
    disconnect(keyEast, SIGNAL(activated()), this, SLOT(rightPushButton_on()));
    disconnect(keyLight, SIGNAL(activated()), this, SLOT(lightPushButton_on()));
}


void MainWindow::openPortPushButton_on()
{
    if (ui->openPortPushButton->text() == "Открыть")
    {
        emit openPortsSignal(ui->portComboBox->currentText(),
                             ui->keithlyPortComboBox->currentText(),
                             ui->lightPortComboBox->currentText());
        ui->openPortPushButton->setText("Закрыть");
    } else
    {
        if (ui->scanPushButton->isChecked() || ui->continueFromButton->isChecked())
        {
            showMessageBox("warning", "Нельзя закрыть порт во время обхода пластины");
            return;
        }
        emit closePortsSignal();
        ui->openPortPushButton->setText("Открыть");
        ui->portComboBox->setCurrentText("Планар");
        ui->keithlyPortComboBox->setCurrentText("Keithley");
        ui->lightPortComboBox->setCurrentText("Диод");

        ui->measureBButton->setEnabled(false);
        ui->pauseButton->setEnabled(false);
        ui->scanPushButton->setEnabled(false);
        QMessageBox::information(this, "Сообщение", "COM порты закрыты");

    }
}


void MainWindow::openPortsResult()
{
    QString work = "открыт\n";
    QString no = "закрыт\n";
    portsReady();
    QMessageBox::information(this, "Сообщение", "Выбранные порты:\n"
                                      + "Планар " + periph->planar_open? work : no
                                      + "Измеритель " + periph->meter? work : no
                                      + "Диода " + periph->light_open? work : no;
}


bool MainWindow::portsReady()
{
    bool res = periph->lan? periph->keysight_open : periph->keithley_open;
    res = periph->planar_open &&
            periph->light && res;

    ui->measureBButton->setEnabled(res);
    ui->orientationButton->setEnabled(res);
    ui->toAPushButton->setEnabled(res);
    ui->toBPushButton->setEnabled(res);
    ui->moveGroupBox->setEnabled(res);
    ui->coordsGroupBox->setEnabled(res);

    ui->FCMeasureButton->setEnabled(res);
    ui->measure2pushButton->setEnabled(res);

    return res;
}


bool MainWindow::readyCheck()
{
    bool res = portsReady() && periph->orientation;
    //block some buttons in case COMports not open

    ui->goToGroupBox->setEnabled(res);
    ui->goToButton->setEnabled(res);
    ui->saveMeasureButton->setEnabled(res);
    ui->FCMeasureButton->setEnabled(res);
    ui->measure2pushButton->setEnabled(res);
    ui->continueFromButton->setEnabled(res);
    ui->scanPushButton->setEnabled(res);
    //ui->loadFilePushButton->setEnabled(res);
    ui->stopPushButton->setEnabled(res);
    return res;
}


void MainWindow::statePushButton_on()
{
    //emit sendPackageSignal(serialPortA5, "State\r\n", 1000);
    emit getCurrentCoordsSignal(-1, ui->planarCheckBox->isChecked());
}


void MainWindow::coordsPushButton_on()
{
    QByteArray x = ui->xLineEdit->text().toUtf8();
    QByteArray y = ui->yLineEdit->text().toUtf8();
    planarSender("Set " + x + " " + y + '\r' + '\n');
}


void MainWindow::tableUpPushButton_on()
{
    planarSender("Table UP\r\n");
}


void MainWindow::tableDownPushButton_on()
{
    planarSender("Table DN\r\n");
}


void MainWindow::forwardPushButton_on()
{
    planarSender(("Move 0 -" + QString::number(ui->stepSpinBox->value()) + "\r\n").toUtf8());//0 100
}


void MainWindow::backwardPushButton_on()
{
    planarSender(("Move 0 " + QString::number(ui->stepSpinBox->value()) + "\r\n").toUtf8());//0 -100
}


void MainWindow::leftPushButton_on()
{
    planarSender(("Move -" +  QString::number(ui->stepSpinBox->value()) + " 0\r\n").toUtf8());//-100 0
}


void MainWindow::rightPushButton_on()
{
    planarSender(("Move " + QString::number(ui->stepSpinBox->value()) + " 0\r\n").toUtf8());//100 0
}


void MainWindow::planarSender(QString msg)
{
    emit tableControllerSignal(msg.toUtf8(), periph);
    //ui->planarCheckBox->isChecked()
}


void MainWindow::measurePushButton_on()
{
    updateDelays();
    emit measureSignal(walk, delays, currs, dots);
}


void MainWindow::lightPushButton_on()
{
    if (ui->lightPushButton->text() == "Диод Вкл")
    {
        emit lightControllerSignal("1111\n", ui->lightCheckBox->isChecked());
        ui->lightPushButton->setText("Диод Выкл");
    } else
    {
        emit lightControllerSignal("0001\n",  ui->lightCheckBox->isChecked());
        ui->lightPushButton->setText("Диод Вкл");
    }
}


//функция записи последних измерений в таблицу
//int index, double FC, double DC10mV, double DC1V, double LC
void MainWindow::addRowToTable()
{
    int column = currs->currentIndex / (die->numY * (die->numX+1)) + 1;
    int row = currs->currentIndex % (die->numY * (die->numX+1)) / (die->numX+1) + 1;
    int element = currs->currentIndex % (die->numY * (die->numX+1)) % (die->numX+1) + 1;

    number = currs->currentIndex - die->downRight * (die->numX+1);
    number = (column>1)? number - (die->upRight + die->downLeft) * (die->numX+1) : number;
    number = (column>2)? number - (die->upLeft + die->downCenter) * (die->numX+1) : number;

    addElement(number, 0, currs->currentIndex);       //индекс
    addElement(number, 1, column);      //колонка
    addElement(number, 2, row);         //ряд //index % (numY * (numX+1)) / (numX+1) + 1
    addElement(number, 3, element);     //элемент // index % (numY * (numX+1)) % (numX+1) + 1
    addElement(number, 4, currs->forward05V);          //прямой ток
    addElement(number, 5, currs->dark10mV);      //темновой ток при 10мВ
    addElement(number, 6, currs->dark1V);        //темновой ток при 1В
    addElement(number, 7, currs->light10mV);          //фототок


    //focus on the last row
    QItemSelectionModel::SelectionFlags flags;
    flags = QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows;
    QModelIndex i = ui->tableView->model()->index(number, 0);
    ui->tableView->selectionModel()->select(i, flags);
    ui->tableView->scrollTo(i);

    //add actual data to spinners
    ui->columnSpinBox->setValue(column);
    ui->rowSpinBox->setValue(row);
    ui->elemSpinBox->setValue(element);
}


//записываем ячейку таблицы на форму
void MainWindow::addElement(int row, int element, double value)
{
    QModelIndex index;
    index = model->index(row, element);
    model->setData(index, value);

    if (!ui->colorRangeCheckBox->isChecked()) return;

    int rank = 0;
    if (element == 4) rank = (value < - qPow(10, -4)) ? 1 : 9;
    if (element == 5) rank = (value < qPow(10, -12)) ? 1 : (value < 5 * qPow(10, -12)) ? 2 : (value < qPow(10, -11)) ? 3 : 9;
    if (element == 6) rank = (value < qPow(10, -10)) ? 1 : 9;
    if (element == 7) rank = (value > 1.07026 * qPow(10, -7)) ? 1 : 9;

    switch(rank)
    {
    case 0: ((QStandardItemModel*)index.model())->item(row, element)->setData(QBrush(Qt::white), Qt::BackgroundRole); break;
    case 1: ((QStandardItemModel*)index.model())->item(row, element)->setData(QBrush(QColor(0, 187, 63)), Qt::BackgroundRole); break;
    case 2: ((QStandardItemModel*)index.model())->item(row, element)->setData(QBrush(QColor(10, 207, 0)), Qt::BackgroundRole); break;
    case 3: ((QStandardItemModel*)index.model())->item(row, element)->setData(QBrush(QColor(131, 233, 0)), Qt::BackgroundRole); break;
    case 4: ((QStandardItemModel*)index.model())->item(row, element)->setData(QBrush(QColor(220, 249, 0)), Qt::BackgroundRole); break;
    case 9: ((QStandardItemModel*)index.model())->item(row, element)->setData(QBrush(QColor(255, 113, 0)), Qt::BackgroundRole); break;
//    default: ((QStandardItemModel*)index.model())->item(row, element)->setData(QBrush(Qt::darkGray), Qt::BackgroundRole);
    }
}


void MainWindow::writeLog(QByteArray log)
{
    //ui->logsListWidget->addItem(log); //добавление в конец
    ui->logsListWidget->insertItem(0, log); //вставка в начало
}


void MainWindow::setProgressBarValue(int val)
{
    ui->progressBar->setValue(val);
}


void MainWindow::setProgressBarRange(int minVal, int maxVal)
{
    ui->progressBar->setMinimum(minVal);
    ui->progressBar->setMaximum(maxVal);
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
    /*
    int numRows = ((int) rightColumn) * (numberX + 1) * (numberY - downRight - upRight);
    numRows += ((int) leftColumn) * (numberX + 1) * (numberY - downLeft - upLeft);
    numRows += ((int) centerColumn) * (numberX + 1) * (numberY - downCenter - upCenter);
    */

    int row = ui->rowSpinBox->value();
    int element = ui->elemSpinBox->value();
    int col = ui->columnSpinBox->value();
    int index = (col - 1) * (die->numX+1) * die->numY + (row - 1) * (die->numX+1) + element - 1;

    return index;
}


void MainWindow::goToButton_clicked()
{
    walk->currentIndex = getUIIndex();
    emit goToElementSignal(walk, dots);

}


void MainWindow::saveMeasureButton_clicked()
{
    updateDelays();
    walk->currentIndex = getUIIndex();
    if (!busy)
    {
        emit saveMeasureSignal(walk, dots, currs);
    }
}


void MainWindow::continueFromButton_clicked(bool checked)
{
    updateDelays();
    bool cond = true;
    if (dir_name == "" || dir_name == "С:\temp\1.csv")
    {
        QFileDialog directory;
        QString dir = directory.getSaveFileName(this,"Choose directory and name");

        if (dir != "")
        {
            dir_name = dir.endsWith(".csv") ? dir : dir + ".csv";
            cond = true;
        }
    }
    else
    {
        cond = true;
    }

    if(cond)
    {
        ui->pauseButton->setText("Пауза");
        ui->pauseButton->setEnabled(true);
        ui->scanPushButton->setEnabled(false);
        emit autoWalkSignal(walk, delays, currs, dots);
        busy = true;
        checkBusy();
    }
    ui->continueFromButton->setChecked(false);
}


void MainWindow::scanPushButton_clicked(bool checked)
{
    updateDelays();
    QFileDialog directory;
    QString dir = directory.getSaveFileName(this,"Choose directory and name");
    if (dir != "")
    {
        dir_name = dir.endsWith(".csv") ? dir : dir + ".csv";
        ui->pauseButton->setEnabled(true);
        ui->addressLabel->setText(dir_name);
        updateDelays();
        walk->currentIndex = 0;
        emit autoWalkSignal(walk, delays, currs, dots);
        busy = true;
        checkBusy();
    }
    ui->scanPushButton->setChecked(false);
}


void MainWindow::orientationButton_clicked()
{
    die = new DieParameters();
    die->AX = ui->AXspinBox->value();
    die->AY = ui->AYspinBox->value();
    die->BX = ui->BXspinBox->value();
    die->BY = ui->BYspinBox->value();
    die->stepX = ui->stepXspinBox->value();
    die->stepY = ui->stepYspinBox->value();
    die->numX = ui->numXspinBox->value();
    die->numY = ui->numYspinBox->value();

    die->upLeft = ui->upLeftSpinBox->value();
    die->upRight = ui->upRightSpinBox->value();
    die->downLeft = ui->downLeftSpinBox->value();
    die->downRight = ui->downRightSpinBox->value();
    die->downCenter = ui->downCenterSpinBox->value();
    die->upCenter = ui->upCenterSpinBox->value();
    //сдвиг меж столбцов и рядов
    die->colSlide = (double)ui->stepColSpinBox->value();
    //double rowSlide = (double)ui->stepRowSpinBox->value();

    initializeModel();
    qDebug()<<"all througth";
    emit calculateDotsSignal(die, dots, walk);
    updateDelays();
    //orientation = true;
    readyCheck();
    syncSettings();
}


void MainWindow::initializeModel()
{
    die->numX = ui->numXspinBox->value();
    die->numY = ui->numYspinBox->value();

    die->centerColumn = ui->centerCheckBox->isChecked();
    die->leftColumn = ui->leftCheckBox->isChecked();
    die->rightColumn = ui->rightCheckBox->isChecked();

    //die offset due to cirle border cut
    die->upLeft = ui->upLeftSpinBox->value();
    die->upRight = ui->upRightSpinBox->value();
    die->downLeft = ui->downLeftSpinBox->value();
    die->downRight = ui->downRightSpinBox->value();
    die->downCenter = ui->downCenterOffspinBox->value();
    die->upCenter = ui->centerUpOffSpinBox->value();

    if (((die->upLeft + die->downLeft) > (die->numX+1)*die->numY)
            || ((die->downRight + die->upRight) > (die->numX+1)*die->numY)
            || ((die->downCenter + die->upCenter) > (die->numX+1)*die->numY))
    {
        showMessageBox("warning", "Не допустимое значение отступов");
        return;
    }

    //количество измерений(рядов в таблице)
    numRows = ((int) die->rightColumn) * (die->numX + 1)
            * (die->numY - die->downRight - die->upRight);
    numRows += ((int) die->leftColumn) * (die->numX + 1)
            * (die->numY - die->downLeft - die->upLeft);
    numRows += ((int) die->centerColumn) * (die->numX + 1)
            * (die->numY - die->downCenter - die->upCenter);

    model = new QStandardItemModel{numRows, 8, this};
    model->setHeaderData(0, Qt::Horizontal, "№");
    model->setHeaderData(1, Qt::Horizontal, "Столб");
    model->setHeaderData(2, Qt::Horizontal, "Ряд");
    model->setHeaderData(3, Qt::Horizontal, "Элем");
    model->setHeaderData(4, Qt::Horizontal, "FC");
    model->setHeaderData(5, Qt::Horizontal, "DC10mV");
    model->setHeaderData(6, Qt::Horizontal, "DC1V");
    model->setHeaderData(7, Qt::Horizontal, "PhotoCur");

    ui->tableView->setModel(model);
}


void MainWindow::autoPortButton_clicked()
{
    emit autoOpenPortsSignal(periph);
    ui->openPortPushButton->setText("Закрыть");
}


void MainWindow::measureBButton_clicked()
{
    emit getCurrentCoordsSignal(-2, ui->planarCheckBox->isChecked());
}


void MainWindow::setBCoords(int x, int y)
{
    ui->BXspinBox->setValue(x);
    ui->BYspinBox->setValue(y);

    ui->AXspinBox->setValue(0);
    ui->AYspinBox->setValue(0);
}


void MainWindow::setCurrentCoords(int x, int y)
{
    ui->xLineEdit->setText(QString::number(x));
    ui->yLineEdit->setText(QString::number(y));
}


void  MainWindow::createStatsThread()
{
    qInfo(logInfo()) << "создание Stats";
    stats = new Stats();
    //stats->moveToThread(&statsThread);
    //statsThread.start();
    connect(this, &MainWindow::showChartsSignal, stats, &Stats::showCharts);
}


void MainWindow::on_chartsButton_clicked()
{
    //emit showChartsSignal(dir_name);
    QFileDialog directory;
    QString stats_dir = directory.getOpenFileName(this,"Выберите данные для построенния графика");
    qInfo(logInfo()) << "Построение гистограммы из ->" << stats_dir;
    stats->showCharts(stats_dir);
    qInfo(logInfo()) << "Построили гистограммы из ->" << stats_dir;
}


void MainWindow::showMessageBox(QString msg_type, QString msg)
{
    if (msg_type == "information")
    {
        QMessageBox::information(this, "Информация", msg);
    } else if (msg_type == "critical")
    {
        QMessageBox::critical(this, "Ошибка", msg);
        qCritical(logCritical()) << "Critical Button";
    } else if (msg_type == "warning")
    {
        QMessageBox::warning(this, "Предупреждение", msg);
    } else {
        QMessageBox::information(this, msg_type, msg);
    }
}


void MainWindow::syncSettings()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    int BX = ui->BXspinBox->value();
    int BY = ui->BYspinBox->value();

    if(BX != 0 || BY != 0)
    {
        settings.setValue(POINT_B_X, BX);
        settings.setValue(POINT_B_Y, BY);
    }

    settings.setValue(ZERO_D, ui->zeroSpinBox->value());
    settings.setValue(FC_D, ui->FCSpinBox->value());
    settings.setValue(DC10mV_D, ui->DC10spinBox->value());
    settings.setValue(DC1V_D, ui->DC1VSpinBox->value());
    settings.setValue(LIGHT_D, ui->lightSpinBox->value());
    settings.setValue(PLANAR_D, ui->planarSpinBox->value());
    settings.setValue(FC_V, ui->voltageSpinBox->value());
    settings.sync();
}


void MainWindow::measure2pushButton_clicked()
{
    updateDelays();
    emit measureSignal(ui->planarCheckBox->isChecked(), ui->keithleyCheckBox->isChecked(), ui->lightCheckBox->isChecked());
}


void MainWindow::on_FCMeasureButton_clicked()
{
    updateDelays();
    emit measureFCSignal(ui->planarCheckBox->isChecked(), ui->keithleyCheckBox->isChecked());
}


void MainWindow::sendEndWalk()
{
    busy = false;
    checkBusy();
    writeCSV();
}


void MainWindow::on_hotKeysCheckBox_stateChanged(int arg1)
{
    if (arg1==0)
    {
        //unchecked
        deactivateShortKeys();
    }
    else if (arg1==2)
    {
        //checked
        activateShortKeys();
    }
}


void MainWindow::savePushButton_clicked()
{
    if(!busy) writeCSV();
}


void MainWindow::on_loadFilePushButton_clicked()
{
    if (busy)
    {
        showMessageBox("warning", "Нельзя открыть файл во время обхода");
    }
    else if (model == nullptr)
    {
        showMessageBox("warning", "Ориентация не выполнена");//model not initialized
    }
    else
    {
        QFileDialog directory;
        QString dir = directory.getOpenFileName(this,"Choose directory and name");

        if (dir != "")
        {
            dir_name = dir.endsWith(".csv") ? dir : dir + ".csv";
            ui->scanPushButton->setChecked(false);
            ui->addressLabel->setText(dir_name);

            updateDelays();
            initializeModel();

            emit openCsvFileSignal(dir_name);
            readyCheck();
        }
    }
}


void MainWindow::stopPushButton_clicked()
{
    mutex.lock();
    worker->stopWalk();
    mutex.unlock();

    busy = false;
    checkBusy();
    writeCSV();
}


void MainWindow::on_toAPushButton_clicked()
{
    QByteArray x = ui->AXspinBox->text().toUtf8();
    QByteArray y = ui->AYspinBox->text().toUtf8();
    emit tableControllerSignal("Set " + x + " " + y + '\r' + '\n', ui->planarCheckBox->isChecked());
}


void MainWindow::on_toBPushButton_clicked()
{
    QByteArray x = ui->BXspinBox->text().toUtf8();
    QByteArray y = ui->BYspinBox->text().toUtf8();
    emit tableControllerSignal("Set " + x + " " + y + '\r' + '\n', ui->planarCheckBox->isChecked());

}


void MainWindow::checkBusy()
{
    ui->toAPushButton->setEnabled(!busy);
    ui->toBPushButton->setEnabled(!busy);
    ui->measureBButton->setEnabled(!busy);
    ui->orientationButton->setEnabled(!busy);
    ui->scanPushButton->setEnabled(!busy);

    ui->continueFromButton->setEnabled(!busy);
    ui->goToGroupBox->setEnabled(!busy);
    ui->moveGroupBox->setEnabled(!busy);
    ui->coordsGroupBox->setEnabled(!busy);

    ui->pauseButton->setEnabled(busy);

}


void MainWindow::on_planarCMDButton_clicked()
{
    QString line = ui->queryLineEdit->text();
    QByteArray cmd = line.toUtf8();
    planarSender(cmd + '\r' + '\n');
}


void MainWindow::writeCSV()
{
    QFile file(dir_name);

    QVariant cellData; //Сюда положим данные из ячейки
    QModelIndex modelIndex;
    QString line = "";
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream output(&file);
        for (int row = 0; row < model->rowCount(); ++row)
        {
            //output << model->data(row) << '\n';
            int column = 0;
            for (; column < model->columnCount() - 1; ++column)
            {
                if (column > 0 && column<4 ) continue;
                modelIndex = model->index( row, column, QModelIndex());
                cellData = model->data(modelIndex);
                line = column==0 ? QString::number(cellData.toInt()) : QString::number(cellData.toDouble());
                if (line == "") break;
                output << line << ", ";
            }
            output << model->index(row, column).data().toString()<< "\n";
        }
    }
}


void MainWindow::on_resetPortsPushButton_clicked()
{
    emit closePortsSignal();

    ui->portComboBox->clear();
    ui->keithlyPortComboBox->clear();
    ui->lightPortComboBox->clear();

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->portComboBox->addItem(serialPortInfo.portName());
        ui->keithlyPortComboBox->addItem(serialPortInfo.portName());
        ui->lightPortComboBox->addItem(serialPortInfo.portName());
    }
}


void MainWindow::setEndOfWalkTime(QString endTime)
{
    ui->endTimeLabel->setText(endTime);
}


void MainWindow::on_stop2pushButton_clicked()
{
    mutex.lock();
    worker->stopWalk();
    mutex.unlock();

    busy = false;
    checkBusy();
    writeCSV();
}


void MainWindow::drawCanvas()
{
    ui->tabWidget->setTabVisible(4, true);
}


void MainWindow::on_admCheckBox_stateChanged(int arg1)
{

    adm = ui->admCheckBox->isChecked();
    ui->planarCheckBox->setEnabled(adm);
    ui->keithleyCheckBox->setEnabled(adm);
    ui->lightCheckBox->setEnabled(adm);

    busy = !adm;

    ui->measureBButton->setEnabled(adm);
    ui->orientationButton->setEnabled(adm);
    ui->toAPushButton->setEnabled(adm);
    ui->toBPushButton->setEnabled(adm);
    ui->moveGroupBox->setEnabled(adm);
    ui->coordsGroupBox->setEnabled(adm);

    ui->FCMeasureButton->setEnabled(adm);
    ui->measure2pushButton->setEnabled(adm);

    ui->scanPushButton->setEnabled(adm);

    ui->continueFromButton->setEnabled(adm);
    ui->goToGroupBox->setEnabled(adm);

    ui->pauseButton->setEnabled(adm);
    ui->loadFilePushButton->setEnabled(adm);
    ui->stop2pushButton->setEnabled(adm);

    checkBusy();
}


void MainWindow::on_schemePushButton_clicked()
{
    drawCanvas();
    QMessageBox::information(this, "Информация", "auf");
}


void MainWindow::updateDelays()
{
    delays->zero = ui->zeroSpinBox->value();
    delays->planar = ui->planarSpinBox->value();
    delays->fc = ui->FCSpinBox->value();
    delays->dc_10mV = ui->DC10spinBox->value();
    delays->dc_1V = ui->DC1VSpinBox->value();
    delays->light = ui->lightSpinBox->value();
    delays->fc_volt = ui->voltageSpinBox->value();

    walk->planar_status = ui->planarCheckBox->isChecked();
    walk->keithley_status = ui->keithleyCheckBox->isChecked();
    walk->light_status = ui->lightCheckBox->isChecked();
}
