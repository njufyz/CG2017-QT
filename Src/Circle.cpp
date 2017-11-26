#include "Circle.h"
#include"common.h"


void Circle::MidpointCircle()
{
    int x0 = this->cc.x;
    int y0 = this->cc.y;
    int R = this->r;

    int  x = 0;
    int  y = R;
    int  d = 1 - R;
    int  deltax = 3;
    int  deltay = 5 - 2 * R;

    for(; x <= y; x++)
    {
        setpixel_8(x0, y0, x, y);
        if(d < 0)
        {
            d += deltax;
            deltax += 2;
            deltay += 2;

        }

        else
        {
            d += deltay;
            deltax += 2;
            deltay += 4;

            y--;
         }

    }

    if(isSelected)
        drawborder();
}

void Circle::drawborder()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable( GL_LINE_STIPPLE);
    glLineStipple( 4.0f, 0x0F0F0F0F);

    glBegin(GL_POLYGON);
        glVertex3f(cc.x - r - 1,cc.y - r - 1, 0);
        glVertex3f(cc.x + r + 1,cc.y - r - 1, 0);
        glVertex3f(cc.x + r + 1,cc.y + r + 1, 0);
        glVertex3f(cc.x - r - 1,cc.y + r + 1, 0);
    glEnd();
}
