#ifndef COMMON_H
#define COMMON_H

#include<glu.h>
#include<QVector>
#include<QColor>
#include<memory>

#include "Point.h"
#include "property.h"
extern Property gproperty;

#include "graph.h"
#include "Line.h"
#include "Circle.h"

#define HEIGHT 500
#define WIDTH 500


extern int SELECT;

extern QVector<std::shared_ptr<Graph>> graph;
enum TYPE{LINE, CIRCLE};


#endif

