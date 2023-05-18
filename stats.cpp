#include "stats.h"
#include "ui_stats.h"
#include <QtCharts>

//using namespace QtCharts;

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
    series->setName("Dark current 10mv");// + QString::number(nameIndex)

    QLineSeries *series2 = new QLineSeries();
    series2->append(0, 1);
    series2->append(2, 3);
    series2->append(3, 6);
    series2->append(7, 2);
    *series2 << QPointF(9, 2) << QPointF(11, 0);
    series2->setName("Dark current 1v");

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->createDefaultAxes();
    chart->setTitle("Some title");
    //chart->axes(Qt::Horizontal).first()->setRange(0, 15);
    //chart->axes(Qt::Vertical).first()->setRange(0, 20);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //QMainWindow window;
    this->setCentralWidget(chartView);
    this->resize(1400, 1400/16*9);
    this->show();
}

Stats::~Stats()
{
    delete ui;
}

void Stats::showCharts(QString dir_c)
{
    dir = dir_c;
    getData();
    drawCharts();
}

void Stats::getData()
{
    QFile source (dir);
    if (source.open(QIODevice::ReadWrite)) {
        QTextStream output(&source);
        int i = 0;
        QStringList arr;
        double tmpFC;
        while (!output.atEnd()) {
            i++;
            //распарсить строку на 4 тока для отображения на графике
            arr = output.readLine().split(", ");

            curFC.append(arr[1].toDouble());
            if (arr[1].endsWith("9.9000E+37"))
            {
                curFCmax = std::max(curFCmax, curFC[i]);
                curFCmin = std::min(curFCmin, curFC[i]);
            }
            curFC.append(arr[1].toDouble());

        }
        //количество интервалов
        n = qPow(i, 0.5);


    }
    source.close();
}


void Stats::getFrequancies()
{
    for (int i = 0; i < curFC.length(); i++){
        curFC[i];
    }
}


void Stats::drawCharts()
{
    QLineSeries *seriesDC06 = new QLineSeries();
    QLineSeries *seriesDC10 = new QLineSeries();
    QLineSeries *seriesDC1V = new QLineSeries();
    QLineSeries *seriesLight = new QLineSeries();
}


