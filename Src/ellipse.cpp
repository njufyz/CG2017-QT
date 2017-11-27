#include "ellipse.h"
#include"common.h"
#include<QDebug>

void Ellipse::MidpointEllipse()
{
    if(rx ==0 || ry == 0)
        return;

    int cx = c.x;
    int cy = c.y;
    int x = 0;
    int y = ry;

    if(isSelected)
    {
      drawborder();
      glPointSize(gproperty.point_size + 4);
    }

    setpixel_4(cx, cy, x, y);
    setpixel_4(cx, cy, rx, 0);

    int k = 0;
    for(; ry * ry * x <= rx * rx * y; x++ )
    {
        k = fEllipse(x + 1 , y - 0.5);
        if(k < 0)
        {
            setpixel_4(cx, cy, x + 1, y);
        }
        else
        {
            setpixel_4(cx, cy, x + 1, y - 1);
            y--;
        }
    }

    for(; y>=0; y--)
    {
        k = fEllipse(x + 0.5 , y - 1);
        if(k > 0)
        {
            setpixel_4(cx, cy, x, y - 1);
        }
        else
        {
            setpixel_4(cx, cy, x + 1, y - 1);
            x++;
        }
    }

    glPointSize(gproperty.point_size);
}

int Ellipse::fEllipse(double x, double y)
{
    double k = (ry * ry) * (x * x) + (rx * rx) * (y * y) - (rx * rx) * (ry * ry);

    if(k < 0 )
        return -1;

    else if(k == 0)
        return 0;

    else
        return 1;
}

//画边框
void Ellipse::drawborder()
{
    drawControlPoint(lb);
    drawControlPoint(lt);
    drawControlPoint(rb);
    drawControlPoint(rt);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable( GL_LINE_STIPPLE);
    glLineStipple( 2.0, 0x0F0F);
    glLineWidth(2.5);
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


bool Ellipse::containsPoint(int x, int y)
{
    double a2 = rx * rx;
    double b2 = ry * ry;
    double x2 = (x - c.x) * (x - c.x);
    double y2 = (y - c.y) * (y - c.y);

    if(rx >= ry)
    {
       return  (abs(x2/a2 + y2/b2 - 1) <= 0.05) ;
    }
    else
    {
       return  (abs(x2/b2 + y2/a2 - 1) <= 0.05) ;
    }

}

void Ellipse::translate(int x, int y)
{
    c.x += x;
    c.y += y;

    lb.x += x;
    lb.y += y;
    rb.x += x;
    rb.y += y;
    rt.x += x;
    rt.y += y;
    lt.x += x;
    lt.y += y;
}

bool Ellipse::isPointInRect(int x, int y)
{
    return (x >= c.x -rx) && (x <= c.x + rx) && (y >= c.y - ry) && (y <= c.y + ry);
}
