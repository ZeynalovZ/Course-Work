#ifndef VECTOR_H
#define VECTOR_H
#include "point3d.h"
#include <cmath>



class Vector
{
public:
    Vector();

    Vector(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
        w = 1;
    }

    Vector(Point3D P1, Point3D P2);

    void normalize();
    double vectorLength();
    void transform(const std::shared_ptr<Matrix> matrix);
    void addVector(Vector vec);
    // Векторное произведение
//    void crossProduct(Vector V1, Vector V2);
//    // Скалярное произвдение
//    void crossProductScalar(Vector V1, Vector V2);

    Vector& operator=(const Vector &rv);
    const Vector operator+(const Vector& rv) const;
    const Vector operator-(const Vector& rv) const;
    const Vector operator*(const double src) const;
    // operator -
    // operator +
    // operator =
    // operator *
    // operator * num

    //bool normalSign();

public:
    double x;
    double y;
    double z;
    double w;
};

Vector crossProduct(Vector V1, Vector V2);
double crossProductScalar(Vector V1, Vector V2);

#endif // VECTOR_H
