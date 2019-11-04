#ifndef TRANSFOR_MATRIX_H
#define TRANSFOR_MATRIX_H
#include "matrix.h"
#include <cmath>

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

#endif // TRANSFOR_MATRIX_H
