#ifndef CUBE_H
#define CUBE_H
#include <QOpenGLWidget>

namespace fyz {

class MyCube : public QOpenGLWidget
{
    Q_OBJECT

public:
    MyCube(QWidget *parent = 0);
    ~MyCube();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
};
}




#endif // CUBE_H
