#include "basedrawer.h"
#include "QGraphicsScene"
#include "cmath"
#include <QDebug>
BaseDrawer::BaseDrawer()
{

}



void BaseDrawer::drawPoint(int x, int y)
{
    this->addEllipse(x, y, POINT_SIZE, POINT_SIZE);
}

void BaseDrawer::drawLine(qreal xFirst, qreal yFirst, qreal xLast, qreal yLast)
{
    this->addLine(xFirst, yFirst, xLast, yLast);
}


void BaseDrawer::repaint()
{
    this->clear();
}
