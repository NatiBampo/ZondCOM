#include "worker.h"


Worker::Worker(QMutex* mtxp, struct Peripherals* periph)
{
    mutex = mtxp;
    connect(this, &Worker::sendPackageSignal, this, &Worker::sendPackage);
    connect(this, &Worker::sendPackageSignalRead, this, &Worker::sendPackageRead);
    connecter = new Connecter(periph);
}

Worker::~Worker()
{
    delete mutex;
}


void Worker::calculate_dots(struct DieParameters* die, struct Dots* dots)
{
    //функция пересчета таблицы координат первоначально или после изменений спинбаров на форме
    //сперва обновляем глобальные переменные
    //numberX необходимо привести к фактическому параметру
    dots->X.clear();
    dots->Y.clear();

    double tgAlpha = ((die->numY - 1) * die->stepY) / ((die->numX - 1) * die->stepX);
    double CosAlpha = qPow(1 + tgAlpha * tgAlpha, -0.5);
    double SinAlpha = tgAlpha * CosAlpha;

    die->BX = abs(die->AX - die->BX);
    die->BY = abs(die->AY - die->BY);
    emit sendBCoordsSignal(die->BX, die->BY);

    double X3 = -die->BX * CosAlpha * CosAlpha - die->BY * SinAlpha * CosAlpha + die->BX;
    double Y3 = -die->BY * CosAlpha * CosAlpha + die->BX * SinAlpha * CosAlpha + die->BY;
    double StepxX = (X3 - die->BX) / (die->numX - 1);
    double StepxY = (Y3 - die->BY) / (die->numX - 1);
    double StepyX = -X3 / (die->numY - 1);
    double StepyY = -Y3 / (die->numY - 1);
    double K = 1.75 / 2.805;
    double slideX = (die->colSlide - (die->numX + 1) * die->stepX) * 1000;


    //сперва правый столбец
    for (int j = 0; j < die->numY; j++)
    {
        for (int i = - 2 - die->numX; i < -1 ; i++)
        {
            if (i % 2 == 0) dots->X.push_back(die->BX + StepxX * i + StepyX * j  + slideX);
            else dots->X.push_back(die->BX + StepxX * i + StepyX * j - StepyX * K + slideX);
            if (i % 2 == 0) dots->Y.append(BY + StepxY * i + StepyY * j);
            else dots->Y.append(die->BY + StepxY * i + StepyY * j - StepyY * K);
        }
    }

    //потом левый столбец
    for (int j = 0; j < die->numY; j++)
    {
        for (int i = die->numX; i < die->numX * 2 + 1; i++)
        {
            if (i % 2 == 0) dots->X.push_back(die->BX + StepxX * i + StepyX * j  - slideX);
            else dots->X.push_back(die->BX + StepxX * i + StepyX * j - StepyX * K - slideX);
            if (i % 2 == 0) dots->Y.append(die->BY + StepxY * i + StepyY * j);
            else dots->Y.append(die->BY + StepxY * i + StepyY * j - StepyY * K);
        }
    }

    //центральный столбец
    for (int j = 0; j < die->numY; j++)
    {
        for (int i = -1; i < die->numX; i++)
        {
            if (i % 2 == 0) dots->X.push_back(die->BX + StepxX * i + StepyX * j);
            else dots->X.push_back(die->BX + StepxX * i + StepyX * j - StepyX * K);
            if (i % 2 == 0) dots->Y.append(die->BY + StepxY * i + StepyY * j);
            else dots->Y.append(die->BY + StepxY * i + StepyY * j - StepyY * K);
        }
    }
    lastIndex = dots->X.length() - 1;

    //нижний правый угол
    dots->gap[0] = 0;
    dots->gap[1] = dots->gap[0] + (die->numX + 1) * die->downRight - 1;
    //верхний правый угол --
    dots->gap[2] = (die->numX + 1) * die->numY - 1;
    dots->gap[3] = (dots->gap[2] - (die->numX + 1) * die->upRight + 1);
    //нижний левый угол
    dots->gap[4] = ((die->numX + 1) * die->numY );
    dots->gap[5] = (dots->gap[4] + (die->numX + 1) * die->downLeft - 1);
    //верний левый угол --
    dots->gap[6] = ((die->numX + 1) * die->numY * 2 - 1);
    dots->gap[7] = (dots->gap[6] - (die->numX + 1) * die->upLeft + 1);
    //центр низ
    dots->gap[8] = ((die->numX + 1) * die->numY * 2);
    dots->gap[9] = (dots->gap[8] + (die->numX + 1) * die->downCenter - 1);
    //центр верх
    dots->gap[10] = ((die->numX + 1) * die->numY * 3 - 1);
    dots->gap[11] = (dots->gap[10] - (die->numX + 1) * die->upCenter + 1);

    //gapIndex = gap[0] + (die->numX+1) * die->downRight;
    qInfo(logInfo()) << "Ориентация выполнена";
}

