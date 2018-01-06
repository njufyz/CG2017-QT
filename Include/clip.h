#ifndef CLIP_H
#define CLIP_H
#include"common.h"
#include<QVector>

using fyz::Point;
using fyz::Line;

inline short inside(short code);
inline short reject(short code1,short code2);
inline short accept(short code1,short code2);
inline void swapPoint(Point& a,Point& b);
inline void swapCode(short& a,short& b);
short encode(Point &p,QVector<Point>Rect);

#endif // CLIP_H
