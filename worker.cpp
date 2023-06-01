#include "worker.h"
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QSerialPortInfo>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <ctime>
#include <QMessageBox>
#include <windows.h>


HANDLE hSerial;


Worker::Worker(QMutex* mtxp)
{
    this->mutex = mtxp;
    initPort9();
}

Worker::~Worker()
{
    delete serialPortA5;
    delete serialPortKeithly;
    delete serialPortLight;
}


void Worker::connectPorts()
{
    connect(serialPortA5, &QSerialPort::errorOccurred, this, &Worker::handleError_planar);
    connect(serialPortA5, &QSerialPort::readyRead, this, &Worker::readData_planar);

    connect(serialPortKeithly, &QSerialPort::errorOccurred, this, &Worker::handleError_keithley);
    connect(serialPortKeithly, &QSerialPort::readyRead, this, &Worker::readData_keithley);
    connect(&m_timer, &QTimer::timeout, this, &Worker::handleTimeout_Keithley);

//    m_timer.start(5000);

    connect(serialPortLight, &QSerialPort::errorOccurred, this, &Worker::handleError_light);
    connect(serialPortLight, &QSerialPort::readyRead, this, &Worker::readData_light);
    //connect(serialPortA5, &Worker::getData, this, &Worker::writeData);

}


void Worker::writeData_planar(const QByteArray& data)
{
    serialPortA5->write(data);
}


void Worker::readData_planar()
{
    const QByteArray data = serialPortA5->readAll();
    planarResponce = data;
}


void Worker::handleError_planar(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        //QMessageBox::critical(this, tr("Critical Error"), serialPortA5->errorString());
        emit sendMessageBox("critical", serialPortA5->errorString());
        closePorts();
    }
}


void Worker::writeData_keithley(const QByteArray& data)
{
//    serialPortKeithly->write(data);
    writeWin(data);
}


void Worker::readData_keithley()
{
    const QByteArray data = serialPortKeithly->readAll();
    keithleyResponce = data;
//    if (!m_timer.isActive())
//            m_timer.start(5000);
}


void Worker::handleError_keithley(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        emit sendMessageBox("critical", serialPortKeithly->errorString());
        closePorts();
    }
}


void Worker::handleTimeout_Keithley()
{
    if (!keithleyResponce.isEmpty()) {
        qDebug() << "i'm in handle";
    }
}

void Worker::writeData_light(const QByteArray& data)
{
    serialPortLight->write(data);
}


void Worker::readData_light()
{
    const QByteArray data = serialPortLight->readAll();
    lightResponce = data;
}


void Worker::handleError_light(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        emit sendMessageBox("critical", serialPortLight->errorString());
        closePorts();
    }
}


void Worker::openPorts(QString portNameA5, QString portNameKeithly, QString portNameLight)
{
    serialPortA5 = new QSerialPort();
    serialPortKeithly = new QSerialPort();
    serialPortLight = new QSerialPort();
    emit openPortResultSignal(portNameA5, "Planar", openPort(serialPortA5, portNameA5, QSerialPort::Baud115200));
    emit openPortResultSignal(portNameKeithly,"Keithley", openPort(serialPortKeithly, portNameKeithly, QSerialPort::Baud57600));
    emit openPortResultSignal(portNameLight, "Light", openPort(serialPortLight, portNameLight, QSerialPort::Baud9600));

    connectPorts();
}


void Worker::autoOpenPorts()
{
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
        //сперва окрываем порт планара
        if (!map.contains(serialPortA5)) {
            tmp_flag = openPort(serialPortA5, list[i%3], QSerialPort::Baud115200);
            if (tmp_flag && checkPlanarCOM()) {
                map.insert(serialPortA5, list[i%3]);
                emit openPortResultSignal(list[i%3], "Planar", tmp_flag);
                continue;
            }
            if (serialPortA5->isOpen())serialPortA5->close();
        }

        //порт кейтли
        if (!map.contains(serialPortKeithly)) {
            tmp_flag = openPort(serialPortKeithly, list[i%3], QSerialPort::Baud57600);
            if (tmp_flag && checkKeithlyCOM()) {
                map.insert(serialPortKeithly, list[i%3]);
                emit openPortResultSignal(list[i%3], "Keithley", tmp_flag);
                continue;
            }
            if (serialPortKeithly->isOpen()) serialPortKeithly->close();
        }
        //порт ардуины/диода

        if (!map.contains(serialPortLight)) {
            qDebug() << i << " light condition";
            tmp_flag = openPort(serialPortLight, list[i%3], QSerialPort::Baud9600);
            if (tmp_flag && checkLightCOM()) {
                map.insert(serialPortLight, list[i%3]);
                emit openPortResultSignal(list[i%3], "Light", tmp_flag);
            } else {
                if (serialPortLight->isOpen()) serialPortLight->close();
            }
        }
    }
}