//check if measure is odd
bool Worker::checkIndex(int i)
{
    if (i < die->numX * die->numY)
    {
        return !rightDie || (i >= gap[0] && i <= gap[1]) || (i <= gap[2] && i >= gap[3]);
    }
    else if (i < die->numX * die->numY * 2)
    {
        return !leftDie || (i >= gap[4] && i <= gap[5]) || (i <= gap[6] && i >= gap[7]);
    }
    else if (i < die->numX * die->numY * 3)
    {
        return !centerDie || (i >= gap[8] && i <= gap[9]) || (i <= gap[10] && i >= gap[11]);
    }
    return false;
}


void Worker::autoWalk(struct WalkSettings* walk, struct Peripherals* periph)
{

    //if (!planar_status) return;
    //сдвиг индекса до начала рабочей зоны(не попадает в отступ)
    walk->currentIndex = walk->startIndex < gapIndex ? gapIndex : walk->startIndex;

    QFileInfo fileInfo(dir_cur);
    QString dir_dump = "C:/qt/dump/" + fileInfo.baseName() + "_start_index_"
            + QString::number(walk->currentIndex) + ".csv";

    emit sendProgressBarRangeSignal(walk->currentIndex, lastIndex);

    QFile file(dir_dump);

    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream output(&file);
        int walkTime = (lastIndex - walk->currentIndex) * 5;

        QDateTime estFinish = QDateTime::currentDateTime().addSecs(walkTime);

        emit sendLogSignal(("Время окончания : " + estFinish.toString("hh:mm:ss")).toUtf8());
        emit sendEndOfWalkTime(estFinish.toString("hh:mm"));

        int start = clock();
        stopped = false;
        QString res = "";
        qInfo(logInfo()) << "Начат обход пластины " << fileInfo.baseName()
                         <<" , начиная с элемента -> " << QString::number(walk->currentIndex);
        int lowFCcounter = 0;

        while (walk->currentIndex <= lastIndex && !stopped)
        {
            //если индекс попал на срез, то пропускаем
            if (checkIndex(walk->currentIndex))
            {
                walk->currentIndex++;
                continue;
            }

            goToDot(walk);//

            //проверка отзывчивости планара в конце ряда,
            //дабы не дырявить пластины активностью(вверх/вниз) на месте
            if (walk->currentIndex % 16 == 0 && !getCurrentCoords(walk))
            //(currentIndex, planar_status)
            {
                emit sendLogSignal(planarResponce);
                emit sendMessageBox("Ошибка", "Планар не отвечает на элементах :\n"
                                    + QString::number(walk->currentIndex-15)  + " - "
                                    + QString::number(walk->currentIndex));
                stopped = true;
                paused = false;
                break;
            }

            //проверка нажатия Паузы
            checkPause();

            //начинаем мерить элемент
            if (walk->keithley_status)
                MeasureDie(periph, walk, currents);

            //запись в файл строки с измерениями токов
            res = QString::number(walk->currentIndex, 'D', 0) + ", " + QString::number(ForwardCurrent, 'E', 4)
                    + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                    QString::number(DarkCurrent1V, 'E', 4) + ", "
                    + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + '\n';
            output << res;

            //считаем количество элементов без прямого контакта, если больше 2 подряд выключаем
            if (ForwardCurrent > FCBorder || LightCurrent < LightBorder)
            {
                lowFCcounter++;
            }
            else
            {
                lowFCcounter=0;
            }
            //отправляем данные на таблицу, если ток в норме
            if (lowFCcounter<=2 || badDie || !keithley_status)
            {
                emit sendAddTableSignal(currentIndex, ForwardCurrent,
                                        DarkCurrent10mV, DarkCurrent1V,
                                        LightCurrent - DarkCurrent10mV);
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

        qInfo(logInfo())<<"Закончен обход пластины " << fileInfo.baseName()
                       <<"  на элементе -> " << QString::number(currentIndex);

        currentIndex = 0;

        file.close();

        tableController("Table DN\r\n", walk->planar_status);
        timeSpent(start);
    }
    else
    {
        emit sendMessageBox("warning", "Файл открыт другой программой.\nЗапись не возможна.");
    }
    emit sendEndWalkSignal();

}


void Worker::checkPause()
{
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
}

void Worker::timeSpent(int start)
{
    int end = clock();
    int t = (end - start) / CLOCKS_PER_SEC;
    int s = t % 60;
    t /= 60;
    int m = t % 60;
    t /= 60;
    int h = t % 24;
    //int d = t - h;
    emit sendMessageBox("Обход закончен", "Прошло времени: " + QString::number(h)
                        + " часов, " +  QString::number(m) + " минут, "
                        + QString::number(s) + " секунд.");
}

void Worker::pauseWalk(struct WalkSettings* walk)
{
    walk->paused = !walk->paused;
}


void Worker::stopWalk(struct WalkSettings* walk)
{
    walk->paused = false;
    walk->stopped = true;
}


void Worker::goToDot(struct WalkSettings* walk)
{
    //опустить стол
    tableController("Table DN\r\n", walk->planar_status);
    //перевод координат в массив байтов для передачи станку
    QByteArray x = QByteArray::number((int)DotsX[index]);
    QByteArray y = QByteArray::number((int)DotsY[index]);
    tableController("Set " + x + " " + y + '\r' + '\n', walk->planar_status);
}


void Worker::saveMeasure(struct WalkSettings* walk)
{
    if (checkIndex(index))
    {
        emit sendMessageBox("info", "Индекс за пределами измеряемой зоны."
                                    "\nПроверье отступы по краям\n и выполните ориентацию");
        return;
    }
    currentIndex = startIndex;
    goToElement(walk);

    MeasureDie(serialPortA5, serialPortKeithly, walk, currents);
    emit sendAddTableSignal(currentIndex, ForwardCurrent, DarkCurrent10mV,
                            DarkCurrent1V, LightCurrent - DarkCurrent10mV);
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


            //отправляем данные на таблицу(в модель)
            emit sendAddTableSignal(arr[0].toInt(), arr[1].toDouble(),arr[2].toDouble(),
                                    arr[3].toDouble(), arr[4].toDouble());
            line = QString::fromUtf8(file.readLine());
        }
    }
    file.close();
    //source.remove();
}


