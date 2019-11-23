#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "Roundness.h"
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iterator> 
using namespace std;

ostream& operator<<(std::ostream& out, const Point& p)
{  
  return out << p.x << " " << p.y << endl;
}

istream& operator>>(istream& is, Point &p)
{
  is >> p.x >> p.y;
  return is;
}

string line;
int main() {
  int idx = 0, idx2;
  vector<vector<Point>> point_Data;
  string line;

  ifstream myfile("a.in");
  if (myfile.is_open())
  {
    cout << "Opened!" << endl;
    while(getline(myfile, line))
    {
      istringstream ss(line);
      vector<Point> point;
      Point p0;
      while(ss >> p0)
      {
        point.push_back(p0);
      }
      
      point_Data.push_back(point);
      
      idx++;    
    }
    myfile.close();
    cout << "Closed!" << '\n';
  }
  else 
    cout << "Unable to open file";

  Point p00;
  vector<double> size_Data;
  for (auto &list : point_Data)
    {
      size_Data.push_back(list.size());
      
        for (auto &mdata : list)
        {
            std::cout<<mdata.getX() << '\t' << mdata.getY() << '\t'<<p00.distance(mdata) << endl;
        }
        cout << endl;
    }
    for (auto &id : size_Data)
      cout << "Sizes:" << id << '\t' << "" << endl;
  return 0;
}