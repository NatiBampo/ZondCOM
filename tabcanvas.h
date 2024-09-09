#ifndef TABCANVAS_H
#define TABCANVAS_H

#include <QObject>
#include <QWidget>
//#include <vector>
//using std::vector;

class tabCanvas: public QWidget {
    Q_OBJECT
public:
    tabCanvas(QWidget* parent=0);
    ~tabCanvas();
protected:
   void paintEvent(QPaintEvent*);
   int numx, numy;
};


#endif // TABCANVAS_H
