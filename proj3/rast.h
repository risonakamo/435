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

  void calcVec(); //do math setup
  void rasterise(); //do rasterising pipeline thing stuff
  
 private:
  /*--M functions--*/
  /* void Mcam_old(iobj* tri); */
  void Mcam(iobj* tri);
  void MP(iobj* tri);
  void Morth(iobj* tri);
  void Mvp(iobj* tri);
  void MZdiv(iobj* tri);

  /*--boundfill--*/
  void boundFill(iobj* tri); //make bound box, go over pixels, fill in img array

  /*--boundfill helpers--*/
  void calcBoundBox(iobj* tri); //calc bound box and put in m_boundBox
  void fillP(int x,int y,iobj* tri); /*checks if a 2d point is inside a triangle's
                                      transformed 2d form, fills in img array*/

  void iLight(iobj* tri);
  void objN(iobj* tri);
  void intColour(double& triU,double& triV,iobj* tri);
  
  void writeImg(); //write colours from img array
    
  /*--given values--*/
  string m_ofile;
  SlVector3 m_from;
  SlVector3 m_at;
  SlVector3 m_up;
  int m_angle;
  int m_dim;
  double m_hither;
  unsigned char m_background[3];
  double m_backgroundF[3]; //double version for accurate calculation
  unsigned char m_colour[3]; //my windows computer -> G B R colour for some reason (correct in gl)
  double m_colourF[3];
  
  /*--calculated values for mathyness--*/
  int m_psize; //pixel grid size
  SlVector3 m_w;
  SlVector3 m_u;
  SlVector3 m_v;
  double m_d;
  double m_m;

  /*--data arrays--*/
  SlVector3* m_ppointsV; //pixel points vector
                         //size should be psize

  iobj* m_light; //lights list
  double m_maxLight; //max lights (not really data but goes with m lights)
  iobj* m_adata; //alldata list
  double** m_img; //image data

  /*--M matrix temps--*/
  double m_Mtemp[4];

  /*--calcboundbox stuff--*/
  double m_boundBox[4]; //bounding box [min x,min y,max x,max y]

  /*--fillP temps--*/
  SlVector3 m_baryT[3]; //temp bary vectors
  double m_baryTF[5]; //temp dot products

  /*--ilight temps--*/
  SlVector3 m_lray;
  SlVector3 m_haf;

  /*--objN--*/
  SlVector3 m_objN[3]; //[0]=obj normal, [1,2]=temps
};

#endif