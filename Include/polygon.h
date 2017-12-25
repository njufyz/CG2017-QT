#ifndef POLYGON_H
#define POLYGON_H

#include "graph.h"
#include "common.h"
#include <QVector>

namespace fyz{

struct Edge
{
    double xi;
    double dx;
    double ymax;
};

class Polygon : public Graph
{
    QVector<Point> points;
    QVector<Line> lines;

    double ymax;
    double ymin;

    void generateVertexes() {}

    void getMax_and_Min();
    void InitNewEdgeTable(QVector<QList<Edge>> &Net);
    void ProcessScanLineFill(QVector<QList<Edge>> &Net);
    void InsertAet(QList<Edge> &Net, QList<Edge> &Aet);
    void RemoveEdge(QList<Edge> &Aet, double y);
    void FillAetScanLine(QList<Edge> &Aet, int y);
    void UpdateAet(QList<Edge> &Aet);

public:
    Polygon() {}

    Polygon(QVector<Point> &p): points(p)
    {
        isSelected = true;
        isFilled   = false;
        this->property = gproperty;

        for(auto i = points.begin(), j = i + 1; j != points.end(); i++, j++)
        {
            Line* p = new Line(*i, *j);
            lines.push_back(*p);
        }
        getMax_and_Min();
        fill();
    }

    bool isStartPoint(Point &a)
    {
        return (abs(a.x - points[0].x) <= 4 ) && (abs(a.y - points[0].y) <= 4);
    }


    void draw();

    bool containsPoint(double x, double y);

    void drawborder(){}

    void translate(double x, double y);

    int containsControlPoint(double x, double y);

    void rotate(double x, double y, double theta);

    void fill();

    void scale(Point cc, double scale);

    void edit(int x, int y, int index);
};

}
#endif // POLYGON_H
