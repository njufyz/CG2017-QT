#include "Circle.h"
#include"common.h"
#include<algorithm>

using fyz::Circle;

void Circle::generateVertexes()
{
    MidpointCircle();
}

void Circle::setControlPoints()
{
    controlPoints[0] = Point(cc.x -r -1, cc.y - r - 1);
    controlPoints[1] = Point(cc.x + r + 1,cc.y - r - 1);
    controlPoints[2] = Point(cc.x + r + 1,cc.y + r + 1);
    controlPoints[3] = Point(cc.x - r - 1,cc.y + r + 1);

}

void Circle::MidpointCircle()
{
    int x0 = this->cc.x;
    int y0 = this->cc.y;
    int R = this->r;

    int  x = 0;
    int  y = R;
    int  d = 1 - R;
    int  deltax = 3;
    int  deltay = 5 - 2 * R;

    for(; x <= y; x++)
    {
        setpixel_8(x0, y0, x, y);

        //if(isFilled)
        //{
            for(int i = 0; i < y; i++)
                 setpixel_8_inside(x0, y0, x, i);
        //}

        if(d < 0)
        {
            d += deltax;
            deltax += 2;
            deltay += 2;
        }

        else
        {
            d += deltay;
            deltax += 2;
            deltay += 4;
            y--;
         }
    }
}

void Circle::drawborder()
{  
    drawControlPoint(cc);
    for(auto &i:controlPoints)
        drawControlPoint(i);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable( GL_LINE_STIPPLE);
    glLineStipple( 2.0, 0x0F0F);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
    for(auto i : controlPoints)
        glVertex3f(i.x,i.y, 0);
    glEnd();

    double r = property.color.redF(), g = property.color.greenF(), b = property.color.blueF();
    glColor3f(r, g, b);

}

bool Circle::containsPoint(double x, double y)
{
    return  (fabs( (x-cc.x)*(x-cc.x) + (y-cc.y)*(y-cc.y) - r*r ) <= 1000);
}

void Circle::translate(double x, double y)
{
    cc.x += x;
    cc.y += y;

    for(auto &i : controlPoints)
    {
        i.x += x;
        i.y += y;
    }
    vertexes.clear();
    vertexes_inside.clear();
    generateVertexes();

}

int Circle::containsControlPoint(double x, double y)
{
    Point p(x, y);
   for(int i =0 ; i < 4; i++)
   {
       if(isOnPoint(p, controlPoints[i]))
           return i;
   }
   return -1;
}

void Circle::rotate(double xr, double yr, double theta)
{
    cc = Rotate(cc, xr, yr, theta);
    setControlPoints();

    vertexes.clear();
    vertexes_inside.clear();
    generateVertexes();
}

void Circle::scale(fyz::Point c, double scale)
{
    cc = Scale(c, cc, scale);
    r *= scale;

    setControlPoints();

    vertexes.clear();
    vertexes_inside.clear();
    generateVertexes();
}

void Circle::edit(int x, int y, int index)
{

    int forward = (index + 5) % 4;
    int backward =(index + 3) % 4;
    double px = 0, py = 0, k =1;
    if(index == 1 || index == 3)
    {
       k = -1;
    }
    px = (k * controlPoints[index].x + x / k + y - controlPoints[index].y) / (1 / k + k);
    py = -1 / k * (px - x) + y;

    controlPoints[index].x = px;
    controlPoints[index].y = py;

    if(index == 1 || index == 3)
    {
        controlPoints[forward].x = px;
        controlPoints[backward].y = py;
    }
    else
    {
        controlPoints[forward].y = py;
        controlPoints[backward].x = px;
    }

    r =fabs(((controlPoints[1].x - controlPoints[0].x) - 2)/2);
    cc.x = fabs((controlPoints[0].x + controlPoints[2].x)/2);
    cc.y = fabs((controlPoints[0].y + controlPoints[2].y)/2);

    vertexes.clear();
    vertexes_inside.clear();
    generateVertexes();
}