bool Worker::checkPlanarCOM()
{
    writeData_planar("State\r\n");
    readData_planar();
    QString responce = QString(planarResponce);
    if (responce != "") {
        qDebug() << responce;
        if (responce.contains(QRegularExpression(R"(< \d+ \d+ \d+ \d+\r\n)"))) {
            return true;
        }
    }
    return false;
}


bool Worker::checkKeithlyCOM()
{
    try {
        KeithlyZeroCorrection2();
        //emit sendPackageSignal(serialPortA5, "Table UP\r\n", ANSWER_DELAY);
        Keithly05VSet2();
        ForwardCurrent = KeithlyGet2();
        QString responce = QString(keithleyResponce);
        //emit sendPackageSignal(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
        if (responce.contains(QRegularExpression(R"(\d+A,)"))) return true;//\d+.\d+[+-]\d+A,
    }
    catch (const char* error){}

    return false;
}


bool Worker::checkLightCOM()
{
    try {
        LightOn2();
        if (lightResponce.contains("C3B2A1")) {
            LightOff2();
            return true;
        }
    } catch (QSerialPort::SerialPortError error) {
        qDebug() << error;
    }
    return false;
}


bool Worker::openPort(QSerialPort *port, QString portName, QSerialPort::BaudRate baudRate)
{
    port->setPortName(portName);
    port->setBaudRate(baudRate);
    port->setDataBits(QSerialPort::DataBits::Data8);
    port->setStopBits(QSerialPort::StopBits::OneStop);
    port->setParity(QSerialPort::Parity::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);

    //emit openPortResultSignal(portName, port->open(QSerialPort::ReadWrite));
    return port->open(QSerialPort::ReadWrite);
}


void Worker::closePorts()
{
    QString result;
    if (serialPortA5->isOpen()) serialPortA5->close();
    if (serialPortKeithly->isOpen()) serialPortKeithly->close();
    if (serialPortLight->isOpen()) serialPortLight->close();
}


void Worker::closePort(QSerialPort* port)
{
    if (port->isOpen())
        port->close();
}


void Worker::scanningPlate(double BX, double BY, double stepX, double stepY, double numberX,
                           double numberY, double colSlide, bool all_three,
                           int upLeft, int upRight, int downLeft, int downRight)
{
    //функция пересчета таблицы координат первоначально или после изменений спинбаров на форме
    //сперва обновляем глобальные переменные
    //numberX необходимо привести к фактическому параметру
    DotsX.clear();
    DotsY.clear();
    //lastIndex = (numberX + 1) * numberY * 3;

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

    three_columns = all_three;
    upLeft_offset = upLeft;
    upRight_offset = upRight;
    downLeft_offset = downLeft;
    downRight_offset = downRight;

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

    if (all_three) {//все три столбца измеряем
        //сперва левый столбец
        for (int j = 0; j < numberY; j++) {
            for (int i = -2-numberX; i < -1 ; i++) {
                if (i % 2 == 0) DotsX.append(BX + StepxX * i + StepyX * j  + slideX); else DotsX.append(BX + StepxX * i + StepyX * j - StepyX * K + slideX);
                if (i % 2 == 0) DotsY.append(BY + StepxY * i + StepyY * j); else DotsY.append(BY + StepxY * i + StepyY * j - StepyY * K);
            }
        }
        //потом правый столбец
        for (int j = 0; j < numberY; j++) {
            for (int i = numberX; i < numberX*2+1; i++) {
                if (i % 2 == 0) DotsX.append(BX + StepxX * i + StepyX * j  - slideX); else DotsX.append(BX + StepxX * i + StepyX * j - StepyX * K - slideX);
                if (i % 2 == 0) DotsY.append(BY + StepxY * i + StepyY * j); else DotsY.append(BY + StepxY * i + StepyY * j - StepyY * K);
            }
        }
    }

    lastIndex = DotsX.length() - 1;
    //заполним индексы обрезанных элементов
    //нижний левый угол
    gap.append((numberX+1) * numberY);
    gap.append(gap[0] + (numberX+1) * downLeft - 1);
    //верний левый угол --
    gap.append((numberX+1) * numberY * 2 - 1);
    gap.append(gap[2] - (numberX+1) * upLeft + 1);
    //нижний правый угол
    gap.append((numberX+1) * numberY * 2);
    gap.append(gap[4] + (numberX+1) * downRight - 1);
    //верний правый угол --
    gap.append((numberX+1) * numberY * 3 - 1);
    gap.append(gap[6] - (numberX+1) * upLeft + 1);

}


bool Worker::checkIndex(int i)
{
    return ((i >= gap[0] && i <= gap[1]) || (i <= gap[2] && i >= gap[3]) || (i >= gap[4] && i <= gap[5]) || (i <= gap[6] && i >= gap[7]));
}


