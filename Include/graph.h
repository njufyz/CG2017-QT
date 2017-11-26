#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>

#include "Point.h"
#include"property.h"

class  Graph
{
public:
    Graph() {}

    virtual void draw() = 0;
    virtual void drawborder() = 0;

protected:
    bool isSelected;

    Property property;

    void setpixel(int x, int y);

    void setpixel_8(int cx, int cy, int x, int y);

    void setpixel_4(int cx, int cy, int x, int y);

};



#endif