bool Worker::currentCoords(int index, bool planar_status)
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
                qDebug(logDebug()) << "Парсинг x, y : " << x << ", " << y << "  Dots: i, x , y = "
                                   << currentIndex << ", " << DotsX[currentIndex] << ", "
                                   << DotsY[currentIndex];
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



void Worker::measureElement(struct WalkSettings* walk,
                            struct Delays* delays,
                            struct Currents* curr)
{
    if (walk->keithley_status)
    {
        int start = clock();
        connector->measureDot(walk, delays, curr);

        int end = clock();
        int t = (end - start);
        emit sendMessageBox("Последнее измерение: ",
                            "FC: " + QString::number(curr->forward05V, 'E', 4)
                            + ", \nDC10mV: " + QString::number(curr->dark10mV, 'E', 4)
                            + ", \nDC1V: " + QString::number(curr->dark1V, 'E', 4)
                            + ", \nLC10mV: " + QString::number(curr->light10mV, 'E', 4)
                            + "\n\nВремя: " + QString::number(t / CLOCKS_PER_SEC) + "сек");
        //QString::number(t));
    }
}

void Worker::measureFC(struct WalkSettings* walk,
                       struct Delays* delays,
                       struct Currents* curr)
{

    if (allPortsOpen() || walk->keithley_status)
    {
        KeithlyZeroCorrection(serialPortKeithly);
        if (walk->planar_status) emit sendPackageSignalRead(serialPortA5, "Table UP\r\n", ANSWER_DELAY);
        Keithly05VSet(serialPortKeithly);
        ForwardCurrent = KeithlyGet(serialPortKeithly);
        if (walk->planar_status) emit sendPackageSignalRead(serialPortA5, "Table DN\r\n", ANSWER_DELAY);
        emit sendMessageBox("Прямой ток измерение: ", "Voltage : "
                            + QByteArray::number(((double)FCVoltage) / 1000) + " V : "
                            + QString::number(ForwardCurrent, 'E', 4));
    }
    else
    {
        emit sendMessageBox("warning", "Один из портов закрыт.\n Измерение не возможно.");
    }
}


/*void Worker::setDelay(struct Delays* delays)
{
    zeroDelay = delays->at(0);
    FCdelay = delays->at(1);
    DC10mVDelay = delays->at(2);
    DC1VDelay = delays->at(3);
    lightDelay = delays->at(4);
    FCVoltage =  delays->at(5);
    planarDelay = delays->at(6);
}*/
//
