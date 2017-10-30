#ifndef LINE_H
#define LINE_H

#include"common.h"

void DDALine(int x1, int y1, int x2, int y2, QColor &c);
void BresenhamLine(int x, int y, int, int, QColor &);
void bresenham_line(int x1, int y1, int x2, int y2, QColor &c);

class Line :
	public Graph
{
	Point start;
	Point end;
public:
	Line() {}
	Line(Point x, Point y) 
	{ 
        this->color = Pcolor;
		start = x;
		end = y;
	}
	Line(int x0, int y0, int x1, int y1)
	{
        this->color = Pcolor;
		start = Point(x0, y0);
		end = Point(x1, y1);
	}

	void draw()
	{
        BresenhamLine(start.x, start.y, end.x, end.y, this->color);
	}
};

#endif
