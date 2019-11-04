#include "edges.h"

/*
edges::edges(edges _edges)
{
    for (int i = _edges.list.begin(); i < _edges.list.end(); i++)
    {
        this->list.push_back(_edges.Edges[i]);
    }
}
*/

// добавить и для р1 > р2 и тд

void edges::addEdge(Point3D first, Point3D second)
{
    std::pair<Point3D, Point3D> tmp(first, second);
    this->list.push_back(tmp);
}
