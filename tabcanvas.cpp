#include "tabcanvas.h"
#include <QPainter>


tabCanvas::tabCanvas(QWidget *parent):QWidget(parent)
{

}
tabCanvas::~tabCanvas(){}

void tabCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.begin(this);
    int s = 9;
    int g = 2;
    QSize rectSize(s, s);
    std::vector<QRect> rects;
    int x_0 = (s + g) * 16 * 3 - 130;
    int y_0 = 50;
    int c = 0;
    for (int k = 0; k < 3; k++)
    {
        if (k == 1) x_0 -= (s + g) * 17 * 2;
        if (k == 2) x_0 += (s + g) * 17;

        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 30; j++)
            {

                rects.push_back(QRect(QPoint(x_0 + i*(s+g) + c, y_0 + j*(s+g)), rectSize));
            }
        }
    }
    for (int i = 0; i < rects.size(); i++)
    {
        painter.fillRect(rects[i], Qt::white);
    }
    //painter.fillRect(0, 0, 128, 128, Qt::green);//0, 0, 128, 128, Qt::green
    //painter.fillRect(QRect(QPoint(0,0), rectSize), Qt::green);
    painter.beginNativePainting();
    painter.end();
}
