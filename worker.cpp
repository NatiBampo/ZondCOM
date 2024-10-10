#include "worker.h"


Worker::Worker(QMutex* mtxp, struct Peripherals* periph)
{
    mutex = mtxp;
    connector = new Connector(periph);
}

Worker::~Worker()
{
    delete mutex;
}


void Worker::calculateDots(struct DieParameters* die,
                            struct Dots* dots,
                            struct WalkSettings* walk)
{
    //функция пересчета таблицы координат первоначально или после изменений спинбаров на форме
    //сперва обновляем глобальные переменные
    //numberX необходимо привести к фактическому параметру
    dots->X->clear();
    dots->Y->clear();

    double tgAlpha = ((die->numY - 1) * die->stepY) / ((die->numX - 1) * die->stepX);
    double CosAlpha = qPow(1 + tgAlpha * tgAlpha, -0.5);
    double SinAlpha = tgAlpha * CosAlpha;

    die->BX = abs(die->AX - die->BX);
    die->BY = abs(die->AY - die->BY);
    //emit sendBCoordsSignal(die->BX, die->BY);

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
            if (i % 2 == 0) dots->X->push_back(die->BX + StepxX * i + StepyX * j  + slideX);
            else dots->X->push_back(die->BX + StepxX * i + StepyX * j - StepyX * K + slideX);
            if (i % 2 == 0) dots->Y->append(BY + StepxY * i + StepyY * j);
            else dots->Y->append(die->BY + StepxY * i + StepyY * j - StepyY * K);
        }
    }

    //потом левый столбец
    for (int j = 0; j < die->numY; j++)
    {
        for (int i = die->numX; i < die->numX * 2 + 1; i++)
        {
            if (i % 2 == 0) dots->X->push_back(die->BX + StepxX * i + StepyX * j  - slideX);
            else dots->X->push_back(die->BX + StepxX * i + StepyX * j - StepyX * K - slideX);
            if (i % 2 == 0) dots->Y->append(die->BY + StepxY * i + StepyY * j);
            else dots->Y->append(die->BY + StepxY * i + StepyY * j - StepyY * K);
        }
    }

    //центральный столбец
    for (int j = 0; j < die->numY; j++)
    {
        for (int i = -1; i < die->numX; i++)
        {
            if (i % 2 == 0) dots->X->push_back(die->BX + StepxX * i + StepyX * j);
            else dots->X->push_back(die->BX + StepxX * i + StepyX * j - StepyX * K);
            if (i % 2 == 0) dots->Y->append(die->BY + StepxY * i + StepyY * j);
            else dots->Y->append(die->BY + StepxY * i + StepyY * j - StepyY * K);
        }
    }
    walk->lastIndex = dots->X->length() - 1;

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

    walk->orientation = true;
    qInfo(logInfo()) << "Ориентация выполнена";
}


bool Worker::checkIndex(int i, struct DieParameters* die, struct Dots* dots)
{
    if (i < die->numX * die->numY)
    {
        return !die->rightColumn || (i >= dots->gap[0] && i <= dots->gap[1]) || (i <= dots->gap[2] && i >= dots->gap[3]);
    }
    else if (i < die->numX * die->numY * 2)
    {
        return !die->leftColumn || (i >= dots->gap[4] && i <= dots->gap[5]) || (i <= dots->gap[6] && i >= dots->gap[7]);
    }
    else if (i < die->numX * die->numY * 3)
    {
        return !die->centerColumn || (i >= dots->gap[8] && i <= dots->gap[9]) || (i <= dots->gap[10] && i >= dots->gap[11]);
    }
    return false;
}


