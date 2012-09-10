#include "point.h"

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}


void Point::move(double dx, double dy)
{
    x += dx;
    y += dy;
}

double Point::getX()
{
    return x;
}

double Point::getY()
{
    return y;
}

void Point::setX(double x)
{
    this->x = x;
}

void Point::setY(double y)
{
    this->y = y;
}

bool Point::operator==(Point right)
{
    return(this->x == right.x && this->y == right.y);
}

bool Point::operator != ( Point rhs )
{
    return( this->x != rhs.x || this->y != rhs.y );
}
