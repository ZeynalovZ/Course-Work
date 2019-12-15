#include "paintingwidget.h"
#include "triangle.h"
#include <QDebug>
#include <QtGlobal>
#include "fire.h"


#define X_SIZE  850 / 2
#define Y_SIZE  715 / 2
#define W_WIDTH 850
#define W_HEIGHT 715
#define AMBIENT 0.2
#define SPECULARSTRENGHT 0.5


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
    //bg_color = Qt::black;
    bg_color.setRed(12);
    bg_color.setGreen(196);
    bg_color.setBlue(255);
    borders_color = Qt::black;
    fill_color = Qt::blue;
    lightColor = Qt::yellow;
    image = new QImage(widget_width, widget_height, QImage::Format_RGB32);
    image->fill(QColor(Qt::black));
    setGeometry(20, 20, widget_width, widget_height);
    painter = new QPainter(image);
    //_visibleCamera.setCameraPos(Point3D(0, 0, -1000));
    //_visibleCamera.changeAll(0, 0, 1000);
    //fillAutoZBuffer(ZBuffer);
    CameraPosition.changeAll(0, 0, 1000);
    //    Vector vUp(0, 0, 1);
    //    Vector vFront(Point3D(0, 0, 0), CameraPosition);
    //    camera = LookAt(CameraPosition, vUp, vFront);
    //printTransformedMatrix(camera);
    lightPoint = Point3D(0, 1000, 1000);
    lightSource.setPosition(lightPoint);
    lightSource.setXAngle(45); // or -50
    WindowAspectRatio = widget_width / widget_height;
    fillShadow = false;
    //image->setColorTable(Palette);
    findLightAngles(lightPoint);
    firePoint.changeAll(X_SIZE - 37, Y_SIZE, 10000);

    qDebug() << WindowAspectRatio << "is Window aspect ratio";
}

void change(Point3D &point)
{
    //double screenx = point.x() * W_WIDTH / 2 + X_S;
    // i don't know why i need to sum z coordinate, but i will fix it
    // small spoiler           coordinate z is null in computing z what's why
    point.changeAll(point.x() + X_SIZE, point.y() + Y_SIZE, point.z() + 10000);
}


