#ifndef CONE_H
#define CONE_H
#include "point3d.h"
#include "baseobject.h"
#include "edges.h"
#include <vector>
#include "triangle.h"
#include <QColor>




// ::baseobject
class Cone : public BaseObject
{
public:
    Cone(){}

    void createCone(Point3D _center, qreal _radius1, qreal _radius2, qreal _height, int VertexCount, QColor ObjColor);
    void CreateCircle(std::vector<Point3D> &CirclePoints, Point3D _center, qreal radius, int n);
    void createRightPolygon(double xc, double yc, double zc, double R,
                            std::vector<Point3D> &CirclePoints, int n);
    void createConnectedLines();
    void createVertexShader();
    void computeNormals();
    void Rotatex(int angle_x);
    void Rotatey(int angle_y, qreal _y, qreal _z);
    void Rotatez(int angle_z, qreal _y, qreal _x);
    void MoveCone(int x, int y, int z);
public:
    Point3D ConeCenter;
    qreal radius1;
    qreal radius2;
    qreal height;
    qreal currentAngleX = 0;
    qreal currentAngleY = 0;
    qreal currentAngleZ = 0;

    std::vector<Point3D> firstCircle;
    std::vector<Point3D> secondCircle;
    std::vector<Point3D> vertexShader;
    std::vector<Triangle> Triangles;

    Point3D FirstCenter;
    Point3D SecondCenter;
    edges Edges;
    QColor ObjectColor;
    int index = 0;
};

#endif // CONE_H
