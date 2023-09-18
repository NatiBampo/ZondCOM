#include "stats.h"
#include "ui_stats.h"
#include <QtCharts>

using namespace std;


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
    //getFreq();
    //drawCharts();

}

void Stats::getData(QString dir)
{

    int n = qPow(480, 0.5);
//    double max_d = 9.9 * qPow(10, 37);
//    double min_d = (max_d - 1) * (-1);
    double max_d = qPow(10, -1);
    double min_d = qPow(10, -16);
    double max_d1 = (-1) * qPow(10, -16);
    double min_d1 = (-1) * qPow(10, -1);
    vector<double> currMin{ max_d1, max_d, max_d, max_d };
    vector<double> currMax{ min_d1, min_d, min_d, min_d };
    vector<vector<double>> currValue;
    vector<vector<int>> currFreq;
    vector<vector<double>>  currRang;
    vector<double> step;


    for (int i = 0; i < 4; i++)
    {
        vector<double> v1, v2;
        vector<int> v3;
        currValue.push_back(v1);
        currRang.push_back(v2);
        currFreq.push_back(v3);

    }


    QFile source(dir);
    if (source.open(QIODevice::ReadWrite))
    {
        //QTextStream output(&source);
        //int i = 0;
        QString line = source.readLine();
        QStringList arr;
        //while (!output.atEnd())
        for (int i = 0; !line.isNull(); ++i)
        {
            arr = line.split(", ");
            for (int j = 0; j < 4; j++)
            {
                currValue[j].push_back(arr[j+1].toDouble());
                if (j==0)
                {
                    if (currValue[j][i] > min_d1 && currValue[j][i] < max_d1)
                    {
                        currMax[j] = maxDouble(currMax[j], currValue[j][i]);
                        currMin[j] = minDouble(currMin[j], currValue[j][i]);
                    }
                }
                else
                {
                    if (currValue[j][i] > min_d && currValue[j][i] < max_d)
                    {
                        currMax[j] = maxDouble(currMax[j], currValue[j][i]);
                        currMin[j] = minDouble(currMin[j], currValue[j][i]);
                    }
                }
            }
            line = source.readLine();
        }

        for (int i = 0; i < 4; i++)
        {
            sort(currValue[i].begin(), currValue[i].end());
            step.push_back((currMax[i] - currMin[i]) / n);
        }


        //compute ranges for each of currents
        //float o = (currMax[0] - currMin[0]) / n;

        //initiate ranges with zero
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < n; j++)
            {
                currFreq[i].push_back(0);
                currRang[i].push_back(currMin[i] + j * step[0]);
            }
        }

    }
    getFreq(currValue, currFreq, currRang, currMin, currMax, step);
}

void Stats::getFreq(const vector<vector<double>>  &currValue, vector<vector<int>> &currFreq,
                    const vector<vector<double>> &currRang, const vector<double> &currMin,
                    const vector<double> &currMax, const vector<double> &step)
{
    vector<int> currFreqMax =  {0, 0, 0, 0};
    for (int j = 0; j < (int) currValue.size(); j++)
    {
        int n = (int) currValue[j].size();
        for (int i = 0; i < n; i++)
        {
            //needs rounding and being put as an index to currFreq
    //            double p = currValue[j][i];
    //            double t = currMin[j];
    //            double u = step[j];
            //if (currValue[j][i] < currMin[j])  currFreq[i];//|| currValue[i][j] > currMax[j]) continue;

            //calc proper range
            int idx = (currValue[j][i] - currMin[j]) / step[j] - 1;// - 1;
            //raising frequency

            if (idx < 0) currFreq[j][0] += 1;
            else if (idx >= n) currFreq[j][n-1] += 1;
            else
            {
                currFreq[j][idx] += 1;
                currFreqMax[j] = maxDouble(currFreqMax[j], currFreq[j][idx]);
            }
        }
    }

    drawCharts(currRang, currFreq, currFreqMax, currMin, step);

}


void Stats::borderRange()
{

}


