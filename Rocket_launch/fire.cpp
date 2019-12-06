#include "fire.h"

#define WIDTH  850
#define HEIGHT  715

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
    int i = 0;
    int tmp_x, tmp_y;
    int clr;
    Point.setX(Point.x() + 12);
    for(int y = 0; y < FIRE_HEIGHT; y++)
    {
        for(int x = 0; x < FIRE_WIDTH; x++)
        {
            i = y * FIRE_WIDTH + x;
            //qDebug() << i << "is i";
            //rowData[x] = firePixels[i];
            clr = firePixels[i];
            if (clr > 1)
            {
                painter.setPen(paletteColor[clr]);
                //painter.drawPoint(Point.x() + x, Point.y() + y);
                tmp_x = int(Point.x() + x);
                tmp_y = int(Point.y() + y);
                if (tmp_x + tmp_y * WIDTH >= 0 && tmp_x + tmp_y * WIDTH < WIDTH * HEIGHT)
                {
                    if (Zbuffer.zbuffer[tmp_x + WIDTH * tmp_y] < Point.z())
                    {
                        painter.drawPoint(tmp_x, tmp_y);
                    }
                }
            }




        }
    }

}
