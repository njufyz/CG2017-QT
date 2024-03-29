#ifndef POINT_H
#define POINT_H
#include<cmath>
namespace fyz{

struct Point
{
    double x;
    double y;
    Point() { x = -1; y = -1; }
    Point(double x, double y) { this->x = x; this->y = y; }

};

}
using fyz::Point;

static inline double distance(Point &x0, Point &x1)
{
   return  sqrt ( (x1.x - x0.x) *  (x1.x - x0.x) + (x1.y - x0.y) *  (x1.y - x0.y));
}

static inline double distance2(Point &x0, Point &x1)
{
   return  ( (x1.x - x0.x) *  (x1.x - x0.x) + (x1.y - x0.y) *  (x1.y - x0.y));
}

static inline bool isOnPoint(Point &x, Point &y)
{
    return distance2(x, y) <= 16;
}

#endif
