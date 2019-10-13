#ifndef CONE_H
#define CONE_H
#include "point3d.h"
#include "baseobject.h"
// ::baseobject
class Cone : public BaseObject
{
public:
    Cone(){}

    void createCone(Point3D _center, qreal _radius1, qreal _radius2, qreal _height, qreal _scale);
    void Rotatex(int angle_x);
    void Rotatey(int angle_y);
    void Rotatez(int angle_z);
public:
    Point3D ConeCenter;
    qreal radius1;
    qreal radius2;
    qreal height;
    qreal scale;
    qreal currentAngle = 0;
};

#endif // CONE_H
