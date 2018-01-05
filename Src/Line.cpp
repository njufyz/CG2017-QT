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


//    int x = x0;
//    int y = y0;

//    int stepx = 1, stepy = 1;

//    int dx = x1 - x0;
//    int dy = y1 - y0;


//    if (dx < 0)
//    {
//        dx = -dx;
//        stepx = -1;
//    }

//    if (dy < 0)
//    {
//        dy = -dy;
//        stepy = -1;
//    }

//    if (dx > dy)
//    {

//        int p = 2 * dy - dx;
//        for(;x != x1; x += stepx)
//       {
//           setpixel(x, y);
//           if (p >= 0)
//           {
//              y += stepy;
//              p += 2 * (dy - dx);
//           }
//           else
//           {
//               p += 2 * dy;
//           }
//        }

//     }
//    else
//    {
//        int p = 2 * dx - dy;
//        for (; y != y1; y += stepy)
//        {
//            setpixel(x, y);
//            if (p >= 0)
//            {
//                x += stepx;
//                p += 2 * (dx - dy);
//            }
//           else
//            {
//                p += 2 * dx;
//            }
//        }
//    }

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (setpixel(x0, y0), x0 != x1 || y0 != y1) {
        int e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
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

        return (fabs(dis) < 4) && ( y>= MIN(start.y, end.y) && y <= MAX(start.y, end.y));
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

int Line::containsControlPoint(double x, double y)
{
    Point p(x, y);

    if(isOnPoint(start, p))
        return 0;
    else if(isOnPoint(end, p))
        return 1;

    return -1;
}

void Line::rotate(double x, double y, double theta)
{
   start = Rotate(start, x, y, theta);
   end = Rotate(end, x, y, theta);

   vertexes.clear();
   generateVertexes();
}

void Line::scale(fyz::Point cc, double scale)
{
    start = Scale(cc, start, scale);
    end = Scale(cc, end, scale);

    vertexes.clear();
    generateVertexes();
}

void Line::edit(int x, int y, int index)
{
    if(index == 1)
        end = Point(x, y);
    else
        start = Point(x, y);

    vertexes.clear();
    generateVertexes();
}

