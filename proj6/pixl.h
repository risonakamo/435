/*pixl.h - pixel object
  khang ngo
  cmsc 435 proj 6
  sotres data for a single pixel, including seam parent and energy*/

#ifndef PIXL_H
#define PIXL_H

#include "../common/slVector.h"

using namespace std;

class pixl
{
 public:
  pixl();

  pixl(double l,double a,double b,int index);

  SlVector3 m_lab; //lab colours
  int m_parent; //parent index mark
  int m_index; //if removed
  double m_energy; //energy of pixl

 private:
  
};

#endif