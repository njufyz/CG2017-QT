#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "graph.h"
#include "common.h"

class Ellipse:
        public Graph
{
    Point c;
    int   rx;
    int   ry;

    Point lb, rb, rt, lt;

public:

    Ellipse()   {}
    Ellipse(Point c, int ra, int rb)
    {
        isSelected = true;
        this->c = c;
        this->rx=ra;
        this->ry=rb;
        this->property = gproperty;

        this->lb = Point(c.x - rx - 1,c.y - ry - 1);
        this->rb = Point(c.x + rx + 1,c.y - ry - 1);
        this->rt = Point(c.x + rx + 1,c.y + ry + 1);
        this->lt = Point(c.x - rx - 1,c.y + ry + 1);

    }
    //override
    void draw()
    {
        MidpointEllipse();
    }

    void drawborder();

    bool containsPoint(int x, int y);

    void translate(int x, int y);

    bool isPointInRect(int x, int y);

    void rotate(int x, int y, double theta);


private:
    void MidpointEllipse();
    int fEllipse(double x, double y);
};

#endif // ELLIPSE_H
