#include "camera.h"


Camera::Camera(): _x_angle(0), _y_angle(0), _z_angle(0)
{
    _position = Point3D(0, 0, -1000);
}

const Point3D &Camera::getPosition() const
{
    return _position;
}
void Camera::setPosition(const Point3D &_position)
{
    Camera::_position = _position;
}

double Camera::getXAngle() const
{
    return _x_angle;
}
void Camera::setXAngle(double _x_angle)
{
    Camera::_x_angle = _x_angle;
}
double Camera::getYAngle() const
{
    return _y_angle;
}
void Camera::setYAngle(double _y_angle)
{
    Camera::_y_angle = _y_angle;
}
double Camera::getZAngle() const
{
    return _z_angle;
}
void Camera::setZAngle(double _z_angle)
{
    Camera::_z_angle = _z_angle;
}

void Camera::setCameraPos(Point3D p)
{
    this->_position.setX(p.x());
    this->_position.setY(p.y());
    this->_position.setZ(p.z());
}

void Camera::transformCamera(const std::shared_ptr<Matrix> matrix)
{
    _position.transform(matrix);
}
/*
void Camera::draw(std::shared_ptr<BaseDrawManager> drawer)
{
    drawer->draw(*this);
}
*/
