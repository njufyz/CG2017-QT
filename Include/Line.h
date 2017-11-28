#ifndef LINE_H
#define LINE_H
#include"common.h"

class Line :
	public Graph
{
	Point start;
	Point end;

    void generateVertexes();

public:
	Line() {}
    ~Line() {}
	Line(Point x, Point y) 
	{ 
        isSelected = true;
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

    bool containsPoint(float x, float y);

    void translate(float x, float y);

    bool isPointInRect(float x, float y)
    {
        return containsPoint(x, y);
    }

    void rotate(float x, float y, double theta);

private:
     void BresenhamLine();
};

#endif