void Stats::drawCharts(const vector<vector<double>> &currRang, const vector<vector<int>> &currFreq,
                       const vector<int> &currFreqMax, const vector<double> &currMin,
                       const vector<double> &step)
{
    QLineSeries *seriesFC = new QLineSeries();
    QLineSeries *seriesDC10mV = new QLineSeries();
    QLineSeries *seriesDC1V = new QLineSeries();
    QLineSeries *seriesLC = new QLineSeries();
    int n = currFreq[0].size();
    for (int i = 0; i < n; i ++)
    {
        /*
        //bar names
        barlist.append(new QBarSet(QString::number(currRang[0][i], 'E', 2)));

        *barlist[i] << currFreq[3][i];
        series->append(barlist[i]);*/

        seriesFC->append(i*step[0] + currMin[0], currFreq[0][i]);
        seriesDC10mV->append(i*step[1] + currMin[1], currFreq[1][i]);
        seriesDC1V->append(i*step[2] + currMin[2], currFreq[2][i]);
        seriesLC->append(i*step[3] + currMin[3], currFreq[3][i]);
    }

    seriesFC->setName("Forward current 600mV");
    seriesDC10mV->setName("Dark current 10mV");
    seriesDC10mV->setName("Dark current 1V");
    seriesLC->setName("Light current 10mV");

    QChart *chartDC = new QChart();
    chartDC->legend()->hide();
    chartDC->addSeries(seriesDC10mV);
    chartDC->addSeries(seriesDC1V);
    chartDC->createDefaultAxes();

    QValueAxis *axisY = new QValueAxis;
    //axisX->setRange(10, 20.5);
    axisY->setTickCount(10);
    axisY->setLabelFormat("%.0f");
    //chartView->chart()->setAxisX(axisX, series);
    chartDC->setAxisY(axisY, seriesDC10mV);
    chartDC->setTitle("Dark Currents");

    QChart *chartFC = new QChart();
    chartFC->legend()->hide();
    chartFC->addSeries(seriesFC);
    chartFC->createDefaultAxes();
    chartFC->setTitle("Forward Current");

    QChart *chartLC = new QChart();
    chartLC->legend()->hide();
    chartLC->addSeries(seriesLC);
    chartLC->createDefaultAxes();
    chartLC->setTitle("Light Current");

    /*QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    this->setCentralWidget(chartView);
    this->resize(1400, 1400/16*9);
    this->show();*/


    //----


    /*QBarSeries *series = new QBarSeries();
    QList<QBarSet*> barlist;
    int n = currFreq[0].size();
    for (int i = 0; i < n; i ++)
    {
        //bar names
        barlist.append(new QBarSet(QString::number(currRang[0][i], 'E', 2)));

        *barlist[i] << currFreq[3][i];
        series->append(barlist[i]);
    }*/

    /*
        QBarSet *set0 = new QBarSet("Jane");
        QBarSet *set1 = new QBarSet("John");
        QBarSet *set2 = new QBarSet("Axel");
        QBarSet *set3 = new QBarSet("Mary");
        QBarSet *set4 = new QBarSet("Samantha");

        *set0 << 1;// << 2 << 3 << 4 << 5 << 6;
        *set1 << 5;// << 0 << 0 << 4 << 0 << 7;
        *set2 << 3;// << 5 << 8 << 13 << 8 << 5;
        *set3 << 5;// << 6 << 7 << 3 << 4 << 5;
        *set4 << 9;// << 7 << 5 << 3 << 1 << 2;

        QBarSeries *series = new QBarSeries();
        series->push_back(set0);
        series->push_back(set1);
        series->push_back(set2);
        series->push_back(set3);
        series->push_back(set4);
    */
    /*
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->push_back(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    */

    /*
    QString barTitle = "Forward current histogram";
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(barTitle);
    chart->setAnimationOptions(QChart::SeriesAnimations);


    QValueAxis *axisY = new QValueAxis();
    //axisY->setRange(0, currFreqMax[0]);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    */


    QChartView *chartViewDC = new QChartView(chartDC);
    QChartView *chartViewFC = new QChartView(chartFC);
    QChartView *chartViewLC = new QChartView(chartLC);

    chartViewFC->setRenderHint(QPainter::Antialiasing);
    chartViewLC->setRenderHint(QPainter::Antialiasing);
    chartViewDC->setRenderHint(QPainter::Antialiasing);


    QFrame* centralFrame = new QFrame();

    QHBoxLayout* myLayoutHorizontal = new QHBoxLayout;
    QVBoxLayout* myLayoutVertical = new QVBoxLayout;
    myLayoutHorizontal->addWidget(chartViewFC);
    myLayoutHorizontal->addWidget(chartViewLC);
    myLayoutVertical->addWidget(chartViewDC);
    myLayoutVertical->addLayout(myLayoutHorizontal);

    centralFrame->setLayout(myLayoutVertical);


    this->setCentralWidget(centralFrame);
    this->resize(1280, 950);
    this->show();
}


QString Stats::getE(double number)
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


double Stats::maxDouble(double x1, double x2)
{
    if (x1 > x2) return x1;
    return x2;
}


double Stats::minDouble(double x1, double x2)
{
    if (x1 < x2) return x1;
    return x2;
}
