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
  float rSphere(SlVector3 &ray,float* sOrigin); //intRsect sphere

  float rTri(SlVector3 &ray,float* p); //inteRsect Triangle
  float rTri(SlVector3 &ray,SlVector3* p);
  
  /*--given values--*/
  string m_ofile;
  SlVector3 m_from;
  SlVector3 m_at;
  SlVector3 m_up;
  int m_angle;
  int m_dim;

  unsigned char m_background[3];
  unsigned char m_colour[3]; //my windows computer -> G B R colour for some reason (correct in gl)

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

  /* flink2<float*>* m_cdata2; //circle data */
  /* flink2<float**>* m_pdata; //polygon data */
  iobj* m_adata;

  /*--rsphere temps--*/
  float m_sflots[5]; //sphere floats
  
  /*--rtri temps--*/
  SlVector3 m_rvecs[5]; //tRi vectors
  float m_rflots[3]; //tRi floats
};

#endif
