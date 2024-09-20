#include "planar.h"

Planar::Planar(QSerialPort *port, QString* com_name)
{
    serial = port;
    name = com_name;
}


bool Planar::parsePort(QSerialPort *port, QString* com_name)
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
    if (serialPortA5->isOpen() || walk->planarStatus)
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
        emit sendMessageBox("warning",
                            "Порт планара закрыт.\n Отправка комманды не работает");
    }
}


void Planar::up()
{

}
void Planar::down()
{

}
