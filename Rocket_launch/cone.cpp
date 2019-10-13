#include "cone.h"
#include "cmath"
#define TO_RAD_180 180
// scale  - для взятия конкретнгого размера конуса
void Cone::createCone(Point3D _center, qreal _radius1, qreal _radius2, qreal _height, qreal _scale)
{
    this->ConeCenter = _center;
    this->radius1 = _radius1 * _scale;
    this->radius2 = _radius2 * _scale;
    this->height = _height * _scale;
    this->scale = _scale;
}
// сделать вращение для каждой точки !!! по каждой координате и в цикле построения окружности выводить какждую точку через поворот
// в объекте cone хранить угол по каждой координате, значение которых равно сумме всех углов поворотов.
void Cone::Rotatex(int angle_x)
{
    qreal center_y = this->ConeCenter.y();
    qreal center_z = this->ConeCenter.z();
    if (angle_x != 0)
    {
        double cosa = cos(angle_x * M_PI / TO_RAD_180);
        double sina = sin(angle_x * M_PI / TO_RAD_180);
        double y = center_y * cosa - center_z * sina;
        double z = center_y * sina + center_z * cosa;

        this->ConeCenter.setY(y);
        this->ConeCenter.setZ(z);
    }
}

void Cone::Rotatey(int angle_y)
{
    qreal center_y = this->ConeCenter.y();
    qreal center_z = this->ConeCenter.z();
    if (angle_y != 0)
    {
        double cosa = cos(angle_y * M_PI / TO_RAD_180);
        double sina = sin(angle_y * M_PI / TO_RAD_180);
        double x = center_y * cosa - center_z * sina;
        double z = center_y * sina + center_z * cosa;

        this->ConeCenter.setX(x);
        this->ConeCenter.setZ(z);
    }
}

void Cone::Rotatez(int angle_z)
{
    qreal center_y = this->ConeCenter.y();
    qreal center_x = this->ConeCenter.x();
    if (angle_z != 0)
    {
        double cosa = cos(angle_z * M_PI / TO_RAD_180);
        double sina = sin(angle_z * M_PI / TO_RAD_180);
        double x = center_x * cosa - center_y * sina;
        double y = center_x * sina + center_y * cosa;

        this->ConeCenter.setX(x);
        this->ConeCenter.setY(y);
    }
}
