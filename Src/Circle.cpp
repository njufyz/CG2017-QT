#include "Circle.h"
#include"common.h"


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

//画边框
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

    float r = gproperty.color.redF(), g = gproperty.color.greenF(), b = gproperty.color.blueF();
    glColor3f(r, g, b);

}

bool Circle::containsPoint(float x, float y)
{
    return  (fabs( (x-cc.x)*(x-cc.x) + (y-cc.y)*(y-cc.y) - r*r ) <= 1000);
}

void Circle::translate(float x, float y)
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
    generateVertexes();

}

bool Circle::isPointInRect(float x, float y)
{
    return (x >= cc.x - r) && (x <= cc.x + r) && (y >= cc.y - r) &&(y <= cc.y + r);
}

void Circle::rotate(float xr, float yr, double theta)
{
    cc = Rotate(cc, xr, yr, theta);

    lb = Point(cc.x - r -1, cc.y - r - 1);
    rb = Point(cc.x + r + 1,cc.y - r - 1);
    rt = Point(cc.x + r + 1,cc.y + r + 1);
    lt = Point(cc.x - r - 1,cc.y + r + 1);

    vertexes.clear();
    generateVertexes();
}
