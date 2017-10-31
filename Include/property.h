#ifndef PROPERTY_H
#define PROPERTY_H
#include<QColor>

struct Property{

    QColor color;
    float  point_size;

    Property() {    color = Qt::black;  point_size = 4.0;}

    Property(QColor &color, float size)
    {
        this->color = color;
        point_size = size;
    }
};

#endif // PROPERTY_H
