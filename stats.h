#ifndef STATS_H
#define STATS_H

#include <QMainWindow>
#include <windows.h>
#include <vector>
using namespace std;

namespace Ui {
class Stats;
}

class Stats : public QMainWindow
{
   Q_OBJECT

public:
   explicit Stats(QWidget *parent = nullptr);
   ~Stats();
   void showCharts(QString);

private:
   Ui::Stats *ui;
   QString dir;
   int n = qPow(480, 0.5);
   double max_d = 9.9 * qPow(10, 37);
   double min_d = (max_d - 1) * (-1);
   QList<double> currMin{max_d, max_d, max_d, max_d};
   QList<double> currMax{min_d, min_d, min_d, min_d};
   vector<vector<double>> currValue;
   vector<vector<double>>  currFreq;
   QList<int> currFreqMax{0, 0, 0, 0};
   vector<vector<double>>  currRang;
   QList<double> step;

   void getData(QString);
   void getFreq();
   void drawCharts();
   QString getE(double);
   double maxDouble(double, double);
   double minDouble(double, double);

public slots:

};

#endif // STATS_H
