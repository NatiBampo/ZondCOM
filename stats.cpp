#include "stats.h"
#include "ui_stats.h"
#include <QtCharts>
#include <QDebug>

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

    int n = qPow(480, 0.5) * 4;
    vector<double> min_d{ -qPow(10,-2), qPow(10,-14), qPow(10,-14), qPow(10, -10) };
    vector<double> max_d{ -qPow(10,-6), qPow(10,-10), qPow(10, -8), qPow(10, -5) };

    vector<double> currMin{ -qPow(10,-6), qPow(10, -14), qPow(10, -14), qPow(10, -10) };
    vector<double> currMax{ -qPow(10,-2), qPow(10,-10), qPow(10, -8), qPow(10, -5) };
    vector<vector<double>> currValue;
    vector<vector<int>> currFreq;
    vector<vector<double>>  currRang;
    vector<double> step;
    vector<vector<int>> percent;

    for (int i = 0; i < 4; i++)
    {
        vector<double> v1, v2;
        vector<int> v3, v4;
        currValue.push_back(v1);
        currRang.push_back(v2);
        currFreq.push_back(v3);
        percent.push_back(v4);
    }

    qDebug() << "waz here";
    QFile source(dir);
    if (source.open(QIODevice::ReadWrite))
    {
        //QTextStream output(&source);
        //int i = 0;
        QString line = source.readLine();
        QStringList arr;
        //while (!output.atEnd())
        int i = 0;
        for (; !line.isNull(); ++i)
        {
            arr = line.split(", ");
            for (int j = 0; j < 4; j++)
            {
                currValue[j].push_back(arr[j+1].toDouble());
                /*if (j==0)
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
                }*/
            }
            line = source.readLine();
        }

        for (int k = 0; k < 4; k++)
        {
            sort(currValue[k].begin(), currValue[k].end());
            /*int p = (k==1 || k==2) ? 5 : 1;
            //увеличиваем процент брака пока не попадет в диапазон
            int idx = (int) (i * p /100);
            double tmp =  currValue[k][idx];
            qDebug()<< inRange(max_d, min_d, tmp, 0);
            while(!inRange(max_d, min_d, currValue[k][(int) (i * p /100)], k))
            {
                p++;
            }
            currMin[k] = currValue[k][(int) (i * p /100)];
            percent[k].push_back(p);

            p = (k==2 || k==1) ? 5 : 1;
            while(!inRange(max_d, min_d, currValue[k][(int) (i  - i * p / 100)], k))
            {
                p++;
            }
            currMax[k] = currValue[k][(int) (i - i * p / 100)];
            percent[k].push_back(p);
            */
            qDebug() << "k " << k;
            clear3Percentyles(currValue[k]);

            step.push_back((currMax[k] - currMin[k]) / n);
        }

        //compute ranges for each of currents
        //float o = (currMax[0] - currMin[0]) / n;

        //initiate ranges with zero
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < n; j++)
            {
                currFreq[i].push_back(0);
                currRang[i].push_back(currMin[i] + j * step[i]);
            }
        }

    }
    getFreq(currValue, currFreq, currRang, currMin, currMax, step);
}


bool Stats::inRange(vector<double> &max_d, vector<double> &min_d, double num, int i)
{
    return (num > min_d[i] && num < max_d[i]);
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
            double tmp = currValue[j][i] - currMin[j];
            int idx = abs(currValue[j][i] - currMin[j]) / step[j];// - 1;
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

//takes sorted vector and gets rid off 3 sigmas() given 25-75 percentile is one sigma
//may be should be done substitute median value
void Stats::clear3Percentyles(std::vector<double> &v)
{
    int sizeV = v.size();
    //3sigma border
    double p25 = v.at(sizeV*0.25) * 3;
    double p75 = v.at(sizeV*0.75) * 3;

    double sigma = p75 - p25;
    double l = p25 - 3 * sigma;
    double r = p75 + 3 * sigma;
    double med = v.at(sizeV * 0.5);


    int counter = 0;
    for (auto it = v.begin(); it != v.end();)
    {
        if (*it > r || *it < l)
        {
            it = v.erase(it);
            ++counter;
        }
        else
        {
            ++it;
        }
    }
    qDebug() << "sizeV " << sizeV << " | sigma " << sigma << " | l " << l
             << " | r " << r << " | counter " << counter;

}

void Stats::normalize(std::vector<double> &v)
{}

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
    seriesDC1V->setName("Dark current 1V");
    seriesLC->setName("Light current 10mV");

    QChart *chartDC10mV = new QChart();
    chartDC10mV->legend()->hide();
    chartDC10mV->addSeries(seriesDC10mV);
    chartDC10mV->createDefaultAxes();

    QChart *chartDC1V = new QChart();
    chartDC1V->legend()->hide();
    chartDC1V->addSeries(seriesDC1V);
    chartDC1V->createDefaultAxes();

    QValueAxis *axisY = new QValueAxis;
    //axisX->setRange(10, 20.5);
    axisY->setTickCount(10);
    axisY->setLabelFormat("%.0f");
    //chartView->chart()->setAxisX(axisX, series);
    chartDC10mV->setAxisY(axisY, seriesDC10mV);
    chartDC10mV->setTitle("Dark Current 10mV");

    QValueAxis *axisY1 = new QValueAxis;
    //axisX->setRange(10, 20.5);
    axisY1->setTickCount(10);
    axisY1->setLabelFormat("%.0f");
    //chartView->chart()->setAxisX(axisX, series);
    chartDC1V->setAxisY(axisY1, seriesDC1V);
    chartDC1V->setTitle("Dark Current 1V");

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


    QChartView *chartViewDC10mV = new QChartView(chartDC10mV);
    QChartView *chartViewDC1V = new QChartView(chartDC1V);
    QChartView *chartViewFC = new QChartView(chartFC);
    QChartView *chartViewLC = new QChartView(chartLC);

    chartViewFC->setRenderHint(QPainter::Antialiasing);
    chartViewLC->setRenderHint(QPainter::Antialiasing);
    chartViewDC10mV->setRenderHint(QPainter::Antialiasing);
    chartViewDC1V->setRenderHint(QPainter::Antialiasing);

    QFrame* centralFrame = new QFrame();

    QHBoxLayout* myLayoutHorizontal1 = new QHBoxLayout;
    QHBoxLayout* myLayoutHorizontal2 = new QHBoxLayout;
    QVBoxLayout* myLayoutVertical = new QVBoxLayout;

    myLayoutHorizontal1->addWidget(chartViewFC);
    myLayoutHorizontal1->addWidget(chartViewLC);
    myLayoutVertical->addLayout(myLayoutHorizontal1);

    myLayoutHorizontal2->addWidget(chartViewDC10mV);
    myLayoutHorizontal2->addWidget(chartViewDC1V);
    myLayoutVertical->addLayout(myLayoutHorizontal2);

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
//
