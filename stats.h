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
   /*
    vector<double> currMin{max_d, max_d, max_d, max_d};
    vector<double> currMax{min_d, min_d, min_d, min_d};
    vector<double> currValueFC, currValueDC10, currValueDC1, currValuePh;
    vector<int> currFreqFC, currFreqDC10, currFreqDC1, currFreqPh;
    vector<int> currFreqMax;
    vector<double>  currRangFC, currRangDC10, currRangDC1, currRangPh;
    vector<double> step;
   */

   void getData(QString);
   void getFreq(const vector<vector<double>>  &, vector<vector<int>>  &,
                const vector<vector<double>>  &, const vector<double>  &,
                const vector<double>  &, const vector<double> &);
   void drawCharts(const vector<vector<double>> &, const vector<vector<int>> &,
                   const vector<int> &, const vector<double> &,
                   const vector<double> &);
   QString getE(double);
   double maxDouble(double, double);
   double minDouble(double, double);
   void borderRange();

public slots:

};

#endif // STATS_H