void PaintWidget::drawCone(Cone &_cone)
{
    int angleX = _cone.currentAngleX;
    int angleY = _cone.currentAngleY;
    //painter->setRenderHint(QPainter::Antialiasing, true);
    Point3D tmp1, tmp2, tmp3;
    Point3D stmp1, stmp2, stmp3;
    int pointIndex1, pointIndex2, pointIndex3;
    bool triangleIsVisible, triangleIsVisibleForLight;
    Point3D tmpLight = lightSource.getPosition();
    rotateCamera(tmpLight);
    //findLightAngles(tmpLight);
    //rotateLight(tmpLight);
    //вычисление усредненных нормелей
//    vertexNormals.clear();
//    for (int i = 0; i < _cone.vertexShader.size(); i++)
//    {
//        vertexNormals.push_back(Vector());
//    }


//    for (auto &triangle : _cone.Triangles)
//    {
//        //qDebug() << triangle.A.triangleIndexes.size() << "size";
//        tmp1 = triangle.A;
//        tmp2 = triangle.B;
//        tmp3 = triangle.C;
//        computeVertexNormals(tmp1, tmp2, tmp3);
//    }
//    for (int i = 0; i < vertexNormals.size(); i++)
//    {
//        vertexNormals[i].normalize();
//        //qDebug() << vertexNormals[i].x << vertexNormals[i].y << vertexNormals[i].z << "vertex normals";
//    }

    for (auto &triangle : _cone.Triangles)
    {
        //qDebug() << triangle.A.triangleIndexes.size() << "size";
        tmp1 = triangle.A;
        tmp2 = triangle.B;
        tmp3 = triangle.C;
        //        qDebug() << tmp1.pointIndex << "point index A";
        //        qDebug() << tmp2.pointIndex << "point index B";
        //        qDebug() << tmp3.pointIndex << "point index C";
        //printPoints1(tmp1, tmp2, tmp3);
        tmp1.rotateX(angleX);
        tmp2.rotateX(angleX);
        tmp3.rotateX(angleX);

        tmp1.rotateY(angleY);
        tmp2.rotateY(angleY);
        tmp3.rotateY(angleY);

        pointIndex1 = tmp1.pointIndex;
        pointIndex2 = tmp2.pointIndex;
        pointIndex3 = tmp3.pointIndex;

        rotateCamera(tmp1);
        rotateCamera(tmp2);
        rotateCamera(tmp3);

        if (fillShadow == true)
        {
            //qDebug() << lightSource.getXAngle() << lightSource.getYAngle() << lightSource.getZAngle() << "light";
            stmp1 = triangle.A;
            stmp2 = triangle.B;
            stmp3 = triangle.C;

            stmp1.rotateX(angleX);
            stmp2.rotateX(angleX);
            stmp3.rotateX(angleX);

            stmp1.rotateY(angleY);
            stmp2.rotateY(angleY);
            stmp3.rotateY(angleY);

            rotateLight(stmp1);
            rotateLight(stmp2);
            rotateLight(stmp3);

            PerspectiveProjection(stmp1, forward);
            PerspectiveProjection(stmp2, forward);
            PerspectiveProjection(stmp3, forward);
            //            stmp1.transform(matrixInvX);
            //            stmp2.transform(matrixInvY);
            //            stmp3.transform(matrixInvZ);


            fillShadowBuffer(stmp1, stmp2, stmp3);
//            std::thread tr1(PaintWidget::fillShadowBuffer, this, stmp1, stmp2, stmp3);
//            tr1.join();
            //            triangleIsVisibleForLight = isTriangleVisible(stmp1, stmp2, stmp3, lightSource.getPosition());
            //            if (triangleIsVisibleForLight == false)
            //            {
            //               fillShadowBuffer(stmp1, stmp2, stmp3);
            //            painter->setPen(QColor(Qt::red));

            //            }
        }
        //        painter->setPen(QColor(Qt::red));
        //        drawTriangleEdge(stmp1, stmp2, stmp3);

        if (tmp1.z() <= 1000 && tmp2.z() <= 1000 && tmp3.z() <= 1000)
        {
            PerspectiveProjection(tmp1, forward);
            PerspectiveProjection(tmp2, forward);
            PerspectiveProjection(tmp3, forward);
            //qDebug() << tmp1.w() << tmp2.w() << tmp3.w() << "temp";

            tmp1.pointIndex = pointIndex1;
            tmp2.pointIndex = pointIndex2;
            tmp3.pointIndex = pointIndex3;

            // Перед растеризацией, сделаем проверку на лицевые грани
            triangleIsVisible = isTriangleVisible(tmp1, tmp2, tmp3, _camera.getPosition());
            //bool triangleIsVisible = true;
            if (triangleIsVisible == true)
            {
                resultColor = ambientLightning(tmp1, tmp2, tmp3, _cone.ObjectColor, tmpLight);
                //qDebug() << ambient << "ambient";
    //            resultColor = QColor(Qt::white);
                painter->setPen(resultColor);
    //            drawTriangleEdge(tmp1, tmp2, tmp3);
                fillObject(tmp1, tmp2, tmp3);
            }
            else
            {
                // do nothing
            }
        }

    }

    update();
}


