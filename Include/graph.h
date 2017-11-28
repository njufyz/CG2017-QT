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
    virtual void drawborder() = 0;
    virtual bool containsPoint(float x, float y) = 0;
    virtual bool isPointInRect(float x, float y) = 0;
    virtual void translate(float x, float y) = 0;
    virtual void rotate(float x, float y, double theta) = 0;

    virtual void draw();
    void setSelect(bool set){
        isSelected = set;
    }

protected:
    QVector<Point> vertexes;

    bool isSelected;
    Property property;

    void setpixel(int x, int y);
    void setpixel_8(int cx, int cy, int x, int y);
    void setpixel_4(int cx, int cy, int x, int y);
    virtual void generateVertexes() = 0;




};

void drawControlPoint(Point &a);

static inline Point Rotate(Point cc, float xr, float yr, double theta)
{
     float x2 = xr + (cc.x - xr) * cos(theta) - (cc.y - yr) * sin(theta);
     float y2 = yr + (cc.x - xr) * sin(theta) + (cc.y - yr) * cos(theta);

     return Point(x2, y2);
}

#endif

