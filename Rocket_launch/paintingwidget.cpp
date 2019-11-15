#include "paintingwidget.h"
#include "triangle.h"
#include <QDebug>
#include "fire.h"


#define X_SIZE  850 / 2
#define Y_SIZE  715 / 2
#define EPS 0.00001


PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    widget_width = 850;
    widget_height = 715;
    bg_color = Qt::white;
    borders_color = Qt::black;
    fill_color = Qt::blue;
    image = new QImage(widget_width, widget_height, QImage::Format_RGB32);
    image->fill(bg_color);
    setGeometry(20, 20, widget_width, widget_height);
    painter = new QPainter(image);

    //fillAutoZBuffer(ZBuffer);
}

void change(Point3D &point)
{
    point.changeAll(point.x() + X_SIZE, point.y() + Y_SIZE, point.z());
}

void PaintWidget::drawCone(Cone &_cone)
{
    int angleX = _cone.currentAngleX;
    int angleY = _cone.currentAngleY;
    painter->setRenderHint(QPainter::Antialiasing, true);
    for (auto &triangle : _cone.Triangles)
    {
        Point3D tmp1 = triangle.A;
        Point3D tmp2 = triangle.B;
        Point3D tmp3 = triangle.C;

//        qDebug() << tmp1.x() << tmp2.x() << tmp3.x() << "x";
//        qDebug() << tmp1.y() << tmp2.y() << tmp3.y() << "y";
        tmp1.rotateX(angleX);
        tmp2.rotateX(angleX);
        tmp3.rotateX(angleX);

        tmp1.rotateY(angleY);
        tmp2.rotateY(angleY);
        tmp3.rotateY(angleY);

        PerspectiveProjection(tmp1);
        PerspectiveProjection(tmp2);
        PerspectiveProjection(tmp3);
        painter->setPen(_cone.ObjectColor);
        fillObject(tmp1, tmp2, tmp3);

        //ComputeBarycentric(tmp1, tmp2, tmp3);
//        painter->drawLine(tmp1.x() + X_SIZE, tmp1.y() + Y_SIZE,
//                          tmp2.x() + X_SIZE, tmp2.y() + Y_SIZE);

//        painter->drawLine(tmp2.x() + X_SIZE, tmp2.y() + Y_SIZE,
//                          tmp3.x() + X_SIZE, tmp3.y() + Y_SIZE);
//        painter->drawLine(tmp1.x() + X_SIZE, tmp1.y() + Y_SIZE,
//                          tmp3.x() + X_SIZE, tmp3.y() + Y_SIZE);
        //Triangle triangleOnImageTmp(tmp1, tmp2, tmp3);
        //trianglesOnImage.push_back(triangleOnImageTmp);

        /*
        triangle.A.rotateX(angleX);
        triangle.B.rotateX(angleX);
        triangle.C.rotateX(angleX);

        triangle.A.rotateY(angleY);
        triangle.B.rotateY(angleY);
        triangle.C.rotateY(angleY);

        PerspectiveProjection(triangle.A);
        PerspectiveProjection(triangle.B);
        PerspectiveProjection(triangle.C);

        painter->drawLine(triangle.A.x() + X_SIZE, triangle.A.y() + Y_SIZE,
                          triangle.B.x() + X_SIZE, triangle.B.y() + Y_SIZE);

        painter->drawLine(triangle.B.x() + X_SIZE, triangle.B.y() + Y_SIZE,
                          triangle.C.x() + X_SIZE, triangle.C.y() + Y_SIZE);

        painter->drawLine(triangle.C.x() + X_SIZE, triangle.C.y() + Y_SIZE,
                          triangle.A.x() + X_SIZE, triangle.A.y() + Y_SIZE);
        */
    }
    update();
}

void PaintWidget::drawRocket(rocket &_rocket, Point3D CameraPosition)
{
    _camera.setPosition(CameraPosition);


    for (int i = 0; i < _rocket.modules.size(); i++)
    {
        _rocket.modules[i].currentAngleX = _rocket.angleX;
        _rocket.modules[i].currentAngleY = _rocket.angleY;
        _rocket.modules[i].currentAngleZ = _rocket.angleZ;
        drawCone(_rocket.modules[i]);
    }

}

void PaintWidget::drawLine3D(Point3D first, Point3D second)
{
    PerspectiveProjection(first);
    PerspectiveProjection(second);
    painter->drawLine(first.x() + X_SIZE, first.y() + Y_SIZE, second.x() + X_SIZE, second.y() + Y_SIZE);
    update();
}

void PaintWidget::drawLaunchPad(Point3D point)
{
    Cone cone;
    cone.createCone(point, 100, 100, 50, 4, QColor(Qt::darkCyan));
    drawCone(cone);
}

void PaintWidget::PerspectiveProjection(Point3D &point)
{
    auto cam_pos = _camera.getPosition();
    std::shared_ptr<Matrix> transform_matrix(new MoveMatrix(-cam_pos.x(), -cam_pos.y(), 0));
    point.transform(transform_matrix);
    transform_matrix.reset(new RotateOxMatrix(-_camera.getXAngle() * M_PI / TO_RAD_180));
    point.transform(transform_matrix);
    transform_matrix.reset(new RotateOyMatrix(-_camera.getYAngle() * M_PI / TO_RAD_180));
    point.transform(transform_matrix);
    transform_matrix.reset(new RotateOzMatrix(-_camera.getZAngle() * M_PI / TO_RAD_180));
    point.transform(transform_matrix);

    double eps = 1e-10;
    double znam = point.z() + cam_pos.z();
    if (znam < eps && znam > -eps) {
        znam = eps;
    }
    double distCoef = cam_pos.z() / znam;
    point.setX(point.x() * distCoef);
    point.setY(point.y() * distCoef);
}

