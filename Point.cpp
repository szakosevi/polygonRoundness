#include "Point.h"
#include "math.h"
Point::Point(double x, double y)
{
    Point::setXY(x,y);
}
double Point::getX() const
{
  return x;
}
double Point::getY() const
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

void Point::setXY(double x, double y)
{
  this->x = x;
  this->y = y;
}

double Point::distance(Point theOther)
{
  double dx = getX() - theOther.x;
  double dy = getY() - theOther.y;
  return sqrt(dx*dx + dy*dy);
}

Point::Point(const Point &p) 
{
  x = p.x; y = p.y;
} 