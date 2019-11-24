#include "vector.h"
#include <QDebug>

#define EPS 0.0001

Vector::Vector()
{

}

Vector::Vector(Point3D P1, Point3D P2)
{
    this->x = P2.x() - P1.x();
    this->y = P2.y() - P1.y();
    this->z = P2.z() - P1.z();
}

void Vector::normalize()
{
    double length = this->vectorLength();
    if (length < EPS || length > -EPS)
    {
        this->x /= length;
        this->y /= length;
        this->z /= length;
    }

}

double Vector::vectorLength()
{
    double length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return  length;
}

void Vector::transform(const std::shared_ptr<Matrix> matrix)
{
    std::vector<double> result(4);
    std::vector<double> data = {this->x, this->y, this->z, this->w};
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i] += data[j] * matrix->get(i, j);
        }
    }
    *this = {result[0], result[1], result[2]};
}

Vector crossProduct(Vector V1, Vector V2)
{
    Vector vResult;
    vResult.x = V1.y * V2.z - V1.z * V2.y;
    vResult.y = V1.z * V2.x - V1.x * V2.z;
    vResult.z = V1.x * V2.y - V1.y * V2.x;
    return vResult;
}

double crossProductScalar(Vector V1, Vector V2)
{
    double result = V1.x * V2.x + V1.y * V2.y + V1.z * V2.z;
    return result;
}

