#ifndef POINT_H
#define POINT_H
#include<cmath>

struct Point
{
    double x;
    double y;
	Point() { x = 0; y = 0; }
    Point(double x, double y) { this->x = x; this->y = y; }

};

static inline double distance(Point &x0, Point &x1)
{
   return  sqrt ( (x1.x - x0.x) *  (x1.x - x0.x) + (x1.y - x0.y) *  (x1.y - x0.y));
}

static inline double distance2(Point &x0, Point &x1)
{
   return  ( (x1.x - x0.x) *  (x1.x - x0.x) + (x1.y - x0.y) *  (x1.y - x0.y));
}


//static inline Point operator+(Point &a, Point &b)
//{
//    return Point(a.x + b.x, a.y +b.y);
//}

//static inline Point operator/(Point a, int b)
//{
//    return Point(a.x/b, a.y/b);
//}

#endif
