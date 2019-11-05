#include "rocket.h"
#include <QDebug>
#define SCALE 10
rocket::rocket(Point3D center)
{

}

void rocket::addModule(Cone &_cone)
{
    this->modules.push_back(_cone);
}

void rocket::createRocket(qreal _scale)
{
    this->_scale = _scale;
    Cone cone0, cone1, cone2, cone3, cone4, cone5;
    Point3D center(0, 0, 335);
    qreal radius1 = 0;
    qreal radius2 = 30;
    qreal height = 30;

    cone0.createCone(center, radius1, radius2, height);
    this->addModule(cone0);

    center.setX(0);
    center.setY(0);
    center.setZ(270);
    radius1 = 30;
    radius2 = 30;
    height = 100;

    cone1.createCone(center, radius1, radius2, height);
    this->addModule(cone1);


    center.setX(0);
    center.setY(0);
    center.setZ(210);
    radius1 = 30;
    radius2 = 40;
    height = 20;

    cone2.createCone(center, radius1, radius2, height);
    this->addModule(cone2);

    center.setX(0);
    center.setY(0);
    center.setZ(125);
    radius1 = 40;
    radius2 = 40;
    height = 150;

    cone3.createCone(center, radius1, radius2, height);
    this->addModule(cone3);

    center.setX(0);
    center.setY(0);
    center.setZ(40);
    radius1 = 40;
    radius2 = 30;
    height = 20;

    cone4.createCone(center, radius1, radius2, height);
    this->addModule(cone4);

    center.setX(0);
    center.setY(0);
    center.setZ(15);
    radius1 = 30;
    radius2 = 40;
    height = 30;

    cone5.createCone(center, radius1, radius2, height);
    this->addModule(cone5);

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
