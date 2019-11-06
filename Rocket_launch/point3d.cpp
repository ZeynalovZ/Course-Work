#include "point3d.h"
#include <cmath>
#include <QDebug>
#include <iostream>
using namespace std;



void printMatrix(double matrix[][4], int row_count, int column_count)
{
    cout << "Matrix:" << row_count << column_count << endl;
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < column_count; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int multiplicateMatrix(double src1[][4], double src2[][4], int rc1, int cc1, int rc2, int cc2, Point3D &tmp)
{
    double tmpMtr[1][4] = {0.};
    if (cc1 != rc2)
    {
        return -1;
    }
    if (src1 == NULL || src2 == NULL)
    {
        return -2;
    }
    for (int i = 0; i < rc1; i++)
    {
        for (int j = 0; j < cc2; j++)
        {
            for (int k = 0; k < cc1; k++)
            {
                double tmp = src1[i][k] * src2[k][j];
                tmpMtr[i][j] = tmpMtr[i][j] + tmp;
            }
        }
    }
    tmp.setX(tmpMtr[0][0]);
    tmp.setY(tmpMtr[0][1]);
    tmp.setZ(tmpMtr[0][2]);
}

void Point3D::rotateX(int angle_x)
{
    if (angle_x == 0)
    {
        return;
    }
    double matrix[4][4] = {1,  0,              0,               0,
                        0,  cos(angle_x * M_PI / TO_RAD_180),   sin(angle_x * M_PI / TO_RAD_180),    0,
                        0,  -sin(angle_x * M_PI / TO_RAD_180),  cos(angle_x * M_PI / TO_RAD_180),    0,
                        0,  0,              0,               1};

    //qDebug() << cos(angle_x * M_PI / TO_RAD_180);
    double matrixsrc[1][4] = {this->x(), this->y(), this->z(), 1};
    Point3D tmp;
    multiplicateMatrix(matrixsrc, matrix, 1, 4, 4, 4, tmp);

    this->setY(tmp.y());
    this->setZ(tmp.z());

    /*
    qreal center_y = this->y();
    qreal center_z = this->z();
    if (angle_x != 0)
    {
        double cosa = cos(angle_x * M_PI / TO_RAD_180);
        double sina = sin(angle_x * M_PI / TO_RAD_180);
        double y = center_y * cosa - center_z * sina;
        double z = center_y * sina + center_z * cosa;

        this->setY(y);
        this->setZ(z);
    }
    */
}

void Point3D::rotateY(int angle_y)
{
    if (angle_y == 0)
    {
        return;
    }
    double matrix[4][4] = {cos(angle_y * M_PI / TO_RAD_180),  0,             -sin(angle_y * M_PI / TO_RAD_180),               0,
                        0,  1,   0,    0,
                        sin(angle_y * M_PI / TO_RAD_180), 0,  cos(angle_y * M_PI / TO_RAD_180),    0,
                        0,  0,              0,               1};

    //qDebug() << cos(angle_x * M_PI / TO_RAD_180);
    double matrixsrc[1][4] = {this->x(), this->y(), this->z(), 1};
    Point3D tmp;
    //printMatrix(matrixsrc, 1, 4);
    multiplicateMatrix(matrixsrc, matrix, 1, 4, 4, 4, tmp);
    //qDebug() << tmp.x() << tmp.y() << tmp.z() << "tmp";
    this->setX(tmp.x());
    this->setZ(tmp.z());
}

void Point3D::move(int x, int y, int z)
{
    if (x == 0 && y == 0 && z == 0)
    {
        return;
    }
    double matrix[4][4] = {1,   0,   0,    0,
                           0,   1,   0,    0,
                           0,   0,   1,    0,
                           x,   y,   z,    1};

    //qDebug() << cos(angle_x * M_PI / TO_RAD_180);
    double matrixsrc[1][4] = {this->x(), this->y(), this->z(), 1};
    Point3D tmp;
    //printMatrix(matrixsrc, 1, 4);
    multiplicateMatrix(matrixsrc, matrix, 1, 4, 4, 4, tmp);
    //qDebug() << tmp.x() << tmp.y() << tmp.z() << "tmp";
    this->setX(tmp.x());
    this->setZ(tmp.z());
}

void Point3D::transform(const std::shared_ptr<Matrix> matrix)
{
    std::vector<double> result(4);
    std::vector<double> data = {this->x(), this->y(), this->z(), 1.};
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i] += data[j] * matrix->get(i, j);
        }
    }
    *this = {result[0], result[1], result[2]};
}
