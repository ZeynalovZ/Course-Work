#include "fire.h"

static void spreadFire(int src) {
    auto pixel = firePixels[src];
    if (pixel == 0) {
        firePixels[src - FIRE_WIDTH] = 0;
    } else {
        int randIdx = qrand() % 3;
        int dst = src - randIdx + 1;
        firePixels[dst - FIRE_WIDTH] = pixel - (randIdx & 1);
    }
}

static void doFire() {
    for (int x = 0 ; x < FIRE_WIDTH; x++) {
        for (int y = 1; y < FIRE_HEIGHT; y++) {
            spreadFire(y * FIRE_WIDTH + x);
        }
    }
}

fire::fire()
{
    // Initialize framebuffer
    framebuffer = QImage(320, 240, QImage::Format_Indexed8);
    framebuffer.setColorTable(palette);


    // Initialize effect
    for (uint i = 0; i < FIRE_WIDTH*FIRE_HEIGHT; i++)
    {
        firePixels[i] = 0;
    }


    for(uint i = 0; i < FIRE_WIDTH; i++) {
        firePixels[(FIRE_HEIGHT - 1) * FIRE_WIDTH + i] = 36;
    }
    qDebug() << "here";
}

void fire::update()
{
    doFire();

    for(int y = 0; y < FIRE_HEIGHT; y++) {
        auto rowData = framebuffer.scanLine(y);
        for(int x = 0; x < FIRE_WIDTH; x++) {
            rowData[x] = firePixels[y * FIRE_WIDTH + x];
        }
    }
}
