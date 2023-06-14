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
    double max_d = 9.9 * qPow(10, 37);
    double min_d = (max_d - 1) * (-1);
    QList<double> currMin = {max_d, max_d, max_d, max_d};
    QList<double> currMax = {min_d, min_d, min_d, min_d};
    QList<QList<double>> currValue = {{}, {}, {}, {}};
    QList<QList<double>> currFreq = {{}, {}, {}, {}};
    QList<QList<double>> currRang = {{}, {}, {}, {}};
    QList<double> interval;


public slots:
    void showCharts(QString);
    void getData(QString);
    void getFreq();
    void drawCharts();
};

#endif // STATS_H
