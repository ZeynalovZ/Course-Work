#include "paintingwidget.h"
#include "triangle.h"
#include <QDebug>


#define X_SIZE  850 / 2
#define Y_SIZE  715 / 2
#define EPS 0.00001


PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    widget_width = 850;
    widget_height = 715;
    bg_color = Qt::black;
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
    // Рисовать здесь точно не нужно !
    // Для этого есть модель внутри конуса, туда нужно еще записать индексы точек связей для отображения

    // Затем добавить перспективное проецирование

    // Добавить алгоритм Z- буффера


    int angleX = _cone.currentAngleX;
    int angleY = _cone.currentAngleY;
    //qDebug() << _cone.firstCircle[2].x() << " " << _cone.firstCircle[2].y() << " " <<_cone.firstCircle[2].z();
    /*
    for (int i = 0; i < _cone.Edges.list.size(); i++)
    {

        Point3D tmp1 = _cone.Edges.list[i].first;
        Point3D tmp2 = _cone.Edges.list[i].second;

        tmp1.rotateX(angleX);
        tmp2.rotateX(angleX);

        tmp1.rotateY(angleY);
        tmp2.rotateY(angleY);

        PerspectiveProjection(tmp1);
        PerspectiveProjection(tmp2);

        //tmp1 = PerspectiveProjection(tmp1);
        //tmp2 = PerspectiveProjection(tmp2);
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->drawLine(tmp1.x() + X_SIZE, tmp1.y() + Y_SIZE,
                          tmp2.x() + X_SIZE, tmp2.y() + Y_SIZE);
    }
    */
    painter->setRenderHint(QPainter::Antialiasing, true);

    for (auto &triangle : _cone.Triangles)
    {
        Point3D tmp1 = triangle.A;
        Point3D tmp2 = triangle.B;
        Point3D tmp3 = triangle.C;
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
//        fillObject(tmp1, tmp2, tmp3);
        ComputeBarycentric(tmp1, tmp2, tmp3);
        //        painter->drawLine(tmp1.x() + X_SIZE, tmp1.y() + Y_SIZE,
        //                          tmp2.x() + X_SIZE, tmp2.y() + Y_SIZE);

        //        painter->drawLine(tmp2.x() + X_SIZE, tmp2.y() + Y_SIZE,
        //                          tmp3.x() + X_SIZE, tmp3.y() + Y_SIZE);
        //        painter->drawLine(tmp1.x() + X_SIZE, tmp1.y() + Y_SIZE,
        //                          tmp3.x() + X_SIZE, tmp3.y() + Y_SIZE);
        Triangle triangleOnImageTmp(tmp1, tmp2, tmp3);
        trianglesOnImage.push_back(triangleOnImageTmp);

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
    cone.createCone(point, 300, 300, 50, 4, QColor(Qt::white));
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
    if (x1 < x2 && x1 < x3)
    {
        min = x1;
    }
    if (x2 < x1 && x2 < x3)
    {
        min = x2;
    }
    if (x3 < x2 && x3 < x1)
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
            if (points[j].y() > points[j + 1].y())
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

    //qDebug() << A.y() << B.y() << C.y();
    // for object
    // needed at least 2 points

    // change is a fuction transforming to display axis

    //qDebug() << A.y() << B.y() << C.y();

    change(A);
    change(B);
    change(C);


    if (A.y() > B.y()) std::swap(A, B);
    if (A.y() > C.y()) std::swap(A, C);
    if (B.y() > C.y()) std::swap(B, C);
    //qDebug() << A.y() << B.y() << C.y();


    //qDebug() << a << b << c << d;

    int total_height = C.y() - A.y();

    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > B.y() - A.y() || B.y() == A.y();
        int segment_height = second_half ? C.y() - B.y() : B.y() - A.y();
        if (total_height != 0 && segment_height != 0)
        {
            float alpha = (float)i / total_height;
            float beta  = (float)(i - (second_half ? B.y() - A.y() : 0)) / segment_height; // be careful: with above conditions no division by zero here
            //            int x_beg = A.x() + (C.x() - A.x())*alpha;
            //            int x_last = second_half ? B.x() + (C.x() - B.x()) * beta : A.x() + (B.x() - A.x()) * beta;

            Point3D A1(A.x() + (C.x() - A.x()) * alpha, A.y() + (C.y() - A.y()) * alpha, A.z() + (C.z() - A.z()) * alpha) ;
            Point3D B1(second_half ? B.x() + (C.x() - B.x()) * beta : A.x() + (B.x() - A.x()) * beta,
                       second_half ? B.y() + (C.y() - B.y()) * beta : A.y() + (B.y() - A.y()) * beta,
                       second_half ? B.z() + (C.z() - B.z()) * beta : A.z() + (B.z() - A.z()) * beta);
            if (A1.x() > B1.x()) std::swap(A1, B1);
            for (int j = A1.x(); j <= B1.x(); j++)
            {
                float phi = A1.x() == B1.x() ? 1. : (float)(j - A1.x())/(float)(B1.x() - A1.x());

                Point3D P(A1.x() + (B1.x() - A1.x()) * phi, A1.y() + (B1.y() - A1.y()) * phi, A1.z() + (B1.z() - A1.z()) * phi);

                //qDebug() << P.x() + P.y() * WIDTH << HEIGHT * WIDTH;
                //qDebug() << P.x() << P.y() << "hey";
                int idx = P.x() + P.y() * WIDTH;
                int ix = idx % WIDTH;
                int iy = idx / WIDTH;
                //qDebug() << ix << iy << idx << WIDTH * HEIGHT;

                //                if (ZBuffer.zbuffer[idx] < P.z())
                //                {
                //                    ZBuffer.zbuffer[idx] = P.z();
                //                    painter->drawPoint(P.x(), P.y());
                //                }

                painter->drawPoint(j, A.y() + i);

                //                if (z >= ZBuffer.zbuffer[j + i * WIDTH])
                //                {
                //                    ZBuffer.zbuffer[j + i * WIDTH] = z;
                //                    painter->drawPoint(j, A.y() + i);
                //                }

                //qDebug() << A.z();
                //painter->drawPoint(j, A.y() + i);
                //painter->drawPoint(j, A.y() + i);
                //image.set(j, y, color); // attention, due to int casts t0.y+i != A.y
            }
        }

    }
    update();


    /*
    int y_curr = A.y();
    int y_end = C.y();
    int xa, xb, za, zb, z;

    while (y_curr < y_end)
    {
        if (A.y() != B.y() && A.y() != C.y())
        {
            xa = A.x() + (B.x() - A.x()) * (y_curr - A.y()) / (B.y() - A.y());
            xb = A.x() + (C.x() - A.x()) * (y_curr - A.y()) / (C.y() - A.y());
            za = A.z() + (B.z() - A.z()) * (y_curr - A.y()) / (B.y() - A.y());
            zb = A.z() + (C.z() - A.z()) * (y_curr - A.y()) / (C.y() - A.y());
            for (int x = xa; x < xb; x++)
            {
                z = za + (zb - za) * (x - xa) / (xb - xa);

//                if (z > ZBuffer.buffer[x][y_curr])
//                {
//                    ZBuffer.buffer[x][y_curr] = z;
//                    painter->drawPoint(x, y_curr);
//                }
                if (x < xmax && x > xmin)
                {
                    painter->drawPoint(x, y_curr);
                }

            }

        }
        y_curr++;

    }
    */
    /*
    painter->drawLine(xmin, ymin, xmin, ymax);
    painter->drawLine(xmax, ymin, xmax, ymax);
    painter->drawLine(xmin, ymin, xmax, ymin);
    painter->drawLine(xmin, ymax, xmax, ymax);
    */
    //qDebug() << xmax << ymax << xmin << ymin;

    /*
     * Вычисление коэффициентов плоскости

            //-------------------
            a = y1 *(z2 - z3) + y2 *(z3 - z1) + y3* (z1 - z2) ;
            b = z1 *(x2 - x3) + z2 *(x3 - x1) + z3 *(x1 - x2);
            c = x1 *(y2 - y3) + x2 *(y3 - y1) + x3 *(y1 - y2) ;
            d = -(x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));
            //-----------------
    */

    /*
    edges _edges;
    _edges.addEdge(A, B);
    _edges.addEdge(B, C);
    _edges.addEdge(C, A);
    for (int i = 0; i < _edges.list.size(); i++)
    {

        double x1e = _edges.list[i].first.x();
        double x2e = _edges.list[i].second.x();
        double y1e = _edges.list[i].first.y();
        double y2e = _edges.list[i].second.y();
        //qDebug() << y1e << "y1e " << y2e << "y2e";
        // Если горизонтальная
        if (y2e == y1e)
            continue;

        if (y1e > y2e)
        {
            std::swap(y1e, y2e);
            std::swap(x1e, x2e);
        }

        double y = y1e;
        double end_y = y2e;
        double dx = x2e - x1e;
        double dy = y2e - y1e;
        double k = dx / dy;
        double start_x = x1e;
        while (y < end_y)
        {
            double x = start_x;
            while (x < xmax)
            {
                //qDebug() << QPoint(x, y);
                //painter->setPen(QColor(color_shading));

                painter->drawPoint(x, y);
                x++;
            }
            start_x += k;
            y++;

        }
    }
    */

    painter->setPen(QColor(Qt::black));
}



