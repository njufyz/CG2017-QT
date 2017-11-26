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

public:

    Ellipse()   {}
    Ellipse(Point c, int ra, int rb)
    {
        this->c = c;
        this->rx=ra;
        this->ry=rb;
        this->property = gproperty;
    }
    //override
    void draw()
    {
        MidpointEllipse();
    }

private:
    void MidpointEllipse();
    int fEllipse(double x, double y);
};

#endif // ELLIPSE_H
