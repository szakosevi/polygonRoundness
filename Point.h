#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#ifndef POINT_H
#define POINT_H

class Point
{
  private:
    double x,y;
  public:
    Point(double x = 0.0, double y = 0.0);
    Point(const Point &p);
    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
    void setXY(double x, double y);
    double distance(Point theOther);
    friend std::istream& operator>>(std::istream& is, Point& p);
    friend std::ostream& operator<<(std::ostream& out, const Point& p);
};

#endif