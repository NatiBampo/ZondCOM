#include "worker.h"
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QSerialPortInfo>
#include <ctime>
#include <QMessageBox>
#include <windows.h>
#include <typeinfo>
#include <QDebug>
#include "LoggingCategories.h"

HANDLE hSerial;

Worker::Worker(QMutex* mtxp)
{
    this->mutex = mtxp;
    connect(this, &Worker::sendPackageSignal, this, &Worker::sendPackage);
    connect(this, &Worker::sendPackageSignalRead, this, &Worker::sendPackageRead);

    serialPortA5 = new QSerialPort();
    serialPortKeithly = new QSerialPort();
    serialPortLight = new QSerialPort();
    closePorts();

}

Worker::~Worker()
{
    closePorts();
    delete serialPortA5;
    delete serialPortKeithly;
    delete serialPortLight;
}

void Worker:: sendPackage(QSerialPort *serialPort, QByteArray package, int delay)
{
    lastAnswer = "";
    serialPort->write(package);
    serialPort->flush();
    serialPort->waitForBytesWritten(400);
}

void Worker:: sendPackageRead (QSerialPort *serialPort, QByteArray package, int delay)
{
    lastAnswer = "";
    serialPort->write(package);
    serialPort->flush();
    serialPort->waitForBytesWritten(400);
    if (serialPort->waitForReadyRead(400)) lastAnswer.append(serialPort->readAll());
}


void Worker::tableController(const QByteArray message, const bool &planarStatus)
{
    if (serialPortA5->isOpen() || planarStatus)
    {
        //if (message == "State\r\n") serialPortA5->flush();
        emit sendPackageSignalRead(serialPortA5, message, 400);//1000
        planarResponce = "";
        planarResponce.append(lastAnswer);

        QString responce = QString(planarResponce);//lastAnswer
        //
        qInfo(logInfo())<< responce << "<- в ответ на ->" + QString(message);//\r\n

        if (responce == "")
        {
            endLinePlanar();
        }
        else if (responce.contains(QRegularExpression(R"(BSY)")))//< BSY\r\n
        {
            stopped = true;
            emit sendMessageBox("warning", "BSY. Планар не отвечает.\n Проверьте передачу управления.");
            qWarning(logWarning()) << "BSY – ЗУ находится в режиме ручной настройки, обхода или исполняет команду";
        }
        else if (responce.contains(QRegularExpression(R"(FLT)")))
        {
            stopped = true;
            emit sendMessageBox("warning", "FLT – авария ЗУ");
            qCritical(logCritical()) << "FLT – авария ЗУ";
        }
        else if (responce.contains(QRegularExpression(R"(ERC)")))
        {
            emit sendMessageBox("warning", "ERC – ошибка команды или формата");
            qWarning(logWarning()) << "ERC – ошибка команды или формата";

            endLinePlanar();
        }
    }
    else
    {
        stopped = true;
        emit sendMessageBox("warning", "Порт планара закрыт.\n Отправка комманды не работает");
    }
}


void Worker::endLinePlanar()
{
    serialPortA5->write("\r\n");
    serialPortA5->flush();
    serialPortA5->waitForBytesWritten(400);
    lastAnswer = "";
    planarResponce = "";
    if (serialPortA5->waitForReadyRead(400)) lastAnswer.append(serialPortA5->readAll());
    if (lastAnswer==planarResponce)
    {
        errorCount++;
        emit sendLogSignal(lastAnswer + "<-ответ на /r/n||прошлый->" + planarResponce);
    }
    else
    {
        errorCount = 0;
    }
    if (errorCount > 5)
    {
        stopWalk();

        emit sendMessageBox("warning", "Планар не отвечает");
    }
    planarResponce.append(lastAnswer);
}


void Worker::openPorts(QString portNameA5, QString portNameKeithly, QString portNameLight)
{
    closePorts();
    emit openPortResultSignal(portNameA5, "Planar", openPort(serialPortA5, portNameA5, QSerialPort::Baud115200));
    emit openPortResultSignal(portNameKeithly,"Keithley", openPort(serialPortKeithly, portNameKeithly, QSerialPort::Baud57600));
    emit openPortResultSignal(portNameLight, "Light", openPort(serialPortLight, portNameLight, QSerialPort::Baud9600));
}


