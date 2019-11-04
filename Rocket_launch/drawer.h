#ifndef DRAWER_H
#define DRAWER_H
#include "basedrawer.h"
#include "point3d.h"
#include "cone.h"
#include "rocket.h"
#include "transfor_matrix.h"

class Drawer : public BaseDrawer
{
public:
    Drawer();

    void drawCone(Cone &_cone);
    void drawRocket(rocket &_rocket, Point3D CameraPosition);
    void PerspectiveProjection(Point3D &point);
    Camera _camera;
    //double PerspectiveProjectionX(double x);
    //double PerspectiveProjectionY(double y);
    //double PerspectiveProjection(Point3D &point);
};

#endif // DRAWER_H
