#include"graph.h"
#include"common.h"
#ifdef __APPLE__
#include<glu.h>
#else
#include<Windows.h>
#include<gl/glut.h>
#endif

#include<QColor>


void Graph::setpixel(int x, int y)
{
   QColor c = property.color;
   glColor3f(c.redF(), c.greenF(), c.blueF());
   glBegin(GL_POINTS);
   glVertex3f(x, y, 0);
   glEnd();

}

void Graph::setpixel_8(int cx, int cy, int x, int y)
{
    QColor c = property.color;
    glColor3f(c.redF(), c.greenF(), c.blueF());

    glBegin(GL_POINTS);

    glVertex3f(x + cx, y + cy, 0);
    glVertex3f(x + cx, -y + cy, 0);
    glVertex3f(y + cx, x + cy, 0);
    glVertex3f(y + cx, -x + cy, 0);
    glVertex3f(-x + cx, -y + cy, 0);
    glVertex3f(-x + cx, y + cy, 0);
    glVertex3f(-y + cx, -x + cy, 0);
    glVertex3f(-y + cx, x + cy, 0);

    glEnd();

}

void Graph::setpixel_4(int cx, int cy, int x, int y)
{
    QColor c = property.color;
    glColor3f(c.redF(), c.greenF(), c.blueF());

    glBegin(GL_POINTS);

    glVertex3f(x + cx, y + cy, 0);
    glVertex3f(-x + cx, y + cy, 0);
    glVertex3f(x + cx, -y + cy, 0);
    glVertex3f(-x + cx, -y + cy, 0);

    glEnd();

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
