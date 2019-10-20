#include "drawer.h"
#include "QDebug"
#define ANGLE_X 150
Drawer::Drawer()
{

}

void Drawer::drawCone(Cone _cone)
{
    qDebug() << _cone.ConeCenter.x();
    PerspectiveProjection(_cone);
    qDebug() << _cone.ConeCenter.x();
    qreal distance = _cone.height / 2;
    Point3D ConeCenter = _cone.ConeCenter;
    qreal radius1 = _cone.radius1;
    qreal radius2 = _cone.radius2;


    Point3D FirstCenter = ConeCenter;
    Point3D SecondCenter = ConeCenter;

    // Удаляем окружности друг от друга на h = distance
    FirstCenter.setZ(ConeCenter.z() + distance);
    SecondCenter.setZ(ConeCenter.z() - distance);


    this->CreateCircle(_cone.firstCircle, FirstCenter, radius1);
    this->CreateCircle( _cone.secondCircle, SecondCenter, radius2);

    // Сделать все отрисованное в одну модель
    // В классе ракеты вектор из модулей и один центр на всю ракету или ее положение при z = 0 ( т.е основание)

    // Рисовать здесь точно не нужно !
    // Для этого есть модель внутри конуса, туда нужно еще записать индексы точек связей для отображения
    // Трансформацию вынести в отдельный модуль

    // Затем добавить перспективное проецирование

    // Добавить алгоритм Z- буффера

    // Трансформация относительно оси ОХ
    for (int i = 0; i < _cone.firstCircle.size(); i++)
    {
        _cone.Rotatex(ANGLE_X, _cone.firstCircle[i]);
        this->drawPoint(_cone.firstCircle[i].x(), _cone.firstCircle[i].y());
    }

    for (int i = 0; i < _cone.secondCircle.size(); i++)
    {
        _cone.Rotatex(ANGLE_X, _cone.secondCircle[i]);
        this->drawPoint(_cone.secondCircle[i].x(), _cone.secondCircle[i].y());
    }

    // Получение ребер
    if (_cone.radius1 < _cone.radius2)
    {
        int k = _cone.secondCircle.size() / _cone.firstCircle.size();
        for (int i = 0; i <= _cone.firstCircle.size(); i += 92)
        {
            this->drawLine(_cone.firstCircle[i].x(), _cone.firstCircle[i].y(),
                    _cone.secondCircle[i * k].x(), _cone.secondCircle[i * k].y());
            this->drawLine(_cone.firstCircle[i + 1].x(), _cone.firstCircle[i + 1].y(),
                    _cone.secondCircle[i * k + 1].x(), _cone.secondCircle[i  * k + 1].y());
            this->drawLine(_cone.firstCircle[i + 2].x(), _cone.firstCircle[i + 2].y(),
                    _cone.secondCircle[i * k + 2].x(), _cone.secondCircle[i * k + 2].y());
            this->drawLine(_cone.firstCircle[i + 3].x(), _cone.firstCircle[i + 3].y(),
                           _cone.secondCircle[i * k + 3].x(), _cone.secondCircle[i * k + 3].y());
        }
    }
    else
    {
        int k = _cone.firstCircle.size() / _cone.secondCircle.size();
        for (int i = 0; i <= _cone.secondCircle.size(); i += 92)
        {
            this->drawLine(_cone.secondCircle[i].x(), _cone.secondCircle[i].y(),
                    _cone.firstCircle[i * k].x(), _cone.firstCircle[i * k].y());
            this->drawLine(_cone.secondCircle[i + 1].x(), _cone.secondCircle[i + 1].y(),
                    _cone.firstCircle[i * k + 1].x(), _cone.firstCircle[i  * k + 1].y());
            this->drawLine(_cone.secondCircle[i + 2].x(), _cone.secondCircle[i + 2].y(),
                    _cone.firstCircle[i * k + 2].x(), _cone.firstCircle[i * k + 2].y());
            this->drawLine(_cone.secondCircle[i + 3].x(), _cone.secondCircle[i + 3].y(),
                           _cone.firstCircle[i * k + 3].x(), _cone.firstCircle[i * k + 3].y());
        }
    }

}

void Drawer::PerspectiveProjection(Cone &_cone)
{
    double x =  K * _cone.ConeCenter.x() / (_cone.ConeCenter.z() + K);
    double y =  K * _cone.ConeCenter.y() / (_cone.ConeCenter.z() + K);
    _cone.ConeCenter.setX(x);
    _cone.ConeCenter.setY(y);
}
