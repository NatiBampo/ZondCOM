#include "worker.h"
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QSerialPortInfo>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

Worker::Worker(QMutex* mtxp)
{
    this->mutex = mtxp;
    connect(this, &Worker::sendPackageSignal, this, &Worker::sendPackage);
}

Worker::~Worker() {

}

void Worker::openPorts(QString portNameA5, QString portNameKeithly, QString portNameLight) {
    serialPortA5 = new QSerialPort();
    serialPortKeithly = new QSerialPort();
    serialPortLight = new QSerialPort();
    emit openPortResultSignal(portNameA5, "Planar", openPort(serialPortA5, portNameA5, QSerialPort::Baud115200));
    emit openPortResultSignal(portNameKeithly,"Keithley", openPort(serialPortKeithly, portNameKeithly, QSerialPort::Baud57600));
    emit openPortResultSignal(portNameLight, "Light", openPort(serialPortLight, portNameLight, QSerialPort::Baud9600));
}

void Worker::autoOpenPorts() {
    serialPortA5 = new QSerialPort();
    serialPortKeithly = new QSerialPort();
    serialPortLight = new QSerialPort();
    QList<QString> list;
    foreach(const QSerialPortInfo &port,  QSerialPortInfo::availablePorts()) {
        list.append(port.portName());
    };
    QHash<QSerialPort *, QString> map;
    bool tmp_flag;
    for (int i=0; i < list.length(); i++) {
        qDebug() << "cycle" << i << "  port " << list[i%3];
        //сперва окрываем порт планара
        if (!map.contains(serialPortA5)) {
            qDebug() << i << " planar condition";
            tmp_flag = openPort(serialPortA5, list[i%3], QSerialPort::Baud115200);
            if (tmp_flag && checkPlanarCOM()) {
                map.insert(serialPortA5, list[i%3]);
                emit openPortResultSignal(list[i%3], "Planar", tmp_flag);
                qDebug() << "serialPortA5 is now open with :" << list[i%3];
                continue;
            }
            if (serialPortA5->isOpen())serialPortA5->close();
        }

        //порт кейтли
        if (!map.contains(serialPortKeithly)) {
            qDebug()<<i<<" keithley condition";
            tmp_flag = openPort(serialPortKeithly, list[i%3], QSerialPort::Baud57600);
            if (tmp_flag && checkKeithlyCOM()) {
                map.insert(serialPortKeithly, list[i%3]);
                emit openPortResultSignal(list[i%3], "Keithley", tmp_flag);
                qDebug()<<"serialPortKeithly is now open with " << list[i%3];
                continue;
            }
            if (serialPortKeithly->isOpen()) serialPortKeithly->close();
        }
        //порт ардуины/диода

        if (!map.contains(serialPortLight)) {
            qDebug()<<i<<" light condition";
            tmp_flag = openPort(serialPortLight, list[i%3], QSerialPort::Baud9600);
            if (tmp_flag && checkLightCOM()) {
                qDebug()<<"inside light";
                map.insert(serialPortLight, list[i%3]);
                emit openPortResultSignal(list[i%3], "Light", tmp_flag);
                qDebug()<<"portNameLight is now open with :" << list[i%3];
            } else {
                if (serialPortLight->isOpen()) serialPortLight->close();
            }
        }
    }
}

bool Worker::checkPlanarCOM() {
    QString localAnswer = "";
    serialPortA5->write("State\r\n");
    serialPortA5->flush();
    while (serialPortA5->waitForReadyRead(ANSWER_DELAY)) localAnswer.append(serialPortA5->readAll());

    if (localAnswer != "") {
        qDebug()<<localAnswer;
        if (localAnswer.contains(QRegularExpression(R"(< \d+ \d+ \d+ \d+\r\n)"))) {
            qDebug() << "Planar : " << true;
            return true;
        }
    }
    return false;
}

