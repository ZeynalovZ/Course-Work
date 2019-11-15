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

void draw_brezenham_circle(double xc, double yc, double R, std::vector<Point3D> &CirclePoints, double zc)
{
    int x = 0, y = R;
    int d = 2 * (1 - R);
    int y_end = 0;
    int d1, d2;
    while (y >= y_end)
    {

        Point3D FirstPoint(xc + x, yc - y, zc);
        Point3D SecondPoint(xc - x, yc - y, zc);
        Point3D ThirdPoint(xc - x, yc + y, zc);
        Point3D LastPoint(xc + x, yc + y, zc);
        CirclePoints.push_back(FirstPoint);
        CirclePoints.push_back(SecondPoint);
        CirclePoints.push_back(ThirdPoint);
        CirclePoints.push_back(LastPoint);

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


void Cone::createCone(Point3D _center, qreal _radius1, qreal _radius2, qreal _height, int VertexCount, QColor ObjColor)
{
    this->ConeCenter = _center;
    this->radius1 = _radius1;
    this->radius2 = _radius2;
    this->height = _height;
    this->ObjectColor = ObjColor;
    qreal distance = _height / 2;
    Point3D ConeCenter = _center;
    qreal radius1 = _radius1;
    qreal radius2 = _radius2;


    FirstCenter = ConeCenter;
    SecondCenter = ConeCenter;

    // Удаляем окружности друг от друга на h = distance
    FirstCenter.setZ(ConeCenter.z() + distance);
    SecondCenter.setZ(ConeCenter.z() - distance);


    //this->firstCircle.clear();
    //this->secondCircle.clear();
    this->CreateCircle(this->firstCircle, FirstCenter, radius1, VertexCount);
    this->CreateCircle(this->secondCircle, SecondCenter, radius2, VertexCount);
    createConnectedLines();

    /*
    for (int i = 0; i < Triangles.size(); i++)
    {
        // это важная часть реализации при построении по ребрам

        Edges.addEdge(Triangles[i].A, Triangles[i].B);
        Edges.addEdge(Triangles[i].B, Triangles[i].C);
        Edges.addEdge(Triangles[i].C, Triangles[i].A);

    }
    */
    /*
    for (int i = 0; i < this->firstCircle.size() - 4; i += 4)
    {
        if (i == firstCircle.size() - 8)
        {
            Edges.addEdge(firstCircle[i], firstCircle[i + 3]);
            Edges.addEdge(firstCircle[i + 1], firstCircle[i + 2]);
            //qDebug() << firstCircle[0].z() << "z";
        }
        else
        {
            Edges.addEdge(firstCircle[i], firstCircle[i + 4]);
            //qDebug() << firstCircle[i + 4].z() << "is z " << i << " " <<  firstCircle.size();
            Edges.addEdge(firstCircle[i + 1], firstCircle[i + 5]);
            Edges.addEdge(firstCircle[i + 2], firstCircle[i + 6]);
            Edges.addEdge(firstCircle[i + 3], firstCircle[i + 7]);
        }
    }

    for (int i = 0; i < this->secondCircle.size() - 4; i += 4)
    {
        if (i == secondCircle.size() - 8)
        {
            Edges.addEdge(secondCircle[i], secondCircle[i + 3]);
            Edges.addEdge(secondCircle[i + 1], secondCircle[i + 2]);
            //Edges.addEdge(firstCircle[i], firstCircle[0]);
            //qDebug() << firstCircle[0].z() << "z";
        }
        else
        {
            Edges.addEdge(secondCircle[i], secondCircle[i + 4]);
            //qDebug() << firstCircle[i + 4].z() << "is z " << i << " " <<  firstCircle.size();
            Edges.addEdge(secondCircle[i + 1], secondCircle[i + 5]);
            Edges.addEdge(secondCircle[i + 2], secondCircle[i + 6]);
            Edges.addEdge(secondCircle[i + 3], secondCircle[i + 7]);
        }
    }
    */
    Point3D tmp1;
    Point3D tmp2;
    // Создание ребер
    /*
    if (radius1 <= radius2 && this->firstCircle.size() != 4)
    {
        qreal k = this->secondCircle.size() / this->firstCircle.size();
        for (qreal i = 0; i < this->firstCircle.size(); i += 74)
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
        for (int i = 0; i < this->secondCircle.size(); i += 74)
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
    */
}

void Cone::CreateCircle(std::vector<Point3D> &CirclePoints, Point3D _center, qreal radius, int n)
{
    //draw_brezenham_circle(_center.x(), _center.y(), radius, CirclePoints, _center.z());
    createRightPolygon(_center.x(), _center.y(), _center.z(), radius, CirclePoints, n);
}

void Cone::createRightPolygon(double xc, double yc, double zc, double R,
                              std::vector<Point3D> &CirclePoints, int n)
{
    Point3D point;
    double x, y, z = zc;
    if (R > 0 && n > 0)
    {
        double angle = double(360.0 / double(n));
        int i = 0;
        double curAngle = 0;
        while (i < n + 1)
        {
            x = xc + int(round(cos(curAngle / 180 * M_PI) * R));
            y = yc - int(round(sin(curAngle / 180 * M_PI) * R));
            point.changeAll(x, y, z);
            i++;
            curAngle += angle;
            CirclePoints.push_back(point);
        }

        /*
        for (int i = 0; i < CirclePoints.size() - 1; i++)
        {
            Edges.addEdge(CirclePoints[i], CirclePoints[i + 1]);
        }
        Edges.addEdge(CirclePoints[CirclePoints.size() - 1], CirclePoints[0]);
        */
    }
}

void Cone::createConnectedLines()
{
    Point3D A = FirstCenter;
    Point3D B;
    Point3D C;
    //  конус с вевршиной вверху
    if (radius1 == 0 && radius2 != 0)
    {
        for (int i = 0; i < secondCircle.size() - 1; i++)
        {
            B = secondCircle[i];
            C = secondCircle[i + 1];
            Triangle tr(A, B, C);
            Triangles.push_back(tr);
        }
        B = secondCircle[secondCircle.size() - 1];
        C = secondCircle[0];
        Triangle tr(A, B, C);
        Triangles.push_back(tr);

        //qDebug() << secondCircle.size() << "size";
        for (int i = 1; i < secondCircle.size() - 2; i++)
        {
            A = secondCircle[0];
            B = secondCircle[i];
            C = secondCircle[i + 1];
            Triangle tr(A, B, C);
            Triangles.push_back(tr);
        }

        A = secondCircle[0];
        B = secondCircle[secondCircle.size() - 2];
        C = secondCircle[secondCircle.size() - 1];
        Triangle tr1(A, B, C);
        Triangles.push_back(tr1);
    }

    // конус с вершиной внизу
    if (radius2 == 0 && radius1 != 0)
    {
        for (int i = 0; i < firstCircle.size() - 1; i++)
        {
            B = firstCircle[i];
            C = firstCircle[i + 1];
            Triangle tr(A, B, C);
            Triangles.push_back(tr);
        }
        B = firstCircle[firstCircle.size() - 1];
        C = firstCircle[0];
        Triangle tr(A, B, C);
        Triangles.push_back(tr);

        for (int i = 0; i < firstCircle.size() - 2; i++)
        {
            A = firstCircle[0];
            B = firstCircle[i + 1];
            C = firstCircle[i + 2];
            Triangle tr(A, B, C);
            Triangles.push_back(tr);
        }
    }

    // обычный конус
    if (radius1 != 0 && radius2 != 0)
    {
        for (int i = 0; i < firstCircle.size() - 1; i++)
        {
            A = firstCircle[i];
            B = secondCircle[i];
            C = secondCircle[i + 1];
            Triangle tr(A, B, C);
            Triangles.push_back(tr);
        }
        for (int i = 1; i < secondCircle.size(); i++)
        {
            A = secondCircle[i];
            B = firstCircle[i];
            C = firstCircle[i - 1];
            Triangle tr1(A, B, C);
            Triangles.push_back(tr1);
        }

        for (int i = 0; i < firstCircle.size() - 2; i++)
        {
            A = firstCircle[0];
            B = firstCircle[i + 1];
            C = firstCircle[i + 2];
            Triangle tr(A, B, C);
            Triangles.push_back(tr);
        }

        for (int i = 0; i < secondCircle.size() - 2; i++)
        {
            A = secondCircle[0];
            B = secondCircle[i + 1];
            C = secondCircle[i + 2];
            Triangle tr(A, B, C);
            Triangles.push_back(tr);
        }


    }




    /*
    if (radius1 != 0 && radius2 != 0)
    {
        A.changeAll(firstCircle[0].x(), firstCircle[0].y(), firstCircle[0].z());
        qreal k;
        if (radius1 <= radius2)
        {
            k = secondCircle.size() / firstCircle.size();
            for (int i = 0; i < firstCircle.size() - 1; i++)
            {
                A = firstCircle[i];
                B = secondCircle[i * k];
                C = secondCircle[i * k + 1];
                Triangle tr(A, B, C);
                Triangles.push_back(tr);
            }

            for (int i = 1; i < secondCircle.size(); i++)
            {
                A = secondCircle[i];
                B = firstCircle[i / k];
                C = firstCircle[i / k - 1];
                Triangle tr1(A, B, C);
                Triangles.push_back(tr1);
            }
        }
        else
        {
            k = firstCircle.size() / secondCircle.size();
            for (int i = 0; i < secondCircle.size() - 1; i++)
            {
                A = secondCircle[i];
                B = firstCircle[i * k];
                C = firstCircle[i * k + 1];
                Triangle tr(A, B, C);
                Triangles.push_back(tr);
            }

            for (int i = 1; i < secondCircle.size(); i++)
            {
                A = firstCircle[i];
                B = secondCircle[i / k];
                C = secondCircle[i / k - 1];
                Triangle tr1(A, B, C);
                Triangles.push_back(tr1);
            }
        }

    }
    */


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

    /*

    for (int i = 0; i < this->Edges.list.size(); i++)
    {
        this->Edges.list[i].first.rotateX(angle_x);
        this->Edges.list[i].second.rotateX(angle_x);
    }
    */
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
//    for (int i = 0; i < this->firstCircle.size(); i++)
//    {
//        this->firstCircle[i].move(0, 0, 1);
//    }

//    for (int i = 0; i < this->secondCircle.size(); i++)
//    {
//        this->secondCircle[i].move(0, 0, 1);

//    }
    for (auto &triangle : Triangles)
    {

        triangle.A.move(0, 0, 1);
        triangle.B.move(0, 0, 1);
        triangle.C.move(0, 0, 1);

    }
}
