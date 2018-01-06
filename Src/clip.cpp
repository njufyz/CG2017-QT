#include "common.h"
#include <QVector>
#include<algorithm>

using fyz::Line;
using fyz::Point;

const short leftBitCode=0x1;
const short rightBitCode=0x2;
const short buttonBitCode=0x4;
const short topBitCode=0x8;

inline short inside(short code)
{
    return short(!code);
}   //判断点是否在裁剪区内

inline short reject(short code1,short code2)
{
    return short(code1 & code2);
}    //判断能否完全排除一条线段

inline short accept(short code1,short code2)
{
    return short(!(code1 | code2));
}   //判断能否完全接受一条线段

inline void swapPoint(Point& a,Point& b)
{
    Point t=a;
    a=b;
    b=t;
}  //交换两个点

inline void swapCode(short& a,short& b)
{
    short t=a;
    a=b;
    b=t;
}   //交换两个区域码

short encode(Point &p,QVector<Point>Rect)
{
    short code=0x00;
    double right = std::max_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.x < b.x);})->x;
    double left = std::min_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.x < b.x);})->x;
    double top = std::max_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.y < b.y);})->y;
    double bottom = std::min_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.y < b.y);})->y;

    if(p.x<left)
        code |= leftBitCode;
    if(p.x>right)
        code |= rightBitCode;
    if(p.y<bottom)
        code |= buttonBitCode;
    if(p.y>top)
        code |= topBitCode;
    return code;
}

bool Line::clip(QVector<Point>Rect){


    short code1, code2;
    bool done = false;
    double k = 0;
    double right = std::max_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.x < b.x);})->x;
    double left = std::min_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.x < b.x);})->x;
    double top = std::max_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.y < b.y);})->y;
    double bottom = std::min_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.y < b.y);})->y;

    while(!done)
    {
        code1 = encode(start,Rect);
        code2 = encode(end, Rect);

        if(accept(code1,code2))         //当前直线能完全绘制
            return true;

        else
        {
            if(reject(code1,code2))     //当前直线能完全排除
                return false;

            else
            {
                if(inside(code1))   //若start端点在裁剪区内则交换两个端点使它在裁剪区外
                {
                    swapPoint(start,end);
                    swapCode(code1,code2);
                }
                //计算斜率
                if(start.x != end.x)
                    k = k = (end.y - start.y)/(end.x - start.x);
                //开始裁剪,以下与运算若结果为真，
                //则start在边界外，此时将start移向直线与该边界的交点
                if(code1 & leftBitCode)
                {
                    start.y += (left-start.x)*k;
                    start.x = left;
                }
                else if(code1 & rightBitCode)
                {
                    start.y += (right-start.x)*k;
                    start.x = right;
                }
                else if(code1 & buttonBitCode)
                {
                    if(start.x != end.x)
                        start.x += (bottom-start.y)/k;
                    start.y = bottom;
                }
                else if(code1 & topBitCode)
                {
                    if(start.x != end.x)
                        start.x += (top-start.y)/k;
                    start.y = top;
                }
            }
        }
    }
}