void PaintWidget::clear()
{
    image->fill(bg_color);
    //trianglesOnImage.clear();
}

void PaintWidget::ComputeBarycentric(Point3D A, Point3D B, Point3D C)
{
//    painter->setPen(QColor(Qt::white));
    change(A);
    change(B);
    change(C);


    qDebug() << A.y() << B.y() << C.y() << " y1 ==";


    if (B.x() > A.x()) std::swap(B, A);
    if (B.x() > C.x()) std::swap(B, C);
    if (A.x() > C.x()) std::swap(A, C);


    if (A.y() > B.y()) std::swap(A, B);
    if (A.y() > C.y()) std::swap(A, C);
    if (B.y() > C.y()) std::swap(B, C);
    qDebug() << A.y() << B.y() << C.y() << " y2 ==";
    //qDebug() << A.x() << B.x() << C.x() << " x ==";

    double x1 = A.x();
    double x2 = B.x();
    double x3 = C.x();
    double y1 = A.y();
    double y2 = B.y();
    double y3 = C.y();
    Point3D P;
    double xmax, xmin, ymax, ymin;
    xmax = getMaxFor3(x1, x2, x3);
    xmin = getMinFor3(x1, x2, x3);
    ymax = getMaxFor3(y1, y2, y3);
    ymin = getMinFor3(y1, y2, y3);
    double square = (B.y() - C.y()) * (A.x() - C.x()) + (A.y() - C.y()) * (C.x() - B.x());
    //qDebug() << square;
    for (int y = ymin; y < ymax; y++)
    {
        for (int x = xmin; x < xmax; x++)
        {
            P.changeAll(x, y, 0);
            if (square > EPS)
            {
                BarCoor.b1 = (P.y() - C.y()) * (A.x() - C.x()) + (A.y() - C.y()) * (C.x() - P.x());
                BarCoor.b1 /= square;
                BarCoor.b2 = (P.y() - B.y()) * (C.x() - B.x()) + (C.y() - B.y()) * (B.x() - P.x());
                BarCoor.b2 /= square;
                BarCoor.b3 = 1 - BarCoor.b1 - BarCoor.b2;
                //qDebug() << BarCoor.b1 << BarCoor.b2 << BarCoor.b3;
                if (BarCoor.b1 >= 0 && BarCoor.b1 <= 1 && BarCoor.b2 >= 0 && BarCoor.b2 <= 1 &&
                        BarCoor.b3 >= 0 && BarCoor.b3 <=1)
                {
                    //qDebug() << BarCoor.b1 << BarCoor.b2 << BarCoor.b3;
                    painter->drawPoint(x, y);
                }
            }
            else
            {
                //qDebug() << "hey";
                BarCoor.b1 = -1;
            }
        }
        update();
    }

    /*
    double square = (A.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - A.x());
    if (square > EPS)
    {
        BarCoor.b1 = (P.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - P.x());
        BarCoor.b1 /= square;
        BarCoor.b2 = (P.y() - A.y()) * (C.x() - A.x()) + (C.y() - A.y()) * (A.x() - P.x());
        BarCoor.b2 /= square;
        BarCoor.b3 = 1 - barCoords[0] - barCoords[1];
    }
    else
    {
        BarCoor.b1 = -1;
    }
    */
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
