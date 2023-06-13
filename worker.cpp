#include "worker.h"
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QSerialPortInfo>
#include <QRegularExpressionMatch>
#include <ctime>



Worker::Worker(QMutex* mtxp)
{
    this->mutex = mtxp;
    connect(this, &Worker::sendPackageSignal, this, &Worker::sendPackage);
}

Worker::~Worker()
{

}


void Worker::sendPackage(Agent ag, QByteArray package, int delay) {//QSerialPort *serialPort
    //if (serialPort == serialPortKeithly)
    switch (ag)
    {
    case Agent::Keithley :
        kSerialWin->writeCOM(package);
        //writeCOM(package);
        break;
    case Agent::Planar :
        pSerial->writeCOM(package);
        break;
    case Agent::Light :
        lSerial->writeCOM(package);
    }
    /*
    else
    {
        lastAnswer = "";
        serialPort->write(package);
        serialPort->flush();
        //emit sendLogSignal(package.remove(package.indexOf("\\"), package.length() - package.indexOf("\\")));
        while (serialPort->waitForReadyRead(delay)) lastAnswer.append(serialPort->readAll());
        //if (lastAnswer != "") emit sendLogSignal(lastAnswer.remove(lastAnswer.indexOf("\\"), lastAnswer.length() - lastAnswer.indexOf("\\")));
    }
    */
}


