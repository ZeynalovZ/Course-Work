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


class PaintWidget : public QWidget
{

    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = nullptr);

    void drawCone(Cone &_cone);
    void drawRocket(rocket &_rocket, Point3D CameraPosition);
    void drawLine3D(Point3D first, Point3D second);
    void PerspectiveProjection(Point3D &point);
    void SetCameraAngleS(int angleX, int angleY, int angleZ);
    void clear();
    Camera _camera;

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
    QPainter *painter;

};

#endif // DRAWWIDGET_H
