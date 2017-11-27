#include "polygon.h"

Polygon::Polygon()
{

}

void Polygon::translate(int x, int y)
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

bool Polygon::isPointInRect(int x, int y)
{
    return containsPoint(x, y);
}
