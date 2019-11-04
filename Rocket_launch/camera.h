#ifndef CAMERA_H
#define CAMERA_H
#include <string>
#include "point3d.h"
#include "matrix.h"
class Camera
{
public:
    Camera();

    const Point3D &getPosition() const;
    void setPosition(const Point3D &position);
    double getXAngle() const;
    void setXAngle(double x_angle);
    double getYAngle() const;
    void setYAngle(double y_angle);
    double getZAngle() const;
    void setZAngle(double z_angle);

    void transformCamera(const std::shared_ptr<Matrix> matrix);
//    void draw(std::shared_ptr<BaseDrawManager> drawer) override;
private:
    Point3D _position;
    double _x_angle;
    double _y_angle;
    double _z_angle;
};


#endif // CAMERA_H
