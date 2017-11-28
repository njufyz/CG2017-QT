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
    double angle;

    void generateVertexes();

public:

    Ellipse()   {}
    Ellipse(Point c, int ra, int rb)
    {
        isSelected = true;
        isFilled   = true;

        this->c = c;
        this->rx = ra;
        this->ry = rb;
        this->property = gproperty;

        this->lb = Point(c.x - rx - 1,c.y - ry - 1);
        this->rb = Point(c.x + rx + 1,c.y - ry - 1);
        this->rt = Point(c.x + rx + 1,c.y + ry + 1);
        this->lt = Point(c.x - rx - 1,c.y + ry + 1);

         generateVertexes();

    }
    //override

    void drawborder();

    bool containsPoint(double x, double y);

    void translate(double x, double y);

    bool isPointInRect(double x, double y);

    void rotate(double x, double y, double theta);



private:
    void MidpointEllipse();
    int fEllipse(double x, double y);
};

#endif // ELLIPSE_H
