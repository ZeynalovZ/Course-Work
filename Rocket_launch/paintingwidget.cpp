#include "paintingwidget.h"
#include "triangle.h"
#include <QDebug>


#define X_SIZE  850 / 2
#define Y_SIZE  715 / 2
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

    for (auto &triangle : _cone.TrianglesImage)
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
        fillObject(tmp1, tmp2, tmp3);

        painter->drawLine(tmp1.x() + X_SIZE, tmp1.y() + Y_SIZE,
                          tmp2.x() + X_SIZE, tmp2.y() + Y_SIZE);

        painter->drawLine(tmp2.x() + X_SIZE, tmp2.y() + Y_SIZE,
                          tmp3.x() + X_SIZE, tmp3.y() + Y_SIZE);
        painter->drawLine(tmp1.x() + X_SIZE, tmp1.y() + Y_SIZE,
                          tmp3.x() + X_SIZE, tmp3.y() + Y_SIZE);
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
    cone.createCone(point, 40, 40, 50, 4);
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
    if (max < x2)
    {
        max = x2;
    }
    if (max < x3)
    {
        max = x3;
    }
    return max;
}

double getMinFor3(double x1, double x2, double x3)
{
    double max = x1;
    if (max > x2)
    {
        max = x2;
    }
    if (max > x3)
    {
        max = x3;
    }
    return max;
}
void PaintWidget::fillObject(Point3D A, Point3D B, Point3D C)
{

    // for object
    // needed at least 2 points
    QColor color_background = QColor(Qt::white);
    QColor color_shading = QColor(Qt::gray);
    painter->setPen(color_shading);
    change(A);
    change(B);
    change(C);
    double sx1 = A.x();
    double sx2 = B.x();
    double sx3 = C.x();
    double sy1 = A.y();
    double sy2 = B.y();
    double sy3 = C.y();

    double xmax = getMaxFor3(sx1, sx2, sx3);
    double ymax = getMaxFor3(sy1, sy2, sy3);
    double xmin = getMinFor3(sx1, sx2, sx3);
    double ymin = getMinFor3(sy1, sy2, sy3);

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

                QColor color = image->pixelColor(QPoint(x, y));

                if (color == color_background)
                {
                    painter->setPen(QColor(color_shading));
                }
                else if (color == color_shading)
                {
                    painter->setPen(QColor(color_background));
                }
                painter->drawPoint(x, y);

                x++;
            }
            start_x += k;
            y++;

        }
    }


    painter->setPen(QColor(Qt::black));
}



void PaintWidget::clear()
{
    image->fill(bg_color);
    //trianglesOnImage.clear();
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