bool Worker::checkKeithlyCOM() {
    try {
        KeithlyZeroCorrection(serialPortKeithly);
        //emit sendPackageSignal(serialPortA5, "Table UP\r\n", ANSWER_DELAY);
        Keithly05VSet(serialPortKeithly);
        ForwardCurrent = KeithlyGet(serialPortKeithly);
        QString responce = QString(lastAnswer);
        //emit sendPackageSignal(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
        qDebug() << lastAnswer;
        if (responce.contains(QRegularExpression(R"(\d+A,)"))) return true;//\d+.\d+[+-]\d+A,
    } catch (QSerialPort::SerialPortError error) {
        qDebug() << "error with Keithley COM port" << error;
    } catch (const char* error_message) {
        qDebug() << error_message;
    }

    return false;
}

bool Worker::checkLightCOM() {
    try {
        lastAnswer = "";
        QByteArray package = "1101/n";
        serialPortLight->write(package);
        serialPortLight->flush();
        emit sendLogSignal(package.remove(package.indexOf("\\"), package.length() - package.indexOf("\\")));
        while (serialPortLight->waitForReadyRead(ANSWER_DELAY)) lastAnswer.append(serialPortLight->readAll());
        if (lastAnswer != "") emit sendLogSignal(lastAnswer.remove(lastAnswer.indexOf("\\"), lastAnswer.length() - lastAnswer.indexOf("\\")));
        qDebug() <<"light response: " << lastAnswer;
        if (lastAnswer.contains("C3B2A1") || lastAnswer.contains("A1B2C3")) return true;
    } catch (QSerialPort::SerialPortError error) {
        qDebug() << error;
    }
    return false;
}

bool Worker::openPort(QSerialPort *port, QString portName, QSerialPort::BaudRate baudRate) {
    port->setPortName(portName);
    port->setBaudRate(baudRate);
    port->setDataBits(QSerialPort::DataBits::Data8);
    port->setStopBits(QSerialPort::StopBits::OneStop);
    port->setParity(QSerialPort::Parity::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);

    //emit openPortResultSignal(portName, port->open(QSerialPort::ReadWrite));
    return port->open(QSerialPort::ReadWrite);
}

void Worker::closePorts() {
    if (serialPortA5->isOpen()) serialPortA5->close();
    if (serialPortKeithly->isOpen()) serialPortKeithly->close();
    if (serialPortLight->isOpen()) serialPortLight->close();
    delete serialPortA5;
    delete serialPortKeithly;
    delete serialPortLight;
}

void Worker::sendPackage(QSerialPort *serialPort, QByteArray package, int delay) {
    lastAnswer = "";
    serialPort->write(package);
    serialPort->flush();
    emit sendLogSignal(package.remove(package.indexOf("\\"), package.length() - package.indexOf("\\")));
    while (serialPort->waitForReadyRead(delay)) lastAnswer.append(serialPort->readAll());
    if (lastAnswer != "") emit sendLogSignal(lastAnswer.remove(lastAnswer.indexOf("\\"), lastAnswer.length() - lastAnswer.indexOf("\\")));
}

