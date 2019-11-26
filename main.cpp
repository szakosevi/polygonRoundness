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
vector<vector<double>> original_radius_points(vector<vector<Point>> point_Data, Point p)
{
  vector<vector<double>> dis_Data;
  double r;
  for (auto &list : point_Data)
    {      
        vector<double> dis;
        for (auto &mdata : list)
        {
            r = p.distance(mdata);
            dis.push_back(r);
        }
        dis_Data.push_back(dis);
    }
    return dis_Data;
}

/*Calculate the avarage radius*/
vector<double> avarage_radius(vector<vector<Point>> point_Data, Point p)
{
  vector<vector<double>> r_data = original_radius_points(point_Data,p);  
  vector<double> r_av; 
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
        r_av.push_back(av);
    }
    return r_av;
}

/*Search max radius*/
vector<double> max_radius(vector<vector<Point>> point_Data, Point p)
{
  vector<vector<double>> r_data = original_radius_points(point_Data,p); 
  double max;
  vector<double> max_Data;
  for (auto &list : r_data)
    {      
        max = list[0];
        for (auto &mdata : list)
        {
            if(max<mdata)
              max = mdata;
        }
        max_Data.push_back(max);
    }
  return max_Data; 
}

/*Search min radius*/
vector<double> min_radius(vector<vector<Point>> point_Data, Point p)
{
  vector<vector<double>> r_data = original_radius_points(point_Data,p); 
  double min;
  vector<double> min_Data;
  for (auto &list : r_data)
    {      
        min = list[0];
        for (auto &mdata : list)
        {
            if(min>mdata)
              min = mdata;
        }
        min_Data.push_back(min);
    }
  return min_Data; 
}

/*Calculate the error beetween original radius and estimated radius*/
vector<double> error_calculation(vector<double> r_Data, vector<double> min_max_Data)
{
  vector<double> res;
  double tmp;
  for(int i = 0; i < r_Data.size(); ++i) 
  {
    for(int j = 0; j < min_max_Data.size(); ++j) 
    {
      tmp =r_Data[i]-min_max_Data[j];
    } 
    res.push_back(tmp);  
  }  
  return res; 
}

/*Calculate radius difference in %: (orig radius - estimated radius)/ orig radius*/
vector<double> error_percentage(vector<double> r_Data, vector<double> min_max_Data)
{
  vector<double> res;
  double tmp;
  for(int i = 0; i < r_Data.size(); ++i) 
  {
    for(int j = 0; j < min_max_Data.size(); ++j) 
    {
      if(r_Data[i] == 0 || min_max_Data[j] == 0 )
        tmp = 0;
      else
        {
          tmp =abs(r_Data[i]-min_max_Data[j]);
          tmp = (tmp*100) /r_Data[i];
        }
    } 
    res.push_back(tmp);  
  }  
  return res; 
}

