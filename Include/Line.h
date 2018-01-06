#ifndef LINE_H
#define LINE_H
#include"common.h"

namespace fyz{

class Line :
    public Graph
{
     Point start;
     Point end;

    void generateVertexes();
    void BresenhamLine();

public:
	Line() {}
    ~Line() {}
	Line(Point x, Point y) 
	{ 
        isSelected = true;
        isFilled   = false;
        this->property = gproperty;
		start = x;
		end = y;

        generateVertexes();
	}

	Line(int x0, int y0, int x1, int y1)
	{
        isSelected = true;
        this->property = gproperty;
		start = Point(x0, y0);
		end = Point(x1, y1);

         generateVertexes();
	}


     //override

    void drawborder();

    bool containsPoint(double x, double y);

    void translate(double x, double y);

    int containsControlPoint(double x, double y);

    void rotate(double x, double y, double theta);

    void scale(Point cc, double scale);

    void edit(int x, int y, int index);

    bool clip(QVector<Point>Rect);

};

}
#endif
