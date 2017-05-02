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

 private:
  int m_parent;
  int m_energy;
};

#endif