void Worker::openPorts(QString portNameA5, QString portNameKeithly, QString portNameLight)
{
    /*old qt comport version
    //serialPortA5 = new QSerialPort();
    //serialPortKeithly = new QSerialPort();
    //serialPortLight = new QSerialPort();

    //QString str1 = "\\\\.\\" + portNameKeithly;
    //QByteArray ba = str1.toLocal8Bit();
    //const char *c_str2 = ba.data();
    //int k_result = kSerialWin->initCOM(c_str2);

    //serial with dll.currently not working
    //int k_result = initCOM(c_str2);

    if (portNameA5 != "Планар"){emit openPortResultSignal(portNameA5, "Planar", openPort(serialPortA5, portNameA5, QSerialPort::Baud115200));}
    if (portNameKeithly != "Keithley"){emit openPortResultSignal(portNameKeithly,"Keithley", (bool) k_result);}
                                                                 //openPort(serialPortKeithly, portNameKeithly, QSerialPort::Baud57600));}
    if (portNameLight != "Диод"){emit openPortResultSignal(portNameLight, "Light", openPort(serialPortLight, portNameLight, QSerialPort::Baud9600));}
    */

    if (portNameA5 != "Планар")
    {
        int p_result = pSerial->initCOM(("\\\\.\\" + portNameA5).toLocal8Bit().data(), 115200);
        emit openPortResultSignal(portNameA5, "Planar", p_result > 0 ? true : false);
    }
    if (portNameKeithly != "Keithley")
    {
        int k_result = kSerialWin->initCOM(("\\\\.\\" + portNameKeithly).toLocal8Bit().data(), 57600);
        emit openPortResultSignal(portNameKeithly,"Keithley", k_result > 0 ? true : false);
    }
    if (portNameLight != "Диод")
    {
        int l_result = lSerial->initCOM(("\\\\.\\" + portNameLight).toLocal8Bit().data(), 9600);
        emit openPortResultSignal(portNameLight, "Light", l_result > 0 ? true : false);
    }
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
/*
    if (serialPortA5->isOpen()) serialPortA5->close();
    if (serialPortKeithly->isOpen()) serialPortKeithly->close();
    if (serialPortLight->isOpen()) serialPortLight->close();

        delete serialPortA5;
        delete serialPortKeithly;
        delete serialPortLight;
*/
    if (kSerialWin->isOpen()) kSerialWin->closeCOM();
    if (pSerial->isOpen()) pSerial->closeCOM();
    if (lSerial->isOpen()) lSerial->closeCOM();

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


bool Worker::checkPlanarCOM() {
    /*
    QString localAnswer = "";
    serialPortA5->write("State\r\n");
    serialPortA5->flush();
    while (serialPortA5->waitForReadyRead(ANSWER_DELAY)) localAnswer.append(serialPortA5->readAll());

    if (localAnswer != "") {
        qDebug()<<localAnswer;
        if (localAnswer.contains(stateReg)) {
            return true;
        }
    }
    */

    try {
        return planarState().contains(stateReg);
    } catch (...){
        qDebug()<<"Port is not open or not responding";
    }
    return false;
}


bool Worker::checkKeithlyCOM() {
    try {
        KeithlyZeroCorrection(Agent::Keithley);
        Keithly05VSet(Agent::Keithley);
        ForwardCurrent = KeithlyGet(Agent::Keithley);
        if (ForwardCurrent!=0) return true;
    }
    catch (const char* error){}

    return false;
}


bool Worker::checkLightCOM() {
    try {
        LightOn();
        char * str = lSerial->readCOM(15, 500);
        QString localAns = QString::fromLocal8Bit(str);
        if (localAns.contains("C3B2A1")) {
                LightOff();
                return true;
        }
    } catch (...) {
        qDebug() << "light com port error";
    }
    return false;
}


void Worker::scanningPlate(double BX, double BY, double stepX, double stepY, double numberX,
                           double numberY, double colSlide, double rowSlide, bool all_three,
                           int upLeft, int upRight, int downLeft, int downRight) {
    //функция пересчета таблицы координат первоначально или после изменений спинбаров на форме
    //сперва обновляем глобальные переменные
    //numberX необходимо привести к фактическому параметру
    DotsX.clear();
    DotsY.clear();

    /*
     //original code
    lastIndex = (numberX + 1) * numberY * 3;

    double tgAlpha = ((numberY - 1) * stepY) / ((numberX - 1) * stepX);
    double CosAlpha = qPow(1 + tgAlpha * tgAlpha, -0.5);
    double SinAlpha = tgAlpha * CosAlpha;
    double X3 = (BX - AX) * CosAlpha * CosAlpha + (BY - AY) * SinAlpha * CosAlpha + AX;
    double Y3 = (BY - AY) * CosAlpha * CosAlpha - (BX - AX) * SinAlpha * CosAlpha + AY;
    double StepxX = (X3 - AX) / (numberX - 1);
    double StepxY = (Y3 - AY) / (numberX - 1);
    double StepyX = (BX - X3) / (numberY - 1);
    double StepyY = (BY - Y3) / (numberY - 1);
    double K = 1.75 / 2.805;

    QList<double> DotsX;
    QList<double> DotsY;
    for (int j = 0; j < numberY; j++) {
        for (int i = -1; i < numberX; i++) {
            if (i % 2 == 0) DotsX.append(AX + StepxX * i + StepyX * j); else DotsX.append(AX + StepxX * i + StepyX * j - StepyX * K);
            if (i % 2 == 0) DotsY.append(AY + StepxY * i + StepyY * j); else DotsY.append(AY + StepxY * i + StepyY * j - StepyY * K);
        }
    }
    */

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


bool Worker::checkIndex(int i) {
    return ((i >= gap[0] && i <= gap[1]) || (i <= gap[2] && i >= gap[3]) || (i >= gap[4] && i <= gap[5]) || (i <= gap[6] && i >= gap[7]));
}


void Worker::autoWalk(bool allNew, QString dir_cur) {

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
            tableController("Table DN\r\n");
            //перевод координат в массив байтов для передачи станку
            i = currentIndex;
            Worker::goToElement(i);
//            Worker::MeasureDie(serialPortA5, serialPortKeithly);
            Worker::MeasureDie(Agent::Planar, Agent::Keithley);
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
        int end = clock();
        int t = (end - start) / CLOCKS_PER_SEC;
        qDebug() << t << " seconds ";
        tableController("Table DN\r\n");
    }
}


void Worker::measureElement() {
    int start = clock();
//    MeasureDie(serialPortA5, serialPortKeithly);
    MeasureDie(Agent::Planar, Agent::Keithley);
    int end = clock();
    int t = (end - start);
    //qDebug() << end;
    qDebug() << t << " milli seconds ";
    //QThread::msleep(500);
}


void Worker::goToElement(int index) {
    //опустить стол
    //emit sendPackageSignal(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
    emit sendPackageSignal(Agent::Planar, "Table DN\r\n", ANSWER_DELAY);
    //перевод координат в массив байтов для передачи станку
    QByteArray x = QByteArray::number((int)DotsX[index]);
    QByteArray y = QByteArray::number((int)DotsY[index]);
    emit sendPackageSignal(Agent::Planar, "Set " + x + " " + y + '\r' + '\n', ANSWER_DELAY);
//    emit sendPackageSignal(serialPortA5, "Set " + x + " " + y + '\r' + '\n', ANSWER_DELAY);
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
//    MeasureDie(serialPortA5, serialPortKeithly);
    //MeasureDie(Agent::Planar, Agent::Keithley);
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
    tableController("Table DN\r\n");
//    emit sendPackageSignal(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
}


void Worker::tableController(QByteArray message) {
    emit sendPackageSignal(Agent::Planar, message, ANSWER_DELAY);//serialPortA5

}


QString Worker::planarState()
{
    tableController("State\r\n");
    char * str = pSerial->readCOM(50, ansDelay);
    return QString::fromLocal8Bit(str);
}


void Worker::getBCoordinates() {
    int x = 0;
    int y = 0;
    QString answer = planarState();
    if (answer.contains(stateReg)) {
        x = answer.split(" ")[2].toInt();
        y = answer.split(" ")[3].toInt();
        emit sendBCoordsSignal(x, y);
    }
}


void Worker::lightController(QByteArray message) {
    emit sendPackageSignal(Agent::Light, message, NO_ANSWER_DELAY);//serialPortLight
}


void Worker::MeasureDie(Agent serialPortA5, Agent serialPortKeithly) {//(QSerialPort *serialPortA5, QSerialPort *serialPortKeithly)
    int start = clock();
    KeithlyZeroCorrection(serialPortKeithly);
    //int stopZero = clock();
    //qDebug() << "zerocor estimated: " << QString::number(zeroDelay*3) <<" . real :" << QString::number(stopZero-start);
    tableController("Table UP\r\n");

    Keithly05VSet(serialPortKeithly);
    ForwardCurrent = KeithlyGet(serialPortKeithly);
    //int stopGet05 = clock();
    //qDebug() << "set FC estimated: " << QString::number(FCdelay) <<" . real :" << QString::number(stopGet05 - stopZero);

    Keithly10mVSet(serialPortKeithly);
    QThread::msleep(DC10mVDelay);//800
    DarkCurrent10mV = KeithlyGet(serialPortKeithly);
    //int stopGetDC10mV = clock();
    //qDebug() << "set DC 10mV estimated: "<< QString::number(DC10mVDelay) << " . real :" << QString::number(stopGetDC10mV - stopGet05);

    Keithly1VSet(serialPortKeithly);
    DarkCurrent1V = KeithlyGet(serialPortKeithly);
    //int stopGetDC1V = clock();
    //qDebug() << "set DC 1V estimated: "<< QString::number(DC1VDelay) << " . real :" << QString::number(stopGetDC1V - stopGetDC10mV);

    LightOn();

    Keithly10mVSet(serialPortKeithly);
    emit sendPackageSignal(serialPortKeithly, "CURR:RANG 2e-6\n", NO_ANSWER_DELAY);
    QThread::msleep(photoDelay);//400//200
    LightCurrent = KeithlyGet(serialPortKeithly);
    //int stopGetLightCurrent = clock();
    //qDebug() << "set Light current estimated: "<< QString::number(photoDelay) << " . real :" << QString::number(stopGetLightCurrent - stopGetDC1V);

    emit sendPackageSignal(serialPortKeithly, "*RST\n", NO_ANSWER_DELAY);
    emit sendLogSignal((QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                        QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4)).toUtf8());
    LightOff();

    int stop = clock();
    qDebug() << "Total time estimated: "<< QString::number(zeroDelay*3 + FCdelay + DC10mVDelay + DC1VDelay + photoDelay) << " . real :" << QString::number(stop-start);
}