void PaintWidget::computeVertexNormals(Point3D A, Point3D B, Point3D C)
{
    Vector V1(A, B);
    Vector V2(B, C);
    Vector Vn = crossProduct(V1, V2);
    Vn.normalize();
    //qDebug() << Vn.x << Vn.y << Vn.z << "Vn";
    //qDebug() << vertexNormals[A.pointIndex].x << vertexNormals[A.pointIndex].y << vertexNormals[A.pointIndex].z << "before";
    vertexNormals[A.pointIndex].addVector(Vn);
    vertexNormals[B.pointIndex].addVector(Vn);
    vertexNormals[C.pointIndex].addVector(Vn);
    //qDebug() << vertexNormals[A.pointIndex].x << vertexNormals[A.pointIndex].y << vertexNormals[A.pointIndex].z << "after";
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

void PaintWidget::drawLaunchPad(Point3D point, int n)
{
    Cone cone;
    QColor LaunchPadColor;
    LaunchPadColor.setRed(154);
    LaunchPadColor.setGreen(255);
    LaunchPadColor.setBlue(154);
    cone.createCone(point, 300, 300, 50, n, LaunchPadColor);
    drawCone(cone);
}

void PaintWidget::drawTriangleEdge(Point3D a, Point3D b, Point3D c)
{
    //qDebug() << a.x() << b.x() << c.x() << "points";
    painter->drawLine(a.x() + X_SIZE, a.y() + Y_SIZE, b.x() + X_SIZE, b.y() + Y_SIZE);
    painter->drawLine(b.x() + X_SIZE, b.y() + Y_SIZE, c.x() + X_SIZE, c.y() + Y_SIZE);
    painter->drawLine(c.x() + X_SIZE, c.y() + Y_SIZE, a.x() + X_SIZE, a.y() + Y_SIZE);
}


void PaintWidget::rotateCamera(Point3D &point)
{
    auto cam_pos = _camera.getPosition();
    std::shared_ptr<Matrix> transform_matrix(new MoveMatrix(-cam_pos.x(), -cam_pos.y(), 0));
    point.transform(transform_matrix);
    if (_camera.getXAngle() != 0)
    {
        point.transform(matrixCameraX);
    }
    if (_camera.getYAngle() != 0)
    {
        point.transform(matrixCameraY);
    }

    if(_camera.getZAngle() != 0)
    {
        point.transform(matrixCameraZ);
    }
}

void PaintWidget::rotateInversedCamera(Point3D &point)
{
    auto cam_pos = _camera.getPosition();
    std::shared_ptr<Matrix> transform_matrix(new MoveMatrix(cam_pos.x(), cam_pos.y(), 0));
    point.transform(transform_matrix);
    if (_camera.getXAngle() != 0)
    {
        point.transform(matrixInvX);
    }
    if (_camera.getYAngle() != 0)
    {
        point.transform(matrixInvY);
    }

    if(_camera.getZAngle() != 0)
    {
        point.transform(matrixInvZ);
    }
}

void PaintWidget::rotateLight(Point3D &point)
{
    auto cam_pos = lightSource.getPosition();
    if (lightSource.getXAngle() != 0)
    {
        point.transform(matrixLightX);
    }
    if (lightSource.getYAngle() != 0)
    {
        point.transform(matrixLightY);
    }

    if (lightSource.getZAngle() != 0)
    {
        point.transform(matrixLightZ);
    }
}

void PaintWidget::PerspectiveProjection(Point3D &point, drawDirect d)
{
    auto cam_pos = _camera.getPosition();
    double eps = 1e-10;
    double znam = 1 - point.z() / cam_pos.z();
    //qDebug() << cam_pos.x() << cam_pos.y() << cam_pos.z() << "cam pos";
    if (znam < eps && znam > -eps) {
        znam = eps;
    }
    //double distCoef = cam_pos.z() / znam;
    if (d == forward)
    {
        point.setX(point.x() / znam);
        point.setY(point.y() / znam);
        //point.setW(znam);
    }
    else
    {
        point.setX(point.x() * znam);
        point.setY(point.y() * znam);
        //point.setW(znam);
    }

    //    double near = 20;
    //    double far = 120;
    //    double fovy = 90;
    //    std::shared_ptr<Matrix> transform_matrix(new perspectiveProjection(near, far, fovy, WindowAspectRatio));
    //    point.transform(transform_matrix);
}

void PaintWidget::findLightAngles(Point3D &P)
{
    //qDebug() << P.x() << P.y() << P.z() << "point";
    Vector vec_view(0, 0, -1);
    Vector vecProjX(0, -P.y(), -P.z());
    Vector vecProjY(-P.x(), 0, -P.z());
    Vector vecProjZ(-P.x(), -P.y(), 0);

    vecProjX.normalize();
    vecProjY.normalize();
    vecProjZ.normalize();
    double angleX = crossProductScalar(vec_view, vecProjX);
    double angleY = crossProductScalar(vec_view, vecProjY);
    double angleZ = crossProductScalar(vec_view, vecProjZ);
    //    angleX /= vecProjX.vectorLength();
    //    angleY /= vecProjY.vectorLength();
    //    angleZ /= vecProjZ.vectorLength();

    angleX = acos(angleX);
    angleY = acos(angleY);
    angleZ = acos(angleZ);

    angleX = angleX * TO_RAD_180 / M_PI;
    angleY = angleY * TO_RAD_180 / M_PI;
    angleZ = angleZ * TO_RAD_180 / M_PI;
    if (P.x() < 0)
    {
        angleY = -angleY;
    }
    if (P.y() < 0)
    {
        angleX = -angleX;
    }
    qDebug() << angleX << angleY << angleZ - 90 << "angles";
    lightSource.setXAngle(angleX);
    lightSource.setYAngle(-angleY);
    lightSource.setZAngle(angleZ - 90);
    matrixLightX.reset(new RotateOxMatrix(lightSource.getXAngle() * M_PI / TO_RAD_180));
    matrixLightY.reset(new RotateOyMatrix(lightSource.getYAngle() * M_PI / TO_RAD_180));
    matrixLightZ.reset(new RotateOzMatrix(lightSource.getZAngle() * M_PI / TO_RAD_180));
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
    ;
}


void PaintWidget::SetCameraAngleS(int angleX, int angleY, int angleZ)
{
    // TODO:
    // добавить проверку на углы > 30 и <30 для корректного отображения теней
    // добавить интерполяцию нормалей или интенсивностей
    _camera.setXAngle(angleX);
    _camera.setYAngle(angleY);
    _camera.setZAngle(angleZ);
    //fillShadow = true;
    //    lightSource.setXAngle(angleX);
    //    lightSource.setYAngle(angleY);
    //    lightSource.setZAngle(angleZ);

    matrixCameraX.reset(new RotateOxMatrix(-angleX * M_PI / TO_RAD_180));
    matrixCameraY.reset(new RotateOyMatrix(-angleY * M_PI / TO_RAD_180));
    matrixCameraZ.reset(new RotateOzMatrix(-angleZ * M_PI / TO_RAD_180));

    matrixInvX.reset(new RotateOxMatrix(angleX * M_PI / TO_RAD_180));
    matrixInvY.reset(new RotateOyMatrix(angleY * M_PI / TO_RAD_180));
    matrixInvZ.reset(new RotateOzMatrix(angleZ * M_PI / TO_RAD_180));

    //qDebug() << lightSource.getXAngle() << lightSource.getYAngle() << lightSource.getZAngle() << "light";


//    Point3D tmpLight = lightSource.getPosition();
//    //lightSource.setYAngle(angleY);
//    //qDebug() << tmpLight.x() << tmpLight.y() << "before";
//    rotateCamera(tmpLight);
    //qDebug() << tmpLight.x() << tmpLight.y() << "after";
    //findLightAngles(tmpLight);

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
    Vector aNormal = vertexNormals[A.pointIndex];
    Vector bNormal = vertexNormals[B.pointIndex];
    Vector cNormal = vertexNormals[C.pointIndex];
    Vector scanA, scanB, scanP;

    //qDebug() << aNormal.x << bNormal.x << cNormal.x << "normal";

    double x1 = A.x();
    double x2 = B.x();
    double x3 = C.x();
    double y1 = A.y();
    double y2 = B.y();
    double y3 = C.y();
    double xmax, xmin, ymax, ymin;
    xmax = getMaxFor3(x1, x2, x3);
    xmin = getMinFor3(x1, x2, x3);
    ymax = getMaxFor3(y1, y2, y3);
    ymin = getMinFor3(y1, y2, y3);
    //Point3D P, ShadowPoint;
    double square = (A.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - A.x());
    A.setZ(1. / A.z());
    B.setZ(1. / B.z());
    C.setZ(1. / C.z());
    threadParams params;
    params.ymax = ymax;
    params.ymin = ymin;
    params.square = square;
    std::vector<std::thread> threads(8);
    double xStart = xmin;
    double xStep = (xmax - xmin) / 8.0;
    //qDebug() << xStart << xStep;
    params.xmin = xStart;
    params.xmax = xmax;
    renderBuffer(A, B, C, params);
//    for (auto &thread : threads)
//    {
//        params.xmin = round(xStart);
//        params.xmax = round(xStart + xStep);
//        thread = std::thread(&PaintWidget::renderBuffer, this, A, B, C, params);
//        xStart += xStep;
//    }
//    for (auto &thread:threads)
//    {
//        thread.join();
//    }
}

void PaintWidget::renderBuffer(Point3D A, Point3D B, Point3D C, threadParams params)
{
    double z;
    Point3D P, ShadowPoint;
    BarycentricCoords BarCoor;
    for (int y = params.ymin; y <= params.ymax; y++)
    {
        for (int x = params.xmin; x <= params.xmax; x++)
        {
            P.changeAll(x, y, 0);
            ComputeBarycentric(A, B, C, P, params.square, BarCoor);
            if (BarCoor.b1 >= 0 && BarCoor.b2 >= 0 && BarCoor.b3 >= 0)
            {
                z = 1 / (BarCoor.b1 * A.z() + BarCoor.b2 * B.z() + BarCoor.b3 * C.z());
                if (x + y * WIDTH >= 0 && x + y * WIDTH < WIDTH * HEIGHT)
                {
                    if (z > ZBuffer.zbuffer[x + y * WIDTH])
                    {

                        ZBuffer.zbuffer[x + y * WIDTH] = z;
                        if (fillShadow == true)
                        {
                            ShadowPoint.changeAll(x - X_SIZE, y - Y_SIZE, z - 10000);
                            drawShadow(ShadowPoint);
                        }
                        painter->drawPoint(x, y);
                        //image->setPixelColor(x, y, resultColor);
                    }
                }
                else
                {
                }

            }
            else
            {
            }
        }
    }
}

void PaintWidget::fillShadowBuffer(Point3D A, Point3D B, Point3D C)
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
    Point3D P, ShadowPoint;
    double square = (A.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - A.x());
    A.setZ(1. / A.z());
    B.setZ(1. / B.z());
    C.setZ(1. / C.z());
    BarycentricCoords BarCoor;
    for (int y = int(ymin); y <= int(ymax); y++)
    {
        for (int x = int(xmin); x <= int(xmax); x++)
        {
            // third num has no effect. Then x, y, 0
            P.changeAll(x, y, 0);
            ComputeBarycentric(A, B, C, P, square, BarCoor);
            if (BarCoor.b1 >= 0 && BarCoor.b1 <= 1 && BarCoor.b2 >= 0 && BarCoor.b2 <= 1 &&
                    BarCoor.b3 >= 0 && BarCoor.b3 <=1)
            {

                z = 1 / (BarCoor.b1 * A.z() + BarCoor.b2 * B.z() + BarCoor.b3 * C.z());
                //qDebug() << A.z() << B.z() << C.z() << BarCoor.b1 << BarCoor.b2 << BarCoor.b3 << z << "====";
                if (x + y * WIDTH >= 0 && x + y * WIDTH < WIDTH * HEIGHT)
                {
                    //qDebug() << z << " is Z";
                    if (z > ZBufferShadows.zbuffer[x + y * WIDTH])
                    {
                        //                        drawShadow(ShadowPoint);
                        ZBufferShadows.zbuffer[x + y * WIDTH] = z;
                        //painter->drawPoint(x, y);
                    }
                    //                    painter->drawPoint(x, y);
                }
                else
                {
                }

            }
            else
            {
            }
        }
    }

}