void Worker::autoOpenPorts()
{
    serialPortA5 = new QSerialPort();
    serialPortKeithly = new QSerialPort();
    serialPortLight = new QSerialPort();
    QList<QString> list;
    foreach(const QSerialPortInfo &port,  QSerialPortInfo::availablePorts())
    {
        list.append(port.portName());
    };

    QHash<QSerialPort *, QString> map;
    bool tmp_flag;
    for (int i=0; i < list.length(); i++)
    {
        //сперва окрываем порт планара
        if (!map.contains(serialPortA5))
        {
            tmp_flag = openPort(serialPortA5, list[i], QSerialPort::Baud115200);

            if (tmp_flag && checkPlanarCOM())
            {
                map.insert(serialPortA5, list[i]);
                emit openPortResultSignal(list[i], "Planar", tmp_flag);
                continue;
            }
            if (serialPortA5->isOpen())serialPortA5->close();
        }

        //порт кейтли
        if (!map.contains(serialPortKeithly))
        {
            tmp_flag = openPort(serialPortKeithly, list[i], QSerialPort::Baud57600);
            if (tmp_flag && checkKeithlyCOM())
            {
                map.insert(serialPortKeithly, list[i]);
                emit openPortResultSignal(list[i], "Keithley", tmp_flag);
                continue;
            }
            if (serialPortKeithly->isOpen()) serialPortKeithly->close();
        }
        //порт ардуины/диода

        if (!map.contains(serialPortLight))
        {
            //qDebug() << i << " light condition";
            tmp_flag = openPort(serialPortLight, list[i], QSerialPort::Baud9600);
            if (tmp_flag && checkLightCOM())
            {
                map.insert(serialPortLight, list[i]);
                emit openPortResultSignal(list[i], "Light", tmp_flag);
            } else
            {
                if (serialPortLight->isOpen()) serialPortLight->close();
            }
        }
    }
}


bool Worker::checkPlanarCOM()
{
    //serialPortA5->flush();
    tableController("State\r\n", true);
    QString responce = QString(planarResponce);
    QRegularExpression re(R"(-?\d+ -?\d+ -?\d+ -?\d+\r\n|BSY|OK|ERC|NBP|EDG)");
    QRegularExpressionMatch match = re.match(responce);
    if (responce != "" && match.hasMatch())
    {
        emit sendLogSignal(match.captured(0).toUtf8());

        return true;
    }
    else if (responce == "")
    {
        QThread::msleep(300);
        tableController("State\r\n", true);
        responce = QString(planarResponce);
        match = re.match(responce);
        if (responce != "" && match.hasMatch())
        {
            return true;
        }

    }
    return false;
}


bool Worker::checkKeithlyCOM()
{
    try
    {
        KeithlyZeroCorrection(serialPortKeithly);
        Keithly05VSet(serialPortKeithly);
        ForwardCurrent = KeithlyGet(serialPortKeithly);
        QString responce = QString(lastAnswer);
        if (responce.contains(QRegularExpression(R"(\d+A,)"))) return true;//\d+.\d+[+-]\d+A,
    }
    catch (const char* error){}

    return false;
}


