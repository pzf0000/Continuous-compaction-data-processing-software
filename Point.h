#ifndef POINT_H
#define POINT_H

#include <cmath>

struct Point
{
    double x, y;
};

bool between(double a, double X0, double X1);

bool detectIntersect(Point p1, Point p2, Point p3, Point p4);

double gettrianglearea(int x1,int y1,int x2,int y2,int x3,int y3);


#endif // POINT_H
