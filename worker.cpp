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


void Worker::tableController(QByteArray message)
{
    if (serialPortA5->isOpen())
    {
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
    planarResponce.append(lastAnswer);
    //emit sendLogSignal('<' + "endLine\\r\\n");
    emit sendLogSignal('>' + planarResponce);
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
    tableController("State\r\n");
    QString responce = QString(planarResponce);
//    QRegularExpression re(R"(?<State>< -?\d+ -?\d+ -?\d+ -?\d+\r\n)|(?<FLT>FLT)|(?<BSY>BSY)|(?<OK>OK)|(?<ERC>ERC)|(?<NBP>NBP)|(?<EDG>EDG)");
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
        tableController("State\r\n");
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
        //emit sendPackageSignal(serialPortA5, "Table UP\r\n", ANSWER_DELAY);
        Keithly05VSet(serialPortKeithly);
        ForwardCurrent = KeithlyGet(serialPortKeithly);
        QString responce = QString(lastAnswer);
        //emit sendPackageSignal(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
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
            LightOn();
            if (serialPortLight->waitForReadyRead(1000)) lastAnswer.append(serialPortLight->readAll());
            emit sendLogSignal(lastAnswer);
            if (lastAnswer.contains("C3B2A1") || lastAnswer.contains("A1B2C3"))
            {
                LightOff();
                return true;
            }
            LightOff();
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


void Worker::autoWalk(bool allNew, QString dir_cur, int startIndex)
{
    //dir = dir_cur.endsWith(".csv") ? dir_cur : dir_cur + ".csv";
    QFileInfo fileInfo(dir_cur);

    QString dir_dump = "C:/qt/dump/" + fileInfo.fileName();

    //сдвиг индекса до начала рабочей зоны(не попадает в отступ)
    currentIndex = startIndex < gapIndex ? gapIndex : startIndex;
    emit sendProgressBarRangeSignal(currentIndex, lastIndex);

    /*
    if (allNew) emit sendProgressBarRangeSignal(currentIndex, lastIndex);
    //если режим продолжить и скопировать не вышло -> выход
    if(!allNew)
    {
        bool copyOk = copyUpToIndex(currentIndex);
        //плохо скопировалось. данные будут потерены
        if (!copyOk) return;
    }
    */
    QFile file(dir_dump);

    //если обход с начала, то переписать файл, иначе добавить
//    if (file.open(allNew ? QIODevice::ReadWrite : QIODevice::Append))
    if (file.open(QIODevice::Append))
    {
        QTextStream output(&file);

        int start = clock();
        stopped = false;
        QString res = "";
        qInfo(logInfo()) << "Начат обход пластины " << dir_dump <<" , начиная с элемента -> " << QString::number(currentIndex);
        while (currentIndex <= lastIndex && !stopped)
        {
            //если индекс попал на срез, то пропускаем
            if (checkIndex(currentIndex))
            {
                currentIndex++;
                continue;
            }

            goToElement(currentIndex);

            //проверка отзывчивости планара в конце ряда, дабы не дырявить пластины активностью(вверх/вниз) на месте
            if (currentIndex % 16 == 0 && !getCurrentCoords(currentIndex))
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
            MeasureDie(serialPortA5, serialPortKeithly);

            //запись в файл строки с измерениями токов
            res = QString::number(currentIndex, 'D', 0) + ", " + QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                    QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + '\n';
            output << res;
            //output.flush();

            //отправляем данные на таблицу
            emit sendAddTableSignal(currentIndex, ForwardCurrent, DarkCurrent10mV, DarkCurrent1V, LightCurrent - DarkCurrent10mV);
            emit sendProgressBarValueSignal(currentIndex);
            currentIndex++;

        }

        qInfo(logInfo())<<"Закончен обход пластины " << dir_dump <<"  на элементе -> " << QString::number(currentIndex);

        currentIndex = 0;

        file.close();

        tableController("Table DN\r\n");

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


void Worker::goToElement(int index)
{
    //опустить стол
    tableController("Table DN\r\n");
    //перевод координат в массив байтов для передачи станку
    QByteArray x = QByteArray::number((int)DotsX[index]);
    QByteArray y = QByteArray::number((int)DotsY[index]);
    tableController("Set " + x + " " + y + '\r' + '\n');
}


bool Worker::copyUpToIndex(int index)
{
    //function copies all lines staring from 0 up to index and replaces source file
    //функция копирует файл до нужного индекса и заменяет собой файл источник
    if (index <= gapIndex)
    {
        return false;
    }
    QFile file (dir);
    QFileInfo fileInfo(dir);
    QString copyPath = "C:/qt/log/copyOrbita/" + fileInfo.baseName() + "__copy" + QString::number(clock()/1000) + ".csv";

    if (!QFile::copy(dir, copyPath))
    {
        qInfo(logInfo()) << "Не удалось скопировать " << dir;
        return false;
    }
    qInfo(logInfo()) << "Копия файла: "<< copyPath;

    QFile dest(dir);
    QFile source(copyPath);
    QString line;
    if (dest.open(QIODevice::ReadWrite))
    {
        if (source.open(QIODevice::ReadWrite))
        {
            //QTextStream input(&source);
            QTextStream output(&dest);
            //QString line = input.readLine();
            line = QString::fromUtf8(source.readLine());
            if (line.isNull())
            {
                emit sendMessageBox("warning", "Попытка считать пустой файл");
                qWarning(logWarning()) << "Попытка считать пустой файл";
                return false;
            }
            else
            {
                int x = line.split(", ")[0].toInt();
                if (x != gapIndex)
                {
                    emit sendMessageBox("warning", "Начальный индекс пластины и файла не совпадают.\n");
                    qWarning(logWarning()) << "Не совпадение начальных индексов: пластины = " << gapIndex << "и файла" << x;
                    return false;
                }

            }

            for (int i = gapIndex; i < index; i++)
            {
                if (!line.isNull()) break;
                output << line;// <<'\n';
                output.flush();
                //line = input.readLine();
                line = QString::fromUtf8(source.readLine());
            }
        }
        else
        {
            emit sendMessageBox("warning", copyPath + "\nФайл открыт другой программой.\nЗапись не возможна.");
        }



        dest.close();
        source.close();
        //source.remove();
        //QFile::rename(dir_tmp, dir);
        return true;
    }
    else
    {
        emit sendMessageBox("warning", dir + "\nФайл открыт другой программой.\nЗапись не возможна.");
    }


    return false;
}


void Worker::saveMeasure(int index)
{
    //функция копирует файл до нужного индекса и заменяет собой файл источник
    //function updates file with new measurement using index
    if (checkIndex(index))
    {
        emit sendMessageBox("info", "Индекс за пределами измеряемой зоны.\nПроверье отступы по краям\n и выполните ориентацию");
        return;
    }
    currentIndex = index;
    goToElement(currentIndex);

    MeasureDie(serialPortA5, serialPortKeithly);
    emit sendAddTableSignal(currentIndex, ForwardCurrent, DarkCurrent10mV, DarkCurrent1V, LightCurrent - DarkCurrent10mV);


    dir = dir.endsWith(".csv") ? dir : dir + ".csv";
    QString dir_tmp = dir.remove(dir.indexOf(".csv"), dir.length() - dir.indexOf(".csv")) + "tmp.csv";
    QFile dest (dir_tmp);
    QFile file (dir);
    QString line;
    if (dest.open(QIODevice::ReadWrite) && file.open(QIODevice::ReadWrite))
    {
        //QTextStream input(&source);//!input.atEnd()
        QTextStream output(&dest);
        line = QString::fromUtf8(file.readLine());

        int i = 0;
        for (; !line.isNull() && i < 1440; ++i)
        {
            if (i==currentIndex)
            {
                //updating line using new measurement data
                output << QString::number(i) + ", " + QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                          QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + '\n';
                //updating table
                emit sendAddTableSignal(i, ForwardCurrent, DarkCurrent10mV, DarkCurrent1V, LightCurrent - DarkCurrent10mV);
            }
            else
            {
                //copying each line except the measured one
                output << line;//input.readLine() << '\n';
            }
            line = QString::fromUtf8(file.readLine());
        }

        //new line will be added in case measurement is ahead of main group
        if (index > i)
        {
            while (i < index)
            {
                output << QString::number(index) + ", 0, 0, 0, 0" + '\n';
                i++;
            }
            {
                output << QString::number(index) + ", " + QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                          QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + '\n';
            }
        }
        //копируем всё обратно и удаляем временный файл

        dest.close();
        file.close();
        file.remove();
        QFile::rename(dir_tmp, dir);
    }
    tableController("Table DN\r\n");
}


void Worker::openCsvFile(QString dir)
{
    QFile file (dir);
    QFileInfo fileInfo(dir);

    QFile::copy(dir,  "C:/qt/log/copyOrbita/" + fileInfo.fileName());
    emit sendMessageBox("info", fileInfo.fileName());
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        line = QString::fromUtf8(file.readLine());
        currentIndex = 0;

        while(!line.isNull() && currentIndex < 1440)
        {
            auto arr = line.split(", ");

            currentIndex = arr[0].toInt();
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


bool Worker::getCurrentCoords(int index)
{
    int x = 0;
    int y = 0;
    tableController("State\r\n");
    QString responce = QString(planarResponce);//lastAnswer
    emit sendLogSignal(planarResponce);
    QRegularExpression re(R"(< -?\d+ -?\d+ -?\d+ -?\d+\r\n)");
    QRegularExpressionMatch match = re.match(responce);

    //if (responce.contains(QRegularExpression(R"(< -?\d+ -?\d+ -?\d+ -?\d+\r\n)")))
    if (match.hasMatch())
        {
        QString line = match.captured(0);
        x = line.split(" ")[2].toInt();
        y = line.split(" ")[3].toInt();

        //qDebug(logDebug()) << "Парсинг x :" << x << "|| y : " << y;

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
            //emit sendLogSignal(("Парсинг x :" + QString::number(x) + "|| y : " + QString::number(y)).toUtf8());
            bool cond1 = x == (int) DotsX.at(index);
            bool cond2 = y == (int) DotsY.at(index);
            return cond1 && cond2;
        }
    }
    return false;
}


void Worker::lightController(QByteArray msg)
{
    if (serialPortLight->isOpen())
    {
        emit sendPackageSignal(serialPortLight, msg, NO_ANSWER_DELAY);
    }
    else
    {
        emit sendMessageBox("warning", "Порт диода закрыт.\n Отправка комманды не работает");
        qWarning(logWarning()) << "Порт диода закрыт. Отправка комманды не работает.\r\n";
    }

}


void Worker::MeasureDie(QSerialPort *serialPortA5, QSerialPort *serialPortKeithly)
{
    if (allPortsOpen())
    {
        KeithlyZeroCorrection(serialPortKeithly);
        emit sendPackageSignalRead(serialPortA5, "Table UP\r\n", 200);
        QThread::msleep(200);//800
        Keithly10mVSet(serialPortKeithly);
        QThread::msleep(DC10mVDelay);//800
        DarkCurrent10mV = KeithlyGet(serialPortKeithly);
        Keithly1VSet(serialPortKeithly);
        DarkCurrent1V = KeithlyGet(serialPortKeithly);
        Keithly05VSet(serialPortKeithly);
        ForwardCurrent = KeithlyGet(serialPortKeithly);
        LightOn();
        Keithly10mVSet(serialPortKeithly);
        emit sendPackageSignal(serialPortKeithly, "CURR:RANG 2e-6\n", NO_ANSWER_DELAY);
        QThread::msleep(lightDelay);//200
        LightCurrent = KeithlyGet(serialPortKeithly);
        emit sendPackageSignal(serialPortKeithly, "*RST\n", NO_ANSWER_DELAY);
        emit sendLogSignal((QString::number(currentIndex) + ", " + QString::number(ForwardCurrent, 'E', 4) + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                        QString::number(DarkCurrent1V, 'E', 4) + ", " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4)).toUtf8());
        LightOff();
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


void Worker::LightOn()
{
    lightController("1111\n");
}

void Worker::LightOff()
{
    lightController("0001\n");
}


void Worker::measureElement()
{
    int start = clock();

    MeasureDie(serialPortA5, serialPortKeithly);

    int end = clock();
    int t = (end - start);
    emit sendMessageBox("Последнее измерение: ", "FC: " + QString::number(ForwardCurrent, 'E', 4) + ", \nDC10mV: " + QString::number(DarkCurrent10mV, 'E', 4) + ", \nDC1V: " +
                        QString::number(DarkCurrent1V, 'E', 4) + ", \nLC10mV: " + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + "\n\nВремя: " + QString::number(t / CLOCKS_PER_SEC) + "сек"); //QString::number(t));
}


void Worker::measureFC()
{
    if (allPortsOpen())
    {
    KeithlyZeroCorrection(serialPortKeithly);
    emit sendPackageSignalRead(serialPortA5, "Table UP\r\n", ANSWER_DELAY);
    Keithly05VSet(serialPortKeithly);
    ForwardCurrent = KeithlyGet(serialPortKeithly);

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


void Worker::copyUpSlot(int idx, QString dir_cur)
{
    if (copyUpToIndex(idx)) emit sendMessageBox("info", "Успех. Файл скопирован");
}
