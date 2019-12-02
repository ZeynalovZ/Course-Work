#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point3d.h"
#include "vector.h"

class Triangle
{
public:
    Triangle(Point3D &_A, Point3D &_B, Point3D &_C);
    Triangle()
    {

    }
    Vector getTriangleNormal();

    Point3D A;
    Point3D B;
    Point3D C;
    Vector normal;

};

#endif // TRIANGLE_H
