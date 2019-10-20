#ifndef CONE_H
#define CONE_H
#include "point3d.h"
#include "baseobject.h"
#include <vector>
// ::baseobject
class Cone : public BaseObject
{
public:
    Cone(){}

    void createCone(Point3D _center, qreal _radius1, qreal _radius2, qreal _height, qreal _scale);
    void Rotatex(int angle_x, Point3D &point);
    void Rotatey(int angle_y, qreal _y, qreal _z);
    void Rotatez(int angle_z, qreal _y, qreal _x);
public:
    Point3D ConeCenter;
    qreal radius1;
    qreal radius2;
    qreal height;
    qreal scale;
    qreal currentAngle = 0;

    std::vector<Point3D> firstCircle;
    std::vector<Point3D> secondCircle;
    std::vector<std::pair<int, int>> edges;
};

#endif // CONE_H
