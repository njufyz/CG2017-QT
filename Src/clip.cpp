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
        {
            vertexes.clear();
            generateVertexes();
            return true;
        }

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
                     k = (end.y - start.y)/(end.x - start.x);
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
    return true;
}

QVector<Point> sutherlandL(double border, QVector<fyz::Point> p);
QVector<Point> sutherlandR(double border, QVector<fyz::Point> p);
QVector<Point> sutherlandT(double border, QVector<fyz::Point> p);
QVector<Point> sutherlandB(double border, QVector<fyz::Point> p);
#include<QDebug>
bool fyz::Polygon::clip(QVector<fyz::Point> Rect)
{
    double right = std::max_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.x < b.x);})->x;
    double left = std::min_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.x < b.x);})->x;
    double top = std::max_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.y < b.y);})->y;
    double bottom = std::min_element(Rect.begin(),Rect.end(), [](Point a, Point b)->bool {return (a.y < b.y);})->y;

    QVector<Point> P = points;
    P = sutherlandL(left, P);
    P = sutherlandT(top, P);
    P = sutherlandR(right, P);
    P = sutherlandB(bottom, P);

    points = P;
    qDebug() << P.size();

    lines.clear();
    vertexes_inside.clear();
    for(auto i = points.begin(), j = i + 1; j != points.end(); i++, j++)
    {
        Line* p = new Line(*i, *j);
        lines.push_back(*p);
    }
    qDebug()<<"finish";
    getMax_and_Min();
    fill();
    return true;

}
//0 1 2 0 size = 4
QVector<Point> sutherlandL(double border, QVector<fyz::Point> p)
{
    QVector<Point> newP;
    double k = 0;
    for(int i =0; i<p.size()-1; i++)
    {
        int j = i + 1;
        if(p[i].x < border && p[j].x < border)
            continue;
        else if(p[i].x < border && p[j].x >= border)
        {
            k = (p[j].y - p[i].y)/(p[j].x - p[i].x);
            double y = p[i].y + k * (border - p[i].x);
            newP.push_back(Point(border, y));
            newP.push_back(p[j]);
        }
        else if(p[i].x >= border && p[j].x < border)
        {
            k = (p[j].y - p[i].y)/(p[j].x - p[i].x);
            double y = p[i].y + k * (border - p[i].x);
            newP.push_back(Point(border, y));
        }
        else if(p[i].x >= border && p[j].x >= border)
        {
            newP.push_back(p[j]);
        }
    }
    newP.push_back(newP[0]);
    return newP;
}

QVector<Point> sutherlandR(double border, QVector<fyz::Point> p)
{
    QVector<Point> newP;
    double k = 0;
    for(int i =0; i<p.size()-1; i++)
    {
        int j = i + 1;
        if(p[i].x > border && p[j].x > border)
            continue;
        else if(p[i].x >= border && p[j].x < border)
        {
            k = (p[j].y - p[i].y)/(p[j].x - p[i].x);
            double y = p[i].y + k * (border - p[i].x);
            newP.push_back(Point(border, y));
            newP.push_back(p[j]);
        }
        else if(p[i].x < border && p[j].x >= border)
        {
            k = (p[j].y - p[i].y)/(p[j].x - p[i].x);
            double y = p[i].y + k * (border - p[i].x);
            newP.push_back(Point(border, y));
        }
        else if(p[i].x <= border && p[j].x <= border)
        {
            newP.push_back(p[j]);
        }
    }
    newP.push_back(newP[0]);
    return newP;
}

QVector<Point> sutherlandT(double border, QVector<fyz::Point> p)
{
    QVector<Point> newP;
    double k = 0;
    for(int i =0; i<p.size()-1; i++)
    {
        int j = i + 1;
        if(p[i].y > border && p[j].y > border)
            continue;
        else if(p[i].y > border && p[j].y <= border)
        {
            k = (p[j].x - p[i].x)/(p[j].y - p[i].y);
            double x = p[i].x + k * (border - p[i].y);
            newP.push_back(Point(x, border));
            newP.push_back(p[j]);
        }
        else if(p[i].y < border && p[j].y >= border)
        {
            k = (p[j].x - p[i].x)/(p[j].y - p[i].y);
            double x = p[i].x + k * (border - p[i].y);
            newP.push_back(Point(x, border));
        }
        else if(p[i].y <= border && p[j].y <= border)
        {
            newP.push_back(p[j]);
        }
    }
    newP.push_back(newP[0]);
    return newP;
}


QVector<Point> sutherlandB(double border, QVector<fyz::Point> p)
{
    QVector<Point> newP;
    double k = 0;
    for(int i =0; i<p.size()-1; i++)
    {
        int j = i + 1;
        if(p[i].y < border && p[j].y < border)
            continue;
        else if(p[i].y <= border && p[j].y > border)
        {
            k = (p[j].x - p[i].x)/(p[j].y - p[i].y);
            double x = p[i].x + k * (border - p[i].y);
            newP.push_back(Point(x, border));
            newP.push_back(p[j]);
        }
        else if(p[i].y >= border && p[j].y < border)
        {
            k = (p[j].x - p[i].x)/(p[j].y - p[i].y);
            double x = p[i].x + k * (border - p[i].y);
            newP.push_back(Point(x, border));
        }
        else if(p[i].y > border && p[j].y > border)
        {
            newP.push_back(p[j]);
        }
    }
    newP.push_back(newP[0]);
    return newP;
}

