#include "planar.h"

Planar::Planar(struct Peripherals* periph)
{
    m_serial = new ComPort( QSerialPort::Baud115200);
    qDebug() << "Planar";
    periph->planar = m_serial->getPort();
    connect(this, &Planar::sendPackageSignal, m_serial, &ComPort::sendPackage);
    connect(this, &Planar::sendPackageReadSignal, m_serial, &ComPort::sendPackageRead);
    qDebug() << "Planar connected sending";
}


Planar::~Planar()
{
    delete m_serial;
}


bool Planar::openPort(QSerialPort *port, QString* comPort,
                 QSerialPort::BaudRate baudRate)
{
    return m_serial->openPort(port, comPort,baudRate);
}

bool Planar::openPort(QString* comPort)
{
    return m_serial->openPort(comPort);
}

void Planar::setPort(QSerialPort* port)
{
    m_serial->setPort(port);
}


void Planar::closePort()
{
    m_serial->closePort();
}

bool Planar::parsePort(QString com_name, struct Peripherals* periph)
{
    //serialPortA5->flush();
    if (working) return true;


    if (!m_serial->isOpen()) openPort(&com_name);
    sendPackageReadSignal("State\r\n", ANSWER_DELAY);
    QRegularExpression re(R"(-?\d+ -?\d+ -?\d+ -?\d+\r\n|BSY|OK|ERC|NBP|EDG)");
    QRegularExpressionMatch match = re.match(m_serial->lastAnswer);
    if (m_serial->lastAnswer != "" && match.hasMatch())
    {
        //emit sendLogSignal(match.captured(0).toUtf8());
        periph->planar_com = &com_name;
        working = true;
        //m_serial = periph->planar;
        return true;
    }
    else if (m_serial->lastAnswer == "")
    {
        QThread::msleep(300);
        sendPackageReadSignal("State\r\n", ANSWER_DELAY);
        match = re.match(m_serial->lastAnswer);
        if (m_serial->lastAnswer != "" && match.hasMatch())
        {
            working = true;
            return true;
        }

    }
    return false;

}

void Planar::endLine(struct WalkSettings* walk)
{
    sendPackageReadSignal("\r\n", ANSWER_DELAY);
    if (m_serial->lastAnswer == "")
    {
        errorCount++;
        emit sendLogSignal((m_serial->lastAnswer + "<-ответ на /r/n").toUtf8());
    }
    else
    {
        errorCount = 0;
    }
    if (errorCount > 5)
    {
        walk->stopped = true;

        emit sendMessageBoxSignal("warning", "Планар не отвечает");
    }
}

void Planar::tableController(const QByteArray message, struct WalkSettings* walk)
{
    if (m_serial->isOpen() && walk->planar_status)
    {
        sendPackageReadSignal(message, ANSWER_DELAY );//1000
        qInfo(logInfo())<< m_serial->lastAnswer << "<- в ответ на ->" + QString(message);//\r\n

        if (m_serial->lastAnswer == "")
        {
            endLine(walk);
        }
        else if (m_serial->lastAnswer.contains(QRegularExpression(R"(BSY)")))//< BSY\r\n
        {
            walk->stopped = true;
            emit sendMessageBoxSignal("warning", "BSY. Планар не отвечает.\n Проверьте передачу управления.");
            qWarning(logWarning()) << "BSY – ЗУ находится в режиме ручной настройки, обхода или исполняет команду";
        }
        else if (m_serial->lastAnswer.contains(QRegularExpression(R"(FLT)")))
        {
            walk->stopped = true;
            emit sendMessageBoxSignal("warning", "FLT – авария ЗУ");
            qCritical(logCritical()) << "FLT – авария ЗУ";
        }
        else if (m_serial->lastAnswer.contains(QRegularExpression(R"(ERC)")))
        {
            emit sendMessageBoxSignal("warning", "ERC – ошибка команды или формата");
            qWarning(logWarning()) << "ERC – ошибка команды или формата";

            endLine(walk);
        }
    }
    else
    {
        walk->stopped = true;
        qWarning(logWarning()) << "Порт планар закрыт. Отправка комманды не работает.\r";

        emit sendMessageBoxSignal("warning",
                            "Порт планара закрыт.\n Отправка комманды не работает");
    }
}


void Planar::up(struct WalkSettings* walk)
{
    if (walk->planar_status)
        sendPackageSignal("Table UP\r\n", NO_ANSWER_DELAY);
}


void Planar::down(struct WalkSettings* walk)
{
        if (walk->planar_status)
            sendPackageSignal("Table DN\r\n", NO_ANSWER_DELAY);
}


void Planar::currentCoords(int index, struct WalkSettings* walk, struct Dots* dots)
{
    int x = 0;
    int y = 0;
    tableController("State\r\n", walk);
    QRegularExpression re(R"(< -?\d+ -?\d+ -?\d+ -?\d+\r\n)");

    //if (responce.contains(QRegularExpression(R"(< -?\d+ -?\d+ -?\d+ -?\d+\r\n)")))
    for (int i = 0; i < 5; i++)
    {
        //emit sendLogSignal(planarResponce);

        QRegularExpressionMatch match = re.match(m_serial->lastAnswer);
        if (match.hasMatch())
        {
            QString line = match.captured(0);
            x = line.split(" ")[2].toInt();
            y = line.split(" ")[3].toInt();

            if (index == -1)
            {
                emit sendCurrentCoordsSignal(x, y, -1);
            }
            if (index == -2)
            {
                emit sendCurrentCoordsSignal(x, y, -2);
            }
            if (index > 0)
            {
                qDebug(logDebug()) << "Парсинг x, y : " << x << ", " << y
                                   << "  Dots: i, x , y = "
                                   << walk->currentIndex << ", "
                                   << dots->X->at(walk->currentIndex) << ", "
                                   << dots->Y->at(walk->currentIndex);
                if ( x==0 && y == 0)//&& (index < walk->currentIndex
                {
                    QThread::msleep(1000);
                    endLine(walk);
                    continue;
                }

                bool cond1 = x == (int) dots->X->at(walk->currentIndex);
                bool cond2 = y == (int) dots->Y->at(walk->currentIndex);

                //stop if current coords differ from calculated for index
                walk->stopped = !(cond1 && cond2);
            }
            //return true;
        }
        else //if (responce == "< OK\r\n")
        {
            endLine(walk);
        }
    }
    //return false;
}


void Planar::goToDot(struct WalkSettings* walk, struct Dots* dots)
{
    //опустить стол
    down(walk);
    //перевод координат в массив байтов для передачи станку
    QByteArray x = QByteArray::number((int)dots->X->at(walk->currentIndex));
    QByteArray y = QByteArray::number((int)dots->Y->at(walk->currentIndex));
    tableController("Set " + x + " " + y + '\r' + '\n', walk);
}
