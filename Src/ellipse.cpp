#include "ellipse.h"
#include"common.h"

void Ellipse::drawborder()
{

}

void Ellipse::MidpointEllipse()
{
    if(rx ==0 || ry == 0)
        return;

    int cx = c.x;
    int cy = c.y;
    int x = 0;
    int y = ry;

    setpixel_4(cx, cy, x, y);
    setpixel_4(cx, cy, rx, 0);

    int k = 0;
    for(; ry * ry * x <= rx * rx * y; x++ )
    {
        k = fEllipse(x + 1 , y - 0.5);
        if(k < 0)
        {
            setpixel_4(cx, cy, x + 1, y);
        }
        else
        {
            setpixel_4(cx, cy, x + 1, y - 1);
            y--;
        }
    }

    setpixel_4(cx, cy, x + 1, y);

    for(; y>=0; y--)
    {
        k = fEllipse(x + 0.5 , y - 1);
        if(k > 0)
        {
            setpixel_4(cx, cy, x, y - 1);
        }
        else
        {
            setpixel_4(cx, cy, x + 1, y - 1);
            x++;
        }
    }

}

int Ellipse::fEllipse(double x, double y)
{
    double k = (ry * ry) * (x * x) + (rx * rx) * (y * y) - (rx * rx) * (ry * ry);

    if(k < 0 )
        return -1;

    else if(k == 0)
        return 0;

    else
        return 1;
}
