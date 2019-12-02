#ifndef ZBUFFER_H
#define ZBUFFER_H

#define WIDTH  850
#define HEIGHT  715

struct DepthBuffer
{
    double *zbuffer = new double[WIDTH * HEIGHT];
    void fillbuffer()
    {
        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            zbuffer[i] = -1000000;
        }
    }
};


#endif // ZBUFFER_H
