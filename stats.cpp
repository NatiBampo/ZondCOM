#include "stats.h"
#include "ui_stats.h"
#include <QtCharts>

Stats::Stats(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Stats)
{
    ui->setupUi(this);



}

Stats::~Stats()
{
    delete ui;
}


void Stats::showCharts(QString dir)
{
    getData(dir);
    getFreq();
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

            arr = output.readLine().split(", ");
            currValue[0].append(arr[1].toDouble());
            currValue[1].append(arr[2].toDouble());
            currValue[2].append(arr[3].toDouble());
            currValue[3].append(arr[4].toDouble());

//            if (arr[1].endsWith("9.9000E+37"))
//
            for (int k = 0; k < 4; k++)
            {
                if ((k < 1 && currValue[k][i] > -1 && currValue[k][i] < 0) || (k > 0 && currValue[k][i] > 0 && currValue[k][i] < 1))
                {
                    currMax[k] = std::max(currMax[k], currValue[k][i]);
                    currMin[k] = std::min(currMin[k], currValue[k][i]);
                }
            }
//            }
            i++;
        }


        for (int i = 0; i < 4; i++)
        {
            //compute ranges for each of currents
            float o = (currMax[i] - currMin[i]) / n;
            step.append(o);
            //initiate ranges with zero
            for (int t = 0; t < n; t++)
            {
                currFreq[i].append(0);
                currRang[i].append(currMin[i] + t * step[i]);
            }
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
//            double p = currValue[j][i];
//            double t = currMin[j];
//            double u = step[j];
            //if (currValue[j][i] < currMin[j])  currFreq[i];//|| currValue[i][j] > currMax[j]) continue;

            //calc proper range
            int k = (currValue[j][i] - currMin[j]) / step[j] - 1;

            //raising frequancy
            if (k < 0) currFreq[j][0] += 1;
            else if (k >= n) currFreq[j][n-1] += 1;
            else
            {
                currFreq[j][k] += 1;
                currFreqMax[j] = std::max(currFreqMax[j], currFreq[j][k]);
            }
        }
    }

}

void Stats::drawCharts()
{
    /*QLineSeries *series = new QLineSeries();
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
    this->show();*/


    QBarSeries *series = new QBarSeries();
    QList<QBarSet*> barlist;
    for (int i = 0; i < n; i ++)
    {
        //bar names
        barlist.append(new QBarSet(QString::number(currRang[0][i], 'E', 2)));

        *barlist[i] << currFreq[0][i];
        series->append(barlist[i]);
    }
//    QBarSet *set0 = new QBarSet("Jane");
//    QBarSet *set1 = new QBarSet("John");
//    QBarSet *set2 = new QBarSet("Axel");
//    QBarSet *set3 = new QBarSet("Mary");
//    QBarSet *set4 = new QBarSet("Samantha");

//    *set0 << 1;// << 2 << 3 << 4 << 5 << 6;
//    *set1 << 5;// << 0 << 0 << 4 << 0 << 7;
//    *set2 << 3;// << 5 << 8 << 13 << 8 << 5;
//    *set3 << 5;// << 6 << 7 << 3 << 4 << 5;
//    *set4 << 9;// << 7 << 5 << 3 << 1 << 2;

//    QBarSeries *series = new QBarSeries();
//    series->append(set0);
//    series->append(set1);
//    series->append(set2);
//    series->append(set3);
//    series->append(set4);

    QString barTitle = "Simple barchart example";
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(barTitle);
    chart->setAnimationOptions(QChart::SeriesAnimations);

//    QStringList categories;
//    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
//    QBarCategoryAxis *axisX = new QBarCategoryAxis();
//    axisX->append(categories);
//    chart->addAxis(axisX, Qt::AlignBottom);
//    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, currFreqMax[0]);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    this->setCentralWidget(chartView);
    this->resize(1400, 1400/16*9);
    this->show();
}


QString getE(double number)
{
    int c = 0;
    while (number < 1)
    {
        c++;
        number *= 10;
    }
    //double
    return QString::number(number/ qPow(10, c));
}