void Worker::goToElement(int index)
{
    //опустить стол
    writeData_planar("Table DN\r\n");
    //перевод координат в массив байтов для передачи станку
    QByteArray x = QByteArray::number((int)DotsX[index]);
    QByteArray y = QByteArray::number((int)DotsY[index]);
    writeData_planar("Set " + x + " " + y + '\r' + '\n');
}


void Worker::copyUpToIndex(int index)
{
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


void Worker::pauseWalk()
{
//    //поменять статус паузы
    pause = !pause;
    pauseIndex = currentIndex;
//    emit sendMessageBox("information", "информация");
//    emit sendMessageBox("warning", "внимание");
//    emit sendMessageBox("critical", "караул");
 }


void Worker::setIndex(int index)
{
    //обновить индекс для обхода с нового элемента
    pauseIndex = currentIndex;
    currentIndex = index;
}


void Worker::stopWalk()
{
    pause = false;
    currentIndex = lastIndex;//DotsX.count()
}


void Worker::saveMeasure(int index)
{
    //функция копирует файл до нужного индекса и заменяет собой файл источник
    goToElement(index);
    MeasureDie2();
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
    writeData_planar("Table DN\r\n");
}


void Worker::tableController(QByteArray message)
{
    writeData_planar(message);
}


void Worker::getBCoordinates()
{
    int x = 0;
    int y = 0;
    writeData_planar("State\r\n");
    readData_planar();
    QString responce = QString(planarResponce);
    if (responce.contains(QRegularExpression(R"(< \d+ \d+ \d+ \d+\r\n)"))) {
        x = responce.split(" ")[2].toInt();
        y = responce.split(" ")[3].toInt();
        emit sendBCoordsSignal(x, y);
    }
}


void Worker::lightController(QByteArray msg)
{
    writeData_light(msg);
}


void Worker::MeasureDie2()
{
    int start = clock();
    KeithlyZeroCorrection2();
    int stopZero = clock();
    qDebug() << "zerocor estimated: " << QString::number(zeroDelay*3) <<" . real :" << QString::number(stopZero-start);

//    writeData_planar("Table UP\r\n");
//    QThread::msleep(1000);

    Keithly05VSet2();//300
    ForwardCurrent = KeithlyGet2();
    int stopGet05 = clock();
    qDebug() << "set FC estimated: " << QString::number(FCdelay) <<" . real :" << QString::number(stopGet05 - stopZero);

    Keithly10mVSet2();
    QThread::msleep(DC10mVDelay);
    DarkCurrent10mV = KeithlyGet2();//800
    int stopGetDC10mV = clock();
    qDebug() << "set DC 10mV estimated: "<< QString::number(DC10mVDelay) << " . real :" << QString::number(stopGetDC10mV - stopGet05);

    Keithly1VSet2();
    DarkCurrent1V = KeithlyGet2();//600
    int stopGetDC1V = clock();
    qDebug() << "set DC 1V estimated: "<< QString::number(DC1VDelay) << " . real :" << QString::number(stopGetDC1V - stopGetDC10mV);

//    LightOn2();

    Keithly10mVSet2();
    writeData_keithley("CURR:RANG 2e-6\n");
    QThread::msleep(lightDelay);
    LightCurrent = KeithlyGet2();
    int stopGetLightCurrent = clock();
    qDebug() << "set Light current estimated: "<< QString::number(lightDelay) << " . real :" << QString::number(stopGetLightCurrent - stopGetDC1V);
    writeData_keithley("*RST\n");

    emit sendLogSignal((QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                        QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4)).toUtf8());

    //LightOff2();

    int stop = clock();
    qDebug() << "Total time estimated: "<< QString::number(zeroDelay*3 + FCdelay + DC10mVDelay + DC1VDelay + lightDelay) << " . real :" << QString::number(stop-start);
}


void Worker::KeithlyZeroCorrection2()
{
    writeData_keithley("*RST\n");
    writeData_keithley("SYST:ZCH ON\n");
    writeData_keithley("CURR:RANG 2e-9\n");
    QThread::msleep(zeroDelay);//400
    writeData_keithley("INIT\n");
    QThread::msleep(zeroDelay);//400
    writeData_keithley("SYST:ZCOR:STAT OFF\n");
    QThread::msleep(zeroDelay);//400
    writeData_keithley("SYST:ZCOR:ACQ\n");
    writeData_keithley("SYST:ZCH OFF\n");
    writeData_keithley("SYST:ZCOR ON\n");
}


