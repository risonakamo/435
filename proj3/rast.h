#ifndef rast_h
#define rast_h

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "../common/slVector.H"
#include "rayp.h"
#include "iobj.h"

using namespace std;

class rast
{
 public:
  rast();
  rast(rayp* raypars);

  void calcVec();

  void Mcam(iobj* tri);
  
 private:
  /*--given values--*/
  string m_ofile;
  SlVector3 m_from;
  SlVector3 m_at;
  SlVector3 m_up;
  int m_angle;
  int m_dim;
  float m_hither;
  unsigned char m_background[3];
  float m_backgroundF[3]; //float version for accurate calculation
  unsigned char m_colour[3]; //my windows computer -> G B R colour for some reason (correct in gl)
  float m_colourF[3];
  
  /*--calculated values for mathyness--*/
  int m_psize; //pixel grid size
  SlVector3 m_w;
  SlVector3 m_u;
  SlVector3 m_v;
  float m_d;
  float m_m;

  /*--data arrays--*/
  SlVector3* m_ppointsV; //pixel points vector
                         //size should be psize

  iobj* m_light; //lights list
  float m_maxLight; //max lights
  iobj* m_adata; //alldata list
  
};

#endif
