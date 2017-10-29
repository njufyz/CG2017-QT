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

static inline double distance(Point &x0, Point &x1)
{
   return sqrt ( (x1.x - x0.x) *  (x1.x - x0.x) + (x1.y - x0.y) *  (x1.y - x0.y));
}

#endif
