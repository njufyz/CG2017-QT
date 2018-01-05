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

    double* xarray = new double[n];
    double* yarray = new double[n];

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

    Point ret(xarray[0], yarray[0]);
    delete[] xarray;
    delete[] yarray;

    return ret;
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
     isSelected = true;
     isFilled   = false;
     this->property = gproperty;
     controlPoints.reserve(8);

     for(int i = 0; i<p.size(); i++)
         controlPoints.push_back(Point(p[i].x, p[i].y));
     generateVertexes();
 }

 void Bezier::addContorlPoint(fyz::Point p)
 {
     controlPoints.push_back(p);
     if(controlPoints.size() >= 2)
        generateVertexes();
 }

 void Bezier::draw()
 {
     glLineWidth(gproperty.point_size);
     QColor c = property.color;
     glColor3f(c.redF(), c.greenF(), c.blueF());

     if(isSelected)
     {
       drawborder();
       glLineWidth(gproperty.point_size + 3);
     }

     glBegin(GL_LINE_STRIP);
     for(auto i:vertexes)
     {
          glVertex3f(i.x, i.y, 0);
     }
     glEnd();

     glLineWidth(gproperty.point_size);
 }

void  Bezier::drawborder()
{
    glEnable( GL_LINE_STIPPLE);
    glLineStipple( 2.0, 0x0F0F);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
    for(auto i : controlPoints)
        glVertex3f(i.x, i.y, 0);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    for(auto i: controlPoints)
        drawControlPoint(i);

    QColor c = property.color;
    glColor3f(c.redF(), c.greenF(), c.blueF());
}

bool Bezier::containsPoint(double x, double y)
{
    Point tmp = Point(x, y);
    for(auto i: vertexes)
    {
        if(isOnPoint(i, tmp))
            return true;
    }
    return false;
}

void  Bezier::translate(double x, double y)
{
    for(auto &i : controlPoints)
    {
        i.x += x;
        i.y += y;
    }
    generateVertexes();
}

int  Bezier::containsControlPoint(double x, double y)
{
    Point tmp = Point(x, y);
    for(int i = 0; i<controlPoints.size(); i++)
    {
        if(isOnPoint(controlPoints[i], tmp))
            return i;

    }
    return -1;
}

void  Bezier::rotate(double x, double y, double theta)
{
    for(auto &i : controlPoints)
    {
        i = Rotate(i, x, y, theta);
    }
    generateVertexes();
}

void  Bezier::scale( Point cc, double scale)
{
    for(auto &i : controlPoints)
    {
        i = Scale(cc, i, scale);
    }
    generateVertexes();
}

void  Bezier::edit(int x, int y, int index)
{
    controlPoints[index].x = x;
    controlPoints[index].y = y;
    generateVertexes();
}
