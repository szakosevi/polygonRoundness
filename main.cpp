#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iterator> 
#include<algorithm>
#include<numeric>
#include"Point.h"
using namespace std;

#define PRINT 0
ostream& operator<<(std::ostream& out, const Point& p)
{  
  return out << p.x << " " << p.y << endl;
}

istream& operator>>(istream& is, Point &p)
{
  is >> p.x >> p.y;
  return is;
}

/*Calculate from points the original radius*/
vector<vector<double>> original_radius_points(vector<vector<Point>> pointData, Point p)
{
  vector<vector<double>> disData;
  double r;
  for (auto &list : pointData)
    {      
        vector<double> dis;
        for (auto &mdata : list)
        {
            r = p.distance(mdata);
            dis.push_back(r);
        }
        disData.push_back(dis);
    }
    return disData;
}

/*Calculate the avarage radius*/
vector<double> avarage_radius(vector<vector<Point>> pointData, Point p)
{
  vector<vector<double>> r_data = original_radius_points(pointData,p);  
  vector<double> rAv; 
  double r;
  for (auto &list : r_data)
    {      
        double r_sum = 0;
        double av = 0;
        for (auto &mdata : list)
        {
            r_sum += mdata;
        }
        av = r_sum/list.size();
        rAv.push_back(av);
    }
    return rAv;
}

/*Search max radius*/
vector<double> max_radius(vector<vector<Point>> pointData, Point p)
{
  vector<vector<double>> rData = original_radius_points(pointData,p); 
  double max;
  vector<double> maxData;
  for (auto &list : rData)
    {      
        max = list[0];
        for (auto &mdata : list)
        {
            if(max<mdata)
              max = mdata;
        }
        maxData.push_back(max);
    }
  return maxData; 
}

/*Search min radius*/
vector<double> min_radius(vector<vector<Point>> pointData, Point p)
{
  vector<vector<double>> rData = original_radius_points(pointData,p); 
  double min;
  vector<double> minData;
  for (auto &list : rData)
    {      
        min = list[0];
        for (auto &mdata : list)
        {
            if(min>mdata)
              min = mdata;
        }
        minData.push_back(min);
    }
  return minData; 
}

/*Calculate the error beetween original radius and estimated radius*/
vector<double> error_calculation(vector<double> rData, vector<double> minMaxData)
{
  vector<double> res;
  double tmp;
  for(int i = 0; i < rData.size(); ++i) 
  {
    for(int j = 0; j < minMaxData.size(); ++j) 
    {
      tmp = rData[i]-minMaxData[j];
    } 
    res.push_back(tmp);  
  }  
  return res; 
}

/*Calculate radius difference in %: (orig radius - estimated radius)/ orig radius*/
vector<double> error_percentage(vector<double> rData, vector<double> minMaxData)
{
  vector<double> res;
  double tmp;
  for(int i = 0; i < rData.size(); ++i) 
  {
    for(int j = 0; j < minMaxData.size(); ++j) 
    {
      if(rData[i] == 0 || minMaxData[j] == 0 )
        tmp = 0;
      else
        {
          tmp =abs(rData[i]-minMaxData[j]);
          tmp = (tmp*100) /rData[i];
        }
    } 
    res.push_back(tmp);  
  }  
  return res; 
}

