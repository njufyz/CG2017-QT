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

    void generateVertexes();

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

         generateVertexes();

    }
    //override

    void drawborder();

    bool containsPoint(float x, float y);

    void translate(float x, float y);

    bool isPointInRect(float x, float y);

    void rotate(float x, float y, double theta);


private:
    void MidpointEllipse();
    int fEllipse(double x, double y);
};

#endif // ELLIPSE_H
