#ifndef FIRE_H
#define FIRE_H
#include <QRgb>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include "point3d.h"
#include "zbuffer.h"

const int FIRE_WIDTH  = 75;
const int FIRE_HEIGHT = 250;
static uchar firePixels[FIRE_WIDTH * FIRE_HEIGHT];

static QVector<QRgb> palette = {
    qRgb(0x07,0x07,0x07),
    qRgb(0x1F,0x07,0x07),
    qRgb(0x2F,0x0F,0x07),
    qRgb(0x47,0x0F,0x07),
    qRgb(0x57,0x17,0x07),
    qRgb(0x67,0x1F,0x07),
    qRgb(0x77,0x1F,0x07),
    qRgb(0x8F,0x27,0x07),
    qRgb(0x9F,0x2F,0x07),
    qRgb(0xAF,0x3F,0x07),
    qRgb(0xBF,0x47,0x07),
    qRgb(0xC7,0x47,0x07),
    qRgb(0xDF,0x4F,0x07),
    qRgb(0xDF,0x57,0x07),
    qRgb(0xDF,0x57,0x07),
    qRgb(0xD7,0x5F,0x07),
    qRgb(0xD7,0x5F,0x07),
    qRgb(0xD7,0x67,0x0F),
    qRgb(0xCF,0x6F,0x0F),
    qRgb(0xCF,0x77,0x0F),
    qRgb(0xCF,0x7F,0x0F),
    qRgb(0xCF,0x87,0x17),
    qRgb(0xC7,0x87,0x17),
    qRgb(0xC7,0x8F,0x17),
    qRgb(0xC7,0x97,0x1F),
    qRgb(0xBF,0x9F,0x1F),
    qRgb(0xBF,0x9F,0x1F),
    qRgb(0xBF,0xA7,0x27),
    qRgb(0xBF,0xA7,0x27),
    qRgb(0xBF,0xAF,0x2F),
    qRgb(0xB7,0xAF,0x2F),
    qRgb(0xB7,0xB7,0x2F),
    qRgb(0xB7,0xB7,0x37),
    qRgb(0xCF,0xCF,0x6F),
    qRgb(0xDF,0xDF,0x9F),
    qRgb(0xEF,0xEF,0xC7),
    qRgb(0xFF,0xFF,0xFF),
    qRgb(0x0C, 0xC4, 0xFF)
};

static QVector<QColor> paletteColor = {
    QColor(0, 0, 0, 255),
    QColor(31, 7, 7, 255),
    QColor(47, 15, 7, 255),
    QColor(71, 15, 7, 255),
    QColor(87, 23, 7, 255),
    QColor(103, 31, 7, 255),
    QColor(119, 31, 7, 255),
    QColor(143, 39, 7, 255),
    QColor(159, 63, 7, 255),
    QColor(175, 63, 7, 255),
    QColor(191, 71, 7, 255),
    QColor(199, 71, 7, 255),
    QColor(223, 79, 7, 255),
    QColor(223, 87, 7, 255),
    QColor(223, 87, 7, 255),
    QColor(215, 95, 7, 255),
    QColor(223, 95, 7, 255),
    QColor(215, 103, 15, 255),
    QColor(207, 111, 15, 255),
    QColor(207, 119, 15, 255),
    QColor(207, 127, 15, 255),
    QColor(207, 135, 23, 255),
    QColor(199, 135, 23, 255),
    QColor(199, 143, 23, 255),
    QColor(199, 151, 31, 255),
    QColor(199, 159, 31, 255), // 191 ?
    QColor(199, 151, 31, 255),
    QColor(191, 167, 39, 255),
    QColor(191, 167, 39, 255),
    QColor(191, 175, 47, 255),
    QColor(183, 175, 47, 255),
    QColor(183, 183, 47, 255),
    QColor(183, 183, 55, 255),
    QColor(207, 207, 111, 255),
    QColor(223, 223, 159, 255),
    QColor(239, 239, 199, 255),
    QColor(255, 255, 255, 255)
};

class fire
{
public:
    fire();
    QImage framebuffer;
public slots:
    void update(QPainter &painter, Point3D Point, DepthBuffer Zbuffer, QImage &image);
};

#endif // FIRE_H