void Worker::KeithlyZeroCorrection(Agent serialPort) {//QSerialPort *serialPort
    emit sendPackageSignal(serialPort, "*RST\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SYST:ZCH ON\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "CURR:RANG 2e-9\n", NO_ANSWER_DELAY);
    QThread::msleep(zeroDelay);//400
    emit sendPackageSignal(serialPort, "INIT\n", NO_ANSWER_DELAY);
    QThread::msleep(zeroDelay);
    emit sendPackageSignal(serialPort, "SYST:ZCOR:STAT OFF\n", NO_ANSWER_DELAY);
    QThread::msleep(zeroDelay);
    emit sendPackageSignal(serialPort, "SYST:ZCOR:ACQ\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SYST:ZCH OFF\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SYST:ZCOR ON\n", NO_ANSWER_DELAY);
}


void Worker::Keithly05VSet(Agent serialPort) //QSerialPort *serialPort
{
    emit sendPackageSignal(serialPort, "CURR:RANG 2e-3\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:RANG 1\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT " + QByteArray::number(0.6) + '\n', NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:ILIM 1e-3\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
    QThread::msleep(FCdelay);//400
}


double Worker::KeithlyGet(Agent serialPort) {
    emit sendPackageSignal(serialPort, "READ?\n", ANSWER_DELAY);
    //char * str = readCOM(50, ansDelay);
    char * str = kSerialWin->readCOM(50, ansDelay);
    QString byteArray = QString::fromLocal8Bit(str);
    byteArray = byteArray.remove(byteArray.indexOf("A"), byteArray.length() - byteArray.indexOf("A"));
    return byteArray.toDouble();
}


void Worker::Keithly10mVSet(Agent serialPort) {
    emit sendPackageSignal(serialPort, "CURR:RANG 2e-10\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT -1e-2\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
}


void Worker::Keithly1VSet(Agent serialPort) {
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT -1\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
    QThread::msleep(DC1VDelay);//600
}


void Worker::LightOn() {
    lightController("1111\n");
}


void Worker::LightOff() {
    lightController("0001\n");
}


void Worker::setDelay(QList<int> *delays) {
    mutex->lock();
    zeroDelay = delays->at(0);
    FCdelay = delays->at(1);
    DC10mVDelay = delays->at(2);
    DC1VDelay = delays->at(3);
    photoDelay = delays->at(4);
    ansDelay = delays->at(5);
    mutex->unlock();
}







