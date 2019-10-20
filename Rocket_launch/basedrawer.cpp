#include "basedrawer.h"
#include "QGraphicsScene"
#include "cmath"
#include <QDebug>
BaseDrawer::BaseDrawer()
{

}

void create_param_circle(double xc, double yc, double R, std::vector<Point3D> &CirclePoints, double zc)
{
    double x, y;
    double step = 1 / R;
    for (double t = 0; t <= M_PI_2; t += step)
    {
        x = round(R * cos(t));
        y = round(R * sin(t));
        Point3D FirstPoint(xc + x, yc - y, zc);
        Point3D SecondPoint(xc - x, yc - y, zc);
        Point3D ThirdPoint(xc - x, yc + y, zc);
        Point3D LastPoint(xc + x, yc + y, zc);
        CirclePoints.push_back(FirstPoint);
        CirclePoints.push_back(SecondPoint);
        CirclePoints.push_back(ThirdPoint);
        CirclePoints.push_back(LastPoint);
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

void BaseDrawer::CreateCircle(std::vector<Point3D> &CirclePoints, Point3D _center, qreal radius)
{
    //this->addEllipse(_center.x(), _center.y(), radius * 2, radius * 2);
    //draw_midpoint_circle(_center.x(), _center.y(), radius, *this);
    create_param_circle(_center.x(), _center.y(), radius, CirclePoints, _center.z());
}

void BaseDrawer::repaint()
{
    this->clear();
}
