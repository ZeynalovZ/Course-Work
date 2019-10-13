#ifndef BASEDRAWER_H
#define BASEDRAWER_H
#include "QGraphicsScene"
#include "point3d.h"
#define POINT_SIZE 1
// Для перспективной проекции
#define K 10
class BaseDrawer:public QGraphicsScene
{
public:
    BaseDrawer();

    void drawPoint(int x, int y);
    // here another algorithm by VU
    void drawLine(qreal xFirst, qreal yFirst, qreal xLast, qreal yLast);

    void drawCircle(Point3D _center, qreal radius);

    void drawEllipse();

    void repaint();

};

#endif // BASEDRAWER_H
