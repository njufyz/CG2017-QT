#ifndef POINT_H
#define POINT_H
#include<cmath>

struct Point
{
	int x;
	int y;
	Point() { x = 0; y = 0; }
	Point(int x, int y) { this->x = x; this->y = y; }
};

static inline int distance(Point &x0, Point &x1)
{
   return (int) sqrt ( (x1.x - x0.x) *  (x1.x - x0.x) + (x1.y - x0.y) *  (x1.y - x0.y));
}

static inline Point operator+(Point &a, Point &b)
{
    return Point(a.x + b.x, a.y +b.y);
}

static inline Point operator/(Point a, int b)
{
    return Point(a.x/b, a.y/b);
}

#endif
