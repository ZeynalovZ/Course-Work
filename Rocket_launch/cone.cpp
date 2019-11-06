#include "cone.h"
#include "cmath"
#include <QDebug>
// scale  - для взятия конкретнгого размера конуса

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

void Cone::createCone(Point3D _center, qreal _radius1, qreal _radius2, qreal _height)
{
    this->ConeCenter = _center;
    this->radius1 = _radius1;
    this->radius2 = _radius2;
    this->height = _height;

    qreal distance = _height / 2;
    Point3D ConeCenter = _center;
    qreal radius1 = _radius1;
    qreal radius2 = _radius2;


    Point3D FirstCenter = ConeCenter;
    Point3D SecondCenter = ConeCenter;

    // Удаляем окружности друг от друга на h = distance
    FirstCenter.setZ(ConeCenter.z() + distance);
    SecondCenter.setZ(ConeCenter.z() - distance);


    //this->firstCircle.clear();
    //this->secondCircle.clear();
    this->CreateCircle(this->firstCircle, FirstCenter, radius1);
    this->CreateCircle(this->secondCircle, SecondCenter, radius2);


    Point3D tmp1;
    Point3D tmp2;
    // Создание ребер

    if (radius1 <= radius2 && this->firstCircle.size() != 4)
    {
        int k = this->secondCircle.size() / this->firstCircle.size();
        for (int i = 0; i < this->firstCircle.size(); i += 92)
        {

            // Это, если что - полигоны

            tmp1.changeAll(firstCircle[i].x(), firstCircle[i].y(), firstCircle[i].z());
            tmp2.changeAll(secondCircle[i * k].x(), secondCircle[i * k].y(), secondCircle[i].z());
            Edges.addEdge(tmp1, tmp2);

            tmp1.changeAll(firstCircle[i + 1].x(), firstCircle[i + 1].y(), firstCircle[i + 1].z());
            tmp2.changeAll(secondCircle[i * k + 1].x(), secondCircle[i  * k + 1].y(), secondCircle[i * k + 1].z());
            Edges.addEdge(tmp1, tmp2);

            tmp1.changeAll(firstCircle[i + 2].x(), firstCircle[i + 2].y(), firstCircle[i + 2].z());
            tmp2.changeAll(secondCircle[i * k + 2].x(), secondCircle[i * k + 2].y(), secondCircle[i * k + 2].z());
            Edges.addEdge(tmp1, tmp2);

            tmp1.changeAll(firstCircle[i + 3].x(), firstCircle[i + 3].y(), firstCircle[i + 3].z());
            tmp2.changeAll(secondCircle[i * k + 3].x(), secondCircle[i * k + 3].y(), secondCircle[i * k + 3].z());
            Edges.addEdge(tmp1, tmp2);
        }
    }

    else
    {
        int k = this->firstCircle.size() / this->secondCircle.size();
        //qDebug() << k << " is k";
        for (int i = 0; i < this->secondCircle.size(); i += 92)
        {
            tmp1.changeAll(secondCircle[i].x(), secondCircle[i].y(), secondCircle[i].z());
            tmp2.changeAll(firstCircle[i * k].x(), firstCircle[i * k].y(), firstCircle[i * k].z());
            Edges.addEdge(tmp1, tmp2);

            tmp1.changeAll(secondCircle[i + 1].x(), secondCircle[i + 1].y(), secondCircle[i].z());
            tmp2.changeAll(firstCircle[i * k + 1].x(), firstCircle[i  * k + 1].y(), firstCircle[i * k + 1].z());
            Edges.addEdge(tmp1, tmp2);

            tmp1.changeAll(secondCircle[i + 2].x(), secondCircle[i + 2].y(), secondCircle[i + 2].z());
            tmp2.changeAll(firstCircle[i * k + 2].x(), firstCircle[i * k + 2].y(), firstCircle[i * k + 2].z());
            Edges.addEdge(tmp1, tmp2);

            tmp1.changeAll(secondCircle[i + 3].x(), secondCircle[i + 3].y(), secondCircle[i + 3].z());
            tmp2.changeAll(firstCircle[i * k + 3].x(), firstCircle[i * k + 3].y(), firstCircle[i * k + 3].z());
            Edges.addEdge(tmp1, tmp2);
        }
    }

}

void Cone::CreateCircle(std::vector<Point3D> &CirclePoints, Point3D _center, qreal radius)
{
    create_param_circle(_center.x(), _center.y(), radius, CirclePoints, _center.z());
}
// сделать вращение для каждой точки !!! по каждой координате и в цикле построения окружности выводить какждую точку через поворот
// в объекте cone хранить угол по каждой координате, значение которых равно сумме всех углов поворотов.
void Cone::Rotatex(int angle_x)
{
    //qDebug() << this->firstCircle.size();
    // поворот относительно оси ОХ
    for (int i = 0; i < this->firstCircle.size(); i++)
    {

        //qDebug() << this->firstCircle[i].y();
        this->firstCircle[i].rotateX(angle_x);
        //qDebug() << this->firstCircle[i].y();
        //Point3D tmp(this->firstCircle[i].x(), this->firstCircle[i].y(), this->firstCircle[i].z());
        //PerspectiveProjection(tmp);
        //this->drawPoint(tmp.x(), tmp.y());
    }

    for (int i = 0; i < this->secondCircle.size(); i++)
    {
        this->secondCircle[i].rotateX(angle_x);
        //Point3D tmp(this->secondCircle[i].x(), this->secondCircle[i].y(), this->secondCircle[i].z());
        //PerspectiveProjection(tmp);
        //this->drawPoint(tmp.x(), tmp.y());
    }

    for (int i = 0; i < this->Edges.list.size(); i++)
    {
        this->Edges.list[i].first.rotateX(angle_x);
        this->Edges.list[i].second.rotateX(angle_x);
    }
}

void Cone::Rotatey(int angle_y, qreal _y, qreal _z)
{
    ;
}

void Cone::Rotatez(int angle_z, qreal _y, qreal _x)
{
    ;
}

void Cone::MoveCone()
{
    for (int i = 0; i < this->firstCircle.size(); i++)
    {
        this->firstCircle[i].move(0, 0, 1);
    }

    for (int i = 0; i < this->secondCircle.size(); i++)
    {
        this->secondCircle[i].move(0, 0, 1);

    }
    for (int i = 0; i < this->Edges.list.size(); i++)
    {

        this->Edges.list[i].first.move(0, 0, 1);
        this->Edges.list[i].second.move(0, 0, 1);

    }
}
