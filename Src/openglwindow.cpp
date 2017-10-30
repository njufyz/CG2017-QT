#include "openglwindow.h"
#include"common.h"
#include<iostream>
#include<cmath>
#include<QVector>
#include<memory>

using namespace std;

QVector<shared_ptr<Graph>> graph;

int SELECT = LINE;

static Point start;
static Point last;

openglwindow::openglwindow(QWidget *parent)
    :QOpenGLWidget(parent)
{

}

openglwindow::~openglwindow()
{

}

void openglwindow::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}

void openglwindow::paintGL()
{
    foreach (auto g, graph)
    {
        g->draw();
    }

    switch (SELECT)
    {
        case LINE:Line(start, last).draw();  break;

        case CIRCLE:Line(start, last).draw();
                    Circle(start, distance(start, last)).draw(); break;
    }

}

void openglwindow::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, width, height);
}



void openglwindow::mousePressEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = HEIGHT - e-> y();
    if (Qt ::LeftButton == e->button())
    {
      start.x = x;
      start.y = y;
    }

}

void openglwindow::mouseReleaseEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = HEIGHT - e-> y();
    last.x = x;
    last.y = y;
    if (Qt ::LeftButton == e->button())
    {
        if(SELECT == LINE)
         {
            shared_ptr<Graph> p(new Line(start, last));
            graph.push_back(p);
        }
        else if(SELECT == CIRCLE)
        {
            shared_ptr<Graph> p(new Circle(start, distance(start, last)));
            graph.push_back(p);

        }
    }
    start = last = Point(0, 0);
    update();
}

void openglwindow::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = HEIGHT - e-> y();

    last.x = x;
    last.y = y;

    update();
}

void openglwindow::changecolor(QColor color)
{
   float r = color.redF(), g = color.greenF(), b = color.blueF();
   glColor3f(r, g, b);

}
