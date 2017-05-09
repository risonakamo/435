#ifndef PIXL_H
#define PIXL_H

#include "../common/slVector.h"

using namespace std;

class pixl
{
 public:
  pixl();

  pixl(double l,double a,double b,int index);

  SlVector3 m_lab;
  int m_parent;
  int m_index;
  double m_energy;

 private:
  
};

#endif