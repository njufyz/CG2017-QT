#ifndef CIRCLE_H
#define CIRCLE_H

#include "graph.h"
#include "common.h"

void bresenham_circle(int cx, int cy, double r);

class Circle :
	public Graph
{
	Point cc;
    double r;

public:
	Circle() {}

    Circle(Point cc, double r) { this->cc = cc; this->r = r; }

    Circle(int cx, int cy, double r)
	{
		cc = Point(cx, cy);
		this->r = r;
	}

	void draw()
	{
		bresenham_circle(cc.x, cc.y, r);
	}

	friend void bresenham_circle(int cx, int cy, int r);
};

#endif
