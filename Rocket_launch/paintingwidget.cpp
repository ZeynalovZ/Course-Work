#include "paintingwidget.h"
#include "triangle.h"
#include <QDebug>
#include "fire.h"


#define X_SIZE  850 / 2
#define Y_SIZE  715 / 2
#define EPS 0.00001

void printPoints1(Point3D tmp1, Point3D tmp2, Point3D tmp3)
{
    qDebug() << tmp1.x() << tmp1.y() << tmp1.z();
    qDebug() << tmp2.x() << tmp2.y() << tmp2.z();
    qDebug() << tmp3.x() << tmp3.y() << tmp3.z();
    qDebug() << "==============================";
}

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    widget_width = 850;
    widget_height = 715;
    bg_color = Qt::black;
    borders_color = Qt::black;
    fill_color = Qt::blue;
    lightColor = Qt::yellow;
    image = new QImage(widget_width, widget_height, QImage::Format_RGB32);
    image->fill(bg_color);
    setGeometry(20, 20, widget_width, widget_height);
    painter = new QPainter(image);
    //_visibleCamera.setCameraPos(Point3D(0, 0, -1000));
    //_visibleCamera.changeAll(0, 0, 1000);
    //fillAutoZBuffer(ZBuffer);
    Vector V1(1, 1, 1);
    Vector V2(4, 6, 11);
    Point3D P(0, 0, -1000);
    LookAt camera(P, V1, V2);
    printTransformedMatrix(camera);
    lightPoint = Point3D(0, 0, 1000);
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
    //changeCameraPos(_visibleCamera);
    //Point3D camPos = _visibleCamera.getPosition();
    //qDebug() << camPos.x() << camPos.y() << camPos.z() << _visibleCamera.getXAngle() << _visibleCamera.getYAngle() << _visibleCamera.getZAngle();
    //qDebug() << _cone.Triangles.size() << " size";
    //qDebug() << V.x << V.y << V.z << "is result";
    for (auto &triangle : _cone.Triangles)
    {
        Point3D tmp1 = triangle.A;
        Point3D tmp2 = triangle.B;
        Point3D tmp3 = triangle.C;

        //printPoints1(tmp1, tmp2, tmp3);

        tmp1.rotateX(angleX);
        tmp2.rotateX(angleX);
        tmp3.rotateX(angleX);

        tmp1.rotateY(angleY);
        tmp2.rotateY(angleY);
        tmp3.rotateY(angleY);

        rotateCamera(tmp1);
        rotateCamera(tmp2);
        rotateCamera(tmp3);

        PerspectiveProjection(tmp1);
        PerspectiveProjection(tmp2);
        PerspectiveProjection(tmp3);


        // Перед растеризацией, сделаем проверку на лицевые грани
        bool triangleIsVisible = isTriangleVisible(tmp1, tmp2, tmp3);
        //bool triangleIsVisible = true;
        if (triangleIsVisible == true)
        {
            QColor ambient = ambientLightning(tmp1, tmp2, tmp3, _cone.ObjectColor);
            qDebug() << ambient << "ambient";
            painter->setPen(ambient);
            //drawTriangleEdge(tmp1, tmp2, tmp3);
            fillObject(tmp1, tmp2, tmp3);
        }
        else
        {
            // do nothing
        }
    }

    update();
}

void PaintWidget::drawRocket(rocket &_rocket)
{


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
    //PerspectiveProjection(first);
    rotateCamera(first);
    rotateCamera(second);
    //PerspectiveProjection(second);
    painter->drawLine(first.x() + X_SIZE, first.y() + Y_SIZE, second.x() + X_SIZE, second.y() + Y_SIZE);
    update();
}

void PaintWidget::drawLaunchPad(Point3D point)
{
    Cone cone;
    cone.createCone(point, 300, 300, 50, 5, QColor(Qt::white));
    drawCone(cone);
}

void PaintWidget::drawTriangleEdge(Point3D a, Point3D b, Point3D c)
{
    painter->drawLine(a.x() + X_SIZE, a.y() + Y_SIZE, b.x() + X_SIZE, b.y() + Y_SIZE);
    painter->drawLine(b.x() + X_SIZE, b.y() + Y_SIZE, c.x() + X_SIZE, c.y() + Y_SIZE);
    painter->drawLine(c.x() + X_SIZE, c.y() + Y_SIZE, a.x() + X_SIZE, a.y() + Y_SIZE);
}

void PaintWidget::rotateCamera(Point3D &point)
{
    auto cam_pos = _camera.getPosition();
    std::shared_ptr<Matrix> transform_matrix(new MoveMatrix(-cam_pos.x(), -cam_pos.y(), 0));
    point.transform(transform_matrix);
    transform_matrix.reset(new RotateOxMatrix(_camera.getXAngle() * M_PI / TO_RAD_180));
    point.transform(transform_matrix);
    transform_matrix.reset(new RotateOyMatrix(_camera.getYAngle() * M_PI / TO_RAD_180));
    point.transform(transform_matrix);
    transform_matrix.reset(new RotateOzMatrix(_camera.getZAngle() * M_PI / TO_RAD_180));
    point.transform(transform_matrix);

}