/*split vector<> and return with error value*/
vector<vector<double>> split(vector<vector<double>> r_data, vector<vector<double>> min_max_Data)
{
    vector<vector<double>> dummy;
    vector<double> a = r_data[0];
    vector<double> b = r_data[1];
    vector<double> c = r_data[2];
    vector<double> d = r_data[3];
    vector<double> e = r_data[4];
    vector<double> f = r_data[5];
    vector<double> g = r_data[6];
    vector<double> h = r_data[7];
    vector<double> j = r_data[8];
    /*vector<double> hh = r_data[9];
    vector<double> jh = r_data[10];*/

    vector<double> am = min_max_Data[0];
    vector<double> bm = min_max_Data[1];
    vector<double> cm = min_max_Data[2];
    vector<double> dm = min_max_Data[3];
    vector<double> em = min_max_Data[4];
    vector<double> fm = min_max_Data[5];
    vector<double> gm = min_max_Data[6];
    vector<double> hm = min_max_Data[7];
    vector<double> jm = min_max_Data[8];
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

/*Generate point with help of r radius*/
vector<Point> generate_reference_circle_point(Point p0,double r)
{
  double x = r, y = 0;
  vector<Point> p_data;
  Point tmp;
  tmp.setXY(x+p0.getX(),y+p0.getY());
  p_data.push_back(tmp);
  /*if(r>0)
  { 
    tmp.setXY(x+p0.getX(),-y+p0.getY());
    p_data.push_back(tmp);
    tmp.setXY(y+p0.getX(),x+p0.getY());
    p_data.push_back(tmp);
    tmp.setXY(-y+p0.getX(),x+p0.getY());
    p_data.push_back(tmp);
  }*/
  double P = 1-r;
  while(x>y)
  {
    y++;
    if(P<=0) //inside
      P = P + 2*y + 1;
    else
    {
      x--; // outside
       P = P + 2*y -2*x + 1;
    }
    if(x<y)
      break;

    tmp.setXY(x+p0.getX(),y+p0.getY());
    p_data.push_back(tmp);
    tmp.setXY(-x+p0.getX(),y+p0.getY());
    p_data.push_back(tmp);
    tmp.setXY(x+p0.getX(),-y+p0.getY());
    p_data.push_back(tmp);
    tmp.setXY(-x+p0.getX(),-y+p0.getY());
    p_data.push_back(tmp);

    if(x!=y)
    {
      tmp.setXY(y+p0.getX(),x+p0.getY());
      p_data.push_back(tmp);
      tmp.setXY(-y+p0.getX(),x+p0.getY());
      p_data.push_back(tmp);
      tmp.setXY(y+p0.getX(),-x+p0.getY());
      p_data.push_back(tmp);
      tmp.setXY(-y+p0.getX(),-x+p0.getY());
      p_data.push_back(tmp);
    }

  }
  return p_data;
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
  vector<vector<Point>> point_Data;
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
      point_Data.push_back(point);
      idx++;    
    }
    myfile.close();
    cout << "Closed!" << '\n';
  }
  else 
    cout << "Unable to open file";

  Point p00; // (0,0)
  vector<double> size_Data;
  vector<double> r = avarage_radius(point_Data,p00);
  vector<vector<double>> r_data = original_radius_points(point_Data,p00);
  vector<double> max_r = max_radius(point_Data,p00);
  vector<double> min_r = min_radius(point_Data,p00);
  vector<vector<double>> e_max,e_min, e_mean, e_perc;
  vector<vector<Point>> p_data_gen;
  vector<Point> ref_gen;
  vector<size_t> stx;

  for (auto &list : r_data)
    { 
      e_max.push_back(error_calculation(max_r, list));
    }

  for (auto &list : r_data)
    { 
      e_min.push_back(error_calculation(min_r, list));
    }
  for (auto &list : r_data)
    { 
      e_mean.push_back(error_calculation(r, list));
    }
#if PRINT
  cout << "POINTS:" << endl;
  for (auto &list : point_Data)
    {
      size_Data.push_back(list.size());
      
        for (auto &mdata : list)
        {
            std::cout<<mdata.getX() << '\t' << mdata.getY() << '\t'<<p00.distance(mdata) << endl;
        }
        cout << endl;
    }
#endif
    e_perc = split(r_data, e_max); // calc error
    vector<double> op = pass(e_perc); // calc similarity
#if PRINT
    for (auto &id : op)
      cout << "Similarity [%]:" << id << '\t' << endl;
#endif
#if PRINT
    for (auto &id : max_r)
      cout << "MAX radius:" << id << '\t' << "" << endl;
    for (auto &id : min_r)
      cout << "MIN radius:" << id << '\t' << "" << endl;
    
    for (auto &x : r_data)
    {      
        for (auto &mdata : x)
        {
            cout << "Orig Radius:" << mdata << '\t' << "" << endl;
            //ref_gen =  generate_reference_circle_point(p00,list);
            //p_data_gen.push_back(ref_gen);
        }
        cout << endl;
    }
    for (auto &list : e_perc)
    {      
        for (auto &mdata : list)
        {
            cout << "Calc Radius:" << mdata << '\t' << "%" << endl;
        }
        cout << endl;
    }
#endif
    cout << "Roundness:" << endl;
    for (auto &id : sort_idx(op))
      cout << id << ' ' << ">";
  return 0;
}