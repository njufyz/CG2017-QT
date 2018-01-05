#include "bezier.h"
#include"common.h"
#include<QVector>
using fyz:: Bezier;

void  Bezier::generateVertexes()
{
    vertexes.clear();
    for(double t = 0; t< 1; t += 0.005)
    {
        Point p = computeBezier(controlPoints, t);
        vertexes.push_back(p);
    }
}

fyz::Point Bezier::computeBezier(QVector<Point> &p, double t)
{
    int n = p.size();
    double *xarray = new double[n];
    double *yarray = new double[n];
    for(int i = 0 ;i< n; i++)
    {
        xarray[i] = p[i].x;
        yarray[i] = p[i].y;
    }

    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < n - i; j++)
        {
            xarray[j] = xarray[j] * (1 - t) + xarray[j + 1] * t;
            yarray[j] = yarray[j] * (1 - t) + yarray[j + 1] * t;

        }
    }
    return Point(xarray[0], yarray[0]);
}


 Bezier::Bezier()
{
     isSelected = true;
     isFilled   = false;
     this->property = gproperty;
     controlPoints.reserve(8);
 }

 Bezier::Bezier(QVector<fyz::Point> &p)
 {
     controlPoints = p;
 }

 void Bezier::addContorlPoint(fyz::Point p)
 {
     controlPoints.push_back(p);
     if(controlPoints.size() >= 2)
        generateVertexes();
 }

 void Bezier::draw()
 {
     QColor c = property.color;
     glColor3f(c.redF(), c.greenF(), c.blueF());

//     if(isSelected)
//     {
//       drawborder();
//       glPointSize(gproperty.point_size + 3);
//     }

     glBegin(GL_LINE_STRIP);
     for(auto i:vertexes)
     {
          glVertex3f(i.x, i.y, 0);
     }
     glEnd();

//     if(isFilled)
//     {
//          glPointSize(gproperty.point_size + 6);
//          glBegin(GL_POINTS);
//          for(auto i:vertexes_inside)
//               glVertex3f(i.x, i.y, 0);
//          glEnd();
//     }

//     glPointSize(gproperty.point_size);
 }

void  Bezier::drawborder()
{
    for(auto i: controlPoints)
        drawControlPoint(i);
}

bool Bezier::containsPoint(double x, double y)
{

}

void  Bezier::translate(double x, double y)
{

}

int  Bezier::containsControlPoint(double x, double y)
{

}

void  Bezier::rotate(double x, double y, double theta)
{

}

void  Bezier::scale( Point cc, double scale)
{

}

void  Bezier::edit(int x, int y, int index)
{

}