void Worker::scanningPlate(double BX, double BY, double stepX, double stepY, double numberX,
                           double numberY, double colSlide, double rowSlide, bool all_three) {
    //функция пересчета таблицы координат первоначально или после изменений спинбаров на форме
    //сперва обновляем глобальные переменные
    //numberX необходимо привести к фактическому параметру
    DotsX.clear();
    DotsY.clear();
    lastIndex = (numberX + 1) * numberY * 3;
    qDebug() << "Your commercial could be here. Call us now 1-300-  " << rowSlide; //vertical gap between columns of rows


//    double tgAlpha = ((numberY - 1) * stepY) / ((numberX - 1) * stepX);
//    double CosAlpha = qPow(1 + tgAlpha * tgAlpha, -0.5);
//    double SinAlpha = tgAlpha * CosAlpha;
//    double X3 = (BX - AX) * CosAlpha * CosAlpha + (BY - AY) * SinAlpha * CosAlpha + AX;
//    double Y3 = (BY - AY) * CosAlpha * CosAlpha - (BX - AX) * SinAlpha * CosAlpha + AY;
//    double StepxX = (X3 - AX) / (numberX - 1);
//    double StepxY = (Y3 - AY) / (numberX - 1);
//    double StepyX = (BX - X3) / (numberY - 1);
//    double StepyY = (BY - Y3) / (numberY - 1);
//    double K = 1.75 / 2.805;

//    QList<double> DotsX;
//    QList<double> DotsY;
//    for (int j = 0; j < numberY; j++) {
//        for (int i = -1; i < numberX; i++) {
//            if (i % 2 == 0) DotsX.append(AX + StepxX * i + StepyX * j); else DotsX.append(AX + StepxX * i + StepyX * j - StepyX * K);
//            if (i % 2 == 0) DotsY.append(AY + StepxY * i + StepyY * j); else DotsY.append(AY + StepxY * i + StepyY * j - StepyY * K);
//        }
//    }

    double tgAlpha = ((numberY - 1) * stepY) / ((numberX - 1) * stepX);
    double CosAlpha = qPow(1 + tgAlpha * tgAlpha, -0.5);
    double SinAlpha = tgAlpha * CosAlpha;
    double X3 = -BX * CosAlpha * CosAlpha - BY * SinAlpha * CosAlpha + BX;
    double Y3 = -BY * CosAlpha * CosAlpha + BX * SinAlpha * CosAlpha + BY;
    double StepxX = (X3 - BX) / (numberX - 1);
    double StepxY = (Y3 - BY) / (numberX - 1);
    double StepyX = -X3 / (numberY - 1);
    double StepyY = -Y3 / (numberY - 1);
    double K = 1.75 / 2.805;
    double slideX = (colSlide - (numberX+1) * stepX) * 1000;

    for (int j = 0; j < numberY; j++) {
        for (int i = -1; i < numberX; i++) {
            if (i % 2 == 0) DotsX.append(BX + StepxX * i + StepyX * j); else DotsX.append(BX + StepxX * i + StepyX * j - StepyX * K);
            if (i % 2 == 0) DotsY.append(BY + StepxY * i + StepyY * j); else DotsY.append(BY + StepxY * i + StepyY * j - StepyY * K);
        }
    }

    if(all_three) {//все три столбца измеряем

        //сперва левый столбец
        for (int j = 0; j < numberY; j++) {
            for (int i = -2-numberX; i < -1 ; i++) {
                if (i % 2 == 0) DotsX.append(BX + StepxX * i + StepyX * j  + slideX); else DotsX.append(BX + StepxX * i + StepyX * j - StepyX * K + slideX);
                if (i % 2 == 0) DotsY.append(BY + StepxY * i + StepyY * j); else DotsY.append(BY + StepxY * i + StepyY * j - StepyY * K);
            }
        }
        //потом правый столбец
        for (int j = 0; j < numberY; j++) {
            for (int i = 15; i < numberX*2+1; i++) {
                if (i % 2 == 0) DotsX.append(BX + StepxX * i + StepyX * j  - slideX); else DotsX.append(BX + StepxX * i + StepyX * j - StepyX * K - slideX);
                if (i % 2 == 0) DotsY.append(BY + StepxY * i + StepyY * j); else DotsY.append(BY + StepxY * i + StepyY * j - StepyY * K);
            }
        }
    }
}

