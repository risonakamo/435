/*rast.h - rasteriser
 khang ngo
 cmsc 435 proj3
 uses data from a rayp obj to perform rasterisation*/

#ifndef rast_h
#define rast_h

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "../common/slVector.H"
#include "rayp.h"
#include "iobj.h"
#include "ilit.h"

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
  void Mcam(iobj* tri);
  void MP(iobj* tri);
  void Morth(iobj* tri);
  void Mvp(iobj* tri);
  void MZdiv(iobj* tri);

  /*--boundfill--*/
  void boundFill(iobj* tri); //make bound box, go over pixels, fill in img array
  /*--boundfill helpers--*/
  void calcBoundBox(iobj* tri); //calc bound box and put in m_boundBox
  void fillP(int xpos,int ypos,iobj* tri); /*checks if a 2d point is inside a triangle's
                                      transformed 2d form, fills in img array*/
  void bCord3(double xpos,double ypos,iobj* tri,double& Ra,double& Rb,double& Rr); //bary coordinates calc
  double bCord3F(int v1,int v2,double xpos,double ypos,iobj* tri); //bary coord helper

  /*--light & colour--*/
  void iLight(iobj* tri);
  void objN(iobj* tri);
  void intColour(double triU,double triV,double triR,iobj* tri);

  /*--output--*/
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

  /*--big data arrays--*/
  SlVector3* m_ppointsV; //pixel points vector
                         //size should be psize

  ilit* m_light; //lights list
  double m_maxLight; //max lights (not really data but goes with m lights)
  iobj* m_adata; //alldata list
  double** m_img; //image data [r,g,b,zdep]

  /*--M matrix temps--*/
  double m_Mtemp[4];

  /*--calcboundbox stuff--*/
  double m_boundBox[4]; //bounding box [min x,min y,max x,max y]

  /*--ilight temps--*/
  SlVector3 m_lray;
  SlVector3 m_haf;

  /*--objN--*/
  SlVector3 m_objN[3]; //[0]=obj normal, [1,2]=temps
};

#endif
