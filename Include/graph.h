#ifndef GRAPH_H
#define GRAPH_H

#include"property.h"


class  Graph
{
public:
    Graph() {}
    virtual void draw() = 0;

protected:
    Property property;

    void setpixel(int x, int y);

    void setpixel_8(int cx, int cy, int x, int y);


};



#endif

