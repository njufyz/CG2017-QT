#ifndef COMMON_H
#define COMMON_H

#ifdef __APPLE__
#include<glu.h>
#else
#include<Windows.h>
#include<gl/glut.h>
#endif

#include<QVector>
#include<QColor>
#include<memory>
#include<cmath>

#include "Point.h"
#include "property.h"
extern Property gproperty;

#include "graph.h"
#include "Line.h"
#include "Circle.h"
#include "ellipse.h"
#include "polygon.h"
#include "bezier.h"
#include "clip.h"


#define HEIGHT 500
#define WIDTH 500

extern QVector<std::shared_ptr<Graph>> graph;
extern std::shared_ptr<Graph> current;
extern QVector<Point> points_for_polygon;
extern bool polygon_start;
extern bool rotate_start;
extern bool locked;
extern int scale_cur;
extern int scale_last;
extern Point scale_point;

extern double AngleX;
extern double AngleY;

enum TYPE{LINE, CIRCLE, ELLIPSE, POLYGON, BEZIER, CUBE};
enum STAT{DRAW, CHOOSE, TRANSLATE, ROTATE, FILL, SCALE, EDIT, CLIP};

extern TYPE SELECT;
extern STAT STATE;


#define MAX(a,b)        (((a) > (b)) ? (a) : (b))
#define MIN(a,b)        (((a) < (b)) ? (a) : (b))

#endif

