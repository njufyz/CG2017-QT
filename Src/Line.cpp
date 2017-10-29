#include<iostream>
using namespace std;
#include"common.h"
#include"Line.h"
#include<QDebug>
 
void DDALine(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

	GLfloat delta_x = (GLfloat)dx / (GLfloat)steps;
	GLfloat delta_y = (GLfloat)dy / (GLfloat)steps;
	GLfloat x = x1;
	GLfloat y = y1;

	setpixel(x, y);

	for (int k = 1; k <= steps; k++)
	{
		x += delta_x;
		y += delta_y;
		setpixel(x, y);
	}
	glFlush();

}

void BresenhamLine(int x0, int y0, int x1, int y1)
{

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

void bresenham_line(int x1, int y1, int x2, int y2)
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