void Worker::Keithly05VSet2()
{
    writeData_keithley("CURR:RANG 2e-3\n");
    writeData_keithley("SOUR:VOLT:RANG 1\n");
    writeData_keithley("SOUR:VOLT " + QByteArray::number(0.6) + '\n');
    writeData_keithley("SOUR:VOLT:ILIM 1e-3\n");
    writeData_keithley("SOUR:VOLT:STAT ON\n");
    QThread::msleep(FCdelay);//300
}


void Worker::Keithly10mVSet2()
{
    writeData_keithley( "CURR:RANG 2e-10\n");
    writeData_keithley("SOUR:VOLT:STAT OFF\n");
    writeData_keithley("SOUR:VOLT -10e-3\n");
    writeData_keithley("SOUR:VOLT:STAT ON\n");
}


void Worker::Keithly1VSet2()
{
    writeData_keithley("SOUR:VOLT:STAT OFF\n");
    writeData_keithley("SOUR:VOLT -1\n");
    writeData_keithley("SOUR:VOLT:STAT ON\n");
    QThread::msleep(DC1VDelay);//600
}


double Worker::KeithlyGet2()
{
    keithleyResponce = keithleyResponce.remove(keithleyResponce.indexOf("A"), keithleyResponce.length() - keithleyResponce.indexOf("A"));
    return keithleyResponce.toDouble();
}

void Worker::LightOn2()
{
    writeData_light("1111\n");
    readData_light();
}


void Worker::LightOff2()
{
    writeData_light("0001\n");
    //readData_light();
}


void Worker::autoWalk2(bool allNew, QString dir_cur)
{

    dir = dir_cur.endsWith(".csv") ? dir_cur : dir_cur + ".csv";
    if (allNew) emit sendProgressBarRangeSignal(currentIndex, lastIndex);
    int i = 0;
    //спросить начать обход или продолжить?
    Worker::copyUpToIndex(currentIndex);
    QFile file(dir);
    QString dir1 = file.fileName();
    //qDebug() << "Если 0, то строки идентичны  : " << QString::compare(dir1, dir_cur, Qt::CaseInsensitive);
    //если обход с начала, то переписать файл, иначе добавить
    if (file.open(allNew ? QIODevice::ReadWrite : QIODevice::Append)) {
        QTextStream output(&file);

        int start = clock();

        while (currentIndex <= lastIndex)
        {
            //если индекс попал на срез, то пропускаем
            if (checkIndex(currentIndex)) {
                currentIndex++;
                continue;
            }
            //опустить стол
            writeData_planar("Table DN\r\n");
            //перевод координат в массив байтов для передачи станку
            i = currentIndex;
            goToElement(i);
            MeasureDie2();
            QThread::msleep(500);
            //запускаем единичное измерение
            //запись в файл строки с измерениями токов
            QString res = QString::number(i, 'D', 0) + ", " + QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                    QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + '\n';
            output << res;
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
                    QThread::msleep(10);
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

        writeData_planar("Table DN\r\n");
        int end = clock();
        int t = (end - start) / CLOCKS_PER_SEC;
        int s = t - t / 60;
        t /= 60;
        int m = t - t / 60;
        t /= 60;
        int h = t - t / 24;
        //int d = t - h;

        emit sendMessageBox("Обход закончен", "Прошло времени: " + QString::number(h) + " часов, " +  QString::number(m) + " минут, " + QString::number(s) + " секунд.");
    }
}


void Worker::measureElement2()
{
    int start = clock();

    MeasureDie2();

    int end = clock();
    int t = (end - start);
    emit sendMessageBox("Information", QString::number(t));

}


void Worker::setDelay(QList<int> * delays)
{
    zeroDelay = delays->at(0);
    FCdelay = delays->at(1);
    DC10mVDelay = delays->at(2);
    DC1VDelay = delays->at(3);
    lightDelay = delays->at(4);

}


void Worker::initPort9()
{
    LPCTSTR sPortName = L"\\\\.\\COM9";

    hSerial = CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            qDebug() << "serial port does not exist.\n";
        }
        qDebug()<< "some other error occurred.\n";
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        qDebug() << "getting state error\n";
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        qDebug() << "error setting serial port state\n";
    }
}


void Worker::readWin()
{
    DWORD iSize;
    char sReceivedChar;
    while (true)
    {
        BOOL ret = ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
        if (iSize > 0)
            // если что-то принято, выводим
            qDebug() << sReceivedChar;
    }
}


void Worker::writeWin(const QByteArray src)
{
    //char data[] = "Hello from C++";  // строка для передачи
    char *dst;
    qstrcpy(dst, src);  // строка для передачи
    DWORD dwSize = sizeof(dst);   // размер этой строки
    DWORD dwBytesWritten;    // тут будет количество собственно переданных байт

    BOOL iRet = WriteFile(hSerial, dst, dwSize, &dwBytesWritten, NULL);
//    qDebug() << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. ";
}

