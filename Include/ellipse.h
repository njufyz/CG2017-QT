#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "graph.h"
#include "common.h"
#include<QVector>
namespace fyz {

class Ellipse:
        public Graph
{
    Point c;
    int   rx;
    int   ry;
    QVector<Point> controlPoints;
    double angle;

    void setControlPoints();
    void generateVertexes();

public:

    Ellipse()   {}
    Ellipse(Point c, int ra, int rb)
    {
        isSelected = true;
        isFilled   = false;
        this->property = gproperty;
        angle = 0;
        this->c = c;
        this->rx = ra;
        this->ry = rb;
        controlPoints.resize(4);
        setControlPoints();
        generateVertexes();

    }
    //override

    void drawborder();

    bool containsPoint(double x, double y);

    void translate(double x, double y);

    int containsControlPoint(double x, double y);

    void rotate(double x, double y, double theta);

    void scale(Point cc, double scale);

    void edit(int x, int y, int index);



private:
    void MidpointEllipse();
    int fEllipse(double x, double y);
};

}
#endif // ELLIPSE_H
