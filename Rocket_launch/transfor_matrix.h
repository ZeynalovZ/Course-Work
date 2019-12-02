#ifndef TRANSFOR_MATRIX_H
#define TRANSFOR_MATRIX_H
#include "matrix.h"
#include <cmath>
#include "vector.h"
#include "point3d.h"

class MoveMatrix: public Matrix
{
public:
    MoveMatrix(int x, int y, int z);
};

class ScaleMatrix: public Matrix
{
public:
    ScaleMatrix(double x, double y, double z);
};

class RotateOxMatrix: public Matrix
{
public:
    RotateOxMatrix(double angle);
};

class RotateOyMatrix: public Matrix
{
public:
    RotateOyMatrix(double angle);
};

class RotateOzMatrix: public Matrix
{
public:
    RotateOzMatrix(double angle);
};

class SimplePos: public Matrix
{
public:
    SimplePos(Point3D Position);

};

class LookAt: public Matrix
{
public:
    LookAt(Point3D _camPos, Vector _camFront, Vector _camUp);
    void multiply(SimplePos &mtr);
};

class perspectiveProjection : public Matrix
{
public:
    perspectiveProjection(double near, double far, double fovy, double AspectRatio);

};

void printTransformedMatrix(Matrix mtr);


#endif // TRANSFOR_MATRIX_H
