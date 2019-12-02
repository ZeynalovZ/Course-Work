#include "fire.h"

static void spreadFire(int src)
{
    auto pixel = firePixels[src];
    if (pixel == 0)
    {
        firePixels[src + FIRE_WIDTH] = 0;
    }
    else
    {
        int randIdx = qrand() % 3;
        int dst = src - randIdx + 1;
        firePixels[dst + FIRE_WIDTH] = pixel - (randIdx & 1);
    }
}

static void doFire()
{
    for (int x = 0 ; x < FIRE_WIDTH; x++)
    {
        for (int y = FIRE_HEIGHT; y >= 1; y--)
        {
            spreadFire(y * FIRE_WIDTH + x);
        }
    }
}

fire::fire()
{
    // Initialize framebuffer
    framebuffer = QImage(FIRE_WIDTH, FIRE_HEIGHT, QImage::Format_Indexed8);
    framebuffer.setColorTable(palette);

    QColor bg_color;
    bg_color.setRed(12);
    bg_color.setGreen(196);
    bg_color.setBlue(255);
    framebuffer.fill(bg_color);

    // Initialize effect
    for (uint i = 0; i < FIRE_WIDTH*FIRE_HEIGHT; i++)
    {
        firePixels[i] = 0;
    }


    for(uint i = 0; i < FIRE_WIDTH; i++)
    {
        firePixels[FIRE_WIDTH + i] = 36;
    }
    qDebug() << "here";
}

void fire::update(QPainter &painter, Point3D Point, DepthBuffer Zbuffer, QImage &image)
{
    doFire();
    for(int y = 0; y < FIRE_HEIGHT; y++)
    {
        auto rowData = framebuffer.scanLine(y);
        for(int x = 0; x < FIRE_WIDTH; x++)
        {
            rowData[x] = firePixels[y * FIRE_WIDTH + x];
            //image.setPixel(x, y, firePixels[y * FIRE_WIDTH + x]);
            painter.setPen(QColor(firePixels[y * FIRE_WIDTH + x]));
            painter.drawPoint(x, y);
            //painter.setPen(QColor(firePixels[y * FIRE_WIDTH + x]));
            //painter.drawPoint(x + 200, y + 200);
            //painter.drawPoint(x + 300, y + 100);
        }
    }
    painter.drawImage(Point.x() + 13, Point.y(), framebuffer);

}
