#ifndef ROCKET_H
#define ROCKET_H
#include <stdio.h>
#include <vector>
#include "point3d.h"
#include "cone.h"

class rocket
{
public:
    rocket()
    {

    }
    rocket(Point3D center);

    void addModule(Cone &_cone);

    void drawRocket();

    void createRocket(Point3D RocketCenter, qreal Scale);

    void deleteRocket();

    void rotateX(int angle_x);

    void rotateY(int angle_y);

    void rotateZ();

    void moveRocket();

    bool is_visible();

public:
    Point3D rocketCenter;
    std::vector<Cone> modules;
    int angleX = 0;
    int angleY = 0;
    int angleZ = 0;
    qreal scale;
};

#endif // ROCKET_H
