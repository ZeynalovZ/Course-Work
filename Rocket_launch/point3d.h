#ifndef POINT3D_H
#define POINT3D_H
#include "QPoint"

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

private:
    qreal xp;
    qreal yp;
    qreal zp;

};

#endif // POINT3D_H
