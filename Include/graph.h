#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include "Point.h"
#include"property.h"

class  Graph
{
public:
    Graph() {}
    virtual ~Graph() {}

    virtual void draw();
    virtual void drawborder() = 0;
    virtual bool containsPoint(double x, double y) = 0;
    virtual bool isPointInRect(double x, double y) = 0;
    virtual void translate(double x, double y) = 0;
    virtual void rotate(double x, double y, double theta) = 0;
    virtual void scale(Point cc, double scale) = 0;

    void setSelect(bool set)
    {
        isSelected = set;
    }

    void setFill(bool set)
    {
        isFilled = set;
    }

    void setColor(QColor c)
    {
        property.color = c;
    }

    void setProperty(Property &p)
    {
        this->property = p;
    }

    bool getFill()
    {
        return isFilled;
    }

protected:
    Property property;
    QVector<Point> vertexes;
    QVector<Point> vertexes_inside;
    bool isSelected;
    bool isFilled;
    virtual void generateVertexes() = 0;

    void setpixel(int x, int y);
    void setpixel_inside(int x, int y);

    void setpixel_8(int cx, int cy, int x, int y);
    void setpixel_8_inside(int cx, int cy, int x, int y);

    void setpixel_4(int cx, int cy, int x, int y);
    void setpixel_4_inside(int cx, int cy, int x, int y);

};


static inline Point Rotate(Point cc, double xr, double yr, double theta)
{
     double x2 = xr + (cc.x - xr) * cos(theta) - (cc.y - yr) * sin(theta);
     double y2 = yr + (cc.x - xr) * sin(theta) + (cc.y - yr) * cos(theta);

     return Point(x2, y2);
}

static inline Point Scale(Point cc, Point s, double scale)
{
     double x2 = s.x * scale + cc.x * (1 - scale);
     double y2 = s.y * scale + cc.y * (1 - scale);

     return Point(x2, y2);
}

#endif