void Worker::autoWalk(struct WalkSettings* walk, struct Delays* delays,
                      struct Currents* currs, struct Dots* dots)
{
    //if (!planar_status) return;
    //сдвиг индекса до начала рабочей зоны(не попадает в отступ)
    walk->currentIndex = walk->startIndex < gapIndex ? gapIndex : walk->startIndex;
    QFileInfo fileInfo(dir_cur);
    QString dir_dump = "C:/qt/dump/" + fileInfo.baseName() + "_start_index_"
            + QString::number(walk->currentIndex) + ".csv";
    emit sendProgressBarRangeSignal();
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
        while (walk->currentIndex <= walk->lastIndex && !stopped)
        {
            //если индекс попал на срез, то пропускаем
            if (checkIndex(walk->currentIndex, die, dots))
            {
                walk->currentIndex++;
                continue;
            }
            //проверка отзывчивости планара в конце ряда,
            //дабы не дырявить пластины активностью(вверх/вниз) на месте
            if (walk->currentIndex % 16 == 0 && !getCurrentCoords(walk, dots))
            //(currentIndex, planar_status)
            {
                //emit sendLogSignal(planarResponce);
                emit sendMessageBox("Ошибка", "Планар не отвечает на элементах :\n"
                                    + QString::number(walk->currentIndex-15)  + " - "
                                    + QString::number(walk->currentIndex));
                walk->stopped = true;
                walk->paused = false;
                break;
            }
            //проверка нажатия Паузы
            checkPause();
            //начинаем мерить элемент
            connector->planar->goToDot(walk, dots);
            connector->measureDot(walk, delays, currs, dots);
            //запись в файл дампа строки с измерениями токов
            res = QString::number(walk->currentIndex, 'D', 0) + ", "
                    + QString::number(ForwardCurrent, 'E', 4)
                    + ", " + QString::number(DarkCurrent10mV, 'E', 4) + ", " +
                    QString::number(DarkCurrent1V, 'E', 4) + ", "
                    + QString::number(LightCurrent - DarkCurrent10mV, 'E', 4) + '\n';
            output << res;
            //считаем количество элементов без прямого контакта, если больше 2 подряд выключаем
            if (currs->forward05V > currs->borderFC
                    || currs->light10mV < currs->borderLC)
            {
                lowFCcounter++;
            }
            else
            {
                lowFCcounter = 0;
            }
            //отправляем данные на таблицу, если ток в норме
            if (lowFCcounter <= 2 || badDie || !keithley_status)
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
            walk->currentIndex++;
        }

        qInfo(logInfo())<<"Закончен обход пластины " << fileInfo.baseName()
                       <<"  на элементе -> " << QString::number(currentIndex);

        walk->currentIndex = 0;
        file.close();
        connector->planar->down();
        timeSpent(start);
    }
    else
    {
        emit sendMessageBox("warning", "Файл открыт другой программой.\nЗапись не возможна.");
    }
    emit sendEndWalkSignal();

}


void Worker::checkPause(struct WalkSettings* walk)
{
    mutex->lock();
    if (walk->paused)
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


void Worker::openCsvFile(QString dir, struct Currents* curr)
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
            curr->currentIndex = arr[0].toInt();
            curr->forward05V = arr[1].toDouble();
            curr->dark10mV = arr[2].toDouble();
            curr->dark1V = arr[3].toDouble();
            curr->light10mV = arr[4].toDouble();

            //отправляем данные на таблицу(в модель)
            emit sendAddTableSignal();
            line = QString::fromUtf8(file.readLine());
        }
    }
    file.close();
    //source.remove();
}


void Worker::saveMeasure(struct WalkSettings* walk, struct Delays* delays,
                         struct Dots* dots, struct Currents* currs)
{
    if (checkIndex(walk->currentIndex, dots))
    {
        emit sendMessageBox("info", "Индекс за пределами измеряемой зоны."
                                    "\nПроверье отступы по краям\n и выполните ориентацию");
        return;
    }
    //currentIndex = startIndex;
    //connector->planar->goToDot(walk, dots);
    connector->measureDot(walk, delays, currs, dots);

    emit sendAddTableSignal(currs);
}

