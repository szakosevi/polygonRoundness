#include "Point.h"
#ifndef ROUNDNESS_H
#define ROUNDNESS_H
class Roundness
{
  private:
    Point *p;
  public:
    Roundness();
    ~Roundness();
    Roundness(const Roundness& theOther);
};

#endif