void PaintWidget::drawShadow(Point3D P)
{
    //rotateInversedCamera(P);

    //qDebug() << P.w();
    //P.setX(P.x() * P.w());
    //P.setY(P.y() * P.w());

    //PerspectiveProjection(P, back);
    if (_camera.getZAngle() != 0)
    {
        P.transform(matrixInvZ);
    }

    if (_camera.getYAngle() != 0)
    {
        P.transform(matrixInvY);
    }

    if (_camera.getXAngle() != 0)
    {
       P.transform(matrixInvX);
    }

    rotateLight(P);
    //PerspectiveProjection(P, forward);
    ///qDebug() << "Point" << P.x() << P.y() << P.z();

    P.setX(P.x() + X_SIZE);
    P.setY(P.y() + Y_SIZE);
    P.setZ(P.z() + 10000);
    if (P.x() + P.y() * WIDTH > 0 && P.x() + P.y() * WIDTH < WIDTH * HEIGHT)
    {
        //qDebug() << ZBufferShadows.zbuffer[int(P.x()) + int(P.y()) * WIDTH] << z;
        if (ZBufferShadows.zbuffer[int(P.x()) + int(P.y()) * WIDTH] - 60 > P.z())
        {
            painter->setPen(ambient);
        }
        else
        {
            painter->setPen(resultColor);
        }

        //                    painter->drawPoint(x, y);
    }
    else
    {
        //qDebug() << "out of" << P.x() << P.y() << P.z();
    }
    //    painter->drawPoint(P.x(), P.y());


}




