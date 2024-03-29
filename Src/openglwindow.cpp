#include "openglwindow.h"
#include"common.h"
#include<iostream>
#include<QVector>
#include<memory>
#include<algorithm>


using std::shared_ptr;
using fyz::Ellipse;
using fyz::Polygon;
using fyz::Circle;
using fyz::Line;
using fyz::Point;
using fyz::Bezier;

QVector<shared_ptr<Graph>> graph;
shared_ptr<Graph> current(nullptr);
shared_ptr<Graph> tmp(nullptr);


double AngleX = 45.0f;
double AngleY = 315.0f;

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

Point scale_point;
int scale_last = 50;
int scale_cur = 50;


QVector<Point> points_for_polygon;
bool polygon_start = false;

bool locked = false;

int edit_index = -1;

QVector<Point> points_for_bezier;

void ClearSelect();
bool searchCurrent(int x, int y);
double rotate_angle(Point c, Point x1, Point x2);



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
    glPointSize(2.5);
    glLineWidth(2.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    gproperty.point_size = 2.5;
    gproperty.color = Qt::black;

}

void openglwindow::paintGL()
{

    if(SELECT != CUBE)
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

        case ELLIPSE: fyz::Ellipse(Point((start.x + last.x)/2, (start.y +last.y)/2), abs((last.x - start.x)/2),abs((start.y-last.y)/2)).draw();
                     break;

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

        case BEZIER:

            Bezier(points_for_bezier).draw();  break;

        case CUBE:
             showCube();     break;

        default: break;
    }
    }

    else if(STATE == ROTATE)
    {
        drawControlPoint(rotate_point);
    }

    else if(STATE == SCALE)
    {
        drawControlPoint(scale_point);
    }

    else if(STATE == CLIP)
    {
        if(last.x == 0 &&  last.y == 0)
            return;
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glEnable( GL_LINE_STIPPLE);
        glLineStipple( 2.0, 0x0F0F);
        glColor3f(0.0, 0.0, 0.0);

        glBegin(GL_POLYGON);
        glVertex3f(start.x,start.y, 0);
        glVertex3f(last.x, start.y, 0);
        glVertex3f(last.x,last.y, 0);
        glVertex3f(start.x, last.y, 0);
        glEnd();
        update();

        glDisable( GL_LINE_STIPPLE);
        double r = gproperty.color.redF(), g = gproperty.color.greenF(), b = gproperty.color.blueF();
        glColor3f(r, g, b);
        glPointSize(gproperty.point_size);
    }


}

void openglwindow::showCube()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DITHER);
    glShadeModel(GL_SMOOTH);
    float aspect = 1;
    float nRange = 100.0f;

    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-nRange, nRange, -nRange * aspect, nRange * aspect, -nRange, nRange);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    {
        float pos = 50.0;
        glRotatef(AngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(AngleY, 0.0f, 1.0f, 0.0f);

        glBegin(GL_POLYGON);
        glColor3ub(136u, 176u, 75u);
        glVertex3f(pos, pos, -pos);
        glVertex3f(pos, -pos, -pos);
        glVertex3f(-pos, -pos, -pos);
        glVertex3f(-pos, pos, -pos);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(pos, -pos, -pos);
        glVertex3f(pos, -pos, pos);
        glVertex3f(-pos, -pos, pos);
        glVertex3f(-pos, -pos, -pos);
        glEnd();

        glBegin(GL_POLYGON);

        glColor3ub(255u, 235u, 205u);
        glVertex3f(pos, pos, pos);
        glVertex3f(pos, pos, -pos);
        glVertex3f(pos, -pos, -pos);
        glVertex3f(pos, -pos, pos);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(-pos, pos, pos);
        glVertex3f(-pos, pos, -pos);
        glVertex3f(-pos, -pos, -pos);
        glVertex3f(-pos, -pos, pos);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(pos, pos, pos);
        glVertex3f(pos, -pos, pos);
        glVertex3f(-pos, -pos, pos);
        glVertex3f(-pos, pos, pos);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(185u, 205u, 246u);
        glVertex3f(pos, pos, -pos);
        glVertex3f(pos, pos, pos);
        glVertex3f(-pos, pos, pos);
        glVertex3f(-pos, pos, -pos);
        glEnd();
    }
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

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
         case SCALE:        mousePress_OnScale(x, y);       break;
         default:                                           break;
    }
}


void openglwindow::mouseReleaseEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = HEIGHT - e-> y();

    last.x = x;
    last.y = y;

    switch(STATE)
    {
         case DRAW :        mouseRelease_OnDraw(x, y);        break;
         case CHOOSE:                                         break;
         case TRANSLATE:    mouseRelease_OnTranslate(x, y);   break;
         case ROTATE:       mouseRelease_OnRotate(x, y);      break;
         case EDIT:         mouseRelease_OnEdit(x, y);        break;
         case CLIP:         mouseRelease_OnClip(x, y);        break;
         default:                                             break;
    }
    start = last = Point(0, 0);
    update();
}

void openglwindow::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = HEIGHT - e-> y();

    //mouse press
    if(e->buttons() & Qt::LeftButton)
    {
        last.x = x;
        last.y = y;

        switch(STATE)
        {
            case DRAW :
            case CHOOSE:                                         break;
            case TRANSLATE:    mouseMove_OnTranslate(x, y);      break;
            case ROTATE:       mouseMove_OnRotate(x, y);         break;
            case EDIT:         mouseMove_OnEdit(x, y, edit_index);           break;

            default:                                             break;
        }
        update();
    }

    emit getxy(e->x(), HEIGHT - e->y());
    mouseMove_OnCursor(x, y);

}


