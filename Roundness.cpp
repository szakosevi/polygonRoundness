#include "Roundness.h"

Roundness::Roundness(){}
Roundness::~Roundness(){ delete []p;}
Roundness::Roundness(const Roundness& theOther)
{
  p = new Point;
  *p = *theOther.p; 
}