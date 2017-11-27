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
    ~Line() {}
	Line(Point x, Point y) 
	{ 
        isSelected = true;
        this->property = gproperty;
		start = x;
		end = y;
	}

	Line(int x0, int y0, int x1, int y1)
	{
        isSelected = true;
        this->property = gproperty;
		start = Point(x0, y0);
		end = Point(x1, y1);
	}

     //override
    void draw()
	{
        BresenhamLine();
	}

    void drawborder();

    bool containsPoint(int x, int y);

    void translate(int x, int y);

    bool isPointInRect(int x, int y)
    {
        return containsPoint(x, y);
    }

    void rotate(int x, int y, double theta);

private:
     void BresenhamLine();
};

#endif