void Worker::autoWalk(bool allNew, QString dir_cur) {

    dir = dir_cur.endsWith(".csv") ? dir_cur : dir_cur + ".csv";
    emit sendProgressBarRangeSignal(currentIndex, lastIndex);
    int i = 0;
    //спросить начать обход или продолжить?
    Worker::copyUpToIndex(currentIndex);
    QFile file(dir);
    QString dir1 = file.fileName();
    //qDebug() << "Если 0, то строки идентичны  : " << QString::compare(dir1, dir_cur, Qt::CaseInsensitive);
    //если обход с начала, то переписать файл, иначе добавить
    if (file.open(allNew ? QIODevice::ReadWrite : QIODevice::Append)) {
        QTextStream output(&file);
        while (currentIndex < lastIndex)
        {
            //опустить стол
            emit sendPackageSignal(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
            //перевод координат в массив байтов для передачи станку
            i = currentIndex;
            Worker::goToElement(i);
            Worker::measureElement();
            //запускаем единичное измерение
            //запись в файл строки с измерениями токов
            output << QString::number(i, 'D', 0) + ", " + QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                      QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + '\n';
            output.flush();

            //отправляем данные на таблицу
            emit sendAddTableSignal(i, ForwardCurrent, DarkCurrent10mV, DarkCurrent1V, LightCurrent - DarkCurrent10mV);

            emit sendProgressBarValueSignal(i);
            currentIndex++;

            //проверка нажатия Паузы
            int tmp = 0;

            mutex->lock();
            if (pause){
                mutex->unlock();
                while (true) {
                    QThread::msleep(100);
                    mutex->lock();
                    if (!pause) {
                        break;
                    }
                    else if (tmp%100==0){
                        qDebug()<<"pause is going  another 10s   tmp : " << tmp/100;
                    }
                    mutex->unlock();
                    tmp++;
                }
            }
            mutex->unlock();

        }
        file.close();

        emit sendPackageSignal(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
    }
}

void Worker::measureElement() {
    MeasureDie(serialPortA5, serialPortKeithly);
    QThread::msleep(500);
}


void Worker::goToElement(int index) {
    //опустить стол
    emit sendPackageSignal(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
    //перевод координат в массив байтов для передачи станку
    QByteArray x = QByteArray::number((int)DotsX[index]);
    QByteArray y = QByteArray::number((int)DotsY[index]);
    emit sendPackageSignal(serialPortA5, "Set " + x + " " + y + '\r' + '\n', ANSWER_DELAY);
    //далее обход существующих измерений для копирования всех значений, кроме измеренных на элемент
}

void Worker::copyUpToIndex(int index) {
    //функция копирует файл до нужного индекса и заменяет собой файл источник
    if (index==0){
        return;
    }
    dir = dir.endsWith(".csv") ? dir : dir + ".csv";
    QString dir_tmp = dir.remove(dir.indexOf(".csv"), dir.length() - dir.indexOf(".csv")) + "tmp.csv";
    QFile dest (dir_tmp);
    QFile source (dir);
    if (dest.open(QIODevice::ReadWrite) && source.open(QIODevice::ReadWrite)) {
        QTextStream output(&source);
        QTextStream input(&dest);
        int i = 0;
        for (; i < index; ++i) {
            if (output.atEnd()){
                input << QString::number(i, 'D', 0) + ",,,,"  + '\n';
            } else {
                input << output.readLine()<<'\n';
            }
            input.flush();
        }
    }

    dest.close();
    source.close();
    source.remove();
    QFile::rename(dir_tmp, dir);
}

void Worker::pauseWalk() {
    //поменять статус паузы
    pause = !pause;
    pauseIndex = currentIndex;
}

void Worker::setIndex(int index) {
    //обновить индекс для обхода с нового элемента
    pauseIndex = currentIndex;
    currentIndex = index;
}

void Worker::stopWalk() {
    pause = false;
    currentIndex = lastIndex;//DotsX.count()
}

void Worker::saveMeasure(int index) {
    //функция копирует файл до нужного индекса и заменяет собой файл источник
    Worker::goToElement(index);
    MeasureDie(serialPortA5, serialPortKeithly);
    dir = dir.endsWith(".csv") ? dir : dir + ".csv";
    QString dir_tmp = dir.remove(dir.indexOf(".csv"), dir.length() - dir.indexOf(".csv")) + "tmp.csv";
    QFile dest (dir_tmp);
    QFile source (dir);

    if (dest.open(QIODevice::ReadWrite) && source.open(QIODevice::ReadWrite)) {
        QTextStream output(&source);
        QTextStream input(&dest);
        int i = 0;
        for (; !output.atEnd(); ++i) {
            if (i==index) {
                input << QString::number(i, 'D', 3) + ", " + QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                          QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + '\n';
            } else {
                output << input.readLine() << '\n';
            }
            output.flush();
        }

        if (index > i) {
            input << QString::number(index, 'D', 3) + ", " + QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                      QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + '\n';
        }
        //копируем всё обратно и удаляем временный файл
        dest.close();
        source.close();
        source.remove();
        QFile::rename(dir_tmp, dir);
    }
    emit sendPackageSignal(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
}

void Worker::tableController(QByteArray message) {
    emit sendPackageSignal(serialPortA5, message, ANSWER_DELAY);
}

void Worker::getBCoordinates() {
    int x = 0;
    int y = 0;
    QByteArray package = "State\r\n";
    QString localAnswer = "";
    serialPortA5->write(package);
    serialPortA5->flush();
    emit sendLogSignal(package.remove(package.indexOf("\\"), package.length() - package.indexOf("\\")) + " ");

    while (serialPortA5->waitForReadyRead(ANSWER_DELAY)) localAnswer.append(serialPortA5->readAll());
    if (localAnswer.contains(QRegularExpression(R"(< \d+ \d+ \d+ \d+\r\n)"))) {
        x = localAnswer.split(" ")[2].toInt();
        y = localAnswer.split(" ")[3].toInt();
        emit sendBCoordsSignal(x, y);
        //if (localAnswer != "") emit sendLogSignal("Bx = " + x + "  By = " + y); не работает
    }
}
void Worker::lightController(QByteArray message) {
    emit sendPackageSignal(serialPortLight, message, NO_ANSWER_DELAY);
}

void Worker::MeasureDie(QSerialPort *serialPortA5, QSerialPort *serialPortKeithly) {
    KeithlyZeroCorrection(serialPortKeithly);
    emit sendPackageSignal(serialPortA5, "Table UP\r\n", ANSWER_DELAY);
    Keithly05VSet(serialPortKeithly);
    ForwardCurrent = KeithlyGet(serialPortKeithly);
    Keithly10mVSet(serialPortKeithly);
    QThread::msleep(800);
    DarkCurrent10mV = KeithlyGet(serialPortKeithly);
    Keithly1VSet(serialPortKeithly);
    DarkCurrent1V = KeithlyGet(serialPortKeithly);
    LightOn();
    Keithly10mVSet(serialPortKeithly);
    emit sendPackageSignal(serialPortKeithly, "CURR:RANG 2e-6\n", NO_ANSWER_DELAY);
    QThread::msleep(200);
    LightCurrent = KeithlyGet(serialPortKeithly);
    emit sendPackageSignal(serialPortKeithly, "*RST\n", NO_ANSWER_DELAY);
//    emit sendLogSignal((QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
//                        QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4)).toUtf8());
    LightOff();
}

void Worker::KeithlyZeroCorrection(QSerialPort *serialPort) {
    emit sendPackageSignal(serialPort, "*RST\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SYST:ZCH ON\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "CURR:RANG 2e-9\n", NO_ANSWER_DELAY);
    QThread::msleep(400);
    emit sendPackageSignal(serialPort, "INIT\n", NO_ANSWER_DELAY);
    QThread::msleep(400);
    emit sendPackageSignal(serialPort, "SYST:ZCOR:STAT OFF\n", NO_ANSWER_DELAY);
    QThread::msleep(400);
    emit sendPackageSignal(serialPort, "SYST:ZCOR:ACQ\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SYST:ZCH OFF\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SYST:ZCOR ON\n", NO_ANSWER_DELAY);
}

void Worker::Keithly05VSet(QSerialPort *serialPort) {
    emit sendPackageSignal(serialPort, "CURR:RANG 2e-3\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:RANG 1\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT " + QByteArray::number(0.6) + '\n', NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:ILIM 1e-3\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
    QThread::msleep(300);
}

double Worker::KeithlyGet(QSerialPort *serialPort) {
    emit sendPackageSignal(serialPort, "READ?\n", ANSWER_DELAY);
    QByteArray byteArray = lastAnswer;
    byteArray = byteArray.remove(byteArray.indexOf("A"), byteArray.length() - byteArray.indexOf("A"));
    return byteArray.toDouble();
}

void Worker::Keithly10mVSet(QSerialPort *serialPort) {
    emit sendPackageSignal(serialPort, "CURR:RANG 2e-10\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT -1e-2\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
}

void Worker::Keithly1VSet(QSerialPort *serialPort) {
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT -1\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
    QThread::msleep(600);
}

void Worker::LightOn() {
    emit sendPackageSignal(serialPortLight, "1101\n", NO_ANSWER_DELAY);
}

void Worker::LightOff() {
    emit sendPackageSignal(serialPortLight, "0001\n", NO_ANSWER_DELAY);
}










