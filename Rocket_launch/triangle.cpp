#include "triangle.h"

Triangle::Triangle(Point3D _A, Point3D _B, Point3D _C)
{
    A.changeAll(_A.x(), _A.y(), _A.z());
    B.changeAll(_B.x(), _B.y(), _B.z());
    C.changeAll(_C.x(), _C.y(), _C.z());
}
