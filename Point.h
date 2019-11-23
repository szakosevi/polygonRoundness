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
    //: x(x), y(y) {} 
    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
    void setXY(double x, double y);
    double distance(Point theOther);
    friend std::istream& operator>>(std::istream& is, Point& p);
    //friend std::istream& operator>>(std::istream& is, Point& p);
    friend std::ostream& operator<<(std::ostream& out, const Point& p);
    //friend std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<Point>>& p);

    //friend std::istream& operator>>(std::istream& is, std::vector<Point>& p);
    //friend std::ostream& operator<<(std::ostream& out, const std::vector<Point>& p);
    //friend std::istream& operator>>(std::istream& is,std::vector<Point>& p);
    //friend std::ostream& operator<<(std::ostream& out, std::vector<Point>& p);
};


#endif