void PaintWidget::clear()
{
    image->fill(QColor(Qt::black));
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

void PaintWidget::ComputeBarycentric(Point3D A, Point3D B, Point3D C, Point3D P, double square, BarycentricCoords &BarCoor)
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
    RocketFire.update(*painter, firePoint, ZBuffer, *image);

    //y_down--;
    update();
    //RocketFire.update();

}

bool PaintWidget::isTriangleVisible(Point3D A, Point3D B, Point3D C, Point3D visiblePoint)
{
    Vector V1(A, B);
    Vector V2(B, C);
    //\Vector V3(C, A);
    //Vector Vntmp = crossProduct(V2, V3);
    Vector Vn = crossProduct(V1, V2);
    Vn.normalize();
    // Vntmp.normalize();

    Point3D CameraPos = visiblePoint;
    //changeCameraPos(CameraPos);
    // позиция камеры
    //qDebug() << CameraPos.x() << CameraPos.y() << CameraPos.z();
    Point3D Null(0, 0, 0);
    Vector CameraVector(Null, CameraPos);
    CameraVector.normalize();
    //qDebug() << CameraVector.x << CameraVector.y << CameraVector.z;
    double result = crossProductScalar(CameraVector, Vn);
    //qDebug() << result << "result of scalar";
    if (result < 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

double max(double p1, double p2)
{
    if (p1 - p2 > EPS)
    {
        return p1;
    }
    return  p2;
}
QColor PaintWidget::ambientLightning(Point3D A, Point3D B, Point3D C, QColor objColor, Point3D LightPoint)
{
    Vector V1(A, B);
    Vector V2(B, C);
    Vector Vn = crossProduct(V1, V2);
    Vn.normalize();
    return getColor(Vn, objColor, LightPoint);
    //    Vn = vertexNormals[A.pointIndex];
    //    qDebug() << A.pointIndex << "point index A";
    //    qDebug() << B.pointIndex << "point index B";
    //    qDebug() << C.pointIndex << "point index C";


    //    qDebug() << Vn.x << Vn.y << Vn.z << "Vn";
    //    qDebug() << Vntmp.x << Vntmp.y << Vntmp.z << "Vntmp";

    //qDebug() << Vn.x << Vn.y << Vn.z << "Vn";
    //    qDebug() << lightPoint.x() << lightPoint.y() << lightPoint.z() << "lightpos";



}

QColor PaintWidget::getColor(Vector normal, QColor objColor, Point3D LightPoint)
{
    Point3D Null(0, 0, 0);
    Vector lightVector(LightPoint, Null);
    lightVector.normalize();
    //qDebug() << CameraVector.x << CameraVector.y << CameraVector.z;

    double intensity = crossProductScalar(lightVector, normal);
    //    qDebug() << intensity << "intensity";
    intensity = max(intensity, 0);

    QColor tmp = objColor;
    double red = tmp.red();
    double green = tmp.green();
    double blue = tmp.blue();

    double reda = lightColor.redF();
    double greena = lightColor.greenF();
    double bluea = lightColor.blueF();

    //qDebug() << red << green << blue << "colors 1";

    reda *= AMBIENT;
    greena *= AMBIENT;
    bluea *= AMBIENT;

    ambient.setRed(red * reda);
    ambient.setGreen(green * greena);
    ambient.setBlue(blue * bluea);

    reda += intensity;
    greena += intensity;
    bluea += intensity;

    //qDebug() << red << green << blue << "colors 2";

    red *= reda;
    green *= greena;
    blue *= bluea;

    //    red *= AMBIENT;
    //    green *


    //    qDebug() << red << "red";
    //    qDebug() << green << "green";
    //    qDebug() << blue << "blue";

    if (green > 255)
        green = 255;
    if (red > 255)
        red = 255;
    if (blue > 255)
        blue = 255;
    tmp.setRed(red);
    tmp.setBlue(blue);
    tmp.setGreen(green);
    //tmp.setAlphaF(intensity);

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
