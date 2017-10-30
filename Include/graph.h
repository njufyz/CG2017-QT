#ifndef GRAPH_H
#define GRAPH_H
#include <glu.h>
#include<QColor>

class  Graph
{ 
public:
    QColor color;
	Graph() {}
	virtual void draw() = 0;

protected:
	int type;

};

static inline void setpixel(int x, int y, QColor &c)
{
    glColor3f(c.redF(), c.greenF(), c.blueF());
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0);
	glEnd();
}

static inline void setpixel_8(int cx, int cy, int x, int y, QColor &c)
{
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

#endif

