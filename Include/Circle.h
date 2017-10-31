#ifndef CIRCLE_H
#define CIRCLE_H

#include "graph.h"
#include "common.h"

class Circle :
	public Graph
{
	Point cc;
    int r;

public:
	Circle() {}

    Circle(Point cc, double r)
    {
        this->property = gproperty;
        this->cc = cc;
        this->r = r;
    }

    Circle(int cx, int cy, double r)
	{
        this->property = gproperty;
		cc = Point(cx, cy);
		this->r = r;
	}

    void MidpointCircle();

    //override
	void draw()
	{
        MidpointCircle();
	}

};

#endif
