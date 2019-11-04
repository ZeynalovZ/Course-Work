#ifndef POINT3D_H
#define POINT3D_H
#include "QPoint"
#include "matrix.h"
#include <memory>

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

    void transform(const std::shared_ptr<Matrix> matrix);
private:
    qreal xp;
    qreal yp;
    qreal zp;

};

#endif // POINT3D_H
