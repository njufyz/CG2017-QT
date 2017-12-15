#ifndef CIRCLE_H
#define CIRCLE_H

#include "graph.h"
#include "common.h"

namespace fyz{

class Circle :
	public Graph
{

	Point cc;
    int r;

    Point lb, rb, rt, lt;           //border

    void generateVertexes();

public:
	Circle() {}
    Circle(Point cc, int r)
    {
        isSelected = true;
        isFilled   = false;
        this->property = gproperty;
        this->cc = cc;
        this->r = r;

        lb = Point(cc.x -r -1, cc.y - r - 1);
        rb = Point(cc.x + r + 1,cc.y - r - 1);
        rt = Point(cc.x + r + 1,cc.y + r + 1);
        lt = Point(cc.x - r - 1,cc.y + r + 1);

        generateVertexes();
    }

    Circle(int cx, int cy, int r)
	{
        isSelected = true;
        isFilled   = false;
        this->property = gproperty;
		cc = Point(cx, cy);
		this->r = r;

        lb = Point(cc.x -r -1, cc.y - r - 1);
        rb = Point(cc.x + r + 1,cc.y - r - 1);
        rt = Point(cc.x + r + 1,cc.y + r + 1);
        lt = Point(cc.x - r - 1,cc.y + r + 1);

         generateVertexes();
	}

    void MidpointCircle();

    //override

    void drawborder();

    bool containsPoint(double x, double y);

    void translate(double x, double y);

    bool isPointInRect(double x, double y);

    void rotate(double x, double y, double theta);

    void scale(Point cc, double scale);

};

}
#endif
