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

#define HEIGHT 500
#define WIDTH 500


extern int SELECT;

extern QVector<std::shared_ptr<Graph>> graph;
enum TYPE{LINE, CIRCLE, ELLIPSE};


#endif

