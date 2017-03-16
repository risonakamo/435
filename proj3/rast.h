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
  void rasterise();

  /* void Mcam_old(iobj* tri); */
  void Mcam(iobj* tri);
  void MP(iobj* tri);
  void Morth(iobj* tri);
  void Mvp(iobj* tri);
  void MZdiv(iobj* tri);

  void boundFill(iobj* tri);
  void calcBoundBox(iobj* tri); //*helper* calc bound box and put in m_boundBox
  void fillP(int x,int y,iobj* tri); //*helper*

  void writeImg();
  
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
  float m_maxLight; //max lights (not really data but goes with m lights)
  iobj* m_adata; //alldata list
  int* m_img; //image data

  /*--M matrix temps--*/
  float m_Mtemp[4];

  /*--calcboundbox stuff--*/
  float m_boundBox[4]; //bounding box [min x,min y,max x,max y]

  /*--fillP temps--*/
  SlVector3 m_baryT[3]; //temp bary vectors
  float m_baryTF[5]; //temp dot products
};

#endif
