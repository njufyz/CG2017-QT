#ifndef POLYGON_H
#define POLYGON_H

#include "graph.h"
#include "common.h"
#include <QVector>

class Polygon : public Graph
{
    QVector<Point> points;
    QVector<Line> lines;

public:
    Polygon();
    Polygon(QVector<Point> &p): points(p)
    {
        isSelected = true;
        this->property = gproperty;

        for(auto i = points.begin(), j = i + 1; j != points.end(); i++, j++)
        {
            Line* p = new Line(*i, *j);
            lines.push_back(*p);
        }
    }

    bool isStartPoint(Point &a)
    {
        return (abs(a.x - points[0].x) <= 4 ) && (abs(a.y - points[0].y) <= 4);
    }

    void draw()
    {
        for(auto i = lines.begin(); i!= lines.end(); i++)
        {
            if(isSelected)
            {
                i->setSelect(true);
                i->draw();
            }
            else
            {
                i->setSelect(false);
                i->draw();
            }
        }
    }

    bool containsPoint(int x, int y)
    {
        for(auto i = lines.begin(); i!=lines.end();i++)
        {
            if(i->containsPoint(x, y))
                return true;
        }
        return false;
    }

    void drawborder(){}
};

#endif // POLYGON_H
