#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWidget>
#include<QMouseEvent>


class openglwindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    openglwindow(QWidget *parent = 0);
    ~openglwindow();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

    void mousePress_OnDraw(int x, int y);
    void mousePress_OnChoose(int x, int y);
    void mousePress_OnTranslate(int x, int y);
    void mousePress_OnRotate(int x, int y);
    void mousePress_OnScale(int x, int y);

    void mouseMove_OnTranslate(int x, int y);
    void mouseMove_OnRotate(int x, int y);
    void mouseMove_OnCursor(int x, int y);
    void mouseMove_OnEdit(int x, int y, int index);


    void mouseRelease_OnDraw(int x, int y);
    void mouseRelease_OnTranslate(int x, int y);
    void mouseRelease_OnRotate(int x, int y);
    void mouseRelease_OnEdit(int x, int y);
    void mouseRelease_OnClip(int x, int y);

    void changecolor(QColor &color);

signals:
    void clickchoose();
    void startscale();
    void getxy(int, int);
    void switchButton();

private slots:
    void clearPoints();

};


#endif // OPENGLWINDOW_H
