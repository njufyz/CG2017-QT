#ifndef CIRCLE_H
#define CIRCLE_H

#include "graph.h"
#include "common.h"

class Circle :
	public Graph
{
	Point cc;
    int r;

    Point lb, rb, rt, lt;           //border

public:
	Circle() {}
    Circle(Point cc, int r)
    {
        isSelected = true;
        this->property = gproperty;
        this->cc = cc;
        this->r = r;

        lb = Point(cc.x -r -1, cc.y - r - 1);
        rb = Point(cc.x + r + 1,cc.y - r - 1);
        rt = Point(cc.x + r + 1,cc.y + r + 1);
        lt = Point(cc.x - r - 1,cc.y + r + 1);
    }

    Circle(int cx, int cy, int r)
	{
        isSelected = true;
        this->property = gproperty;
		cc = Point(cx, cy);
		this->r = r;

        lb = Point(cc.x -r -1, cc.y - r - 1);
        rb = Point(cc.x + r + 1,cc.y - r - 1);
        rt = Point(cc.x + r + 1,cc.y + r + 1);
        lt = Point(cc.x - r - 1,cc.y + r + 1);
	}

    void MidpointCircle();

    //override
    void draw()
	{
        MidpointCircle();
	}

    void drawborder();

    bool containsPoint(int x, int y);

    void translate(int x, int y);

    bool isPointInRect(int x, int y);

    void rotate(int x, int y, double theta);


};

#endif
