#ifndef LINE_H
#define LINE_H
#include"common.h"

void DDALine(int x1, int y1, int x2, int y2);
void BresenhamLine(int x, int y, int, int);
void bresenham_line(int x1, int y1, int x2, int y2);

class Line :
	public Graph
{
	Point start;
	Point end;
public:
	Line() {}
	Line(Point x, Point y) 
	{ 
		start = x;
		end = y;
	}
	Line(int x0, int y0, int x1, int y1)
	{
		start = Point(x0, y0);
		end = Point(x1, y1);
	}

    friend void DDALine(int x1, int y1, int x2, int y2);
    friend void BresenhamLine(int x, int y, int, int);

	void draw()
	{
        BresenhamLine(start.x, start.y, end.x, end.y);
	}
};

#endif
