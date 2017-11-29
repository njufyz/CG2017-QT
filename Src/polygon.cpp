#include "polygon.h"
#include "common.h"

void Polygon::generateVertexes()
{

}

Polygon::Polygon()
{

}

void Polygon::translate(double x, double y)
{
    for(auto i = points.begin(); i != points.end();i++)
    {
        i->x += x;
        i->y += y;
    }
    lines.clear();
    for(auto i = points.begin(), j = i + 1; j != points.end(); i++, j++)
    {
        Line* p = new Line(*i, *j);
        lines.push_back(*p);
    }
}

bool Polygon::isPointInRect(double x, double y)
{
    return containsPoint(x, y);
}

void Polygon::rotate(double x, double y, double theta)
{
    for(auto cc = points.begin(); cc!=points.end();cc++)
    {
        *cc = Rotate(*cc, x, y, theta);
    }

    lines.clear();

    for(auto i = points.begin(), j = i + 1; j != points.end(); i++, j++)
    {
        Line* p = new Line(*i, *j);
        lines.push_back(*p);
    }

}

void Polygon::fill()
{

}
