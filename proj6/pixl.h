#ifndef PIXL_H
#define PIXL_H

#include "../common/slVector.h"

using namespace std;

class pixl
{
 public:
  pixl();

  pixl(double l,double a,double b);

  SlVector3 m_lab;
  int m_parent;
  double m_energy;

 private:
  
};

#endif