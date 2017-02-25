/*rayd2.h - ray data v2
  khang ngo 
  cmsc 435 proj 1
  handles the calulating part after recieving data
  from rayp object*/

#ifndef rayd2_h
#define rayd2_h

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "../common/slVector.H"
#include "rayp.h"
#include "iobj.h"

using namespace std;

class rayd2
{
 public:
  rayd2();
  rayd2(rayp* raypars);
  
  void calcVec(); //calculate vectors and other things too
  void genPpoints(); //generate pixel points
  
  void printPars(); //print out stored values like from, ect.
  void printPpoints(); //print out pixel intersection points
  
  void isect(); //intersect with stuff
  
 private:
  double rSphere(SlVector3 &ray,SlVector3 &from,double* sOrigin); //intRsect sphere

  double rTri(SlVector3 &ray,SlVector3 &from,double* p); //inteRsect Triangle
  double rTri(SlVector3 &ray,SlVector3 &from,SlVector3* p);

  void iLight(SlVector3 &ray,SlVector3 &from,double t,iobj* cobj,int dep); //intersect Light
  void objN(iobj* obj); //object Normal

  iobj* sRay(SlVector3 &ray,SlVector3 &from);
  
  /*--given values--*/
  string m_ofile;
  SlVector3 m_from;
  SlVector3 m_at;
  SlVector3 m_up;
  int m_angle;
  int m_dim;

  unsigned char m_background[3];
  double m_colourF[3];
  unsigned char m_colour[3]; //my windows computer -> G B R colour for some reason (correct in gl)

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
  int m_maxLight; //max lights
  iobj* m_adata; //alldata list
  
  /*--rsphere temps--*/
  double m_sflots[5]; //sphere doubles
  
  /*--rtri temps--*/
  SlVector3 m_rvecs[5]; //tRi vectors
  double m_rflots[3]; //tRi doubles

  /*--isect temps--*/
  SlVector3* m_iRay; 
  SlVector3* m_iFrom;

  /*--ilight temps--*/
  SlVector3 m_ipoint; //intersection point
  SlVector3 m_lray; //light ray (ipoint to light sources)
  SlVector3 m_haf; //light ray and ray half vector
  SlVector3 m_ref;
  SlVector3 m_objN[3]; //object normal [0], others are for function usage

  /*--sray temps--*/
  double m_tValue; //last intersection's best tvalue
};

#endif