bool Worker::checkLightCOM()
{
    for (int i =0; i < 5; i++)
    {
        try
        {
            lightController("1111\r\n", true);
            if (serialPortLight->waitForReadyRead(1000)) lastAnswer.append(serialPortLight->readAll());
            emit sendLogSignal(lastAnswer);
            if (lastAnswer.contains("C3B2A1") || lastAnswer.contains("A1B2C3"))
            {
                lightController("0001\n", true);
                return true;
            }
            lightController("0001\n", true);
        }
        catch (QSerialPort::SerialPortError error)
        {
            qDebug() << error;
        }
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


bool Worker::allPortsOpen()
{
    return (serialPortA5->isOpen() && serialPortKeithly->isOpen() && serialPortLight->isOpen());
}


void Worker::scanningPlate(double AX, double AY,double BX, double BY, double stepX, double stepY, double numberX,
                           double numberY, double colSlide, bool centerColumn,
                           int upLeft, int upRight, int downLeft, int downRight, int upCenter, int downCenter,
                           bool leftColumn, bool rightColumn)
{
    //функция пересчета таблицы координат первоначально или после изменений спинбаров на форме
    //сперва обновляем глобальные переменные
    //numberX необходимо привести к фактическому параметру
    DotsX.clear();
    DotsY.clear();
    gap.clear();

    centerDie = centerColumn;
    leftDie = leftColumn;
    rightDie = rightColumn;

    numX = numberX+1;
    numY = numberY;

    double tgAlpha = ((numberY - 1) * stepY) / ((numberX - 1) * stepX);
    double CosAlpha = qPow(1 + tgAlpha * tgAlpha, -0.5);
    double SinAlpha = tgAlpha * CosAlpha;

    BX = abs(AX - BX);
    BY = abs(AY - BY);
    emit sendBCoordsSignal(BX, BY);

    double X3 = -BX * CosAlpha * CosAlpha - BY * SinAlpha * CosAlpha + BX;
    double Y3 = -BY * CosAlpha * CosAlpha + BX * SinAlpha * CosAlpha + BY;
    double StepxX = (X3 - BX) / (numberX - 1);
    double StepxY = (Y3 - BY) / (numberX - 1);
    double StepyX = -X3 / (numberY - 1);
    double StepyY = -Y3 / (numberY - 1);
    double K = 1.75 / 2.805;
    double slideX = (colSlide - (numberX+1) * stepX) * 1000;


    //сперва правый столбец
    for (int j = 0; j < numberY; j++)
    {
        for (int i = -2-numberX; i < -1 ; i++)
        {
            if (i % 2 == 0) DotsX.append(BX + StepxX * i + StepyX * j  + slideX); else DotsX.append(BX + StepxX * i + StepyX * j - StepyX * K + slideX);
            if (i % 2 == 0) DotsY.append(BY + StepxY * i + StepyY * j); else DotsY.append(BY + StepxY * i + StepyY * j - StepyY * K);
        }
    }

    //потом левый столбец
    for (int j = 0; j < numberY; j++)
    {
        for (int i = numberX; i < numberX*2+1; i++)
        {
            if (i % 2 == 0) DotsX.append(BX + StepxX * i + StepyX * j  - slideX); else DotsX.append(BX + StepxX * i + StepyX * j - StepyX * K - slideX);
            if (i % 2 == 0) DotsY.append(BY + StepxY * i + StepyY * j); else DotsY.append(BY + StepxY * i + StepyY * j - StepyY * K);
        }
    }


    //центральный столбец
    for (int j = 0; j < numberY; j++)
    {
        for (int i = -1; i < numberX; i++)
        {
            if (i % 2 == 0) DotsX.append(BX + StepxX * i + StepyX * j); else DotsX.append(BX + StepxX * i + StepyX * j - StepyX * K);
            if (i % 2 == 0) DotsY.append(BY + StepxY * i + StepyY * j); else DotsY.append(BY + StepxY * i + StepyY * j - StepyY * K);
        }
    }
    lastIndex = DotsX.length() - 1;

    //нижний правый угол
    gap.append(0);
    gap.append(gap[0] + (numberX+1) * downRight - 1);
    //верхний правый угол --
    gap.append((numberX+1) * numberY   - 1);
    gap.append(gap[2] - (numberX+1) * upRight + 1);
    //нижний левый угол
    gap.append((numberX+1) * numberY );
    gap.append(gap[4] + (numberX+1) * downLeft - 1);
    //верний левый угол --
    gap.append((numberX+1) * numberY * 2 - 1);
    gap.append(gap[6] - (numberX+1) * upLeft + 1);
    //центр низ
    gap.append((numberX+1) * numberY * 2);
    gap.append(gap[8] + (numberX+1) * downCenter - 1);
    //центр верх
    gap.append((numberX+1) * numberY * 3 - 1);
    gap.append(gap[10] - (numberX+1) * upCenter + 1); 

    gapIndex = gap[0] + (numberX+1) * downRight;
    qInfo(logInfo()) << "Ориентация выполнена";
}

//check if measure is odd
bool Worker::checkIndex(int i)
{
    if (i < numX*numY)
    {
        return !rightDie || (i >= gap[0] && i <= gap[1]) || (i <= gap[2] && i >= gap[3]);
    }
    else if (i < numX*numY*2)
    {
        return !leftDie || (i >= gap[4] && i <= gap[5]) || (i <= gap[6] && i >= gap[7]);
    }
    else if (i < numX*numY*3)
    {
        return !centerDie || (i >= gap[8] && i <= gap[9]) || (i <= gap[10] && i >= gap[11]);
    }
    return false;
}


void Worker::autoWalk(bool allNew, QString dir_cur, int startIndex, const bool &planar_status, const bool &keithley_status, const bool &light_status, const bool &badDie)
{

    //if (!planar_status) return;

    //сдвиг индекса до начала рабочей зоны(не попадает в отступ)
    currentIndex = startIndex < gapIndex ? gapIndex : startIndex;

    QFileInfo fileInfo(dir_cur);
    QString dir_dump = "C:/qt/dump/" + fileInfo.baseName() + "_start_index_" + QString::number(currentIndex) + ".csv";

    emit sendProgressBarRangeSignal(currentIndex, lastIndex);


    QFile file(dir_dump);

    //если обход с начала, то переписать файл, иначе добавить
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream output(&file);
        int walkTime = (lastIndex - currentIndex) * 5;

        QDateTime estFinish = QDateTime::currentDateTime().addSecs(walkTime);

        emit sendLogSignal(("Время окончания : " + estFinish.toString("hh:mm:ss")).toUtf8());
        emit sendEndOfWalkTime(estFinish.toString("hh:mm"));

        int start = clock();
        stopped = false;
        QString res = "";
        qInfo(logInfo()) << "Начат обход пластины " << fileInfo.baseName() <<" , начиная с элемента -> " << QString::number(currentIndex);
        int lowFCcounter = 0;
        while (currentIndex <= lastIndex && !stopped)
        {
            //если индекс попал на срез, то пропускаем
            if (checkIndex(currentIndex))
            {
                currentIndex++;
                continue;
            }

            goToElement(currentIndex, planar_status);

            //проверка отзывчивости планара в конце ряда, дабы не дырявить пластины активностью(вверх/вниз) на месте
            if (currentIndex % 16 == 0 && !getCurrentCoords(currentIndex, planar_status))
            {
                emit sendLogSignal(planarResponce);
                emit sendMessageBox("Ошибка", "Планар не отвечает на элементах :\n" + QString::number(currentIndex-15)  + " - " + QString::number(currentIndex));
                stopped = true;
                paused = false;
                break;
            }

            //проверка нажатия Паузы
            mutex->lock();
            if (paused)
            {
                qInfo(logInfo()) << "Поставили паузу";
                mutex->unlock();
                while (true)
                {
                    QThread::msleep(10);
                    mutex->lock();
                    if (!paused)
                    {
                        qInfo(logInfo()) << "Убрали паузу";
                        break;
                    }
                    mutex->unlock();
                }
            }
            mutex->unlock();

            //начинаем мерить элемент
            if (keithley_status) MeasureDie(serialPortA5, serialPortKeithly, planar_status, keithley_status, light_status);

            //запись в файл строки с измерениями токов
            res = QString::number(currentIndex, 'D', 0) + ", " + QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                    QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + '\n';
            output << res;

            //считаем количество элементов без прямого контакта, если больше 2 подряд выключаем
            if (ForwardCurrent > FCBorder || LightCurrent < LightBorder) lowFCcounter++;
            else lowFCcounter=0;

            //отправляем данные на таблицу, если ток в норме
            if (lowFCcounter<=2 || keithley_status || badDie)
            {
                emit sendAddTableSignal(currentIndex, ForwardCurrent, DarkCurrent10mV, DarkCurrent1V, LightCurrent - DarkCurrent10mV);
                emit sendProgressBarValueSignal(currentIndex);
            }
            else
            {
                stopWalk();
                emit sendMessageBox("warning", "Недопустимые значения тока");
                qWarning(logWarning())<<"Недопустимые значения тока :"<< res;
            }
            currentIndex++;

        }

        qInfo(logInfo())<<"Закончен обход пластины " << fileInfo.baseName() <<"  на элементе -> " << QString::number(currentIndex);

        currentIndex = 0;

        file.close();

        tableController("Table DN\r\n", planar_status);

        int end = clock();
        int t = (end - start) / CLOCKS_PER_SEC;
        int s = t % 60;
        t /= 60;
        int m = t % 60;
        t /= 60;
        int h = t % 24;
        //int d = t - h;
        emit sendMessageBox("Обход закончен", "Прошло времени: " + QString::number(h) + " часов, " +  QString::number(m) + " минут, " + QString::number(s) + " секунд.");

    }
    else
    {
        emit sendMessageBox("warning", "Файл открыт другой программой.\nЗапись не возможна.");
    }
    emit sendEndWalkSignal();

}


void Worker::pauseWalk()
{
    paused = !paused;
}


void Worker::stopWalk()
{
    paused = false;
    stopped = true;
}


void Worker::goToElement(int index, const bool & planar_status)
{
    //опустить стол
    tableController("Table DN\r\n", planar_status);
    //перевод координат в массив байтов для передачи станку
    QByteArray x = QByteArray::number((int)DotsX[index]);
    QByteArray y = QByteArray::number((int)DotsY[index]);
    tableController("Set " + x + " " + y + '\r' + '\n', planar_status);
}


void Worker::saveMeasure(int index, const bool &planar_status, const bool &keithley_status, const bool &light_status)
{
    if (checkIndex(index))
    {
        emit sendMessageBox("info", "Индекс за пределами измеряемой зоны.\nПроверье отступы по краям\n и выполните ориентацию");
        return;
    }
    currentIndex = index;
    goToElement(currentIndex, planar_status);

    MeasureDie(serialPortA5, serialPortKeithly, planar_status, keithley_status, light_status);
    emit sendAddTableSignal(currentIndex, ForwardCurrent, DarkCurrent10mV, DarkCurrent1V, LightCurrent - DarkCurrent10mV);
}


void Worker::openCsvFile(QString dir)
{
    QFile file (dir);
    QFileInfo fileInfo(dir);
    QString dir_dump = "C:/qt/dump/" + fileInfo.baseName() + "_copy_" + ".csv";

    QFile::copy(dir,  dir_dump);// "C:/qt/log/copyOrbita/" + fileInfo.fileName());
    emit sendMessageBox("info", "Загружен " + fileInfo.baseName());
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        line = QString::fromUtf8(file.readLine());
        int start = line.split(", ")[0].toInt();
        currentIndex = 0;
        int tmp = 0;
        while(!line.isNull() && currentIndex < 1440)
        {
            auto arr = line.split(", ");
            tmp = arr[0].toInt();
            if (tmp == 0 && currentIndex > start ) break;
            //проверка на нулевые строки
            currentIndex = tmp;
            ForwardCurrent = arr[1].toDouble();
            DarkCurrent10mV = arr[2].toDouble();
            DarkCurrent1V = arr[3].toDouble();
            LightCurrent = arr[4].toDouble();

            //отправляем данные на таблицу(в модель)
            emit sendAddTableSignal(currentIndex, ForwardCurrent, DarkCurrent10mV, DarkCurrent1V, LightCurrent);
            line = QString::fromUtf8(file.readLine());
        }
    }
    file.close();
    //source.remove();
}


