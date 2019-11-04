#ifndef EDGES_H
#define EDGES_H
#include <stdio.h>
#include <vector>
#include "point3d.h"
struct edge
{
    edge(int _x1, int _y1, int _x2, int _y2)
    {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
    }

    void changeEdge(int _x1, int _y1, int _x2, int _y2)
    {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
    }
    int x1;
    int y1;
    int x2;
    int y2;
};

class edges
{
public:
    edges(){}

    void addEdge(Point3D first, Point3D second);
    //void deleteEdge(edge _edge);


public:
    std::vector<std::pair<Point3D, Point3D>> list;

};

#endif // EDGES_H
