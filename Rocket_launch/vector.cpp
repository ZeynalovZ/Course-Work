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

void Vector::addVector(Vector vec)
{
    this->x = this->x + vec.x;
    this->y = this->y + vec.y;
    this->z = this->z + vec.z;
    this->w = this->w + vec.w;
}

Vector &Vector::operator=(const Vector &rv)
{
    if (this == &rv)
    {
        return *this;
    }
    this->x = rv.x;
    this->y = rv.y;
    this->z = rv.z;
    this->w = rv.z;
    return *this;
}

const Vector Vector::operator+(const Vector &rv) const
{
    double tmpX = this->x + rv.x;
    double tmpY = this->y + rv.y;
    double tmpZ = this->z + rv.z;
    return Vector(tmpX, tmpY, tmpZ);
}

const Vector Vector::operator-(const Vector &rv) const
{
    double tmpX = this->x - rv.x;
    double tmpY = this->y - rv.y;
    double tmpZ = this->z - rv.z;
    return Vector(tmpX, tmpY, tmpZ);
}

const Vector Vector::operator*(const double src) const
{
    double tmpX = this->x * src;
    double tmpY = this->y * src;
    double tmpZ = this->z * src;
    return Vector(tmpX, tmpY, tmpZ);
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

