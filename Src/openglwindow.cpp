#include "openglwindow.h"
#include"common.h"
#include<iostream>

#include<QVector>
#include<memory>
#include<QDebug>

using namespace std;

QVector<shared_ptr<Graph>> graph;
shared_ptr<Graph> current(nullptr);

TYPE SELECT = LINE;
STAT STATE = DRAW;

static Point start;
static Point last;

static Point tran_first;
static Point tran_last;

static QVector<Point> points_for_polygon;
bool polygon_start = 0;

void mousePress_OnDraw(int x, int y);
void mousePress_OnChoose(int x, int y);
void mousePress_OnTranslate(int x, int y);

void mouseMove_OnTranslate(int x, int y);

void mouseRelease_OnDraw(int x, int y);
void mouseRelease_OnTranslate(int x, int y);

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
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);

    gproperty.point_size = 2;
    gproperty.color = Qt::black;

}

void openglwindow::paintGL()
{
    foreach (auto g, graph)
    {
        g->draw();
    }

    if(STATE == DRAW)
    {
        switch (SELECT)
      {

        case LINE:Line(start, last).draw();  break;

        case CIRCLE:Line(start, last).draw();
                    Circle(start, distance(start, last)).draw(); break;

        case ELLIPSE: Ellipse(Point((start.x + last.x)/2, (start.y +last.y)/2),
                              abs((last.x - start.x)/2),
                              abs((start.y-last.y)/2)).draw(); break;

        case POLYGON: if(points_for_polygon.size() >=2)
                        {
                            for(auto i = points_for_polygon.begin(), j = i + 1; j != points_for_polygon.end(); i++, j++)
                                {
                                    Line(*i, *j).draw();
                                }
                        }
                    break;

        default: break;
        }
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

    start.x = x;
    start.y = y;

    switch(STATE)
    {
         case DRAW :        mousePress_OnDraw(x, y);        break;
         case CHOOSE:       mousePress_OnChoose(x, y);      break;
         case TRANSLATE:  mousePress_OnTranslate(x, y); break;
    }

}


void openglwindow::mouseReleaseEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = HEIGHT - e-> y();

    last.x = x;
    last.y = y;

    if(STATE == DRAW)
   {        
       mouseRelease_OnDraw(x, y);
   }
    if(STATE == TRANSLATE)
    {
        mouseRelease_OnTranslate(x, y);
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

    if(STATE == TRANSLATE)
        mouseMove_OnTranslate(x, y);

    update();

}

void openglwindow::changecolor(QColor &color)
{
   float r = color.redF(), g = color.greenF(), b = color.blueF();
   glColor3f(r, g, b);

}



void mousePress_OnDraw(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    if(SELECT == POLYGON)
    {
        if(polygon_start == 1)
        {
            if((abs(start.x - points_for_polygon[0].x) <= 4 ) && (abs(start.y - points_for_polygon[0].y) <= 4))
            {
                start = points_for_polygon[0];
                points_for_polygon.push_back(start);
                polygon_start = 0;
                shared_ptr<Graph> p(new Polygon(points_for_polygon));
                p->setSelect(false);
                graph.push_back(p);
                points_for_polygon.clear();
            }
            else
                points_for_polygon.push_back(start);
        }
        else //(polygon_start == 0)
        {
            polygon_start = 1;
            points_for_polygon.clear();
            points_for_polygon.push_back(start);
        }

    }
}


void mouseRelease_OnDraw(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    if(SELECT == LINE)
    {
        shared_ptr<Graph> p(new Line(start, last));
        p->setSelect(false);
        graph.push_back(p);
    }


     else if(SELECT == CIRCLE)
    {
        shared_ptr<Graph> p(new Circle(start, distance(start, last)));
        p->setSelect(false);
        graph.push_back(p);
    }

     else if(SELECT == ELLIPSE)
    {
        shared_ptr<Graph> p(new Ellipse(Point((start.x + last.x)/2, (start.y +last.y)/2),
                                        abs((last.x - start.x)/2),
                                        abs((start.y-last.y)/2)));
        p->setSelect(false);
        graph.push_back(p);

     }

}

void mousePress_OnChoose(int x, int y)
{
    foreach (auto g, graph)
    {
        g->setSelect(false);
    }

    for(auto g = graph.end()-1; g >= graph.begin(); g--)
    {
        if((*g)->containsPoint(x, y))
         {
            (*g)->setSelect(true);
            current = (*g);
            return;
         }

    }
    current = nullptr;
}

void mousePress_OnTranslate(int x, int y)
{
    if(current==nullptr)
        return;
    tran_first = Point(x, y);
}

void mouseMove_OnTranslate(int x, int y)
{
    if(current==nullptr)
        return;

    tran_last = Point(x, y);
    x = tran_last.x - tran_first.x;
    y = tran_last.y - tran_first.y;
    tran_first = tran_last;

    current->translate(x, y);
}

void mouseRelease_OnTranslate(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    if(current==nullptr)
        return;
}
