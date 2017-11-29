#include "Circle.h"
#include"common.h"

using fyz::Circle;

void Circle::generateVertexes()
{
    MidpointCircle();
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
    drawControlPoint(lb);
    drawControlPoint(lt);
    drawControlPoint(rb);
    drawControlPoint(rt);
    drawControlPoint(cc);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable( GL_LINE_STIPPLE);
    glLineStipple( 2.0, 0x0F0F);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
        glVertex3f(lb.x,lb.y, 0);
        glVertex3f(rb.x,rb.y, 0);
        glVertex3f(rt.x,rt.y, 0);
        glVertex3f(lt.x,lt.y, 0);
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

    lb.x += x;
    lb.y += y;
    rb.x += x;
    rb.y += y;
    rt.x += x;
    rt.y += y;
    lt.x += x;
    lt.y += y;

    vertexes.clear();
    vertexes_inside.clear();
    generateVertexes();

}

bool Circle::isPointInRect(double x, double y)
{
    return (x >= cc.x - r) && (x <= cc.x + r) && (y >= cc.y - r) &&(y <= cc.y + r);
}

void Circle::rotate(double xr, double yr, double theta)
{
    cc = Rotate(cc, xr, yr, theta);

    lb = Point(cc.x - r -1, cc.y - r - 1);
    rb = Point(cc.x + r + 1,cc.y - r - 1);
    rt = Point(cc.x + r + 1,cc.y + r + 1);
    lt = Point(cc.x - r - 1,cc.y + r + 1);

    vertexes.clear();
    vertexes_inside.clear();
    generateVertexes();
}

