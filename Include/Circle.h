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
    Point controlPoints[4];
    void generateVertexes();
    void setControlPoints();

public:
	Circle() {}
    Circle(Point cc, int r)
    {
        isSelected = true;
        isFilled   = false;
        this->property = gproperty;
        this->cc = cc;
        this->r = r;

        setControlPoints();
        generateVertexes();
    }

    Circle(int cx, int cy, int r)
	{
        isSelected = true;
        isFilled   = false;
        this->property = gproperty;
		cc = Point(cx, cy);
		this->r = r;

        setControlPoints();
        generateVertexes();
	}

    void MidpointCircle();

    //override

    void drawborder();

    bool containsPoint(double x, double y);

    void translate(double x, double y);

    int containsControlPoint(double x, double y);

    void rotate(double x, double y, double theta);

    void scale(Point cc, double scale);

};

}
#endif
