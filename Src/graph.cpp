#include"graph.h"

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
