#include "Circle.h"
#include"common.h"
void bresenham_circle(int cx, int cy, double r)
{
	int x = 0, y = r;
    double p = 3 - 2 * r;
	for (; x <= y; x++)
	{
		setpixel_8(cx, cy, x, y);
		if (p >= 0)
		{
			p += 4 * (x - y) + 10;
			y--;
		}
		else
		{
			p += 4 * x + 6;
		}
	}
}



