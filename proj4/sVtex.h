/*sVtex.h - vertex object
  khang ngo
  cmsc 435 proj4
  represents a vertex.  Stores position data, and things relevant to it
  being transformed during smoothing.  It has an s in the from because 
  every other object we've used so far has an s at the front, i don't know why.*/

#ifndef SVTEX_H
#define SVTEX_H

#include <cstdio>

#include "../common/slVector.H"

using namespace std;

class sVtex
{
 public:
  sVtex(SlVector3 &pt);

  void umbrella(sVtex &v1,sVtex &v2); //update plac using umbrella operation
  void update(float lamb,float dt); //update position with lambda and dt and
                                    //calculated laplacian
  void reset(); //reset plac and m

  void printP(); //debug data print

  SlVector3* m_pt; //vertex point (x,y,z)
  SlVector3 m_plac; //placian
  float m_m;  //m value
};

#endif
