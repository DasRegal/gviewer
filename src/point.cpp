#include "inc/point.h"

Point::Point(float x, float y, float z)
    : point_(sPoint{x, y, z})
{
}

void Point::SetX(float x)
{
    point_.x = x;
}

void Point::SetY(float y)
{
    point_.y = y;
}

void Point::SetZ(float z)
{
    point_.z = z;
}

float Point::GetX(void)
{
    return point_.x;
}

float Point::GetY(void)
{
    return point_.y;
}

float Point::GetZ(void)
{
    return point_.z;
}