bool Worker::getCurrentCoords(int index, const bool & planar_status)
{
    int x = 0;
    int y = 0;
    tableController("State\r\n", planar_status);
    QRegularExpression re(R"(< -?\d+ -?\d+ -?\d+ -?\d+\r\n)");

    //if (responce.contains(QRegularExpression(R"(< -?\d+ -?\d+ -?\d+ -?\d+\r\n)")))
    for (int i = 0; i < 5; i++)
    {
        //emit sendLogSignal(planarResponce);
        QString responce = QString(planarResponce);//lastAnswer
        QRegularExpressionMatch match = re.match(responce);
        if (match.hasMatch())
        {
            QString line = match.captured(0);
            x = line.split(" ")[2].toInt();
            y = line.split(" ")[3].toInt();

            if (index == -1)
            {
                emit sendCurrentCoordsSignal(x, y);
            }
            if (index == -2)
            {
                emit sendBCoordsSignal(x, y);
            }
            if (index > 0)
            {
                qDebug(logDebug()) << "Парсинг x, y : " << x << ", " << y << "  Dots: i, x , y = " << currentIndex << ", " << DotsX[currentIndex] << ", " << DotsY[currentIndex];
                if (currentIndex < lastIndex && (x==0 && y == 0))
                {
                    QThread::msleep(1000);
                    endLinePlanar();
                    continue;
                }

                bool cond1 = x == (int) DotsX.at(index);
                bool cond2 = y == (int) DotsY.at(index);
                return cond1 && cond2;
            }
            return true;
        }
        else //if (responce == "< OK\r\n")
        {
            endLinePlanar();
        }
    }

    return false;
}



