#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point3d.h"

class Triangle
{
public:
    Triangle(Point3D _A, Point3D _B, Point3D _C);
    Triangle()
    {

    }

    Point3D A;
    Point3D B;
    Point3D C;

};

#endif // TRIANGLE_H
