#ifndef DRAWER_H
#define DRAWER_H
#include "basedrawer.h"
#include "point3d.h"
#include "cone.h"

class Drawer : public BaseDrawer
{
public:
    Drawer();

    void drawCone(Cone _cone);

    void PerspectiveProjection(Cone &_cone);
};

#endif // DRAWER_H