void Worker::lightController(QByteArray msg, const bool &light_status)
{
    if (serialPortLight->isOpen() || light_status)
    {
        emit sendPackageSignal(serialPortLight, msg, NO_ANSWER_DELAY);
    }
    else
    {
        emit sendMessageBox("warning", "Порт диода закрыт.\n Отправка комманды не работает");
        qWarning(logWarning()) << "Порт диода закрыт. Отправка комманды не работает.\r\n";
    }

}


void Worker::MeasureDie(QSerialPort *serialPortA5, QSerialPort *serialPortKeithly, const bool &planar_status, const bool &keithley_status, const bool &light_status)
{
    if (allPortsOpen() || keithley_status)
    {
        KeithlyZeroCorrection(serialPortKeithly);

        if (planar_status) emit sendPackageSignalRead(serialPortA5, "Table UP\r\n", 200);

        QThread::msleep(200);//800
        Keithly10mVSet(serialPortKeithly);
        QThread::msleep(DC10mVDelay);//800
        DarkCurrent10mV = KeithlyGet(serialPortKeithly);
        Keithly1VSet(serialPortKeithly);
        DarkCurrent1V = KeithlyGet(serialPortKeithly);
        Keithly05VSet(serialPortKeithly);
        ForwardCurrent = KeithlyGet(serialPortKeithly);

        lightController("1111\n", light_status);

        Keithly10mVSet(serialPortKeithly);
        emit sendPackageSignal(serialPortKeithly, "CURR:RANG 2e-6\n", NO_ANSWER_DELAY);
        QThread::msleep(lightDelay);//200
        LightCurrent = KeithlyGet(serialPortKeithly);
        emit sendPackageSignal(serialPortKeithly, "*RST\n", NO_ANSWER_DELAY);
        emit sendLogSignal((QString::number(currentIndex) + ", " + QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                        QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4)).toUtf8());

        lightController("0001\n", light_status);

        if (planar_status) emit sendPackageSignalRead(serialPortA5, "Table DN\r\n", 200);

    }
    else
    {
        emit sendMessageBox("warning", "Один из портов закрыт.\n Измерение не возможно.");
    }
}