/*split vector<> and return with error value*/
vector<vector<double>> split(vector<vector<double>> rData, vector<vector<double>> minMaxData)
{
    /*TODO: create an object line by line */
    vector<vector<double>> dummy;
    vector<double> a = rData[0];
    vector<double> b = rData[1];
    vector<double> c = rData[2];
    vector<double> d = rData[3];
    vector<double> e = rData[4];
    vector<double> f = rData[5];
    vector<double> g = rData[6];
    vector<double> h = rData[7];
    vector<double> j = rData[8];
    /*vector<double> hh = r_data[9];
    vector<double> jh = r_data[10];*/

    vector<double> am = minMaxData[0];
    vector<double> bm = minMaxData[1];
    vector<double> cm = minMaxData[2];
    vector<double> dm = minMaxData[3];
    vector<double> em = minMaxData[4];
    vector<double> fm = minMaxData[5];
    vector<double> gm = minMaxData[6];
    vector<double> hm = minMaxData[7];
    vector<double> jm = minMaxData[8];
    /*vector<double> hhm = min_max_Data[9];
    vector<double> jhm = min_max_Data[10];*/
    dummy.push_back(error_percentage(a,am));
    dummy.push_back(error_percentage(b,bm));
    dummy.push_back(error_percentage(c,cm));
    dummy.push_back(error_percentage(d,dm));
    dummy.push_back(error_percentage(e,em));
    dummy.push_back(error_percentage(f,fm));
    dummy.push_back(error_percentage(g,gm));
    dummy.push_back(error_percentage(h,hm));
    dummy.push_back(error_percentage(j,jm));
    /*dummy.push_back(error_percentage(hh,hhm));
    dummy.push_back(error_percentage(jh,jhm));*/
    return dummy;
}

/*Calculate with radius is the closest to the orignal radius*/
vector<double> pass(vector<vector<double>> p)
{
  vector<double> pas;
  
  for (auto &it : p)
  {
    double d=0;
    for(auto &ij : it)
     { 
       d = d + ij;
     }
     d = d/it.size();
     pas.push_back(d);
  }
  return pas;
}

/*Organise data in ascending order*/
vector<size_t> sort_idx(vector<double> v)
{
  vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(),0);
  sort(idx.begin(), idx.end(),[&v](size_t i1, size_t i2){return v[i1] >v[i2];});
  return idx;
}


int main() {
  int idx = 0, idx2;
  vector<vector<Point>> pointData;
  string line;

  ifstream myfile("polygons.in");
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
      pointData.push_back(point);
      idx++;    
    }
    myfile.close();
    cout << "Closed!" << '\n';
  }
  else 
    cout << "Unable to open file";

  Point p00; // (0,0)
  vector<double> sizeData;
  vector<double> r = avarage_radius(pointData,p00);
  vector<vector<double>> rData = original_radius_points(pointData,p00);
  vector<double> maxR = max_radius(pointData,p00);
  vector<double> minR = min_radius(pointData,p00);
  vector<vector<double>> errorMax,errorMin, errorMean, errorResult;
  vector<vector<Point>> p_data_gen;
  vector<Point> ref_gen;
  vector<size_t> stx;

  for (auto &list : rData)
    { 
      errorMax.push_back(error_calculation(maxR, list));
    }

  for (auto &list : rData)
    { 
      errorMin.push_back(error_calculation(minR, list));
    }
  for (auto &list : rData)
    { 
      errorMean.push_back(error_calculation(r, list));
    }
#if PRINT
  cout << "POINTS:" << endl;
  for (auto &list : pointData)
    {
      sizeData.push_back(list.size());
      
        for (auto &mdata : list)
        {
            std::cout<<mdata.getX() << '\t' << mdata.getY() << '\t'<<p00.distance(mdata) << endl;
        }
        cout << endl;
    }
#endif
    errorResult = split(rData, errorMax); // calc error
    vector<double> op = pass(errorResult); // calc similarity
#if PRINT
    for (auto &id : op)
      cout << "Similarity [%]:" << id << '\t' << endl;
#endif
#if PRINT
    for (auto &id : maxR)
      cout << "MAX radius:" << id << '\t' << "" << endl;
    for (auto &id : minR)
      cout << "MIN radius:" << id << '\t' << "" << endl;
    
    for (auto &x : rData)
    {      
        for (auto &mdata : x)
        {
            cout << "Orig Radius:" << mdata << '\t' << "" << endl;
        }
        cout << endl;
    }
    for (auto &list : errorResult)
    {      
        for (auto &mdata : list)
        {
            cout << "Calc Radius:" << mdata << '\t' << "%" << endl;
        }
        cout << endl;
    }
#endif
    cout << "Roundness in ascending order:" << endl;
    for (auto &id : sort_idx(op))
      cout << id << ". (shape) " <<"> ";
  return 0;
}