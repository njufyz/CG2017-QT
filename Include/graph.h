#ifndef GRAPH_H
#define GRAPH_H
#include <glu.h>
class  Graph
{
public:
	Graph() {}
	virtual void draw() = 0;

protected:
	int type;

};

static inline void setpixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0);
	glEnd();
}

static inline void setpixel_8(int cx, int cy, int x, int y)
{
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