void openglwindow::changecolor(QColor &color)
{
   double r = color.redF(), g = color.greenF(), b = color.blueF();
   glColor3f(r, g, b);
}

void openglwindow::clearPoints()
{
    if(points_for_bezier.size() > 1)
    {
        shared_ptr<Graph> p(new Bezier(points_for_bezier));
        p->setSelect(false);
        graph.push_back(p);
    }

    points_for_bezier.clear();
    points_for_polygon.clear();
    polygon_start = false;

}

void openglwindow::mousePress_OnDraw(int x, int y)
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
                polygon_start = false;
                shared_ptr<Graph> p(new fyz::Polygon(points_for_polygon));
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

    else if(SELECT == BEZIER)
        points_for_bezier.push_back(start);
}


void openglwindow::mouseRelease_OnDraw(int x, int y)
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
        shared_ptr<Graph> p(new fyz::Ellipse(Point((start.x + last.x)/2, (start.y +last.y)/2),
                                        abs((last.x - start.x)/2),
                                        abs((start.y-last.y)/2)));
        p->setSelect(false);
        graph.push_back(p);

     }

}

void openglwindow::mousePress_OnChoose(int x, int y)
{

    if(current == nullptr)
    {
        if(!searchCurrent(x, y))
            return;
    }
    edit_index = current->containsControlPoint(x, y);
    if(edit_index != -1)
    {
         STATE =  EDIT;
    }
    else if(current->containsPoint(x, y))
    {
        setCursor(Qt::CrossCursor);
        STATE =  TRANSLATE;
        tran_first = Point(x, y);
    }

    else
    {
        ClearSelect();
        setCursor(Qt::ArrowCursor);
        mousePress_OnChoose(x, y);
    }

}

void openglwindow::mousePress_OnTranslate(int x, int y)
{
    if(current==nullptr)
        return;

    tran_first = Point(x, y);
}

void openglwindow::mouseMove_OnTranslate(int x, int y)
{
    if(current==nullptr)
        return;

    tran_last = Point(x, y);
    x = tran_last.x - tran_first.x;
    y = tran_last.y - tran_first.y;
    tran_first = tran_last;

    current->translate(x, y);
}

void openglwindow::mouseRelease_OnTranslate(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    if(current==nullptr)
        return;
    STATE = CHOOSE;
}

void openglwindow::mousePress_OnRotate(int x, int y)
{
   if(rotate_start == false)
   {
       rotate_point = Point(x, y);
       rotate_start = true;
   }
   else
       rotate_first = Point(x, y);
}

void openglwindow::mousePress_OnScale(int x, int y)
{
    scale_point = Point(x, y);

    emit startscale();
}

void openglwindow::mouseMove_OnRotate(int x, int y)
{
    if(current==nullptr)
        return;

    rotate_last = Point(x, y);
    double theta = rotate_angle(rotate_point, rotate_first, rotate_last);
    rotate_first = rotate_last;

    current->rotate(rotate_point.x, rotate_point.y, theta);

}

void openglwindow::mouseMove_OnCursor(int x, int y)
{
    if(STATE == CHOOSE && locked == 0)
    {
        if(tmp != nullptr)
        {
            if(tmp->containsPoint(x, y))
               return;
            else
            {
               tmp->setSelect(false);
               tmp = nullptr;
               setCursor(Qt::ArrowCursor);
            }
        }
        else
        {
            for(auto g = graph.end()-1; g >= graph.begin(); g--)
            {
             if((*g)->containsPoint(x, y))
                {
                 (*g)->setSelect(true);
                 tmp = *g;
                 setCursor(Qt::CrossCursor);
                 break;
                }
            }
        }
         update();
    }

}

void openglwindow::mouseMove_OnEdit(int x, int y, int index)
{
    if(current == nullptr)
        return;
    current->edit(x, y, index);
}

void openglwindow::mouseRelease_OnRotate(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    static int cnt = -1;
    cnt = (cnt + 1) % 2;
    if(cnt == 0)   return;
    if(current==nullptr)
        return;
    STATE = CHOOSE;

    rotate_first = rotate_last = rotate_point = Point(0, 0);
    emit clickchoose();
}

void openglwindow::mouseRelease_OnEdit(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    STATE = CHOOSE;
    edit_index = -1;
}

#include<QDebug>
void openglwindow::mouseRelease_OnClip(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    QVector<Point>rect;
    rect.push_back(start);
    rect.push_back(Point(last.x, start.y));
    rect.push_back(last);
    rect.push_back(Point(start.x, last.y));

    if(current->clip(rect) == false)
    {
       for(auto i = graph.begin(); i<graph.end();i++)
           if(*i == current)
           {
               graph.erase(i);
               break;
           }
        current = nullptr;
    }


    emit clickchoose();
    update();
}


bool searchCurrent(int x, int y)
{
    for(auto g = graph.end()-1; g >= graph.begin(); g--)
    {
        if((*g)->containsPoint(x, y))
         {
            (*g)->setSelect(true);
            locked = true;
            current = (*g);
            return true;
         }

    }
    locked = false;
    return false;
}

void ClearSelect()
{
     foreach (auto g, graph)
     {
         g->setSelect(false);
     }
     current= nullptr;
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