void PaintWidget::PerspectiveProjection(Point3D &point)
{
    auto cam_pos = _camera.getPosition();
    double eps = 1e-10;
    double znam = 1 - point.z() / cam_pos.z();
    //qDebug() << cam_pos.x() << cam_pos.y() << cam_pos.z() << "cam pos";
    if (znam < eps && znam > -eps) {
        znam = eps;
    }
    //double distCoef = cam_pos.z() / znam;
    point.setX(point.x() / znam);
    point.setY(point.y() / znam);
}

void PaintWidget::changeCameraPos(Point3D &cameraView)
{
    Point3D cam_pos = _visibleCamera.getPosition();
    //qDebug() << cam_pos.x() << cam_pos.y() << cam_pos.z() << "cam pos";
    //qDebug() << _camera.getXAngle() << _camera.getYAngle() << _camera.getZAngle() << "cam angles";

    std::shared_ptr<Matrix> transform_matrix(new MoveMatrix(0, 0, 0));
    cameraView.transform(transform_matrix);
    transform_matrix.reset(new RotateOxMatrix(_camera.getXAngle() * M_PI / TO_RAD_180));
    cameraView.transform(transform_matrix);
    transform_matrix.reset(new RotateOyMatrix(_camera.getYAngle() * M_PI / TO_RAD_180));
    cameraView.transform(transform_matrix);
    transform_matrix.reset(new RotateOzMatrix(_camera.getZAngle() * M_PI / TO_RAD_180));
    cameraView.transform(transform_matrix);

//    cameraView.setPosition(cam_pos);
//    cameraView.setXAngle(_camera.getXAngle());
//    cameraView.setYAngle(_camera.getYAngle());
//    cameraView.setZAngle(_camera.getZAngle());

}

void PaintWidget::changeVisCamera(double x, double y, double z)
{
//    qDebug() << _visibleCamera.x() << _visibleCamera.y() << _visibleCamera.z();
//    std::shared_ptr<Matrix> transform_matrix((new RotateOxMatrix(-x * M_PI / TO_RAD_180)));
//    _visibleCamera.transform(transform_matrix);
//    qDebug() << _visibleCamera.x() << _visibleCamera.y() << _visibleCamera.z() << " ==== 1";
//    transform_matrix.reset(new RotateOyMatrix(-y * M_PI / TO_RAD_180));
//    _visibleCamera.transform(transform_matrix);
//    qDebug() << _visibleCamera.x() << _visibleCamera.y() << _visibleCamera.z() << " ==== 2";
//    transform_matrix.reset(new RotateOzMatrix(-z * M_PI / TO_RAD_180));
//    _visibleCamera.transform(transform_matrix);
//    qDebug() << _visibleCamera.x() << _visibleCamera.y() << _visibleCamera.z() << " ==== 3";

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
    A.setZ(1. / A.z());
    B.setZ(1. / B.z());
    C.setZ(1. / C.z());
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
                //qDebug() << A.z() << B.z() << C.z() << BarCoor.b1 << BarCoor.b2 << BarCoor.b3 << z << "====";
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
    if (square > EPS || square < -EPS)
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

bool PaintWidget::isTriangleVisible(Point3D A, Point3D B, Point3D C)
{
    Vector V1(A, B);
    Vector V2(B, C);
    Vector Vn = crossProduct(V1, V2);
    Vn.normalize();

    Point3D CameraPos = _camera.getPosition();
    //changeCameraPos(CameraPos);
    // позиция камеры
    //qDebug() << CameraPos.x() << CameraPos.y() << CameraPos.z();
    Point3D Null(0, 0, 0);
    Vector CameraVector(Null, CameraPos);
    CameraVector.normalize();
    //qDebug() << CameraVector.x << CameraVector.y << CameraVector.z;

    double result = crossProductScalar(CameraVector, Vn);
    //qDebug() << result << "result of scalar";
    if (result <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

QColor PaintWidget::ambientLightning(Point3D A, Point3D B, Point3D C, QColor objColor)
{
    Vector V1(A, B);
    Vector V2(B, C);
    Vector Vn = crossProduct(V1, V2);
    Vn.normalize();

//    qDebug() << Vn.x << Vn.y << Vn.z << "Vn";
//    qDebug() << lightPoint.x() << lightPoint.y() << lightPoint.z() << "lightpos";

    Point3D Null(0, 0, 0);
    Vector lightVector(lightPoint, Null);
    lightVector.normalize();
    //qDebug() << CameraVector.x << CameraVector.y << CameraVector.z;

    double intensity = crossProductScalar(lightVector, Vn);
//    qDebug() << intensity << "intensity";
    QColor tmp = objColor;
    tmp.setAlphaF(intensity);
    return  tmp;


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
