#include "paintingwidget.h"
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

void PaintWidget::drawCone(Cone &_cone)
{
    // Рисовать здесь точно не нужно !
    // Для этого есть модель внутри конуса, туда нужно еще записать индексы точек связей для отображения

    // Затем добавить перспективное проецирование

    // Добавить алгоритм Z- буффера


    int angleX = _cone.currentAngleX;
    int angleY = _cone.currentAngleY;
    //qDebug() << angleX << " x";
    //qDebug() << angleY << " y";
    //qDebug() << _cone.firstCircle[2].x() << "here";

    //this->drawLine(0, 40, 800, 40);


    for (int i = 0; i < _cone.firstCircle.size(); i++)
    {
        Point3D tmp = _cone.firstCircle[i];
        tmp.rotateX(angleX);
        tmp.rotateY(angleY);
        //tmp  = PerspectiveProjection(tmp);
        PerspectiveProjection(tmp);
        // Перенос в центр экрана
        painter->drawPoint(tmp.x() + X_SIZE, tmp.y()+ Y_SIZE);
        //_cone.firstCircle[i].rotateX(ANGLE_X);
        //this->drawPoint(_cone.firstCircle[i].x(), _cone.firstCircle[i].y());
    }

    for (int i = 0; i < _cone.secondCircle.size(); i++)
    {
        Point3D tmp = _cone.secondCircle[i];
        tmp.rotateX(angleX);
        tmp.rotateY(angleY);
        PerspectiveProjection(tmp);
        //tmp = PerspectiveProjection(tmp);
        painter->drawPoint(tmp.x() + X_SIZE, tmp.y() + Y_SIZE);
        //_cone.secondCircle[i].rotateX(ANGLE_X);
        //this->drawPoint(_cone.secondCircle[i].x(), _cone.secondCircle[i].y());
    }

    //qDebug() << _cone.firstCircle[2].x() << " " << _cone.firstCircle[2].y() << " " <<_cone.firstCircle[2].z();
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
        painter->drawLine(tmp1.x() + X_SIZE, tmp1.y() + Y_SIZE,
                         tmp2.x() + X_SIZE, tmp2.y() + Y_SIZE);
        //this->drawLine(_cone.Edges.list[i].first.x(), _cone.Edges.list[i].first.y(),
          //             _cone.Edges.list[i].second.x(), _cone.Edges.list[i].second.y());
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

    double eps = 1e-5;
    double znam = point.z() + cam_pos.z();
    if (znam < eps && znam > -eps) {
        znam = eps;
    }
    double distCoef = cam_pos.z() / znam;
    point.setX(point.x() * distCoef);
    point.setY(point.y() * distCoef);
    update();
}

void PaintWidget::SetCameraAngleS(int angleX, int angleY, int angleZ)
{
    _camera.setXAngle(angleX);
    _camera.setYAngle(angleY);
    _camera.setZAngle(angleZ);

}



void PaintWidget::clear()
{
    image->fill(bg_color);
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
