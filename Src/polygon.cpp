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

void Polygon::rotate(int x, int y, double theta)
{
    for(auto cc = points.begin(); cc!=points.end();cc++)
    {
        double x2 = x + (cc->x - x) * cos(theta) - (cc->y - y) * sin(theta);
        double y2 = y + (cc->x - x) * sin(theta) + (cc->y - y) * cos(theta);

        cc->x = x2;
        cc->y = y2;
    }

    lines.clear();

    for(auto i = points.begin(), j = i + 1; j != points.end(); i++, j++)
    {
        Line* p = new Line(*i, *j);
        lines.push_back(*p);
    }

}
