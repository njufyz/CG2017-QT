#ifndef CIRCLE_H
#define CIRCLE_H

#include "graph.h"
#include "common.h"

void Midpoint_circle(int cx, int cy, int r, QColor &c);

class Circle :
	public Graph
{
	Point cc;
    int r;

public:
	Circle() {}

    Circle(Point cc, double r) { this->color = Pcolor; this->cc = cc; this->r = r; }

    Circle(int cx, int cy, double r)
	{
        this->color = Pcolor;
		cc = Point(cx, cy);
		this->r = r;
	}

	void draw()
	{
        Midpoint_circle(cc.x, cc.y, r, this->color);
	}

};

#endif
