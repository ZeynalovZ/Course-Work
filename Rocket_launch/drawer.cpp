#include "drawer.h"
#include "QDebug"
Drawer::Drawer()
{

}

void Drawer::drawCone(Cone _cone)
{
    qDebug() << _cone.ConeCenter.x();
    PerspectiveProjection(_cone);
    qDebug() << _cone.ConeCenter.x();
    qreal distance = _cone.height / 2;
    Point3D ConeCenter = _cone.ConeCenter;
    qreal radius1 = _cone.radius1;
    qreal radius2 = _cone.radius2;

    Point3D FirstCenter = ConeCenter;
    Point3D SecondCenter = ConeCenter;

    // Удаляем окружности друг от друга на h = distance
    FirstCenter.setZ(ConeCenter.z() + distance);
    SecondCenter.setZ(ConeCenter.z() - distance);
    qDebug() << FirstCenter.x() << ";;;;" << SecondCenter.x();

    this->drawCircle(FirstCenter, radius1);
    this->drawCircle(SecondCenter, radius2);
    this->clear();

    this->drawLine(FirstCenter.x() + radius1, FirstCenter.y(), SecondCenter.x() + radius2, SecondCenter.y());
    this->drawLine(FirstCenter.x() - radius1, FirstCenter.y(), SecondCenter.x() - radius2, SecondCenter.y());
}

void Drawer::PerspectiveProjection(Cone &_cone)
{
    double x =  K * _cone.ConeCenter.x() / (_cone.ConeCenter.z() + K);
    double y =  K * _cone.ConeCenter.y() / (_cone.ConeCenter.z() + K);
    _cone.ConeCenter.setX(x);
    _cone.ConeCenter.setY(y);
}
