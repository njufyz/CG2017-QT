#ifndef BEZIER_H
#define BEZIER_H
#include "graph.h"
#include "common.h"
#include<QVector>

namespace fyz {

class Bezier : public Graph
{
    QVector<Point> controlPoints;
    void generateVertexes();
    Point computeBezier(QVector<Point> &p, double u);

public:
    Bezier();
    Bezier(QVector<Point> &p);
    void addContorlPoint(Point p);

    //override
    void draw();

    void drawborder();

    bool containsPoint(double x, double y);

    void translate(double x, double y);

    int containsControlPoint(double x, double y);

    void rotate(double x, double y, double theta);

    void scale(Point cc, double scale);

    void edit(int x, int y, int index);


};

}

#endif // BEZIER_H
