#include "planar.h"

Planar::Planar(QSerialPort* port) : ComPort(port)
{
    m_rate = QSerialPort::Baud115200;
}


Planar::~Planar()
{}


bool Planar::parsePort(QString* com_name, struct Peripherals* periph)
{
    //serialPortA5->flush();
    if (working) return true;
    tableController("State\r\n", periph);
    QString responce = QString(planarResponce);
    QRegularExpression re(R"(-?\d+ -?\d+ -?\d+ -?\d+\r\n|BSY|OK|ERC|NBP|EDG)");
    QRegularExpressionMatch match = re.match(responce);
    if (responce != "" && match.hasMatch())
    {
        emit sendLogSignal(match.captured(0).toUtf8());
        periph->planar_com = com_name;
        working = true;
        serial = periph->planar;
        return true;
    }
    else if (responce == "")
    {
        QThread::msleep(300);
        tableController("State\r\n", periph);
        responce = QString(planarResponce);
        match = re.match(responce);
        if (responce != "" && match.hasMatch())
        {
            working = true;
            return true;
        }

    }
    return false;

}

void Planar::endLinePlanar()
{
    serial->write("\r\n");
    serial->flush();
    serial->waitForBytesWritten(400);
    lastAnswer = "";
    planarResponce = "";
    if (serial->waitForReadyRead(400))
        lastAnswer.append(serial->readAll());
    if (lastAnswer==planarResponce)
    {
        errorCount++;
        //emit sendLogSignal(lastAnswer + "<-ответ на /r/n||прошлый->" + planarResponce);
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

void Planar::tableController(const QByteArray message, struct WalkSettings* walk)
{
    if (serial->isOpen() || walk->planarStatus)
    {
        sendPackageRead( message, ANSWER_DELAY );//1000
        qInfo(logInfo())<< lastAnswer << "<- в ответ на ->" + QString(message);//\r\n

        if (lastAnswer == "")
        {
            endLinePlanar();
        }
        else if (lastAnswer.contains(QRegularExpression(R"(BSY)")))//< BSY\r\n
        {
            stopped = true;
            emit sendMessageBox("warning", "BSY. Планар не отвечает.\n Проверьте передачу управления.");
            qWarning(logWarning()) << "BSY – ЗУ находится в режиме ручной настройки, обхода или исполняет команду";
        }
        else if (lastAnswer.contains(QRegularExpression(R"(FLT)")))
        {
            stopped = true;
            emit sendMessageBox("warning", "FLT – авария ЗУ");
            qCritical(logCritical()) << "FLT – авария ЗУ";
        }
        else if (lastAnswer.contains(QRegularExpression(R"(ERC)")))
        {
            emit sendMessageBox("warning", "ERC – ошибка команды или формата");
            qWarning(logWarning()) << "ERC – ошибка команды или формата";

            endLinePlanar();
        }
    }
    else
    {
        walk->stopped = true;
        emit sendMessageBox("warning",
                            "Порт планара закрыт.\n Отправка комманды не работает");
    }
}


void Planar::up(struct WalkSettings* walk)
{
    tableController("Table UP\r\n", walk);
}
void Planar::down(struct WalkSettings* walk)
{
    tableController("Table DN\r\n", walk);
}


void Planar::currentCoords(struct WalkSettings* walk, struct Dots* dots)
{
    int x = 0;
    int y = 0;
    tableController("State\r\n", walk);
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

            if (walk->currentIndex == -1)
            {
                emit sendCurrentCoordsSignal(x, y);
            }
            if (walk->currentIndex == -2)
            {
                emit sendBCoordsSignal(x, y);
            }
            if (index > 0)
            {
                qDebug(logDebug()) << "Парсинг x, y : " << x << ", " << y
                                   << "  Dots: i, x , y = "
                                   << walk->currentIndex << ", "
                                   << dots->X->at(walk->currentIndex) << ", "
                                   << dots->Y->at(walk->currentIndex);
                if (walk->currentIndex < walk->currentIndex && (x==0 && y == 0))
                {
                    QThread::msleep(1000);
                    endLinePlanar();
                    continue;
                }

                bool cond1 = x == (int) dots->X->at(walk->currentIndex);
                bool cond2 = y == (int) dots->Y->at(walk->currentIndex);
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


void Planar::goToDot(struct WalkSettings* walk, struct Dots* dots)
{
    //опустить стол
    down(walk);
    //перевод координат в массив байтов для передачи станку
    QByteArray x = QByteArray::number((int)dots->X->at(walk->currentIndex);
    QByteArray y = QByteArray::number((int)dots->Y->at(walk->currentIndex);
    tableController("Set " + x + " " + y + '\r' + '\n', walk);
}
