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
#include "color.h"
#include "zbuffer.h"
#include <thread>
#include <chrono>

#define WIDTH  850
#define HEIGHT  715

enum drawDirect {forward, back};


struct BarycentricCoords
{
    double b1;
    double b2;
    double b3;
};


struct threadParams
{
    double xmax;
    double xmin;
    double ymax;
    double ymin;
    double square;
};

class PaintWidget : public QWidget
{

    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = nullptr);

    void drawCone(Cone &_cone);
    void drawRocket(rocket &_rocket);
    void drawLine3D(Point3D first, Point3D second);
    void drawLaunchPad(Point3D point, int n);
    void drawTriangleEdge(Point3D a, Point3D b, Point3D c);
    void computeVertexNormals(Point3D A, Point3D B, Point3D C);

    void rotateCamera(Point3D &point);
    void rotateInversedCamera(Point3D &point);
    void rotateLight(Point3D &point);
    void PerspectiveProjection(Point3D &point, drawDirect d);
    void findLightAngles(Point3D &P);

    void SetCameraAngleS(int angleX, int angleY, int angleZ);
    void fillObject(Point3D A, Point3D B, Point3D C);
    void renderBuffer(Point3D A, Point3D B, Point3D C, threadParams params);
    void fillShadowBuffer(Point3D A, Point3D B, Point3D C);
    void drawShadow(Point3D P);
    void changeCameraPos(Point3D &cameraView);
    void changeVisCamera(double x, double y, double z);
    void clear();
    void ComputeBarycentric(Point3D A, Point3D B, Point3D C, Point3D P, double square, BarycentricCoords &BarCoor);
    void makeFire();
    bool isTriangleVisible(Point3D A, Point3D B, Point3D C, Point3D visiblePoint);
    QColor ambientLightning(Point3D A, Point3D B, Point3D C, QColor objColor, Point3D LightPoint);
    QColor getColor(Vector normal, QColor objColor, Point3D LightPoint);

    Camera _camera;
    Camera _visibleCamera;
    std::vector<Triangle> trianglesOnImage;
    DepthBuffer ZBuffer;
    DepthBuffer ZBufferShadows;
    //BarycentricCoords BarCoor;
    QPainter *painter;
    fire RocketFire;
    Camera lightSource;
    Point3D lightPoint;
    double WindowAspectRatio;
    int x_down = 200, y_down = 200;
    std::vector<Vector> vertexNormals;
    std::vector<double> vertexIntensity;

    Point3D CameraPosition;
    Vector vUp;
    Vector vFront;
    //LookAt camera;
    Point3D firePoint;

    bool fillShadow = true;
    QColor lightColor;
    double res_time = 0;

    // matrixes
    std::shared_ptr<Matrix> matrixInvX;
    std::shared_ptr<Matrix> matrixInvY;
    std::shared_ptr<Matrix> matrixInvZ;
    std::shared_ptr<Matrix> matrixLightX;
    std::shared_ptr<Matrix> matrixLightY;
    std::shared_ptr<Matrix> matrixLightZ;
    std::shared_ptr<Matrix> matrixCameraX;
    std::shared_ptr<Matrix> matrixCameraY;
    std::shared_ptr<Matrix> matrixCameraZ;

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

    QColor ambient;
    QColor Specular;
    QColor resultColor;




};


static QVector<QRgb> Palette = {
    qRgb(0x07,0x07,0x07),
    qRgb(0x1F,0x07,0x07),
    qRgb(0x2F,0x0F,0x07),
    qRgb(0x47,0x0F,0x07),
    qRgb(0x57,0x17,0x07),
    qRgb(0x67,0x1F,0x07),
    qRgb(0x77,0x1F,0x07),
    qRgb(0x8F,0x27,0x07),
    qRgb(0x9F,0x2F,0x07),
    qRgb(0xAF,0x3F,0x07),
    qRgb(0xBF,0x47,0x07),
    qRgb(0xC7,0x47,0x07),
    qRgb(0xDF,0x4F,0x07),
    qRgb(0xDF,0x57,0x07),
    qRgb(0xDF,0x57,0x07),
    qRgb(0xD7,0x5F,0x07),
    qRgb(0xD7,0x5F,0x07),
    qRgb(0xD7,0x67,0x0F),
    qRgb(0xCF,0x6F,0x0F),
    qRgb(0xCF,0x77,0x0F),
    qRgb(0xCF,0x7F,0x0F),
    qRgb(0xCF,0x87,0x17),
    qRgb(0xC7,0x87,0x17),
    qRgb(0xC7,0x8F,0x17),
    qRgb(0xC7,0x97,0x1F),
    qRgb(0xBF,0x9F,0x1F),
    qRgb(0xBF,0x9F,0x1F),
    qRgb(0xBF,0xA7,0x27),
    qRgb(0xBF,0xA7,0x27),
    qRgb(0xBF,0xAF,0x2F),
    qRgb(0xB7,0xAF,0x2F),
    qRgb(0xB7,0xB7,0x2F),
    qRgb(0xB7,0xB7,0x37),
    qRgb(0xCF,0xCF,0x6F),
    qRgb(0xDF,0xDF,0x9F),
    qRgb(0xEF,0xEF,0xC7),
    qRgb(0xFF,0xFF,0xFF),
    qRgb(0x0C, 0xC4, 0xFF)
};




#endif // DRAWWIDGET_H
