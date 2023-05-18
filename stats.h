#ifndef STATS_H
#define STATS_H

#include <QMainWindow>

namespace Ui {
class Stats;
}

class Stats : public QMainWindow
{
    Q_OBJECT

public:
    explicit Stats(QWidget *parent = nullptr);
    ~Stats();

private:
    Ui::Stats *ui;
    QString dir;
    int n = qPow(480, 0.5);
    double max_double = 9.9 * qPow(10, 37); //__DBL_MAX__; //std::numeric_limits::max();
    double min_double = max_double * (-1);
    double          curFCmin,   curDC10min,     curDC1min,     curPHmin = max_double;
    double          curFCmax,   curDC10max,     curDC1max,     curPHmax = min_double;

    QList<double>   curFC,      curDC10,        curDC1,         curPH;
    QList<double>   curFCfreq,  curDC10freq,    curDC1freq,     curPHfreq;
    QList<double>   rangesFC,   rangesDC10,     rangesDC1,      rangesPH;


public slots:
    void showCharts(QString dir);
    void getData();
    void getFrequancies();
    void drawCharts();
};

#endif // STATS_H
