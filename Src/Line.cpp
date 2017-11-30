#include<iostream>

#include"common.h"
#include"Line.h"

using fyz::Line;

void Line::generateVertexes()
{
    BresenhamLine();
}

void Line::BresenhamLine()
{
    int x0 = this->start.x;
    int y0 = this->start.y;
    int x1 = this->end.x;
    int y1 = this->end.y;


    int x = x0;
    int y = y0;

    int stepx = 1, stepy = 1;

    int dx = x1 - x0;
    int dy = y1 - y0;


    if (dx < 0)
    {
        dx = -dx;
        stepx = -1;
    }

    if (dy < 0)
    {
        dy = -dy;
        stepy = -1;
    }

    if (dx > dy)
    {

        int p = 2 * dy - dx;
        for(;x != x1; x += stepx)
       {
           setpixel(x, y);
           if (p >= 0)
           {
              y += stepy;
              p += 2 * (dy - dx);
           }
           else
           {
               p += 2 * dy;
           }
        }

     }
    else
    {
        int p = 2 * dx - dy;
        for (; y != y1; y += stepy)
        {
            setpixel(x, y);
            if (p >= 0)
            {
                x += stepx;
                p += 2 * (dx - dy);
            }
           else
            {
                p += 2 * dx;
            }
        }
    }
}

void Line::drawborder()
{
    glPointSize(property.point_size + 10);
    glColor3f(1.0, 0, 0);

    glBegin(GL_POINTS);
        glVertex3f(start.x, start.y, 0);
        glVertex3f(end.x, end.y, 0);
    glEnd();

    double r = property.color.redF(), g = property.color.greenF(), b = property.color.blueF();
    glColor3f(r, g, b);
    glPointSize(property.point_size);

}

bool Line::containsPoint(double x, double y)
{
    if(start.x == end.x)
    {
        return (abs(x-start.x) < 4 && y>= MIN(start.y, end.y) && y <= MAX(start.y, end.y));
    }
    else
    {
        int  a = end.y - start.y;
        int  b = start.x - end.x;
        int  c = end.x * start.y - start.x * end.y;
        double dis = 1.0 * (a * x + b * y + c)/sqrt(a * a + b * b);

        return fabs(dis) < 4;
    }
}

void Line::translate(double x, double y)
{
    start.x += x;
    start.y += y;

    end.x += x;
    end.y += y;

    vertexes.clear();
    generateVertexes();

}

void Line::rotate(double x, double y, double theta)
{
   start = Rotate(start, x, y, theta);
   end = Rotate(end, x, y, theta);

    vertexes.clear();
    generateVertexes();
}

//basic, not use
/*void bresenham_line(int x1, int y1, int x2, int y2, QColor &c)
{
    int x = x1;
    int y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p = 2 * dy - dx;
    for (; x <= x2; x++)
    {
        setpixel(x, y);
        if (p >= 0)
        {
            y++;
            p += 2 * (dy - dx);
        }
        else
        {
            p += 2 * dy;
        }
    }
}
*/

/*void DDALine(int x1, int y1, int x2, int y2, QColor &c)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    GLdouble delta_x = (GLdouble)dx / (GLdouble)steps;
    GLdouble delta_y = (GLdouble)dy / (GLdouble)steps;
    GLdouble x = x1;
    GLdouble y = y1;

    setpixel(x, y, c);

    for (int k = 1; k <= steps; k++)
    {
        x += delta_x;
        y += delta_y;
        setpixel(x, y, c);
    }
    glFlush();

}
*/
