#ifndef POINT3D_H
#define POINT3D_H
#include "QPoint"
#include "matrix.h"
#include <memory>
#define TO_RAD_180 180
class Point3D : public QPoint
{
public:
    Point3D()
    {

    }


    Point3D(qreal _x, qreal _y, qreal _z)
    {
        xp = _x;
        yp = _y;
        zp = _z;
    }




//    friend const Point3D operator +(const Point3D p1, const Point3D p2)
//    {
//        return new Point3D(p1.x() + p2.x(), p1.y() + p2.y(), p1.z() + p2.z());
//    }

    // Getters
    qreal x()
    {
        return xp;
    }
    qreal y()
    {
        return yp;
    }
    qreal z()
    {
        return zp;
    }

    void changeAll(qreal _x, qreal _y, qreal _z)
    {
        xp = _x;
        yp = _y;
        zp = _z;
    }
    // Setters
    void setX(qreal x)
    {
        xp = x;
    }
    void setY(qreal y)
    {
        yp = y;
    }

    void setZ(qreal z)
    {
        zp = z;
    }

    void rotateX(int angle_x);
    void rotateY(int angle_y);
    //void rotateZ(int angle_z);

    void move(int x, int y, int z);

    void transform(const std::shared_ptr<Matrix> matrix);
private:
    qreal xp;
    qreal yp;
    qreal zp;

};



#endif // POINT3D_H
