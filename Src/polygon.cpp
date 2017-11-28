#include "polygon.h"
#include "common.h"

void Polygon::generateVertexes()
{
    for(auto i = lines.begin(); i!= lines.end(); i++)
    {

    }
}

Polygon::Polygon()
{

}

void Polygon::translate(float x, float y)
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

bool Polygon::isPointInRect(float x, float y)
{
    return containsPoint(x, y);
}

void Polygon::rotate(float x, float y, double theta)
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
