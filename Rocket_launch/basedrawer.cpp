#include "basedrawer.h"
#include "QGraphicsScene"
#include "cmath"
BaseDrawer::BaseDrawer()
{

}

void draw_param_circle(double xc, double yc, double R, BaseDrawer &scene)
{
    double x, y;
    for (double t = 0; t <= M_PI_2; t += 1 / R)
    {
        x = round(R * cos(t));
        y = round(R * sin(t));
        scene.drawPoint(xc + x, yc - y);
        scene.drawPoint(xc - x, yc - y);
        scene.drawPoint(xc - x, yc + y);
        scene.drawPoint(xc + x, yc + y);
    }
}
void draw_brezenham_circle(double xc, double yc, double R, BaseDrawer &scene)
{
    int x = 0, y = R;
    int d = 2 * (1 - R);
    int y_end = 0;
    int d1, d2;
    while (y >= y_end)
    {
        scene.drawPoint(xc + x, yc - y);
        scene.drawPoint(xc - x, yc - y);
        scene.drawPoint(xc - x, yc + y);
        scene.drawPoint(xc + x, yc + y);

        if (d < 0)
        {
            d1 = 2 * d + 2 * y - 1;
            if (d1 < 0)
            {
                x = x + 1;
                d = d + 2 * x + 1;
            }
            else
            {
                x = x + 1;
                y = y - 1;
                d = d + 2 * (x - y + 1);
            }
        }
        else if (d == 0)
        {
            x = x + 1;
            y = y - 1;
            d = d + 2 * (x - y + 1);
        }
        else
        {
            d2 = 2 * d - 2 * x - 1;
            if (d2 < 0)
            {
                x = x + 1;
                y = y - 1;
                d = d + 2 * (x - y + 1);
            }
            else
            {
                y = y - 1;
                d = d - 2 * y + 1;
            }
        }
    }
}
void draw_midpoint_circle(double xc, double yc, double R, BaseDrawer &scene)
{
    int cx = xc;
    int cy = yc;

    int xr;
    int yr;
    int r2 = R * R;
    int r22 = 2 * r2;
    int rdel2 = round(R / sqrt(2));

    int x = 0;
    int y = R;

    int f = (r2 - r2 * y + 0.25 * r2 + 0.5);
    int df = 0;

    int delta = -r22 * y;

    while(x <= rdel2) {
        xr = x + cx;
        yr = y + cy;
        scene.drawPoint(xr, yr);
        scene.drawPoint(cx - x, yr);
        scene.drawPoint(xr, cy - y);
        scene.drawPoint(cx - x, cy - y);

        x += 1;
        if(f >= 0) {
            y -= 1;
            delta += r22;
            f += delta;
        }
        df += r22;
        f  += df + r2;
    }
    delta = r22 * x;
    f += - r2 * (x + y);
    df = -r22 * y;
    while(y >= 0) {
        xr = x + cx;
        yr = y + cy;
        scene.drawPoint(xr, yr);
        scene.drawPoint(cx - x, yr);
        scene.drawPoint(xr, cy - y);
        scene.drawPoint(cx - x, cy - y);
        y -= 1;
        if(f < 0) {
            x += 1;
            delta += r22;
            f += delta;
        }
        df += r22;
        f  += df + r2;//
    }
}

void BaseDrawer::drawPoint(int x, int y)
{
    this->addEllipse(x, y, POINT_SIZE, POINT_SIZE);
}

void BaseDrawer::drawLine(qreal xFirst, qreal yFirst, qreal xLast, qreal yLast)
{
    this->addLine(xFirst, yFirst, xLast, yLast);
}

void BaseDrawer::drawCircle(Point3D _center, qreal radius)
{
    //this->addEllipse(_center.x(), _center.y(), radius * 2, radius * 2);
    draw_midpoint_circle(_center.x(), _center.y(), radius, *this);
    //draw_param_circle(_center.x(), _center.y(), radius, *this);
}

void BaseDrawer::repaint()
{
    this->clear();

}
