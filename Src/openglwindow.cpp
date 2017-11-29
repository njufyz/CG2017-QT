#include "openglwindow.h"
#include"common.h"
#include<iostream>

#include<QVector>
#include<memory>


using namespace std;

QVector<shared_ptr<Graph>> graph;
shared_ptr<Graph> current(nullptr);

TYPE SELECT = LINE;
STAT STATE = DRAW;

static Point start;
static Point last;

static Point tran_first;
static Point tran_last;

static Point rotate_point;
static Point rotate_first;
static Point rotate_last;
bool rotate_start = false;

static QVector<Point> points_for_polygon;
static bool polygon_start = false;

void mousePress_OnDraw(int x, int y);
void mousePress_OnChoose(int x, int y);
void mousePress_OnTranslate(int x, int y);
void mousePress_OnRotate(int x, int y);

void mouseMove_OnTranslate(int x, int y);
void mouseMove_OnRotate(int x, int y);

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
                      else if(!points_for_polygon.isEmpty())
                                drawControlPoint(points_for_polygon[0]);
                    break;

        default: break;
        }
    }

    else if(STATE == ROTATE)
    {
        drawControlPoint(rotate_point);
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
         case TRANSLATE:    mousePress_OnTranslate(x, y);   break;
         case ROTATE:       mousePress_OnRotate(x, y);      break;
         default:                                           break;
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

    else if(STATE == ROTATE)
        mouseMove_OnRotate(x, y);

    update();

}

void openglwindow::changecolor(QColor &color)
{
   double r = color.redF(), g = color.greenF(), b = color.blueF();
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

void mousePress_OnRotate(int x, int y)
{
   if(rotate_start == false)
   {
       rotate_point = Point(x, y);
       rotate_start = true;
   }
   else
       rotate_first = Point(x, y);
}

double rotate_angle(Point c, Point x1, Point x2)
{
    x1.x -= c.x;
    x1.y -= c.y;
    x2.x -= c.x;
    x2.y -= c.y;

    double angle1 = atan2(x1.y, x1.x);
    double angle2 = atan2(x2.y, x2.x);

    return angle2 - angle1;
}

void mouseMove_OnRotate(int x, int y)
{
    if(current==nullptr)
        return;

    rotate_last = Point(x, y);
    double theta = rotate_angle(rotate_point, rotate_first, rotate_last);
    rotate_first = rotate_last;

    current->rotate(rotate_point.x, rotate_point.y, theta);

}
