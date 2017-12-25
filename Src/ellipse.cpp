#include "ellipse.h"
#include"common.h"

using fyz::Ellipse;

void Ellipse::setControlPoints()
{
    controlPoints[0] = Point(c.x - rx - 1,c.y - ry - 1);
    controlPoints[1] = Point(c.x + rx + 1,c.y - ry - 1);
    controlPoints[2]= Point(c.x + rx + 1,c.y + ry + 1);
    controlPoints[3]= Point(c.x - rx - 1,c.y + ry + 1);
}

void Ellipse::generateVertexes()
{
    MidpointEllipse();
}

void Ellipse::MidpointEllipse()
{
    if(rx ==0 || ry == 0)
        return;

    int cx = c.x;
    int cy = c.y;
    int x = 0;
    int y = ry;

    setpixel_4(cx, cy, x, y);
    setpixel_4(cx, cy, rx, 0);

    int k = 0;

    for(; ry * ry * x <= rx * rx * y; x++ )
    {
        k = fEllipse(x + 1 , y - 0.5);


        for(int i = 0; i < y; i++)
            setpixel_4_inside(cx, cy, x, i);

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

        for(int i = 0; i < y; i++)
            setpixel_4_inside(cx, cy, x, i);

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



void Ellipse::drawborder()
{
    drawControlPoint(c);
    for(auto &i:controlPoints)
        drawControlPoint(i);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable( GL_LINE_STIPPLE);
    glLineStipple( 2.0, 0x0F0F);
    glLineWidth(2.5);
    glColor3f(0.0, 0.0, 0.0);


    glBegin(GL_POLYGON);
    for(auto i : controlPoints)
        glVertex3f(i.x,i.y, 0);
    glEnd();

    double r = property.color.redF(), g = property.color.greenF(), b = property.color.blueF();
    glColor3f(r, g, b);

}


bool Ellipse::containsPoint(double x, double y)
{
    Point p = Rotate(Point(x, y), c.x, c.y, -angle);

    x = p.x;
    y = p.y;

    double a2 = rx * rx;
    double b2 = ry * ry;
    double x2 = (x - c.x) * (x - c.x);
    double y2 = (y - c.y) * (y - c.y);

    return  (fabs(x2/a2 + y2/b2 - 1) <= (0.08 + isFilled * 0.1)) ;

}

void Ellipse::translate(double x, double y)
{
    c.x += x;
    c.y += y;

    for(auto &i : controlPoints)
    {
        i.x += x;
        i.y += y;
    }

    vertexes.clear();
    vertexes_inside.clear();
    generateVertexes();

    for(auto &i : vertexes)
        i = Rotate(i, c.x, c.y, angle);

    for(auto &i : vertexes_inside)
        i = Rotate(i, c.x, c.y, angle);

}

int Ellipse::containsControlPoint(double x, double y)
{
    Point p(x, y);
   for(int i =0 ; i < 4; i++)
   {
       if(isOnPoint(p, controlPoints[i]))
           return i;
   }
   return -1;
}

void Ellipse::rotate(double x, double y, double theta)
{
    c =  Rotate(c, x, y, theta);
    for(auto &i : controlPoints)
        i = Rotate(i, x, y, theta);

    for(auto &i : vertexes)
        i = Rotate(i, x, y, theta);

    for(auto &i : vertexes_inside)
        i = Rotate(i, x, y, theta);

    angle += theta;

}

void Ellipse::scale(fyz::Point cc, double scale)
{
    c = Scale(cc, c, scale);
    rx *= scale;
    ry *= scale;

   setControlPoints();
   for(auto &i : controlPoints)
       i = Rotate(i, c.x, c.y, angle);

    vertexes.clear();
    vertexes_inside.clear();
    generateVertexes();

    for(auto &i : vertexes)
        i = Rotate(i, c.x, c.y, angle);

    for(auto &i : vertexes_inside)
        i = Rotate(i, c.x, c.y, angle);

}

void Ellipse::edit(int x, int y, int index)
{
    Point p(x, y);
    p = Rotate(p, c.x, c.y, -angle);
    x = p.x;
    y = p.y;
    for(auto &i : controlPoints)
        i = Rotate(i, c.x, c.y, -angle);

    int pre = (index + 5) % 4;
    int post =(index + 3) % 4;
    int ops = (index + 2) % 4;

    controlPoints[index] = Point(x, y);
    controlPoints[pre].y = y;
    controlPoints[pre].x = controlPoints[ops].x;
    controlPoints[post].x = x;
    controlPoints[post].y = controlPoints[ops].y;

    for(auto &i : controlPoints)
        i = Rotate(i, c.x, c.y, angle);

    rx = distance(controlPoints[0], controlPoints[1])/2;
    ry = distance(controlPoints[1], controlPoints[2])/2;
    c.x = 1.0 * (controlPoints[0].x + controlPoints[2].x)/2;
    c.y = 1.0 * (controlPoints[0].y + controlPoints[2].y)/2;

    vertexes.clear();
    vertexes_inside.clear();
    generateVertexes();

    for(auto &i : vertexes)
        i = Rotate(i, c.x, c.y, angle);

    for(auto &i : vertexes_inside)
        i = Rotate(i, c.x, c.y, angle);


}
