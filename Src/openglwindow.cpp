#include "openglwindow.h"
#include"common.h"
#include<iostream>

#include<QVector>
#include<memory>
#include<QDebug>
using namespace std;

QVector<shared_ptr<Graph>> graph;

TYPE SELECT = LINE;
STAT STATE = DRAW;

static Point start;
static Point last;

static QVector<Point> points_for_polygon;
bool polygon_start = 0;

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


//记录起点
void openglwindow::mousePressEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = HEIGHT - e-> y();

    if(STATE == DRAW)
    {
        if (Qt ::LeftButton == e->button())
        {
            start.x = x;
            start.y = y;

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

    }

    else if(STATE == CHOOSE)
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
                break;
             }

        }

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
        if (Qt ::LeftButton == e->button())
      {
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

void openglwindow::changecolor(QColor &color)
{
   float r = color.redF(), g = color.greenF(), b = color.blueF();
   glColor3f(r, g, b);

}