void Worker::KeithlyZeroCorrection(QSerialPort *serialPort)
{
    sendPackage(serialPort, "*RST\n", NO_ANSWER_DELAY);
    sendPackage(serialPort, "SYST:ZCH ON\n", NO_ANSWER_DELAY);
    sendPackage(serialPort, "CURR:RANG 2e-9\n", NO_ANSWER_DELAY);
    QThread::msleep(zeroDelay);//400
    sendPackage(serialPort, "INIT\n", NO_ANSWER_DELAY);
    QThread::msleep(zeroDelay);
    sendPackage(serialPort, "SYST:ZCOR:STAT OFF\n", NO_ANSWER_DELAY);
    QThread::msleep(zeroDelay);
    sendPackage(serialPort, "SYST:ZCOR:ACQ\n", NO_ANSWER_DELAY);
    sendPackage(serialPort, "SYST:ZCH OFF\n", NO_ANSWER_DELAY);
    sendPackage(serialPort, "SYST:ZCOR ON\n", NO_ANSWER_DELAY);
}


void Worker::Keithly05VSet(QSerialPort *serialPort)
{
    sendPackage(serialPort, "CURR:RANG 2e-3\n", NO_ANSWER_DELAY);
    sendPackage(serialPort, "SOUR:VOLT:RANG 1\n", NO_ANSWER_DELAY);
    QByteArray tmp = QByteArray::number(((double)FCVoltage) / 1000);
    sendPackage(serialPort, "SOUR:VOLT " + tmp + '\n', NO_ANSWER_DELAY);
    sendPackage(serialPort, "SOUR:VOLT:ILIM 1e-3\n", NO_ANSWER_DELAY);
    sendPackage(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
    QThread::msleep(FCdelay);
}


double Worker::KeithlyGet(QSerialPort *serialPort)
{
    emit sendPackageSignalRead(serialPort, "READ?\n", ANSWER_DELAY);
    QByteArray byteArray = lastAnswer;
    byteArray = byteArray.remove(byteArray.indexOf("A"), byteArray.length() - byteArray.indexOf("A"));
    return byteArray.toDouble();
}

void Worker::Keithly10mVSet(QSerialPort *serialPort)
{
   sendPackage(serialPort, "SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
   sendPackage(serialPort, "SOUR:VOLT -1e-2\n", NO_ANSWER_DELAY);
   sendPackage(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
   QThread::msleep(400);
    sendPackage(serialPort, "CURR:RANG 2e-10\n", NO_ANSWER_DELAY);
}

void Worker::Keithly1VSet(QSerialPort *serialPort)
{
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT OFF\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT -1\n", NO_ANSWER_DELAY);
    emit sendPackageSignal(serialPort, "SOUR:VOLT:STAT ON\n", NO_ANSWER_DELAY);
    QThread::msleep(DC1VDelay);
}


void Worker::measureElement(const bool &planar_status, const bool &keithley_status, const bool &light_status)
{
    if (keithley_status)
    {
        int start = clock();
        MeasureDie(serialPortA5, serialPortKeithly, planar_status, keithley_status, light_status);

        int end = clock();
        int t = (end - start);
        emit sendMessageBox("Последнее измерение: ", "FC: " + QString::number(ForwardCurrent, 'E', 4) + ", \nDC10mV: " + QString::number(DarkCurrent10mV, 'E', 4) + ", \nDC1V: " +
                            QString::number(DarkCurrent1V, 'E', 4) + ", \nLC10mV: " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + "\n\nВремя: " + QString::number(t / CLOCKS_PER_SEC) + "сек"); //QString::number(t));
    }
}

void Worker::measureFC(const bool &planar_status, const bool &keithley_status)
{

    if (allPortsOpen() || keithley_status)
    {
        KeithlyZeroCorrection(serialPortKeithly);
        if (planar_status) emit sendPackageSignalRead(serialPortA5, "Table UP\r\n", ANSWER_DELAY);
        Keithly05VSet(serialPortKeithly);
        ForwardCurrent = KeithlyGet(serialPortKeithly);
        if (planar_status) emit sendPackageSignalRead(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
        emit sendMessageBox("Прямой ток измерение: ", "Voltage : " + QByteArray::number(((double)FCVoltage) / 1000) + " V : " + QString::number(ForwardCurrent, 'E', 4));
    }
    else
    {
        emit sendMessageBox("warning", "Один из портов закрыт.\n Измерение не возможно.");
    }
}


void Worker::setDelay(QList<int> * delays)
{
    zeroDelay = delays->at(0);
    FCdelay = delays->at(1);
    DC10mVDelay = delays->at(2);
    DC1VDelay = delays->at(3);
    lightDelay = delays->at(4);
    FCVoltage =  delays->at(5);
    planarDelay = delays->at(6);
}
