#include "triangle.h"

Triangle::Triangle(Point3D &_A, Point3D &_B, Point3D &_C)
{
    A.changeAll(_A.x(), _A.y(), _A.z());
    B.changeAll(_B.x(), _B.y(), _B.z());
    C.changeAll(_C.x(), _C.y(), _C.z());

    A.triangleIndexes = _A.triangleIndexes;
    B.triangleIndexes = _B.triangleIndexes;
    C.triangleIndexes = _C.triangleIndexes;

    A.pointIndex = _A.pointIndex;
    B.pointIndex = _B.pointIndex;
    C.pointIndex = _C.pointIndex;
}

Vector Triangle::getTriangleNormal()
{
    Vector V1(A, B);
    Vector V2(B, C);
    Vector Vn = crossProduct(V1, V2);
    Vn.normalize();
    return Vn;
}
