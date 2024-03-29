#include "rocket.h"
#include <QDebug>
#define SCALE 10
//#define EdgesCircleCount 50
rocket::rocket(Point3D center)
{

}

void rocket::addModule(Cone &_cone)
{
    this->modules.push_back(_cone);
}

void rocket::createRocket(Point3D RocketCenter, qreal Scale, int n)
{
    int EdgesCircleCount = n;
    this->scale = Scale;
    this->rocketCenter = RocketCenter;
    Cone cone0, cone1, cone2, cone3, cone4, cone5, coneFire;
    int x = rocketCenter.x();
    int y = rocketCenter.y();
    int z = rocketCenter.z();
    qreal radius1 = 30 * scale;
    qreal radius2 = 40 * scale;
    qreal height = 30 * scale;
    Point3D center(x, y, z + height / 2);
    cone0.createCone(center, radius1, radius2, height, EdgesCircleCount, RocketColor);
    this->addModule(cone0);
    z += height;

    radius1 = 40 * scale;
    radius2 = 30 * scale;
    height = 20 * scale;
    center.setX(x);
    center.setY(y);
    center.setZ(z + height / 2);
    cone1.createCone(center, radius1, radius2, height, EdgesCircleCount, RocketColor);
    this->addModule(cone1);
    z += height;

    radius1 = 40 * scale;
    radius2 = 40 * scale;
    height = 150 * scale;
    center.setX(x);
    center.setY(y);
    center.setZ(z + height / 2);
    cone2.createCone(center, radius1, radius2, height, EdgesCircleCount, RocketColor);
    this->addModule(cone2);
    z += height;

    radius1 = 30 * scale;
    radius2 = 40 * scale;
    height = 20 * scale;
    center.setX(x);
    center.setY(y);
    center.setZ(z + height / 2);
    cone3.createCone(center, radius1, radius2, height, EdgesCircleCount, RocketColor);
    this->addModule(cone3);
    z += height;


    radius1 = 30 * scale;
    radius2 = 30 * scale;
    height = 100 * scale;
    center.setX(x);
    center.setY(y);
    center.setZ(z + height / 2);
    cone4.createCone(center, radius1, radius2, height, EdgesCircleCount, RocketColor);
    this->addModule(cone4);
    z += height;

    radius1 = 0 * scale;
    radius2 = 30 * scale;
    height = 30 * scale;
    center.setX(x);
    center.setY(y);
    center.setZ(z + height / 2);
    cone5.createCone(center, radius1, radius2, height, EdgesCircleCount, RocketColor);
    this->addModule(cone5);
    z += height;

    // конус огня
//    radius1 = 40 * scale;
//    radius2 = 50 * scale;
//    height = 100 * scale;
//    center.setX(x);
//    center.setY(y);
//    center.setZ(-height / 2);
//    coneFire.createCone(center, radius1, radius2, height, EdgesCircleCount, QColor(Qt::red));
//    this->addModule(coneFire);

}

void rocket::deleteRocket()
{
    this->modules.clear();
}

void rocket::rotateX(int angle_x)
{
    //qDebug() << this->modules[0].secondCircle.size();
    this->angleX += angle_x;

}

void rocket::rotateY(int angle_y)
{
    this->angleY += angle_y;
}

void rocket::moveRocket()
{
    for (auto &module : modules)
    {
        module.MoveCone(0, 0, 1);
    }
}

void rocket::moveX(int x)
{
    for (auto &module : modules)
    {
        module.MoveCone(x, 0, 0);
    }
}

void rocket::moveY(int y)
{
    for (auto &module : modules)
    {
        module.MoveCone(0, y, 0);
    }
}

void rocket::moveZ(int z)
{
    for (auto &module : modules)
    {
        module.MoveCone(0, 0, z);
    }
}

void rocket::setVertexes()
{
    int i = 0;

}