void PaintWidget::SetCameraAngleS(int angleX, int angleY, int angleZ)
{
    _camera.setXAngle(angleX);
    _camera.setYAngle(angleY);
    _camera.setZAngle(angleZ);

}

double getMaxFor3(double x1, double x2, double x3)
{
    double max = x1;
    if (x1 >= x2 && x1 >= x3)
    {
        max = x1;
    }
    if (x2 >= x1 && x2 >= x3)
    {
        max = x2;
    }
    if (x3 >= x2 && x3 >= x1)
    {
        max = x3;
    }
    return max;
}

double getMinFor3(double x1, double x2, double x3)
{
    double min = x1;
    if (x1 <= x2 && x1 <= x3)
    {
        min = x1;
    }
    if (x2 <= x1 && x2 <= x3)
    {
        min = x2;
    }
    if (x3 <= x2 && x3 <= x1)
    {
        min = x3;
    }
    return min;
}



void sortPointsY(Point3D &A, Point3D &B, Point3D &C)
{
    Point3D points[3];
    points[0] = A;
    points[1] = B;
    points[2] = C;

    Point3D temp;

    // Сортировка массива пузырьком
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i - 1; j++) {
            if (points[j].y() >= points[j + 1].y())
            {
                // меняем элементы местами
                temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
            }
        }
    }
    C = points[0];
    A = points[1];
    B = points[2];
}
void sortPointsX(Point3D &A, Point3D &B, Point3D &C)
{
    Point3D points[3];
    points[0] = A;
    points[1] = B;
    points[2] = C;

    Point3D temp;

    // Сортировка массива пузырьком
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i - 1; j++) {
            if (points[j].x() >= points[j + 1].x())
            {
                // меняем элементы местами
                temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
            }
        }
    }
    A = points[0];
    B = points[1];
    C = points[2];
}

void PaintWidget::fillObject(Point3D A, Point3D B, Point3D C)
{

    change(A);
    change(B);
    change(C);

    double x1 = A.x();
    double x2 = B.x();
    double x3 = C.x();
    double y1 = A.y();
    double y2 = B.y();
    double y3 = C.y();
    A.setZ(1 / A.z());
    B.setZ(1 / B.z());
    C.setZ(1 / C.z());

    double xmax, xmin, ymax, ymin, z;
    xmax = getMaxFor3(x1, x2, x3);
    xmin = getMinFor3(x1, x2, x3);
    ymax = getMaxFor3(y1, y2, y3);
    ymin = getMinFor3(y1, y2, y3);

    //qDebug() << xmin << xmax << ymin << ymax << "BB";
    Point3D P;
    double square = (A.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - A.x());
//    if (square < EPS && square > -EPS)
//    {
//        qDebug() << square;
//        qDebug() << A.x() - X_SIZE << B.x() - X_SIZE << C.x() - X_SIZE << "x";
//        qDebug() << A.y() - Y_SIZE << B.y() - Y_SIZE << C.y() - Y_SIZE << "y";
//    }
    for (int y = int(ymin); y <= int(ymax); y++)
    {
        for (int x = int(xmin); x <= int(xmax); x++)
        {
            // third num has no effect. Then x, y, 0
            P.changeAll(x, y, 0);
            ComputeBarycentric(A, B, C, P, square);
            if (BarCoor.b1 >= 0 && BarCoor.b1 <= 1 && BarCoor.b2 >= 0 && BarCoor.b2 <= 1 &&
                    BarCoor.b3 >= 0 && BarCoor.b3 <=1)
            {
                z = 1 / (BarCoor.b1 * A.z() + BarCoor.b2 * B.z() + BarCoor.b3 * C.z());
                if (x + y * WIDTH >= 0 && x + y * WIDTH < WIDTH * HEIGHT)
                {
                    if (z > ZBuffer.zbuffer[x + y * WIDTH])
                    {
                        ZBuffer.zbuffer[x + y * WIDTH] = z;
                        painter->drawPoint(x, y);
                    }
                }
                else
                {
                    //qDebug() << "out of range";
                }

            }
            else
            {
                //qDebug() << BarCoor.b1 << BarCoor.b2 << BarCoor.b3 << "bar";
            }
        }
    }

    painter->setPen(QColor(Qt::black));
}



void PaintWidget::clear()
{
    image->fill(bg_color);
    //trianglesOnImage.clear();
}

void sortPoints(Point3D &A, Point3D &B, Point3D &C)
{
    for (int i = 0; i < 3; i++)
    {
        if (A.x() <= B.x() && B.x() <= C.x())
            if (A.y() <= B.y() && B.y() <= C.y())
            {
                ;
            }
    }



}

void PaintWidget::ComputeBarycentric(Point3D A, Point3D B, Point3D C, Point3D P, double square)
{
    // вынести вычисление площади, а тут добавить аргумент функции
    if (square > EPS || square < EPS)
    {
        BarCoor.b1 = (P.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - P.x());
        BarCoor.b1 /= square;
        BarCoor.b2 = (P.y() - A.y()) * (C.x() - A.x()) + (C.y() - A.y()) * (A.x() - P.x());
        BarCoor.b2 /= square;
        BarCoor.b3 = 1. - BarCoor.b1 - BarCoor.b2;
    }
    else
    {
        BarCoor.b1 = -1;
    }
}
void PaintWidget::makeFire()
{

    //painter->drawImage(0, 0, RocketFire.framebuffer);

    RocketFire.update();
    update();
    //RocketFire.update();

}


void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    QPainter painter(image);
    painter.setPen(borders_color);

    update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{

    update();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
    Q_UNUSED(event);
}
