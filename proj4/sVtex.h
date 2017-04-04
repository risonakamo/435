#ifndef SVTEX_H
#define SVTEX_H

#include <cstdio>

#include "../common/slVector.H"

using namespace std;

class sVtex
{
 public:
  sVtex(SlVector3 &pt);

  void umbrella(sVtex &v1,sVtex &v2);
  void update(float lamb,float dt);

  void printP();
  
  SlVector3* m_pt; //vertex point (x,y,z)
  SlVector3 m_plac; //placian
  float m_m;  //m value
};

#endif
