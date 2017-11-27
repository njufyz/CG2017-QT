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

#include "Point.h"
#include "property.h"
extern Property gproperty;

#include "graph.h"
#include "Line.h"
#include "Circle.h"
#include "ellipse.h"
#include "polygon.h"

#define HEIGHT 500
#define WIDTH 500


extern QVector<std::shared_ptr<Graph>> graph;
extern std::shared_ptr<Graph> current;

enum TYPE{LINE, CIRCLE, ELLIPSE, POLYGON};
enum STAT{DRAW, CHOOSE, TRANSLATE, ROTATE};

extern TYPE SELECT;
extern STAT STATE;

#define MAX(a,b)        (((a) > (b)) ? (a) : (b))
#define MIN(a,b)        (((a) < (b)) ? (a) : (b))

#endif

