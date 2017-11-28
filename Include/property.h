#ifndef PROPERTY_H
#define PROPERTY_H
#include<QColor>

struct Property{

    QColor color;
    double  point_size;

    Property() {    color = Qt::black;  point_size = 4.0;}

    Property(QColor &color, double size)
    {
        this->color = color;
        point_size = size;
    }
};

#endif // PROPERTY_H
