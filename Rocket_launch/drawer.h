#ifndef DRAWER_H
#define DRAWER_H
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include "camera.h"
#include "point3d.h"
#include "cone.h"
#include "rocket.h"
#include "transfor_matrix.h"
#include "basedrawer.h"


class Drawer : public QWidget
{

    Q_OBJECT

public:
    explicit Drawer(QWidget *parent = nullptr);

    void drawCone(Cone &_cone, QPainter &painter);
    void drawRocket(rocket &_rocket, Point3D CameraPosition, QPainter &painter);
    void drawLine3D(Point3D first, Point3D second, QPainter &painter);
    void PerspectiveProjection(Point3D &point);
    void SetCameraAngleS(int angleX, int angleY, int angleZ);
    void MoveRocket();

    //void init(int WIDTH, int HEIGHT);
    Camera _camera;

    QImage *image;
protected:
    void paintEvent(QPaintEvent *event);


};
#endif // DRAWER_H
