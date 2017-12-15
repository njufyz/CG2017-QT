#include "polygon.h"
#include "common.h"
#include <QVector>
#include <QList>
#include <QtAlgorithms>
#include <QDebug>

using fyz::Polygon;
using fyz::Edge;

void Polygon::translate(double x, double y)
{
    for(auto i = points.begin(); i != points.end();i++)
    {
        i->x += x;
        i->y += y;
    }
    for(auto i = vertexes_inside.begin(); i != vertexes_inside.end();i++)
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

bool Polygon::isPointInRect(double x, double y)
{
    return containsPoint(x, y);
}

void Polygon::rotate(double x, double y, double theta)
{
    for(auto cc = points.begin(); cc!=points.end();cc++)
    {
        *cc = Rotate(*cc, x, y, theta);
    }

    for(auto cc = vertexes_inside.begin(); cc!=vertexes_inside.end();cc++)
    {
        *cc = Rotate(*cc, x, y, theta);
    }

    lines.clear();

    for(auto i = points.begin(), j = i + 1; j != points.end(); i++, j++)
    {
        Line* p = new Line(*i, *j);
        lines.push_back(*p);
    }

}

void Polygon::getMax_and_Min()
{
    ymax = std::max_element(points.begin(), points.end(), [](Point a, Point b)->bool{return a.y < b.y;})->y;
    ymin = std::min_element(points.begin(), points.end(), [](Point a, Point b)->bool{return a.y < b.y;})->y;
}


void Polygon::fill()
{
    getMax_and_Min();
    QVector<QList<Edge>>Net(ymax - ymin + 1);
    InitNewEdgeTable(Net);
    ProcessScanLineFill(Net);
}

void Polygon::scale(fyz::Point cc, double scale)
{

}

void Polygon::InitNewEdgeTable(QVector<QList<Edge> > &Net)
{
    Edge e;
    int num = points.size();
    Point tmp = points[num - 1];
    points.pop_back();
    num = points.size();
    for(int m = 0; m < num; m++)
    {
        Point pre, cur_start, cur_end, post;
        pre = points[(m - 1 + num) % num];
        cur_start = points[m];
        cur_end = points[(m + 1) % num];
        post = points[(m + 2) % num];

        if(cur_start.y != cur_end.y)
        {
            e.dx = (cur_end.x - cur_start.x)/(cur_end.y - cur_start.y);

            if(cur_end.y > cur_start.y)
            {
                e.xi = cur_start.x;
                if(post.y >= cur_end.y)
                    e.ymax = cur_end.y - 1;
                else
                    e.ymax = cur_end.y;

                Net[cur_start.y - ymin].push_front(e);
            }
            else
            {
                e.xi = cur_end.x;
                if(pre.y >= cur_start.y)
                    e.ymax = cur_start.y - 1;
                else
                    e.ymax = cur_start.y;

                Net[cur_end.y - ymin].push_front(e);
            }
        }

    }
    points.push_back(tmp);
}

void Polygon::ProcessScanLineFill(QVector<QList<Edge> > &Net)
{
    QList<Edge> Aet;
    for(int i = ymin; i <= ymax; i++)
    {
        InsertAet(Net[i - ymin], Aet);
        FillAetScanLine(Aet, i);
        RemoveEdge(Aet, i);
        UpdateAet(Aet);
    }
}

void Polygon::InsertAet(QList<Edge> &Net, QList<Edge> &Aet)
{
    for(auto i:Net)
        Aet.push_back(i);
    std::sort(Aet.begin(), Aet.end(), [](Edge &a, Edge &b)->bool
    {
        if(a.xi < b.xi)         return true;
        else                    return false;
     });

}

void Polygon::RemoveEdge(QList<Edge> &Aet, double y)
{
   for (auto i = Aet.begin(); i != Aet.end(); )
   {
       if (i->ymax <= y)
           i = Aet.erase(i);
       else
           i++;
   }
}

void Polygon::FillAetScanLine(QList<Edge> &Aet, int y )
{
   for (auto i = Aet.begin(); i != Aet.end(); )
   {
       double x1 = i->xi;
       i++;
       if(i == Aet.end()) break;
       double x2 = i->xi;
       i++;
       for(int j = MIN(x1, x2); j < MAX(x1, x2); j++)
           setpixel_inside(j, y);
   }
}

void Polygon::UpdateAet(QList<Edge> &Aet)
{
    for(auto &i : Aet)
    {
        i.xi += i.dx;
    }

}

void Polygon::draw()
{
    for(auto i = lines.begin(); i!= lines.end(); i++)
    {
        i->setProperty(property);
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

    if(isFilled)
    {
        QColor c = property.color;
        glColor3f(c.redF(), c.greenF(), c.blueF());
        glPointSize(property.point_size + 2);
        glBegin(GL_POINTS);
         for(auto i:vertexes_inside)
              glVertex3f(i.x, i.y, 0);
         glEnd();
    }

    glPointSize(gproperty.point_size);
}

bool Polygon::containsPoint(double x, double y)
{
    for(auto i = lines.begin(); i!=lines.end();i++)
    {
        if(i->containsPoint(x, y))
            return true;
    }
    return false;
}
