#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <cmath>
#include <QtCore>

#include "rocket.h"
#include "camera.h"
#include "transfor_matrix.h"
#include "point3d.h"
#include "basedrawer.h"
#include "cone.h"
#include "triangle.h"
#include "edges.h"
#include "vector.h"
#include "fire.h"

#define WIDTH  850
#define HEIGHT  715



struct BarycentricCoords
{
    double b1;
    double b2;
    double b3;
};

struct DepthBuffer
{
    double *zbuffer = new double[WIDTH * HEIGHT];
    void fillbuffer()
    {
        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            zbuffer[i] = -10000;
        }
    }
};



class PaintWidget : public QWidget
{

    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = nullptr);

    void drawCone(Cone &_cone);
    void drawRocket(rocket &_rocket);
    void drawLine3D(Point3D first, Point3D second);
    void drawLaunchPad(Point3D point);
    void drawTriangleEdge(Point3D a, Point3D b, Point3D c);

    void rotateCamera(Point3D &point);
    void PerspectiveProjection(Point3D &point);

    void SetCameraAngleS(int angleX, int angleY, int angleZ);
    void fillObject(Point3D A, Point3D B, Point3D C);
    void changeCameraPos(Point3D &cameraView);
    void changeVisCamera(double x, double y, double z);
    void clear();
    void ComputeBarycentric(Point3D A, Point3D B, Point3D C, Point3D P, double square);
    void makeFire();
    bool isTriangleVisible(Point3D A, Point3D B, Point3D C);
    QColor ambientLightning(Point3D A, Point3D B, Point3D C, QColor objColor);
    Camera _camera;
    Camera _visibleCamera;
    std::vector<Triangle> trianglesOnImage;
    DepthBuffer ZBuffer;
    BarycentricCoords BarCoor;
    QPainter *painter;
    fire RocketFire;
    Point3D lightPoint;
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:

    QImage *image;
    int widget_height;
    int widget_width;
    QColor borders_color;
    QColor fill_color;
    QColor bg_color;
    QColor lightColor;




};


#endif // DRAWWIDGET_H
