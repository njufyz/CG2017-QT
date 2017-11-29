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
    virtual bool containsPoint(double x, double y) = 0;
    virtual bool isPointInRect(double x, double y) = 0;
    virtual void translate(double x, double y) = 0;
    virtual void rotate(double x, double y, double theta) = 0;

    virtual void draw();

    void setSelect(bool set){
        isSelected = set;
    }
    void setFill(bool set){
        isFilled = set;
    }

    void regenerateVertexes(){
        vertexes.clear();
        generateVertexes();
    }

    void setColor(QColor c)
    {
        property.color = c;
    }

protected:

    QVector<Point> vertexes;
    QVector<Point> inside_v;

    bool isSelected;
    bool isFilled;

    Property property;

    void setpixel(int x, int y);

    void setpixel_8(int cx, int cy, int x, int y);
    void setpixel_8_inside(int cx, int cy, int x, int y);

    void setpixel_4(int cx, int cy, int x, int y);
    void setpixel_4_indise(int cx, int cy, int x, int y);

    void drawpixel_4(int cx, int cy, int x, int y, int size);

    virtual void generateVertexes() = 0;
};

static inline Point Rotate(Point cc, double xr, double yr, double theta)
{
     double x2 = xr + (cc.x - xr) * cos(theta) - (cc.y - yr) * sin(theta);
     double y2 = yr + (cc.x - xr) * sin(theta) + (cc.y - yr) * cos(theta);

     return Point(x2, y2);
}

#endif

