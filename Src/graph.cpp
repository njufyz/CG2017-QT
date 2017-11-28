#include"graph.h"
#include"common.h"
#ifdef __APPLE__
#include<glu.h>
#else
#include<Windows.h>
#include<gl/glut.h>
#endif

#include<QColor>


void Graph::draw()
{
    QColor c = property.color;
    glColor3f(c.redF(), c.greenF(), c.blueF());

    if(isSelected)
    {
      drawborder();
      glPointSize(gproperty.point_size + 4);
    }

    glBegin(GL_POINTS);
    for(auto i:vertexes)
    {
         glVertex3f(i.x, i.y, 0);
    }
    glEnd();

    glPointSize(gproperty.point_size);
}

void Graph::setpixel(int x, int y)
{
    vertexes.push_back(Point(x, y));
}

void Graph::setpixel_8(int cx, int cy, int x, int y)
{
    vertexes.push_back(Point(x + cx, y + cy));
    vertexes.push_back(Point(x + cx, -y + cy));
    vertexes.push_back(Point(y + cx, x + cy));
    vertexes.push_back(Point(y + cx, -x + cy));
    vertexes.push_back(Point(-x + cx, -y + cy));
    vertexes.push_back(Point(-x + cx, y + cy));
    vertexes.push_back(Point(-y + cx, -x + cy));
    vertexes.push_back(Point(-y + cx, x + cy));

}

void Graph::setpixel_4(int cx, int cy, int x, int y)
{
    vertexes.push_back(Point(x + cx, y + cy));
    vertexes.push_back(Point(-x + cx, y + cy));
    vertexes.push_back(Point(x + cx, -y + cy));
    vertexes.push_back(Point(-x + cx, -y + cy));
}

void drawControlPoint(Point &a)
{
    int x = a.x;
    int y = a.y;

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(10.0);

    glBegin(GL_POINTS);
        glVertex3f(x, y, 0);
    glEnd();

    QColor c = gproperty.color;
    glColor3f(c.redF(), c.greenF(), c.blueF());
    glPointSize(gproperty.point_size);

}
