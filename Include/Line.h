#ifndef LINE_H
#define LINE_H
#include"common.h"

class Line :
	public Graph
{

	Point start;
	Point end;
public:
	Line() {}

	Line(Point x, Point y) 
	{ 
        this->property = gproperty;
		start = x;
		end = y;
	}

	Line(int x0, int y0, int x1, int y1)
	{
        this->property = gproperty;
		start = Point(x0, y0);
		end = Point(x1, y1);
	}

    void BresenhamLine();

     //override
	void draw()
	{
        BresenhamLine();
	}
};

#endif
