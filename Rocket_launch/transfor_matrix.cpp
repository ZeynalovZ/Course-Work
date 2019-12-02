#include "transfor_matrix.h"
#include <QDebug>
MoveMatrix::MoveMatrix(int x, int y, int z)
{
    _data[0][0] = 1;
    _data[1][1] = 1;
    _data[2][2] = 1;
    _data[3][3] = 1;
    _data[0][3] = x;
    _data[1][3] = y;
    _data[2][3] = z;
}

ScaleMatrix::ScaleMatrix(double x, double y, double z)
{
    _data[0][0] = x;
    _data[1][1] = y;
    _data[2][2] = z;
    _data[3][3] = 1;
}

RotateOxMatrix::RotateOxMatrix(double angle)
{
    _data[0][0] = 1;
    _data[1][1] = cos(angle);
    _data[1][2] = -sin(angle);
    _data[2][1] = sin(angle);
    _data[2][2] = cos(angle);
    _data[3][3] = 1;
}

RotateOyMatrix::RotateOyMatrix(double angle)
{
    _data[0][0] = cos(angle);
    _data[1][1] = 1;
    _data[2][0] = -sin(angle);
    _data[0][2] = sin(angle);
    _data[2][2] = cos(angle);
    _data[3][3] = 1;
}

RotateOzMatrix::RotateOzMatrix(double angle)
{
    _data[0][0] = cos(angle);
    _data[0][1] = -sin(angle);
    _data[1][0] = sin(angle);
    _data[1][1] = cos(angle);
    _data[2][2] = 1;
    _data[3][3] = 1;
}

SimplePos::SimplePos(Point3D Position)
{
    _data[0][0] = 1.;
    _data[1][1] = 1.;
    _data[2][2] = 1.;
    _data[3][3] = 1.;

    _data[3][0] = -Position.x();
    _data[3][1] = -Position.y();
    _data[3][2] = -Position.z();
}

LookAt::LookAt(Point3D _camPos, Vector _camFront, Vector _camUp)
{
    this->fillMatrixWZeros();
    Vector _camRight = crossProduct(_camFront, _camUp);
    _data[0][0] = _camRight.x;
    _data[1][0] = _camRight.y;
    _data[2][0] = _camRight.z;

    _data[0][1] = _camUp.x;
    _data[1][1] = _camUp.y;
    _data[2][1] = _camUp.z;

    _data[0][2] = _camFront.x;
    _data[1][2] = _camFront.y;
    _data[2][2] = _camFront.z;

    _data[3][3] = 1;


    SimplePos *mtr = new SimplePos(_camPos);
    multiply(*mtr);
}

void LookAt::multiply(SimplePos &mtr)
{
    Matrix tmp;
    for(int i = 0;i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                tmp.set(i, j, tmp.get(i, j) + (this->get(i, k) * mtr.get(k, j)));
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->set(i,j, tmp.get(i, j));
        }
    }
}

void printTransformedMatrix(Matrix mtr)
{
    for (int i = 0; i < 4; i++)
    {
        qDebug() << mtr.get(i, 0) << mtr.get(i, 1) << mtr.get(i, 2) << mtr.get(i, 3) ;
    }
}

perspectiveProjection::perspectiveProjection(double near, double far, double fovy, double AspectRatio)
{
    if (far == near)
    {
        qDebug() << "far == near !!";
    }
    double zoomy = tan(fovy / 2);
    double zoomx = zoomy / AspectRatio;
    _data[0][0] = zoomx;
    _data[1][1] = zoomy;
    _data[2][2] = -((far + near) / (far - near));
    _data[2][3] = -2 * near * far / (far - near);
    _data[3][2] = -1;
}
