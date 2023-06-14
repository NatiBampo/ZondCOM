#include "stats.h"
#include "ui_stats.h"
#include <QtCharts>

Stats::Stats(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Stats)
{
    ui->setupUi(this);

    QLineSeries *series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    *series << QPointF(9, 6) << QPointF(11, 2);
    series->setName("Dark current 10mV");

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Probe title");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    this->setCentralWidget(chartView);
    this->resize(1400, 1400/16*9);
    this->show();


}

Stats::~Stats()
{
    delete ui;
}


void Stats::showCharts(QString dir)
{
    getData(dir);
    drawCharts();
}

void Stats::getData(QString dir)
{
    QFile source(dir);
    if (source.open(QIODevice::ReadOnly))
    {
        QTextStream output(&source);
        int i = 0;
        QStringList arr;
        while (!output.atEnd())
        {
            i++;
            arr = output.readLine().split(", ");
            currValue[0].append(arr[1].toDouble());
            if (arr[1].endsWith("9.9000E+37"))
            {
                currMax[0] = std::max(currMax[0], currValue[0][i]);
                currMin[0] = std::max(currMin[0], currValue[0][i]);

                currMax[1] = std::max(currMax[1], currValue[1][i]);
                currMin[1] = std::max(currMin[1], currValue[1][i]);

                currMax[2] = std::max(currMax[2], currValue[2][i]);
                currMin[2] = std::max(currMin[2], currValue[2][i]);

                currMax[3] = std::max(currMax[3], currValue[3][i]);
                currMin[3] = std::max(currMin[3], currValue[3][i]);
            }
        }

        for (int i = 0; i < 4; i++)
        {
            interval.append((currMax[i] - currMin[i]) / n);
        }
    }
}

void Stats::getFreq()
{
    for (int i = 0; i < currValue[0].length(); i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //needs rounding and being put as an index to currFreq
            (currValue[j][i] - currMin[j]) / interval[j];
        }
    }

}

void Stats::drawCharts()
{

}
